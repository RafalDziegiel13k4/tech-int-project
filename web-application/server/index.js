const express = require('express');
const app = express();
const http = require("http");
const fs = require('fs');
const path = require('path');
const jsdom = require("jsdom");
const { JSDOM } = jsdom;
const editorFile = path.join(__dirname + '/web-editor.html');

var docID;
var linkEnd;

app.get('/', (req, res) => {
  res.sendStatus(404);
});

app.get('/viewer', (req, res) => {

  linkEnd = '/viewer';

  if(req.url != linkEnd) {
    var parsedUrl = req._parsedUrl;
    docID = parsedUrl.query;
    res.redirect(linkEnd);
  }
  else {
    var host = req.headers.host;
    createEditor(host, res);
  }
});

app.get('/editor', (req, res) => {

  linkEnd = '/editor';

  if(req.url != linkEnd) {
  var parsedUrl = req._parsedUrl;
  docID = parsedUrl.query;
  res.redirect(linkEnd);
  }
  else {
    var host = req.headers.host;
    createEditor(host, res);
  }
});

function createEditor(host, res) {

  var hostName = host.substr(0, host.indexOf(':'));

  http.get('http://' + hostName + ':3000' + '/docs/' + docID, (resp) => {
    let data = '';

    resp.on('data', (chunk) => {
      data += chunk;
    });

    resp.on('end', () => {
      JSDOM.fromFile(editorFile).then(dom => {
        if(linkEnd == '/viewer')
        {
          dom.window.document.body.innerHTML += '<script type="text/javascript" src="js/prepare_viewer.js"></script>\n';
	}
        else
        {
          dom.window.document.body.innerHTML += '<script type="text/javascript" src="js/prepare_editor.js"></script>\n';
        }

        dom.window.document.body.innerHTML += `<script>$(document).ready(function() {$('div.fr-view').html('${data}');});</script>`

        var docHTML = dom.window.document.documentElement.innerHTML;
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.end("<!DOCTYPE html>\n<html>\n" + docHTML + "\n</html>");
      });
    });
  }).on("error", (err) => {
    console.log("Error: " + err.message);
  });
}

app.use('/css', express.static(path.join(__dirname, 'css')));
app.use('/js', express.static(path.join(__dirname, 'js')));

app.listen(3002, () =>
  console.log('Express server is running on localhost:3002')
);
