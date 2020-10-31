function spawnPopup(populateFunction) {
    var popup = document.getElementById("app-popup-container");
    popup.style.display = "flex";
    if (popup.classList.contains("remove-popup-container"))
    popup.classList.remove("remove-popup-container")
    popup.classList.add("spawn-popup-container");
    popup.onclick = removePopup;
    popup = document.getElementById("app-popup-div");
    populateFunction(popup);
    popup.style.display = "block";
    if (popup.classList.contains("remove-popup-div"))
        popup.classList.remove("remove-popup-div")
    popup.classList.add("spawn-popup-div");
}
function removePopup() {
    var popup = document.getElementById("app-popup-container");
    setTimeout(()=>{document.getElementById("app-popup-container").style.display = "none";}, ANIMATION_NORMAL+100)
    if (popup.classList.contains("spawn-popup-container"))
        popup.classList.remove("spawn-popup-container")
    popup.classList.add("remove-popup-container");
    popup = document.getElementById("app-popup-div");
    while (popup.firstChild)
        popup.removeChild(popup.firstChild);
    if (popup.classList.contains("spawn-popup-div"))
        popup.classList.remove("spawn-popup-div")
    popup.classList.add("remove-popup-div");
}