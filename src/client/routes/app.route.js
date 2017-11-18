// J. Ramussen 2017
const express = require('express');
let router = express.Router();

const multer = require('multer');
const storage = multer.diskStorage({
    destination: './uploads/',
    filename: (req, file, cb) => {
        cb(
            null,
            file.originalname
                .split('/')
                .pop()
                .trim()
        );
    }
});
const upload = multer({ storage: storage });

const controller = require('../controllers/app.controller');

router.get('/', (req, res) => res.send('Hello World!'));

router.get('/file/:filename', (req, res) => {
    let files = controller.getFiles();
    let file = files[req.params.filename];
    if (file !== undefined) {
        res.download('./uploads/' + req.params.filename + '/' + file);
    } else {
        res.status(404);
        res.send('Cannot find file: ' + req.params.filename);
    }
});

router.post('/file/:filename/:num', upload.single('hash'), async (req, res) => {
    res.status(204);
    res.send('File successfully uploaded!').end();

    await controller.saveUploadData(req.params.filename, req.params.num);
    await controller.moveUploadData(req.params.filename, req.params.num)
});

module.exports = router;
