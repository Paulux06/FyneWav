const fs = require("fs");
const electron = require('electron');

function createWindow () {
    const {width, height} = electron.screen.getPrimaryDisplay().workAreaSize;
    const win = new electron.BrowserWindow({
        width: width,
        height: height,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: true
        },
        icon: "./resources/icons/logo/icon.png"
    });
    //win.setMenu(null);
    win.setMenuBarVisibility(false);
    win.loadFile('./index.html');
    exports.getWin = ()=>{return win;};
    exports.openSave = (path, callback)=>{
        const options = {
            title: 'Ouvrir un projet',
            defaultPath: path,
            buttonLabel: 'Ouvrir',
            filters: [
              { name: 'fnv', extensions: ['fnv'] }
            ]
        };
        electron.dialog.showOpenDialog(win, options).then(value=>{callback(value.filePaths);});
    };
    exports.saveProject = (path, callback)=>{
        const options = {
            title: 'Sauvegarder un projet',
            defaultPath: path,
            buttonLabel: 'Sauvegarder',
            filters: [
              { name: 'fnv', extensions: ['fnv'] }
            ]
        };
        electron.dialog.showSaveDialog(win, options).then(value=>{callback(value.filePath);});
    };
}

electron.app.whenReady().then(createWindow);