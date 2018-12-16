const express = require('express');
const app = express();
const path = require('path');

app.get('/', (req, res) => {
  res.sendStatus(404);
});

app.get('/editor', (req, res) => {
  res.sendFile(path.join(__dirname + '/web-editor.html'));
});

app.use('/css', express.static(path.join(__dirname, 'css')));
app.use('/js', express.static(path.join(__dirname, 'js')));

app.listen(3002, () =>
  console.log('Express server is running on localhost:3002')
);
