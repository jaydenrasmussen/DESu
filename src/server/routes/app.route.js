// J. Ramussen 2017

const express = require('express');
let router = express.Router();

const multer = require('multer');
const upload = multer({ dest: './uploads/' });

const controller = require('../controllers/app.controller');

router.get('/', (req, res) => {
    res.status(200);
    return res.send('Hello World!');
});

router.get('/client/', (req, res) => {
    let obj = controller.getIP(req, res);
    res = obj.res;
    return res.send(obj.ip);
});

router.post('/file/:filename', upload.single('file'), (req, res) => {
    res.status(204);
    res.send('Upload Successful').end();

    controller.savefilename(req.params.filename);
});

module.exports = router;
