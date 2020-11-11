#! /usr/bin/env node

var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', (socket) => {
    console.log('user connected');

    socket.on('news', (message) => {
      console.log(message);
    });
});
http.listen(3000, () => {
  console.log('listening on *:3000');
});

