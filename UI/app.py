from flask import Flask, render_template, request, jsonify
import open3d as o3d
import numpy as np
import os
import threading
from werkzeug.utils import secure_filename

app = Flask(__name__)

UPLOAD_FOLDER = "uploads"
ALLOWED_EXTENSIONS = {"obj", "stl", "ply", "txt"}
app.config["UPLOAD_FOLDER"] = UPLOAD_FOLDER

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

visualizer_thread = None

def allowed_file(filename):
    return "." in filename and filename.rsplit(".", 1)[1].lower() in ALLOWED_EXTENSIONS

def refine_point_cloud(point_cloud):
    """Removes noise and normalizes the point cloud."""
    print("Refining point cloud (Outlier removal + Normalization)...")

    # Remove noise
    cl, ind = point_cloud.remove_statistical_outlier(nb_neighbors=50, std_ratio=1.0)
    point_cloud = point_cloud.select_by_index(ind)

    # Voxel Downsampling for uniformity
    point_cloud = point_cloud.voxel_down_sample(voxel_size=0.3)

    print(f"Refined point cloud contains {len(point_cloud.points)} points.")
    return point_cloud

def enforce_rectangular_shape(mesh):
    """Generates an Oriented Bounding Box (OBB) for visualization."""
    print("Generating bounding box for reference...")

    obb = mesh.get_oriented_bounding_box()
    obb.color = (0.5, 0.5, 0.5)  # Grey color
    return obb  # Just return the bounding box for visualization

def reconstruct_mesh(point_cloud):
    """Reconstructs a smooth, solid mesh with Poisson Surface Reconstruction."""
    print(f"Running mesh reconstruction on {len(point_cloud.points)} points...")

    # Estimate normals
    point_cloud.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=2.0, max_nn=50))

    # Poisson Surface Reconstruction
    mesh, densities = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(point_cloud, depth=10, linear_fit=True)

    # Remove noise based on density
    density_threshold = np.percentile(densities, 5)
    mesh.remove_vertices_by_mask(densities < density_threshold)

    # Ensure mesh is watertight
    mesh.remove_unreferenced_vertices()
    mesh.remove_degenerate_triangles()
    mesh.remove_non_manifold_edges()

    # Smooth the mesh (Laplacian)
    mesh = mesh.filter_smooth_laplacian(number_of_iterations=15)

    # Apply uniform grey color
    mesh.paint_uniform_color([0.5, 0.5, 0.5])

    print(f"Final mesh has {len(mesh.vertices)} vertices and {len(mesh.triangles)} triangles.")
    return mesh

def process_uploaded_file(file_path):
    """Loads file, refines point cloud, and generates a structured solid mesh."""
    print(f"Processing file: {file_path}")

    point_cloud = o3d.io.read_point_cloud(file_path)
    if point_cloud.is_empty():
        print("Error: No valid point cloud data found.")
        return None, None

    point_cloud = refine_point_cloud(point_cloud)
    mesh = reconstruct_mesh(point_cloud)
    obb = enforce_rectangular_shape(mesh)  # Generate bounding box

    return mesh, obb  # Return both mesh and bounding box

def start_visualizer(mesh, obb):
    """Displays the structured mesh and bounding box."""
    print("Launching 3D Viewer...")
    o3d.visualization.draw_geometries([mesh, obb], window_name="Samsung Charger - Solid 3D Viewer")

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/upload", methods=["POST"])
def upload_file():
    if "meshFile" not in request.files:
        return jsonify({"error": "No file provided"}), 400

    file = request.files["meshFile"]
    if file.filename == "":
        return jsonify({"error": "No selected file"}), 400

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file_path = os.path.join(app.config["UPLOAD_FOLDER"], filename)
        file.save(file_path)

        mesh, obb = process_uploaded_file(file_path)
        if mesh is None:
            return jsonify({"error": "Mesh reconstruction failed."}), 400

        global visualizer_thread
        if visualizer_thread and visualizer_thread.is_alive():
            visualizer_thread.join()

        visualizer_thread = threading.Thread(target=start_visualizer, args=(mesh, obb))
        visualizer_thread.start()

        return jsonify({"message": "Solid Mesh Generated & Viewer Started", "file": filename}), 200
    else:
        return jsonify({"error": "Invalid file format. Only .obj, .stl, .ply, .txt allowed."}), 400

if __name__ == "__main__":
    app.run(debug=True)
