var socket;
var numCancion = 1;
var estado_boton = false;
var cont =0;
window.onload = function() {
	document.getElementById('foto').innerHTML = "<img src='../img/HarryPotter.jpg' width='300px' height='400px'>";
	document.getElementById('atras').innerHTML = "<input id = 'ant' type = 'button' name = 'anterior' class = 'deshabilitar' value='<<' onclick='anterior()' disabled>";
	document.getElementById('adelante').innerHTML = "<input id = 'sig' type='button' name='siguiente' class = 'apagado' value='>>' onclick='siguiente()'>";
	
	socket = io();
	let cmd_sep;
	socket.on('cmd', (cmd) => {
		if(cmd == "sig"){
			
		siguiente();
		}
		else if(cmd == "final"){
			cont = 0;
			estado_boton = false;
			socket.emit('led', {index: numCancion, valor: "0"});
			document.getElementById('play').className = 'apagado';
			document.getElementById('play').className = document.getElementById('play').className.replace( /(?:^|\s)encendido(?!\S)/g , '' );
		
		}
		else if(cmd== "mas"){
			if(estado_boton == false)
			imprimir();
			else{
			imprimir();
			cont++;
			}
		}
	});
}
	
function imprimir(){
	if(cont < 10)
		document.getElementById('tiempo').innerHTML = "0:"+"0"+cont;
	else
		document.getElementById('tiempo').innerHTML = "0:"+cont;
}

function reproducir() {
	if (estado_boton == false) {
		estado_boton = true;
		socket.emit('led', {index: numCancion, valor: "1"});
		document.getElementById('play').className = 'encendido';
		document.getElementById('play').className = document.getElementById('play').className.replace( /(?:^|\s)apagado(?!\S)/g , '' );
		
	}
	else
	{	
		estado_boton = false;
		socket.emit('led', {index: numCancion, valor: "0"});
		document.getElementById('play').className = 'apagado';
		document.getElementById('play').className = document.getElementById('play').className.replace( /(?:^|\s)encendido(?!\S)/g , '' );

	}
}

function anterior() {
	cont = 0;
	estado_boton = true;
	document.getElementById('play').className = 'encendido';
	document.getElementById('play').className = document.getElementById('play').className.replace( /(?:^|\s)apagado(?!\S)/g , '' );

	if (numCancion != 1) {
		
		document.getElementById('adelante').innerHTML = "<input id = 'sig' type='button' name='siguiente' class = 'apagado' value='>>' onclick='siguiente()'>";
		numCancion--;
		if(numCancion == 1)
			document.getElementById('atras').innerHTML = "<input id = 'ant' type='button' name='anterior' class = 'deshabilitar' value='<<' onclick='anterior()' disabled>";
		//document.getElementById('atras').innerHTML = "<input id = 'ant' type='button' name='anterior' class = 'apagado' value='<<' onclick='anterior()' disabled = 'false'>";
	}
	socket.emit('led', {index: numCancion, valor: "1"});
	imagen_nombre();
}

function siguiente() {
	cont = 0;
	estado_boton = true;
	document.getElementById('play').className = 'encendido';
	document.getElementById('play').className = document.getElementById('play').className.replace( /(?:^|\s)apagado(?!\S)/g , '' );

	if (numCancion != 4) {
		document.getElementById('atras').innerHTML = "<input id = 'ant' type = 'button' name = 'anterior' class = 'apagado' value='<<' onclick='anterior()'>";
		numCancion++;

		if(numCancion ==4)
			document.getElementById('adelante').innerHTML = "<input id = 'sig' type='button' name='siguiente' class = 'deshabilitar' value='>>' onclick='siguiente()' disabled>";
		//estado_siguiente = false;
		//socket.emit('led', {index: "2", valor: "1"});
		//document.getElementById('sig').className = 'apagado';
		//document.getElementById('sig').setAttribute("disabled","disabled");
	}
	socket.emit('led', {index: numCancion, valor: "1"});
	imagen_nombre();
}

function imagen_nombre(){
	if(numCancion == 1){
		document.getElementById('nombre').innerHTML = "Harry Potter";
		document.getElementById('foto').innerHTML = "<img src='../img/HarryPotter.jpg' width='300px' height='400px'>";
		
	}
	else if(numCancion == 2){
		document.getElementById('nombre').innerHTML = "Star Wars";
		document.getElementById('foto').innerHTML = "<img src='../img/StarWars.jpg' width='300px' height='400px'>";
	}
	else if(numCancion == 3){
		document.getElementById('nombre').innerHTML = "Marcha del Imperio";
		document.getElementById('foto').innerHTML = "<img src='../img/Marcha.jpg' width='300px' height='400px'>";
	}
	else {
		document.getElementById('nombre').innerHTML = "Entre Dos Aguas";
		document.getElementById('foto').innerHTML = "<img src='../img/DosAguas.jpeg' width='300px' height='400px'>";
	}
}


