// J. Ramussen 2017

const express = require('express');
let router = express.Router();

const multer = require('multer');
const upload = multer({ dest: './uploads/' });

const got = require('got');

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

router.get('/file/:filename', async (req, res) => {
    // look for the filename
    let fileBool = controller.findFile({
        filename:req.params.filename
    });
    if (fileBool = true) {
        // query all the registered clients for
        let clients = await controller.getClients();
        for (let i = 0; i < clients.length; i++) {
            // send a req to each client
            // await got.get(clients[i]);
            console.log(clients[i]);
        }
    } else {
        res.status(404);
        res.send('Cannot find file: ' + file.filename);
    }
    // if we have the file
        // query the
        // put it back together
        // send it back
    // if not,
        // send a 404
        // tell them we dont have it
})

module.exports = router;
