// basic variables
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var fs = require('fs'); // required for file serving

http.listen(3000, function(){
  console.log('listening on *:3000');
});

// location to index.html
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

// only to test chat sample code from sample
io.on('connection', function(socket){

  console.log('a user connected');
    // broadcast a message
  socket.broadcast.emit('chat message', 'System Broadcast Message: a user has been connected');
  socket.on('chat message', function(msg){
    io.emit('chat message', msg);
  });});

// trying to serve the image file from the server
io.on('connection', function(socket){
  fs.readFile(__dirname + '/images/image.jpg', function(err, buf){
    // it's possible to embed binary data
    // within arbitrarily-complex objects
    socket.emit('image', { image: true, buffer: buf });
    console.log('image file is initialized');
  });
});