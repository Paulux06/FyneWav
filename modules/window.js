const WINDOW_CLOSE_PIC = "./resources/icons/windows/close-white.svg";
const WINDOW_MINIMIZE_PIC = "./resources/icons/windows/minimize-white.svg";
const WINDOW_MAXIMIZE_PIC = "./resources/icons/windows/maximize-white.svg";

function createWindow(id="window#"+windows.length, position={x: 300, y: 300},
                      size={width: 300, height: 300}, name="New window") {
    var prod = document.getElementById("app-content-container");
    var container = document.createElement("div");
    var topframe = document.createElement("div");
    var leftframe = document.createElement("div");
    var rightframe = document.createElement("div");
    var bottomframe = document.createElement("div");
    var cornerLeftFrame = document.createElement("div");
    var cornerRightFrame = document.createElement("div");
    var content = document.createElement("div");
    var windowNameCenterer = document.createElement("div");
    var windowNameText = document.createElement("h2");
    var windowClose = document.createElement("img");
    var windowMaximize = document.createElement("img");
    var windowMinimize = document.createElement("img");
    var windowIcons = document.createElement("div");
    container.classList.add("window-container");
    topframe.classList.add("window-topframe");
    leftframe.classList.add("window-leftframe");
    rightframe.classList.add("window-rightframe");
    bottomframe.classList.add("window-bottomframe");
    cornerLeftFrame.classList.add("window-corner-left");
    cornerRightFrame.classList.add("window-corner-right");
    content.classList.add("window-content-container");
    windowNameCenterer.classList.add("window-name-centerer");
    windowNameText.classList.add("window-name-text");
    windowClose.classList.add("window-close");
    windowMaximize.classList.add("window-maximize");
    windowMinimize.classList.add("window-minimize");
    windowIcons.classList.add("window-icons");
    container.id = id;
    windowNameText.innerHTML = name;
    windowClose.src = WINDOW_CLOSE_PIC;
    windowMaximize.src = WINDOW_MAXIMIZE_PIC;
    windowMinimize.src = WINDOW_MINIMIZE_PIC;
    container.updatePlace = (x, y, w, h) => {
        if (x != null) position.x = x;
        if (y != null) position.y = y;
        if (w != null) size.width = w;
        if (h != null) size.height = h;
    };
    container.setOnTop = () => {
        for (let i = 0; i < windows.length; i++) {
            document.getElementById(windows[i].id).style.zIndex = "0";
        }
        container.style.zIndex = "1";
    };
    container.style.top = position.y.toString()+"px";
    container.style.left = position.x.toString()+"px";
    container.style.height = size.height.toString()+"px";
    container.style.width = size.width.toString()+"px";
    container.getContent = () => {
        return content;
    };
    windowClose.onclick = () => {
        //search index
        var index = 0;
        for (let i = 0; i < windows.length; i++) {
            if (windows[i] == container) {
                index = i; break;
            }
        }
        windows[index].remove();
        windows.splice(index, 1);
    };
    var fullscreen = false;
    windowMaximize.onclick = () => {
        //search index
        var index = 0;
        for (let i = 0; i < windows.length; i++) {
            if (windows[i] == container) {
                index = i; break;
            }
        }
        var cont = windows[index];
        cont.setOnTop();
        cont.style.transition = "top 100ms var(--animation-ease),\
                                 left 100ms var(--animation-ease),\
                                 height 100ms var(--animation-ease),\
                                 width 100ms var(--animation-ease)"
        if (fullscreen) {
            cont.style.top = position.y.toString()+"px";
            cont.style.left = position.x.toString()+"px";
            cont.style.width = size.width.toString()+"px";
            cont.style.height = size.height.toString()+"px";
        }
        else {
            var dims = document.getElementById("app-content-container").getBoundingClientRect();
            cont.style.top = dims.y.toString()+"px";
            cont.style.left = dims.x.toString()+"px";
            cont.style.width = dims.width.toString()+"px";
            cont.style.height = dims.height.toString()+"px";
        }
        fullscreen = !fullscreen;
        setTimeout(() => {cont.style.transition = "none";}, 110);
    };
    windowMinimize.onclick = () => {
        var index = 0;
        for (let i = 0; i < windows.length; i++) {
            if (windows[i] == container) {
                index = i; break;
            }
        }
        var cont = windows[index];
        cont.setOnTop();
        var minheight = parseInt(getComputedStyle(bottomframe).height) +
                        parseInt(getComputedStyle(topframe).height);
        if (getComputedStyle(windows[index]).maxHeight == "none")
            cont.style.maxHeight = minheight.toString()+"px";
        else
            cont.style.maxHeight = "none";
        console.log(getComputedStyle(windows[index]).maxHeight)
    };
    windowNameCenterer.appendChild(windowNameText);
    topframe.appendChild(windowNameCenterer);
    windowIcons.appendChild(windowMinimize);
    windowIcons.appendChild(windowMaximize);
    windowIcons.appendChild(windowClose);
    topframe.appendChild(windowIcons);
    container.appendChild(topframe);
    container.appendChild(leftframe);
    container.appendChild(content);
    container.appendChild(rightframe);
    container.appendChild(cornerLeftFrame);
    container.appendChild(bottomframe);
    container.appendChild(cornerRightFrame);
    prod.appendChild(container);
    windows.push(container);
    return content;
}

function dragWindow(target=new  Element, deltaMouse={x: 0, y: 0}) {
    if (target != null && target.classList.contains("window-topframe")) {
        var el = target.parentElement;
        var style = getComputedStyle(el);
        var newPos = {x: parseInt(style.left)+deltaMouse.x, y: parseInt(style.top)+deltaMouse.y};
        el.updatePlace(newPos.x, newPos.y, null, null);
        el.style.top = newPos.y.toString()+"px";
        el.style.left = newPos.x.toString()+"px";
        return true;
    }
    if (target != null && target.classList.contains("window-bottomframe")) {
        var el = target.parentElement;
        var style = getComputedStyle(el);
        var newHeight = parseInt(style.height)+deltaMouse.y;
        el.updatePlace(null, null, null, newHeight);
        el.style.height = newHeight.toString()+"px";
        return true;
    }
    if (target != null && target.classList.contains("window-rightframe")) {
        var el = target.parentElement;
        var style = getComputedStyle(el);
        var newWidth = parseInt(style.width)+deltaMouse.x;
        el.updatePlace(null, null, newWidth, null)
        el.style.width = newWidth.toString()+"px";
        return true;
    }
    if (target != null && target.classList.contains("window-corner-right")) {
        var el = target.parentElement;
        var style = getComputedStyle(el);
        var newSize = {width: parseInt(style.width)+deltaMouse.x, height: parseInt(style.height)+deltaMouse.y}
        el.updatePlace(null, null, newSize.width, newSize.height);
        el.style.height = newSize.height.toString()+"px";
        el.style.width = newSize.width.toString()+"px";
        return true;
    }
    return false;
}