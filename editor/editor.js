"use strict";


document.body.onload = function () {
    var canvas = document.getElementById("main");
    var context = canvas.getContext('2d');
    var mousePos = { x: 0, y: 0 };

    var tiles = [
        { string_value: "   ", color: "#333", description: "EMPTY"},
        { string_value: "1##", color: "#f00", description: "WALL_INDESTRUCTIBLE"},
        { string_value: "1#1", color: "#0f0", description: "WALL_HP_1"},
        { string_value: "1#2", color: "#00f", description: "WALL_HP_2"},
        { string_value: "1#3", color: "#ff0", description: "WALL_HP_3"},
        { string_value: "1#4", color: "#0ff", description: "WALL_HP_4"},
        { string_value: "2#1", color: "#f09", description: "ENEMY1"},
        { string_value: "2#2", color: "#9f0", description: "ENEMY2"},
        { string_value: "2#3", color: "#90f", description: "ENEMY3"},
        { string_value: "2#4", color: "#0ff", description: "ENEMY4"},
        { string_value: "3#a", color: "#ff0", description: "BOSS_A"},
        { string_value: "3#b", color: "#fff", description: "BOSS_B"},
        { string_value: "3#c", color: "#990", description: "BOSS_C"},
        { string_value: "3#c", color: "#099", description: "BOSS_C"},
        { string_value: "4#1", color: "#06f", description: "PLAYER1"},
        { string_value: "4#2", color: "#f60", description: "PLAYER2"},
        { string_value: "4#3", color: "#606", description: "PLAYER3"},
        { string_value: "4#4", color: "#096", description: "PLAYER4"}
    ];

    var create2dArray = function (sizeX, sizeY) {
        var x = new Array(sizeY);
        for (var i = 0; i < sizeY; i++) {
            x[i] = new Array(sizeX);
        }
        return x;
    }

    var mapSize = 20;
    var tileMap = create2dArray(mapSize, mapSize);
    var currentChoice = 0;
    var tileSize = 30;

    context.canvas.width = 1280;
    context.canvas.height = 800;

    var mapViewMargin = {
        x: context.canvas.width * 1 / 4 ,
        y: context.canvas.height * 1 / 8
    };

    var getMousePos = function (canvas, evt) {
        var rect = canvas.getBoundingClientRect()
        return {
            x: evt.clientX - rect.left,
            y: evt.clientY - rect.top
        };
    };

    var writeMessage = function (canvas, message) {
        context.font = '18pt Calibri';
        context.fillStyle = '#ffffff';
        context.fillText(message, 10, 25);
    };

    var update = function (delta) {

    };

    var drawMap = function () {
        for (var y = 0; y < mapSize; y++) {
            for (var x = 0; x < mapSize; x++) {
                var e = tileMap[x][y] || tiles[0];
                context.fillStyle = e.color;
                context.fillRect(
                      x * tileSize + mapViewMargin.x
                    , y * tileSize + mapViewMargin.y
                    , tileSize
                    , tileSize);
            };
        };
    };

    var drawSideBar = function () {
        context.clearRect(0, 0, canvas.width, canvas.height);
        tiles.forEach(function (e, i, a) {
            var x = 0;
            var y = i * tileSize;
            var width = tileSize;
            var height = tileSize;
            context.fillStyle = tiles[i].color;
            context.fillRect(x, y, width, height);

            context.font = tileSize / 2 + 'px menlo';
            context.fillStyle = '#FFF';
            context.fillText(tiles[i].description, width * 1.5, y - height / 3);
        });
    }

    var render = function () {
        drawSideBar();
        context.fillStyle = "#FFFFFF";
        writeMessage(canvas, 'x: ' + mousePos.x + ', y: ' + mousePos.y);
        drawMap();
        context.fillStyle = tiles[currentChoice].color;
        context.globalAlpha = 0.5;
        context.fillRect(
              parseInt((mousePos.x - mapViewMargin.x) / tileSize) * tileSize + mapViewMargin.x
            , parseInt((mousePos.y - mapViewMargin.y) / tileSize) * tileSize + mapViewMargin.y
            , tileSize
            , tileSize);
        context.globalAlpha = 1;
    };

    canvas.addEventListener('mousemove', function (evt) {
        mousePos = getMousePos(canvas, evt);
    });

    var updateSource = function () {
        var outputDiv = document.querySelector('div#output pre');
        var tmp = "";

        for (var y = 0; y < mapSize; y++) {
            for (var x = 0; x < mapSize; x++) {
                var e = tileMap[x][y] || tiles[0];
                tmp += e.string_value + " ";
            }
            tmp += "\n";
        }
        outputDiv.innerHTML = tmp;
    };

    canvas.addEventListener('click', function (evt) {
        if (mousePos.x < tileSize)
        {
            currentChoice = parseInt(mousePos.y / tileSize);
            console.log(currentChoice);
            console.log("choice : " + tiles[currentChoice].string_value);
        }
        else
        {
            var x = parseInt((mousePos.x - mapViewMargin.x) / tileSize);
            var y = parseInt((mousePos.y - mapViewMargin.y) / tileSize);
            console.log("x : " + x + " ; y : " + y);
            tileMap[x][y] = tiles[currentChoice];

            updateSource();
        }
    });

    (function animloop(){
        requestAnimationFrame(animloop);
        render();
    })();
};
