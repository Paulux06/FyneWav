const { readdirSync, statSync } = require('fs');
const { join, basename, extname } = require('path');
const dirs = (p) => readdirSync(p).filter(f => statSync(join(p, f)).isDirectory());
const files = (p) => readdirSync(p).filter(f => statSync(join(p, f)).isFile());
var explorerElements = [];

function setupExplorer() {
    var explorer = document.getElementById("app-explorer-container");
    var h2 = document.createElement('h2');
    h2.innerHTML = "Dossiers";
    h2.classList.add("folder-title");
    explorer.appendChild(h2);
    var foldersContainer = document.createElement('div');
    foldersContainer.id = "folders-container";
    explorer.appendChild(foldersContainer);
    createFolder('/home/paulux/Documents', foldersContainer);
    toogleFolder(foldersContainer.firstChild, '/home/paulux/Documents');
}

function createFolder(path, parent) {
    var fname = basename(path);
    if (fname == ".") fname = "Dossier courant";
    if (fname.startsWith('.')) return;
    var container = document.createElement('div');
    var topPart = document.createElement('div');
    var folderName = document.createElement('p');
    var bottomPart = document.createElement('div');
    container.classList.add("folder-div");
    topPart.classList.add("folder-top");
    bottomPart.classList.add("folder-bottom");
    folderName.classList.add("folder-name");
    folderName.innerHTML = fname;
    topPart.appendChild(folderName);
    container.appendChild(topPart);
    container.appendChild(bottomPart);
    parent.appendChild(container);
    explorerElements.push({div: container, type: 0, open: false, path: path})
    topPart.onclick = () => {
        toogleFolder(container, path);
    }
}

function createFile(path, parent) {
    var extension = extname(path);
    var container = document.createElement('div');
    var fileName = document.createElement('p');
    container.classList.add("file-div");
    fileName.classList.add("file-name");
    var fname = basename(path);
    fileName.innerHTML = fname;
    if (!(extension == ".mp3" || extension == ".wav" ||
          extension == ".ogg" || extension == ".m4a" ||
          extension == ".flac")) fileName.style.color = "var(--color-primary-1)";
    else fileName.style.color = "var(--color-primary-3)";
    container.appendChild(fileName);
    parent.appendChild(container);
    explorerElements.push({div: container, type: 1, open: false, path: path})
    fileName.onclick = ()=>{
        AUDIO_ENGINE.loadFile(path);
    }
}

function toogleFolder(container, path) {
    var index = getElementIndex(container);
    if (index == null)
        return false;
    explorerElements[index].open = !explorerElements[index].open;
    var bottomPart = getBottomPart(container);
    if (explorerElements[index].open) {
        if (bottomPart == null) return false;
        var foldersfound = dirs(path);
        for(let i=0; i<foldersfound.length; i++) {
            createFolder(path+"/"+foldersfound[i], bottomPart);
        }
        var filesfound = files(path);
        for(let i=0; i<filesfound.length; i++) {
            createFile(path+"/"+filesfound[i], bottomPart);
        }
        getElementTitle(container).classList.add("selected");
    } else {
        clearElements(bottomPart);
        getElementTitle(container).classList.remove("selected");
    }
    return true;
}

function getElementIndex(container) {
    for(let i=0; i< explorerElements.length; i++) {
        if (explorerElements[i].div == container)
            return i;
    }
    return null;
}

function getBottomPart(container) {
    return container.querySelectorAll('.folder-bottom')[0];
}

function getElementTitle(container) {
    if (explorerElements[getElementIndex(container)].type == 0)
        return container.querySelectorAll('.folder-top')[0].firstChild;
    else return container.firstChild;
}

function clearElements(container=document.createElement('div')) {
    for(let i=0; i<container.children.length; i++) {
        var index = getElementIndex(container.children[i]);
        if (index == null) continue;
        explorerElements.splice(index, 1);
        container.children[i].classList.add('remove');
        setTimeout(() => {
            container.removeChild(container.children[0])
        }, ANIMATION_NORMAL-10);
    }
}