const { DownloadItem } = require('electron');

let store = {
    SHOP: 1,
    MY_EFFECTS: 2,
    MY_VSTS: 3,
    MY_PLUGINS: 4,
    /**@type HTMLElement*/
    container: null
}
/** Creates the main store window
  * @param {HTMLElement} container */
function spawnStore(container, args) {
    if (store.container == null) { // create the store interface
        var title = document.createElement('h1');
        title.innerHTML = "Magasin";
        title.id = "app-popup-title";

        let scrollDiv = document.createElement("div");
        scrollDiv.classList.add("app-store-scroll-list");
        
        let content = JSON.parse(require('fs').readFileSync("./resources/store.json", 'utf-8'));
        content.forEach(el => {
            let pluginBox = document.createElement("div");
            let iconDiv = document.createElement("div");
            let textDiv = document.createElement("div");
            let titleDiv = document.createElement("div");
            let descDiv = document.createElement("div");
            let typeDiv = document.createElement("div");
            let downloadDiv = document.createElement("div");
            let thumbnail = document.createElement("img");
            let titleText = document.createElement("h2");
            let descText = document.createElement("p");
            let downloadText = document.createElement("p");
            let typeText = document.createElement("p");
            
            pluginBox.classList.add("app-store-plugin-box");
            iconDiv.classList.add("app-store-icon-div");
            textDiv.classList.add("app-store-text-div");
            titleDiv.classList.add("app-store-title-div");
            descDiv.classList.add("app-store-desc-div");
            typeDiv.classList.add("app-store-type-div");
            downloadDiv.classList.add("app-store-download-div");
            thumbnail.classList.add("app-store-icon");
            titleText.classList.add("app-store-title-text");
            descText.classList.add("app-store-desc-text");
            downloadText.classList.add("app-store-download-text");
            typeText.classList.add("app-store-type-text");

            thumbnail.src = el.thumbnail;
            titleText.innerHTML = el.title;
            descText.innerHTML = el.description;
            downloadText.innerHTML = "Télécharger";
            typeText.innerHTML = el.type;

            downloadDiv.appendChild(downloadText);
            typeDiv.appendChild(typeText);
            descDiv.appendChild(descText);
            titleDiv.appendChild(titleText);
            titleDiv.appendChild(downloadDiv);
            textDiv.appendChild(titleDiv);
            textDiv.appendChild(descDiv);
            textDiv.appendChild(typeDiv);
            iconDiv.appendChild(thumbnail);
            pluginBox.appendChild(iconDiv);
            pluginBox.appendChild(textDiv);
            scrollDiv.appendChild(pluginBox);
        });

        container.appendChild(title);
        container.appendChild(scrollDiv);
    }
    switch (args[0]) {
        case store.SHOP:
            
            break;
        case store.MY_VSTS:
            
            break;
        case store.MY_PLUGINS:
            
            break;
        case store.MY_EFFECTS:
            
            break;
    
        default:
            break;
    }
}