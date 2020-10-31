var scrollMenu = { open: false, lastmenu: null, content: [], container: null};
const SCROLLMENU_CLOSEDISTANCE = 60;

function setupScrollMenu() {
    scrollMenu.container = document.getElementById("app-scroll-menu-container");
    var menuFiles = document.getElementById("menu-files");
    var menuPlugins = document.getElementById("menu-plugins");
    var menuOptions = document.getElementById("menu-options");
    menuFiles.onclick = () => { setScrollMenu(
        [{title: "Nouveau", action:()=>{console.log("nouveau")}},
         {title: "Ouvrir", action:()=>{console.log("ouvrir")}},
         {title: "Sauvegarder", action:()=>{console.log("sauvegarder")}},
         {title: "Quitter", action:()=>{AUDIO_ENGINE.disable(); WINDOW.close();}}],
        menuFiles);
    }
    menuPlugins.onclick = () => { setScrollMenu(
        [{title: "Mes VST", action:()=>{console.log("mes VST")}},
         {title: "Mes effets", action:()=>{console.log("mes effets")}},
         {title: "Magasin", action:()=>{console.log("magasin")}}],
        menuPlugins);
    }
    menuOptions.onclick = () => { setScrollMenu(
        [{title:"Options audios", action:()=>{console.log("options audios")}},
         {title:"Options vidéos", action:()=>{console.log("options videos")}},
         {title:"Options de fichiers", action:()=>{console.log("options fichiers")}},
         {title:"Options générales", action:()=>{spawnPopup(spawnOptions);}}],
        menuOptions);
    }
}

function setScrollMenu(content, node) {
    if (node == scrollMenu.lastmenu) {
        scrollMenu.open = !scrollMenu.open;
        if (scrollMenu.open) openScrollMenu();
        else closeScrollMenu();
    } else {
        scrollMenu.lastmenu = node; scrollMenu.content = content;
        setScrollMenuContent(content);
        openScrollMenu(); scrollMenu.open = true;
    }
    var bounds = node.getBoundingClientRect();
    setScrollMenuPos(bounds.x, bounds.y + bounds.height + 5);
}
function setScrollMenuPos(x = 0, y = 0) {
    scrollMenu.container.style.top = y.toString() + "px";
    scrollMenu.container.style.left = x.toString() + "px";
}
function setScrollMenuContent(content = []) {
    clearScrollMenu()
    var p = document.createElement("p");
    for (let i = 0; i < content.length; i++) {
        p = document.createElement('p');
        p.id = "app-scroll-menu-option";
        p.innerHTML = content[i].title;
        p.onclick = content[i].action;
        scrollMenu.container.appendChild(p)
    }
}
function clearScrollMenu() {
    while (scrollMenu.container.firstChild)
        scrollMenu.container.removeChild(scrollMenu.container.firstChild);
}
function openScrollMenu() {
    scrollMenu.container.style.transform = "scale(1, 1)";
    setTimeout(keepScrollMenuOpen, 500);
}
function closeScrollMenu() { scrollMenu.container.style.transform = "scale(1, 0)"; }
function keepScrollMenuOpen() {
    var pos = document.getElementById("app-scroll-menu-container").getBoundingClientRect();
    if (!scrollMenu.open) return;
    if (mouse.x < pos.x-SCROLLMENU_CLOSEDISTANCE ||
        mouse.y < pos.y-SCROLLMENU_CLOSEDISTANCE ||
        mouse.x > pos.x+pos.width+SCROLLMENU_CLOSEDISTANCE ||
        mouse.y > pos.y+pos.height+SCROLLMENU_CLOSEDISTANCE) {
        closeScrollMenu();
        scrollMenu.open = false;
        return;
    };
    setTimeout(keepScrollMenuOpen, 100);
}