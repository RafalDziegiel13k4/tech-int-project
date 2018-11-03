module.exports = function(app) {
const list = require('../controllers/controller');

app.route('/docs')
	.get(list.list_all_docs)
	.post(list.create_a_doc);

app.route('/docs/:docId')
	.get(list.read_a_doc)
	.put(list.update_a_doc)
	.delete(list.delete_a_doc);
};
