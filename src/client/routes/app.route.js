// J. Ramussen 2017
const express = require('express');
let router = express.Router();

const multer = require('multer');
const upload = multer({ dest: './uploads/' });

const controller = require('../controllers/app.controller');

router.get('/', (req, res) => res.send('Hello World!'));

router.get('/files/:filename', (req, res) => {
    let files = controller.getFiles();
    let file = files[req.params.filename];
    if (file !== undefined) {
        res.download('./uploads/' + req.params.filename);
    } else {
        res.status(404);
        res.send('Cannot find file: ' + req.params.filename);
    }
});

router.post('/files/:filename', upload.single('hash'), (req, res) => {
    res.status(204);
    res.send('File successfully uploaded!').end();
});

module.exports = router;
