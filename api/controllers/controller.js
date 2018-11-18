const mongoose = require('mongoose');
Docs = mongoose.model('Docs');
const options = { day: 'numeric', month: 'long', year: 'numeric', hour: 'numeric', minute: 'numeric', second: 'numeric' };

exports.list_all_docs = function(req, res) {
  Docs.find({}, function(err, doc) {
    if (err)
      res.send(err);
    res.json(doc);
  });
};

exports.create_a_doc = function(req, res) {
  var new_doc = new Docs(req.body);
  new_doc.save(function(err, doc) {
    if (err)
      res.send(err);
    res.json(doc);
  });
};

exports.read_a_doc = function(req, res) {
  Docs.findById(req.params.docId, function(err, doc) {
    if (err)
      res.send(err);
    res.json(doc);
  });
};

exports.update_a_doc = function(req, res) {
  var docBody = req.body;
  var currentTime = new Date();
  docBody.modification_date = currentTime.toLocaleDateString("pl-PL", options);

  Docs.findOneAndUpdate({_id: req.params.docId}, docBody, {new: true}, function(err, doc) {
    if (err)
      res.send(err);
    res.json(doc);
  });
};

exports.delete_a_doc = function(req, res) {
  Docs.remove({
    _id: req.params.docId
  }, function(err, doc) {
    if (err) res.send(err);
    res.json({ message: 'Document successfully deleted' });
  });
};
