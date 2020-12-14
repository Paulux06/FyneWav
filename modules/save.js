function openSave(file) {
    if (file != undefined) {
        fs.readFile(file[0], "utf-8", (err, data) => {
            if (err) return;
            try {
                let save = JSON.parse(data);
                console.log("%cfile version: "+save.version, "color: #3498DB;");
            } catch (error) {
                console.log("%cUnable to load file", "color: #E74C3C;")
            }
        });
    }
}

function saveProject(file) {
    if (file != undefined) {
        fs.writeFile(file, "{\"version\": 0.1}", "utf-8", err => {if(err)console.log(err);});
    }
}