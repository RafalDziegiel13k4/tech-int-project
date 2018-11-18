const mongoose = require('mongoose');
const Schema = mongoose.Schema;

var docsSchema = new Schema({
  name: {
    type: String,
    required: 'Doc name'
  },
  modification_date: {
    type: String,
    default: function() {
      var options = { day: 'numeric', month: 'long', year: 'numeric', hour: 'numeric', minute: 'numeric', second: 'numeric' };
      var currentTime = new Date();
      return currentTime.toLocaleDateString("pl-PL", options)
      }
  },
  status: {
      type: String,
      enum: ['free', 'used'],
      default: ['free']
  },
  user: {
    type: String,
    default: 'Anonymous'
  }
});

module.exports = mongoose.model('Docs', docsSchema);
