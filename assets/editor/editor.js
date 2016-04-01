"use strict";

document.body.onload = function () {
    var canvas = document.getElementById("main");
    var context = canvas.getContext('2d');
    var mousePos = { x: 0, y: 0 };

    var tiles = [
        { txt: "   ", color: "#222", src:"../render/textures/grass.bmp", description: "EMPTY" },
        { txt: "1##", color: "#777", src:"../render/textures/dirt.bmp", description: "WALL_INDESTRUCTIBLE" },
        { txt: "1#1", color: "#666", src:"../render/textures/grass.bmp", description: "WALL_HP_1" },
        { txt: "1#2", color: "#555", src:"../render/textures/grass.bmp", description: "WALL_HP_2" },
        { txt: "1#3", color: "#444", src:"../render/textures/grass.bmp", description: "WALL_HP_3" },
        { txt: "1#4", color: "#333", src:"../render/textures/grass.bmp", description: "WALL_HP_4" },
        { txt: "2#1", color: "#900", src:"../render/textures/grass.bmp", description: "ENEMY1" },
        { txt: "2#2", color: "#f00", src:"../render/textures/grass.bmp", description: "ENEMY2" },
        { txt: "2#3", color: "#f90", src:"../render/textures/grass.bmp", description: "ENEMY3" },
        { txt: "2#4", color: "#ff0", src:"../render/textures/grass.bmp", description: "ENEMY4" },
        { txt: "3#a", color: "#ff9", src:"../render/textures/grass.bmp", description: "BOSS_A" },
        { txt: "3#b", color: "#ff9", src:"../render/textures/grass.bmp", description: "BOSS_B" },
        { txt: "3#c", color: "#ff9", src:"../render/textures/grass.bmp", description: "BOSS_C" },
        { txt: "3#c", color: "#ff9", src:"../render/textures/grass.bmp", description: "BOSS_C" },
        { txt: "4#1", color: "#0ea", src:"../render/textures/grass.bmp", description: "PLAYER1" },
        { txt: "4#2", color: "#0db", src:"../render/textures/grass.bmp", description: "PLAYER2" },
        { txt: "4#3", color: "#0cc", src:"../render/textures/grass.bmp", description: "PLAYER3" },
        { txt: "4#4", color: "#0bd", src:"../render/textures/grass.bmp", description: "PLAYER4" },
        { txt: "4#5", color: "#0ae", src:"../render/textures/grass.bmp", description: "PLAYER5" },
        { txt: "5#1", color: "#88f", src:"../render/textures/grass.bmp", description: "BONUS_POWER_UP"},
        { txt: "5#2", color: "#77f", src:"../render/textures/grass.bmp", description: "BONUS_PLUS_ONE"},
        { txt: "5#3", color: "#66f", src:"../render/textures/grass.bmp", description: "BONUS_KICK"},
        { txt: "5#4", color: "#55f", src:"../render/textures/grass.bmp", description: "BONUS_CHANGE"},
        { txt: "5#5", color: "#44f", src:"../render/textures/grass.bmp", description: "BONUS_REMOTE_BOMB"},
        { txt: "5#6", color: "#33f", src:"../render/textures/grass.bmp", description: "BONUS_SPEED_UP"}
    ];

    var create2dArray = function (sizeX, sizeY) {
        var x = new Array(sizeY);
        for (var i = 0; i < sizeY; i++) {
            x[i] = new Array(sizeX);
        }
        return x;
    }

    var mapSizeX = 35;
    var mapSizeY = 35;
    var tileMap = create2dArray(mapSizeX, mapSizeY);
    var currentChoice = 1;
    var tileSize = 20;
	var brushSize = 5;

    context.canvas.width = 1600;
    context.canvas.height = 1200;

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

    var update = function (delta) {

    };

	var preloadImages = function () {
		for (var y = 0; y < mapSizeY; y++) {
			for (var x = 0; x < mapSizeX; x++) {
				var e = tileMap[x][y];
				if (!e.img) {
					e.img = new Image();
					e.img.src = e.src;
					e.img.onload = function () {
						e.imgReady = true;
					};
				}
			}
		}
	};

    var drawMap = function () {
        for (var y = 0; y < mapSizeY; y++) {
            for (var x = 0; x < mapSizeX; x++) {
				// Si la tile est null, afficher la tile par defaut
				if (tileMap[x][y].imgReady) {
					context.drawImage(tileMap[x][y].img, 0, 0, tileMap[x][y].img.width, tileMap[x][y].img.height, x * tileSize + mapViewMargin.x, y * tileSize + mapViewMargin.y, tileSize, tileSize);
				}
				else {
					context.fillStyle = tileMap[x][y].color;
					context.fillRect(
						x * tileSize + mapViewMargin.x
						, y * tileSize + mapViewMargin.y
						, tileSize
						, tileSize);
				}
            };
        };
    };

    var drawSideBar = function () {
        context.clearRect(0, 0, canvas.width, canvas.height);
        tiles.forEach(function (tile, i, a) {
            var x = 0;
            var y = i * tileSize;

			if (tile.imgReady) {
				context.drawImage(tile.img, 0, 0, tile.img.width, tile.img.height, x, y, tileSize, tileSize);
			}
			else {
				context.fillStyle = tile.color;
				context.fillRect(x, y, tileSize, tileSize);
			}
            context.font = tileSize / 2 + 'px Consolas';
            context.fillStyle = '#FFF';
            context.fillText(tile.description, tileSize * 2.5, y + tileSize * 0.65);
        });
    }

    var render = function () {
        drawSideBar();
        drawMap();

        // Map cursor
        if (mousePos.x >= mapViewMargin.x)
        {
			for (var i = 0; i < brushSize; i++) {
				for (var j = 0; j < brushSize; j++) {
					var x = parseInt((mousePos.x - mapViewMargin.x) / tileSize) * tileSize + mapViewMargin.x + i * tileSize;
					var y = parseInt((mousePos.y - mapViewMargin.y) / tileSize) * tileSize + mapViewMargin.y + j * tileSize;
					if (tiles[currentChoice].imgReady) {
						context.drawImage(tiles[currentChoice].img, 0, 0, tiles[currentChoice].img.width, tiles[currentChoice].img.height, x, y, tileSize, tileSize);
					}
					else {
						context.fillStyle = tiles[currentChoice].color;
						context.fillRect(
							x
							, y
							, tileSize
							, tileSize);
					}
				}
			}
        }
        else
        {
			var x = tileSize;
			var y = parseInt((mousePos.y) / tileSize) * tileSize;
			if (tiles[currentChoice].imgReady) {
				context.drawImage(tiles[currentChoice].img, 0, 0, tiles[currentChoice].img.width, tiles[currentChoice].img.height, x, y, tileSize, tileSize);
			}
			else {
				context.fillStyle = tiles[currentChoice].color;
				context.fillRect(
					tileSize
					, parseInt((mousePos.y) / tileSize) * tileSize
					, tileSize
					, tileSize);
			}
        }
    };

    canvas.addEventListener('mousemove', function (evt) {
        mousePos = getMousePos(canvas, evt);
    });


    for (var y = 0; y < mapSizeY; y++) {
        for (var x = 0; x < mapSizeX; x++) {
            tileMap[x][y] = tiles[0];
        }
    }
    var safeBorders = function () {
        for (var y = 0; y < mapSizeY; y++) {
            for (var x = 0; x < mapSizeX; x++) {
                if (x == 0 || x == mapSizeX - 1
                 || y == 0 || y == mapSizeY - 1)
                    tileMap[x][y] = tiles[1];
            }
        }
    }

    var saveMap = function () {
        localStorage.setItem("tileMap", JSON.stringify(tileMap));
        // console.log(localStorage.getItem("tileMap"));
    }

    var loadMap = function () {
        var item = localStorage.getItem("tileMap");
        // console.log(item);
        if (!!item && item != "undefined")
        {
            tileMap = JSON.parse(item);
        }
        // console.log(tileMap);
    }

    var updateMapCode = function () {
        safeBorders();
        var outputDiv = document.querySelector('div#output pre');
        var tmp = "";

        tmp += "x: " + mapSizeX + "\n";
        tmp += "y: " + mapSizeY + "\n";
        tmp += "<-- MAP -->" + "\n";
        for (var y = 0; y < mapSizeY; y++) {
            for (var x = 0; x < mapSizeX; x++) {
                var e = tileMap[x][y] || tiles[0];
                tmp += e.txt;
                if (x != mapSizeX - 1)
                    tmp += ' ';
                localStorage.map
            }
            tmp += "\n";
        }
        tmp += "signature: \"DEEP THOUGHT\"\n";
        tmp += "description: \"AUTOGENERATED\"\n";
        outputDiv.innerHTML = tmp;
        saveMap();
    };

    canvas.addEventListener('click', function (evt) {
        if (mousePos.x < tileSize)
        {
            currentChoice = parseInt(mousePos.y / tileSize);
            // console.log(currentChoice);
            // console.log("choice : " + tiles[currentChoice].txt);
        }
        else
        {

			for (var i = 0; i < brushSize; i++) {
				for (var j = 0; j < brushSize; j++) {
					var x = parseInt((mousePos.x - mapViewMargin.x) / tileSize) + i;
					var y = parseInt((mousePos.y - mapViewMargin.y) / tileSize) + j;

					// console.log("x : " + x + " ; y : " + y);
					tileMap[x][y] = tiles[currentChoice];
				}
			}
            updateMapCode();
        }
    });


    this.addEventListener('keydown', function (evt) {
		if (evt.key == '-') {
			brushSize -= 1;
		}
		if (evt.key == '=') {
			brushSize += 1;
		}
		if (brushSize <= 0)
			brushSize = 1;
    });

    // loadMap();
    updateMapCode();
	preloadImages();
    (function animloop(){
        requestAnimationFrame(animloop);
        render();
    })();
};
