const { app, BrowserWindow, screen } = require('electron');

function createWindow () {
    const {width, height} = screen.getPrimaryDisplay().workAreaSize;
    const win = new BrowserWindow({
        width: width,
        height: height,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: true
        },
        icon: "./resources/icons/icon.png"
    });

    win.setMenuBarVisibility(false);
    win.loadFile('./index.html');
    exports.getWin = ()=>{return win;}
}

app.whenReady().then(createWindow);