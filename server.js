const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');

const app = express();
const port = process.env.PORT || 3000;
const Task = require('./api/models/model');
const routes = require('./api/routes/routes');

mongoose.Promise = global.Promise;
mongoose.connect('mongodb://localhost/Docs', { useNewUrlParser: true });

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

routes(app);
app.listen(port);

console.log('REST API server started on: ' + port);
