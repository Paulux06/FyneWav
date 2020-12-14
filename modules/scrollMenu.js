var scrollMenu = {
    /**@type boolean */
    open: false,
    /**@type HTMLElement */
    lastmenu: null,
    content: [{
        /**@type string */
        title: null,
        /**@type Function */
        action: null
    }],
    /**@type HTMLElement */
    container: null
};
const SCROLLMENU_CLOSEDISTANCE = 60;

function setupScrollMenu() {
    scrollMenu.container = document.getElementById("app-scroll-menu-container");
    var menuFiles = document.getElementById("menu-files");
    var menuPlugins = document.getElementById("menu-plugins");
    var menuOptions = document.getElementById("menu-options");
    menuFiles.onclick = () => { setScrollMenu(
        [{title: "Nouveau", action:()=>{console.log("nouveau")}},
         {title: "Ouvrir", action:()=>{SERVER.openSave("/", file => {openSave(file);});}},
         {title: "Sauvegarder", action:()=>{SERVER.saveProject("/", file => {saveProject(file);})}},
         {title: "Quitter", action:()=>{WRAPPER.disable(); WINDOW.close();}}],
        menuFiles);
    }
    menuPlugins.onclick = () => { setScrollMenu(
        [{title: "Mes VSTs", action:()=>{spawnPopup(spawnStore, [store.VSTS]);}},
         {title: "Mes effets", action:()=>{spawnPopup(spawnStore, [store.EFFECTS]);}},
         {title: "Mes plugins", action:()=>{spawnPopup(spawnStore, [store.PLUGINS]);}},
         {title: "Magasin", action:()=>{spawnPopup(spawnStore, [store.SHOP]);}}],
        menuPlugins);
    }
    menuOptions.onclick = () => { setScrollMenu(
        [{title:"Options audios", action:()=>{spawnPopup(spawnSettings, [settings.AUDIO]);}},
         {title:"Options vidéos", action:()=>{spawnPopup(spawnSettings, [settings.VIDEO]);}},
         {title:"Options de fichiers", action:()=>{spawnPopup(spawnSettings, [settings.FILE]);}},
         {title:"Options générales", action:()=>{spawnPopup(spawnSettings, [settings.GENERAL]);}}],
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
        openScrollMenu();
    }
    setScrollMenuContent(content);
    var bounds = node.getBoundingClientRect();
    setScrollMenuPos(bounds.x, bounds.y + bounds.height + 5);
}
function setScrollMenuPos(x=0, y=0) {
    let pos = document.getElementById("app-scroll-menu-container").getBoundingClientRect();
    let distance = Math.sqrt( (pos.x-x)**2 + (pos.y-y)**2 );
    if (distance > 100) {
        let last = scrollMenu.container.style.transition;
        scrollMenu.container.style.transition = 'transform var(--animation-quick) var(--animation-ease)';
        scrollMenu.container.style.top = y.toString() + "px";
        scrollMenu.container.style.left = x.toString() + "px";
        setTimeout(()=>{scrollMenu.container.style.transition = last;}, 500);
        return
    }
    scrollMenu.container.style.top = y.toString() + "px";
    scrollMenu.container.style.left = x.toString() + "px";
    return;
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
    scrollMenu.open = true;
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