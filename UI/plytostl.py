import open3d as o3d
import numpy as np

def ply_to_stl(input_ply, output_stl):
    # Load the PLY file
    pcd = o3d.io.read_point_cloud(input_ply)

    if pcd.is_empty():
        print("Error: The PLY file is empty or invalid.")
        return

    # Estimate normals (required for surface reconstruction)
    pcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=2.0, max_nn=50))

    # Poisson surface reconstruction
    mesh, densities = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(pcd, depth=9)
    
    # Remove low-density vertices (denoising)
    density_threshold = np.percentile(densities, 5)  # Adjust threshold as needed
    mesh.remove_vertices_by_mask(densities < density_threshold)

    # Ensure the mesh is watertight
    mesh.remove_unreferenced_vertices()
    mesh.remove_degenerate_triangles()
    mesh.remove_non_manifold_edges()

    # Compute normals (Fix Open3D warning)
    mesh.compute_vertex_normals()

    # Save as STL
    o3d.io.write_triangle_mesh(output_stl, mesh)
    print(f"Conversion complete: {output_stl}")

# Example usage
ply_to_stl("./uploads/Axle.ply", "axlet.stl")
