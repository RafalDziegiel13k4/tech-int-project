$(document).ready(function() {
  $('span.fr-placeholder').html(" ");
});

function getContent() {
  var tempText = $('div.fr-view').html();
  return tempText.replace(/\n/g, '');
}

function saveDoc() {
  var docContent = getContent();
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      window.history.back();
    }
  };
  xhttp.open("PUT", "http://" + location.hostname + ":3000/docs/" + pageDocID, true);
  xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  xhttp.send('status=free&user=WebUser&content=' + encodeURIComponent(docContent));
}
