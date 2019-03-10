// Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.

console.log('BitBrain - Web Application Server.');
console.log('');
console.log('Copyright (c) 2019 Lauro Oyen, Jonathan Swinnen, BitBrain contributors. All rights reserved.');
console.log('Licensed under the MIT license. See LICENSE.txt for full terms. This notice is not to be removed.');

// --------------------------------
// REQUIRES
// --------------------------------

const imageIO = require('./private/image.io');

const express = require('express');
const socket = require('socket.io');
const childProcess = require('child_process');
const moment = require('moment');
const path = require('path');
const opn = require('opn');

// --------------------------------
// SETUP
// --------------------------------

const app = express();

const server = app.listen(1509, function() {
	//opn('http://localhost:1509');
});

const io = socket(server);

app.use(express.static(path.join(__dirname, 'public')));

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// --------------------------------
// ROUTES
// --------------------------------

app.get('/', function(req, res) {
	res.render('main');
});

// --------------------------------
// SOCKETS
// --------------------------------

io.on('connection', function(socket) {
	socket.on('image', function(message) {
		const program = path.join(__dirname, '..', 'x64', 'Release', 'BitBrain.exe');
		const fileName = message.username + '-' + moment().format('YYYYMMDD-kkmmss');
		const networkName = path.join(__dirname, '..', 'BitBrain', 'Resource', 'Networks');
		
		imageIO.writeImage(path.join(__dirname, 'temp', fileName), message.image, function(err, path) {
			if (err) throw err;
			
			childProcess.execFile(program, [path, networkName], function(error, stdout, stderr) {
				if (error) throw error;
				if (stderr) console.log(stderr);
				socket.emit('extraction', JSON.parse(stdout));
			});
		});
	});
});
