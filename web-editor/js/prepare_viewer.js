$(document).ready(function() {
  $('div.fr-toolbar').remove();
  $('div#editor').attr('contenteditable','false');
  $('div.fr-view').attr('contenteditable','false');
  $('span.fr-placeholder').html(" ");
});
