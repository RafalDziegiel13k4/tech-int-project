const mongoose = require('mongoose');
const Schema = mongoose.Schema;

var docsSchema = new Schema({
  name: {
    type: String,
    required: 'Enter name'
  },
  Modification_date: {
    type: Date,
    default: Date.now
  },
  status: {
      type: String,
      enum: ['free', 'used'],
      default: ['free']
  }
});

module.exports = mongoose.model('Docs', docsSchema);
