let settings = {
    AUDIO: 1,
    VIDEO: 2,
    FILE: 3,
    GENERAL: 4,
    /**@type HTMLElement*/
    container: null,
    data: null
}
/** Creates the main option window
  * @param {HTMLElement} container */
function spawnSettings(container, args) {
    if (store.container == null) { // create the settings interface
        var title = document.createElement('h1');
        title.innerHTML = "Options";
        title.id = "app-popup-title";

        container.appendChild(title);
    }
    switch (args[0]) {
        case settings.GENERAL:
            
            break;
        case settings.AUDIO:
            
            break;
        case settings.VIDEO:
            
            break;
        case settings.FILE:
            
            break;
    
        default:
            break;
    }
}

function setupSettings() {
    try {settings.data = JSON.parse( fs.readFileSync("./resources/settings.json", "utf-8") );}
    catch (e) {
        console.log(e);
        var dims = document.getElementById("app-content-container").getBoundingClientRect();
        settings.data = {
            version: 0.1,
            audioEngine: {
                sampleRate: 44100,
                channels: 2,
                audioOutIndex: null,
                audioInIndex: null
            },
            interface: {
                windows: [ {
                        id: "app-folders", position: {x: 0, y: dims.top},
                        size: {width: dims.width*0.2, height: dims.height-dims.top},
                        name: "Dossiers"
                    }, {
                        id: "app-arranger", position: {x: dims.width*0.2, y: dims.top},
                        size: {width: dims.width*0.8, height: dims.height*0.6},
                        name: "Arranger"
                    }, {
                        id: "app-instrs", position: {x: dims.width*0.2, y: dims.height*0.6+dims.top},
                        size: {width: dims.width*0.3, height: dims.height*0.4-dims.top},
                        name: "Instruments"
                    }, {
                        id: "app-rack", position: {x: dims.width*0.5, y: dims.height*0.6+dims.top},
                        size: {width: dims.width*0.5, height: dims.height*0.4-dims.top},
                        name: "Channel rack"
                    }
                ]
            }
        };
        fs.writeFileSync("./resources/settings.json", JSON.stringify(settings.data));
    }
}