// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen. All rights reserved.

var fs = require("fs");

// Gets the extension of a base64 encoded image.
function getExtension(dataUrl) {
	return dataUrl.split("data:image/")[1].split(";")[0];
}

// Gets the base64 encoded image of a data url.
function getImage(dataUrl) {
	return dataUrl.split(";base64,").pop();
}

// Saves a base64 encoded image synchronously.
function writeImageSync(filePath, dataUrl, callback) {
	var path = filePath + '.' + getExtension(dataUrl);
	fs.writeFileSync(path, getBa64Img(dataUrl), {encoding: "base64"});
	callback(path);
}

// Saves a base64 encoded image asynchronously.
function writeImage(filePath, dataUrl, callback) {
	var path = filePath + '.' + getExtension(dataUrl);
	fs.writeFile(path, getImage(dataUrl), {encoding: "base64"}, function(error) {
		callback(error, path);
	});
}

module.exports.writeImageSync = writeImageSync;
module.exports.writeImage = writeImage;
