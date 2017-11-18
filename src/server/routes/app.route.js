// J. Ramussen 2017

const path = require('path');
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

const fs = require('fs-extra');
const controller = require('../controllers/app.controller');

router.get('/client/', (req, res) => {
    let obj = controller.getIP(req, res);
    res = obj.res;
    return res.send(obj.ip);
});

router.post('/file/:filename', upload.single('file'), async (req, res) => {
    res.status(204);
    res.send('Upload Successful').end();

    let filename = await controller.savefilename(req.params.filename);
    // encrypt
    await controller.encryptFile(filename);
    controller.splitFile(filename);
});

router.get('/file/:filename', async (req, res) => {
    // look for the filename
    let fileBool = controller.findFile({
        filename: req.params.filename
    });
    if ((fileBool = true)) {
        // query all the registered clients for
        let clients = await controller.getClients();
        for (let i = 0; i < clients.length; i++) {
            console.log(clients[i]);
            controller.streamToClient(clients[i]);
        }
    } else {
        res.status(404);
        res.send('Cannot find file: ' + file.filename);
    }
});

module.exports = router;
