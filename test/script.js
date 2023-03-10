var stockfish = new Worker('stockfish.js');

// fetch(chrome.runtime.getURL('/index.html'))
//     .then(response => response.text())
//     .then(data => {
//         document.getElementById('root').innerHTML = data;
       
//     }).catch(err => {
//         // handle error
//     });
setInterval(UpdatePosition, 2000);


var lastPosition = "";
function UpdatePosition() {
    var element = document.getElementById("position");
    
    var pos = element.innerHTML;
    
    if (pos != lastPosition) {
        console.log("UpdatePosition");
        lastPosition = pos;

        var letters = ["a", "b", "c", "d", "e", "f", "g", "h"];
        var number = 8;
        var x = 0;
        console.log(pos.length);
        console.log(pos);
        //Loop through the string 
        for (var i = 0; i < pos.length; i++) {
            var img = "trans.png";
            console.log(number);
            if (pos[i] == "r") {
                img = "br.png";
            } else if (pos[i] == "n") {
                img = "bn.png";
            } else if (pos[i] == "b") {
                img = "bb.png";
            } else if (pos[i] == "q") {
                img = "bq.png";
            } else if (pos[i] == "k") {
                img = "bk.png";
            } else if (pos[i] == "p") {
                img = "bp.png";
            } else if (pos[i] == "R") {
                img = "wr.png";
            } else if (pos[i] == "N") {
                img = "wn.png";
            } else if (pos[i] == "B") {
                img = "wb.png";
            } else if (pos[i] == "Q") {
                img = "wq.png";
            } else if (pos[i] == "K") {
                img = "wk.png";
            } else if (pos[i] == "P") {
                img = "wp.png";
            } 

            var p = letters[x] + number;
            var divElement = document.getElementById(p);
            var imgElement = divElement.getElementsByTagName("img")[0];
           
            imgElement.src = "./img/" + img;   
            
            x++;
            
            if (x == 8) {
                number--;
                letter = letters[x];
                x = 0;
            }
           
        }
    }
}