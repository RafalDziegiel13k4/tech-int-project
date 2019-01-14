const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
app.use(cors());

const port = process.env.PORT || 3000;
const Task = require('./api/models/model');
const routes = require('./api/routes/routes');

mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost/Docs', { useNewUrlParser: true });

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

var server = app.listen(port);
var websocket = require('socket.io').listen(server);
app.websocket = websocket;

routes(app);

console.log('REST API server started on: ' + port);

websocket.on("connection", socket => {
  console.log("New client connected");
});

const getApiAndEmit = async websocket => {
    websocket.emit("refresh", "007");
};
