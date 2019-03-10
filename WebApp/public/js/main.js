// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

// --------------------------------
// GLOBAL VARIABLES
// --------------------------------

var GImage;
var GBounds;

// --------------------------------
// HTML REFERENCES
// --------------------------------

const socket = io();

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

const fileInput = document.getElementById('fileInput');

const uploadButton = document.getElementById('uploadButton');
const settingsButton = document.getElementById('settingsButton');

const settingsPanel = document.getElementById('settingsPanel');

const username = document.getElementById('username');

const arguments = document.getElementById('arguments');
const evaluateButton = document.getElementById('evaluateButton');

// --------------------------------
// EVENT LISTENERS
// --------------------------------

ResizeCanvas();

uploadButton.addEventListener('click', function(e) {
	fileInput.click();
});

fileInput.addEventListener('change', function(e) {
	FileUpload(e.target.files[0]);
});

settingsButton.addEventListener('click', ToggleSettingsPanel);

window.addEventListener('resize', ResizeCanvas);

function ToggleSettingsPanel() {
	if(username.value.trim()) {
		settingsPanel.classList.toggle('open');
	}
}

// --------------------------------
// MAIN FUNCTIONS
// --------------------------------

function ResizeCanvas() {
	canvas.width = document.body.clientWidth;
	canvas.height = document.body.clientHeight;

	RenderCanvas();
}

function RenderCanvas() {
	ctx.fillStyle = '#FFF';
	ctx.fillRect(0, 0, canvas.width, canvas.height);

	var scale;
	var width;
	var height;
	var x;
	var y;

	if(GImage) {
		scale = Math.min(canvas.width / GImage.width, canvas.height / GImage.height);
		
		width = GImage.width * scale;
		height = GImage.height * scale;

		x = (canvas.width - width) / 2;
		y = (canvas.height - height) / 2;
		
		ctx.drawImage(GImage, x, y, width, height);
	}

	if(GBounds) {
		ctx.lineWidth = 1;
		ctx.fillStyle = '#ff0';
		ctx.strokeStyle = '#ff0';
		ctx.shadowBlur = 16;
		ctx.shadowColor = 'black';
		ctx.font = '30px Lato';
		ctx.textAlign = 'left';

		var expression = '';

		for(var i = 0; i < GBounds.length; i++) {
			var r = GBounds[i];
			ctx.strokeRect(r[1]*scale + x, r[2]*scale + y, r[3] * scale, r[4] * scale);
			ctx.fillText(r[0], r[1]*scale + x, r[2]*scale + y - 10);
			expression += r[0];
		}

		var result = eval(expression);

		var text = expression + ' = ' + result;

		ctx.textAlign = 'center';
		ctx.fillText(text, canvas.width / 2, canvas.height - 50);
	}
}

function FileUpload(file) {
	const reader = new FileReader();
	reader.onload = function(e) {
		GImage = new Image();
		GImage.onload = function() {
			RenderCanvas();
			var message = {
				image: e.target.result,
				username: username.value
			}
			socket.emit('image', message);
		}
		GImage.src = e.target.result;
	}
	reader.readAsDataURL(file);
}

// --------------------------------
// SOCKET EVENTS
// --------------------------------

socket.on('extraction', function(message) {
	GBounds = message;
	console.log(message);
	RenderCanvas();
});

// --------------------------------
// COLLAPSIBLE ELEMENTS
// --------------------------------

const collapsible = document.getElementsByClassName('collapsible');

for (var i = 0; i < collapsible.length; i++) {
	collapsible[i].addEventListener('click', function() {
		this.classList.toggle('open');
		const content = this.nextElementSibling;
		if (content.style.maxHeight) {
			content.style.maxHeight = null;
		} else {
			content.style.maxHeight = content.scrollHeight + 'px';
		} 
	});
}
