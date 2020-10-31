var mouse = {x: 0, y: 0};
var deltaMouse = {x: 0, y: 0};
var lastMouse = {x: 0, y: 0};
var drag = false;
var ANIMATION_QUICK=0, ANIMATION_NORMAL=0, ANIMATION_SLOW=0;
var ELECTRON = require('electron');
var AUDIO_ENGINE = ELECTRON.remote.require("./build/Release/engine");
var WINDOW = ELECTRON.remote.require("./main.js").getWin();
var dancerMode = false;

function stopAudio() {
    AUDIO_ENGINE.stopFile();
}

window.onload = () => {
    startAudioEngine();
    dancerMove();
    var computedStyle = getComputedStyle(document.documentElement);
    ANIMATION_QUICK = parseInt(computedStyle.getPropertyValue("--animation-quick"));
    ANIMATION_NORMAL = parseInt(computedStyle.getPropertyValue("--animation-normal"));
    ANIMATION_SLOW = parseInt(computedStyle.getPropertyValue("--animation-slow"));
    setupScrollMenu();
    setupExplorer();
    setupSequenceur();
    //const { remote } = require("electron");
    //const mainProcess = remote.require('./main.js');
    //mainProcess.func()
}

function startAudioEngine() {
    if(AUDIO_ENGINE.getEngineEnabled()) return;
    if(AUDIO_ENGINE.enable()==0) console.log("audio engine enabled.");
    else {
        console.log("audio engine failed to enable, retrying in 2s.");
        setTimeout(startAudioEngine, 2000);
    }
}

function dancerMove() {
    document.body.style.transform =
        "scale("+(AUDIO_ENGINE.getSoundLevel()/10+1).toString()+")";
    if (dancerMode) setTimeout(dancerMove, 33);
    else document.body.style.transform = "none";
}

window.addEventListener("wheel", (event) => {
    var target = document.elementFromPoint(mouse.x, mouse.y);
    if (target.id == "app-sequenceur-cursor-band" || target.id == "app-sequenceur-cursor-div")
        changePlayerProgressBy(event.deltaX);
})

window.addEventListener("mousemove", (event) => {
    deltaMouse = {x: event.x -mouse.x, y: event.y - mouse.y};
    mouse.x = event.x; mouse.y = event.y;
    if (drag) {

    }
})

window.addEventListener("mousedown", (event)=> {
    lastMouse = {x: mouse.x, y: mouse.y}
    var target = document.elementFromPoint(mouse.x, mouse.y)
    drag = true;
})
window.addEventListener("mouseup", (event)=> {
    drag = false;
})