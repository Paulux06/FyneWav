var sequenceurData = [
    {
        title: "Piste 1", color: "var(--color-green-light)",
        pattern: [
            {width: 2},
            {width: 4}
        ]
    },
    {
        title: "Piste 2", color: "var(--color-yellow-light)",
        pattern: [
            {width: 2}
        ]
    }
]
var nameWidth = 120; //texte en début de piste (Piste1, Piste2, ...)
var progress = 0; //progress du curseur en pixels

function setupSequenceur() {
    var container = document.getElementById("app-sequenceur-piste-container");
    for(let i=0; i<sequenceurData.length; i++) {
        var piste_div = document.createElement("div");
        var piste_name = document.createElement("div");
        var piste_content = document.createElement("div");
        var piste_title = document.createElement("input");
        piste_div.classList.add("app-sequenceur-piste-div");
        piste_name.classList.add("app-sequenceur-piste-name");
        piste_content.classList.add("app-sequenceur-piste-content");
        piste_title.classList.add("app-sequenceur-piste-title");
        piste_name.style.borderColor = sequenceurData[i].color;
        piste_title.value = sequenceurData[i].title;
        piste_name.appendChild(piste_title);
        piste_div.appendChild(piste_name);

        for(let j=0; j<sequenceurData[i].pattern.length; j++) {
            const pattern = sequenceurData[i].pattern[j];
            var pattern_div = document.createElement("div");
            pattern_div.classList.add("app-sequenceur-pattern-div");
            pattern_div.style.backgroundColor = sequenceurData[i].color;
            pattern_div.style.width = (pattern.width*80).toString()+"px";
            piste_content.appendChild(pattern_div);
        }

        piste_div.appendChild(piste_content);
        container.appendChild(piste_div);
    }

    document.getElementById("app-sequenceur-div").onscroll = (ev)=>{
        updateCursorPos();
    }
}

function updateCursorPos() {
    var elmnt = document.getElementById("app-sequenceur-div")
    document.getElementById("app-sequenceur-cursor-div").style.left =
        (nameWidth - elmnt.scrollLeft + progress).toString()+"px";
}

function changePlayerProgressBy(amount) {
    progress -= amount;
    progress = Math.max(progress, 0)
    updateCursorPos();
}