// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

// This array was automatically generated using the SymbolExtractor::GetDebugInfo() function.
var rectangles = [[116,16,80,99],[0,21,96,99],[202,21,99,99],[335,21,66,99],[526,21,96,89],[431,30,70,97],]

window.onload = function()
{
	var canvas = document.querySelector("canvas");
	var image = document.getElementById("image");

	canvas.width = image.naturalWidth;
	canvas.height = image.naturalHeight;

	var ctx = canvas.getContext("2d");
	ctx.drawImage(image, 0, 0);

    ctx.lineWidth = 1;
	ctx.strokeStyle = "#0000FF";

	for(var i = 0; i < rectangles.length; i++)
	{
		var r = rectangles[i];
		ctx.strokeRect(r[0], r[1], r[2], r[3]);
	}
}
