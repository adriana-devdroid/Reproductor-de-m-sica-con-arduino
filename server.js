var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

const SerialPort = require('serialport');
const parsers = SerialPort.parsers;

const parser = new parsers.Readline({
	delimiter: '\r\n'
});

const port = new SerialPort('COM5', {
	baudRate: 9600
});

port.pipe(parser);

port.on('open', () => console.log('Port open'));
parser.on ('data', (cmd) => {
	io.emit('cmd', cmd);
});

app.use(express.static('public'));

io.on('connection', function(socket){
	console.log('a user connected');
	socket.on('led', function(json_dato) {
		// console.log(json_dato);
		port.write(json_dato.index+json_dato.valor);
	});
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
