const express = require('express');
const app = express();
const fs = require('fs');
const path = require('path');
const jsdom = require("jsdom");
const { JSDOM } = jsdom;
const editorFile = path.join(__dirname + '/web-editor.html');

app.get('/', (req, res) => {
  res.sendStatus(404);
});

app.get('/viewer', (req, res) => {
  JSDOM.fromFile(editorFile).then(dom => {
    dom.window.document.body.innerHTML += '<script type="text/javascript" src="js/prepare_viewer.js"></script>\n';
    dom.window.document.body.innerHTML += '<script type="text/javascript" src="js/set_content.js"></script>\n';
    var docHTML = dom.window.document.documentElement.innerHTML;

    res.writeHead(200, {'Content-Type': 'text/html'});
    fs.writeFileSync('/tmp/resp.html', "<!DOCTYPE html>\n<html>\n" + docHTML + "\n</html>");
    res.end("<!DOCTYPE html>\n<html>\n" + docHTML + "\n</html>");
  });
});

app.get('/editor', (req, res) => {
  res.sendFile(path.join(__dirname + '/web-editor.html'));
});

app.use('/css', express.static(path.join(__dirname, 'css')));
app.use('/js', express.static(path.join(__dirname, 'js')));

app.listen(3002, () =>
  console.log('Express server is running on localhost:3002')
);
