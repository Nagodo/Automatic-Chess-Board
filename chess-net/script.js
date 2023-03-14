fetch(chrome.runtime.getURL('/index.html'))
    .then(response => response.text())
    .then(data => {
        document.getElementById('content').innerHTML = data;
        SetupBoard();   
       
    }).catch(err => {
        // handle error
    });


var clicks = [];
var lastPos = "";

var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        if (lastPos != this.responseText) {
            lastPos = this.responseText;
            document.getElementById("position").innerHTML = this.responseText;
            UpdatePosition();

        }
    }
};


function SetupBoard()
{
    //Update .board .squares .square.white class backgrund img
    var squares = document.getElementsByClassName("square white");
    for (var i = 0; i < squares.length; i++) {
        var square = squares[i];
        square.style.backgroundImage = "url(" + chrome.runtime.getURL("/img/wsquare.png") + ")";
    }

    //Update .board .squares .square.black class backgrund img
    var squares = document.getElementsByClassName("square black");
    for (var i = 0; i < squares.length; i++) {
        var square = squares[i];
        square.style.backgroundImage = "url(" + chrome.runtime.getURL("/img/bsquare.png") + ")";
    }

    //On square click
    var squares = document.getElementsByClassName("square");
    for (var i = 0; i < squares.length; i++) {
        var square = squares[i];
        square.addEventListener("click", function () {
            ClickSquare(this.id);
        });
        
    }
}

setInterval(UpdateFEN, 500);



function UpdateFEN() {
    xhttp.open("GET", "/update", true);
    xhttp.send();
}

function ClickSquare(id)
{
    if (clicks[0] == null) {
       
        clicks[0] = id;
    } 
    else if (clicks[0] == id) {
        clicks[0] = null;
    }
    else if (clicks[0] != null && clicks[1] == null) {
        clicks[1] = id;
    }
    console.log(clicks[0] + clicks[1]);
    if (clicks[0] != null && clicks[1] != null) {
        //Send move to server
        console.log("Move: " + clicks[0] + " " + clicks[1]);
        xhttp.open("GET", "/move?from=" + clicks[0] + "&to=" + clicks[1], true);
        xhttp.send();
        clicks[0] = null;
        clicks[1] = null;
    }

    UpdateHighlight();
}

function UpdateHighlight() {
    var squares = document.getElementsByClassName("square");
    for (var i = 0; i < squares.length; i++) {
        var square = squares[i];

        var highlight = square.getElementsByClassName("highlight")[0];
        if (square.id == clicks[0] || square.id == clicks[1]) {
            highlight.style.background = "rgba(255, 0, 0, 0.3)";
        } else {
            highlight.style.background = "none";
        }
    }
}

var lastPosition = "";
function UpdatePosition() {
    var element = document.getElementById("position");
    
    var pos = element.innerHTML;

    
    if (pos != lastPosition) {
        console.log("UpdatePosition");
        document.getElementById("show_position").innerHTML = pos;
    
        lastPosition = pos;

        var letters = ["a", "b", "c", "d", "e", "f", "g", "h"];
        var number = 8;
        var x = 0;

        //Loop through the string 
        for (var i = 0; i < pos.length; i++) {
            var img = "trans.png";
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
           
            var URL = chrome.runtime.getURL("img/" + img);
            imgElement.src = URL;
            
            x++;
            
            if (x == 8) {
                number--;
                letter = letters[x];
                x = 0;
            }
           
        }
    }
}