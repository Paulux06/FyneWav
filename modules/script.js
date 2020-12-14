var mouse = { x: 0, y: 0 };
var deltaMouse = { x: 0, y: 0 };
var lastMouse = { x: 0, y: 0 };
var drag = false;
var ANIMATION_QUICK = 0, ANIMATION_NORMAL = 0, ANIMATION_SLOW = 0;
const ELECTRON = require("electron");
const WRAPPER = ELECTRON.remote.require("./build/Release/engine");
const SERVER = ELECTRON.remote.require("./main.js");
const WINDOW = SERVER.getWin();
const fs = require("fs");
var bpm = 0.5;
var target = null;
/**@type HTMLElement */
var soundLevelCursor;
/**@type HTMLElement */
var procLevelCursor;
var soundLevel = 0;
var procLevel = 0;
var windows = [];
/**@type CSSStyleDeclaration*/
var globalStyle;

windows.get = (id="") => {
    var value = null;
    for (let i = 0; i < windows.length; i++) {
        const el = windows[i];
        if (el.id == id) {
            value = el;
            break;
        }
    }
    return value;
};

function stopAudio() {
    WRAPPER.stopFile();
}

window.onload = () => {
    setupSettings();
    startAudioEngine();
    soundLevelCursor = document.getElementById("app-soundLevel-div");
    procLevelCursor = document.getElementById("app-procLevel-div");
    globalStyle = getComputedStyle(document.documentElement);
    ANIMATION_QUICK = parseInt(globalStyle.getPropertyValue("--animation-quick"));
    ANIMATION_NORMAL = parseInt(globalStyle.getPropertyValue("--animation-normal"));
    ANIMATION_SLOW = parseInt(globalStyle.getPropertyValue("--animation-slow"));
    setupScrollMenu();
    //const { remote } = require("electron");
    //const mainProcess = remote.require('./main.js');
    //mainProcess.func()
    playIntro();
    refreshLevels()
    for (let w = 0; w < settings.data.interface.windows.length; w++) {
        const el = settings.data.interface.windows[w];
        createWindow(el.id, el.position, el.size, el.name);
    }
    setupExplorer(windows.get("app-folders").getContent());
}

function startAudioEngine() {
    if (WRAPPER.getEngineEnabled()) return;
    if (WRAPPER.enable() == 0) console.log("audio engine enabled.");
    else {
        console.log("audio engine failed to enable, retrying in 2s.");
        setTimeout(startAudioEngine, 2000);
    }
}

function refreshLevels() {
    soundLevel += (WRAPPER.getSoundLevel() - soundLevel) / 2;
    soundLevelCursor.style.height = soundLevel.toString()+"%";
    procLevel += (WRAPPER.getProcLevel() - procLevel) / 8;
    procLevelCursor.style.height = procLevel.toString()+"%";
    setTimeout(refreshLevels, 66);
}

window.addEventListener("wheel", (event) => {
    var target = document.elementFromPoint(mouse.x, mouse.y);
    if (target.id == "app-sequenceur-cursor-band" || target.id == "app-sequenceur-cursor-div")
        changePlayerProgressBy(event.deltaX);
})

window.addEventListener("mousemove", (event) => {
    deltaMouse = { x: event.x - mouse.x, y: event.y - mouse.y };
    mouse.x = event.x; mouse.y = event.y;
    if (drag) {
        dragWindow(target, deltaMouse);
    }
    target = document.elementFromPoint(mouse.x, mouse.y);
})

window.addEventListener("mousedown", (event) => {
    lastMouse = { x: mouse.x, y: mouse.y }
    var target = document.elementFromPoint(mouse.x, mouse.y)
    if (target != null) {
        if (target.id == "app-popup-container") removePopup();
        if (target.parentElement.classList.contains("window-container"))
            target.parentElement.setOnTop();
    }
    drag = true;
})
window.addEventListener("mouseup", (event) => {
    lastMouse = { x: mouse.x, y: mouse.y }
    mouse = lastMouse;
    drag = false;
})

function playIntro() {
    WRAPPER.noteOn(592, 5000, 2205, 0);
    setTimeout(() => { WRAPPER.noteOn(658, 10000, 4410, 0) }, 50);
}

function playMusic() {
    WRAPPER.noteOn(246, 65535, 44100 * bpm, -32767);
    WRAPPER.noteOn(329, 65535, 44100 * bpm, -32767);
    WRAPPER.noteOn(392, 65535, 44100 * bpm, -32767);
    WRAPPER.noteOn(494, 65535, 44100 * bpm, -32767);
    WRAPPER.noteOn(659, 65535, 44100 * bpm, -32767);
    WRAPPER.noteOn(784, 65535, 44100 * bpm, -32767);
    setTimeout(() => {
        WRAPPER.noteOn(494, 65535, 44100 * bpm, 0);
    }, 1000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(246, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(311, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(370, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(494, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(622, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(740, 65535, 44100 * bpm, 32767);
    }, 2000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(494, 65535, 22050 * bpm, 0);
    }, 3000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(370, 65535, 22050 * bpm, 0);
    }, 3500 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(246, 65535, 44100 * bpm, -32767);
        WRAPPER.noteOn(329, 65535, 44100 * bpm, -32767);
        WRAPPER.noteOn(392, 65535, 44100 * bpm, -32767);
        WRAPPER.noteOn(494, 65535, 44100 * bpm, -32767);
        WRAPPER.noteOn(659, 65535, 44100 * bpm, -32767);
        WRAPPER.noteOn(784, 65535, 44100 * bpm, -32767);
    }, 4000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(494, 65535, 44100 * bpm, 0);
    }, 5000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(293, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(370, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(440, 65535, 44150 * bpm, 32767);
        WRAPPER.noteOn(587, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(740, 65535, 44100 * bpm, 32767);
        WRAPPER.noteOn(880, 65535, 44100 * bpm, 32767);
    }, 6000 * bpm);
    setTimeout(() => {
        WRAPPER.noteOn(370, 65535, 44100 * bpm, 32767);
    }, 7000 * bpm);
}