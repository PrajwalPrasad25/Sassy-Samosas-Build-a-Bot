document.getElementById("uploadForm").onsubmit = async function(event) {
    event.preventDefault();
    
    let fileInput = document.getElementById("meshFile");
    let formData = new FormData();
    formData.append("meshFile", fileInput.files[0]);

    let statusText = document.getElementById("status");
    let progressText = document.getElementById("progressText");
    let progressCircle = document.querySelector(".circular-progress");
    let loadingContainer = document.getElementById("loadingContainer");
    let samosa = document.getElementById("samosaSpinner");
    let robotContainer = document.getElementById("robotContainer");

    // Show loading elements
    statusText.innerText = "Uploading...";
    loadingContainer.style.display = "block";
    robotContainer.style.display = "block";

    let progress = 0;

    // Fake loading animation
    let interval = setInterval(() => {
        if (progress < 99) {
            progress += Math.random() * 10; // Increase randomly between 0-10%
            progress = Math.min(progress, 99); // Stop at 99% until response

            progressText.innerText = Math.floor(progress) + "%";
            progressCircle.style.background = `conic-gradient(#E69C24 ${progress * 3.6}deg, #444 ${progress * 3.6}deg)`;
        }
    }, 300);

    let response = await fetch("/upload", {
        method: "POST",
        body: formData
    });

    let result = await response.json();
    
    clearInterval(interval); // Stop animation

    if (result.message) {
        statusText.innerText = "Visualizer started!";
        progressText.innerText = "100%";
        progressCircle.style.background = `conic-gradient(#E69C24 360deg, #444 360deg)`;
    } else {
        statusText.innerText = result.error;
    }

    // Hide spinner after loading
    setTimeout(() => {
        loadingContainer.style.display = "none";
        robotContainer.style.display = "none";
    }, 1500);
};
