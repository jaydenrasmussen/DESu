// J. Ramussen 2017

const express = require('express');
let router = express.Router();

const controller = require('../controllers/app.controller');

router.get('/', (req, res) => {
    res.status(200);
    return res.send('Hello World!');
});

router.get('/client/', (req, res) => {
    let obj = controller.getIP(req, res);
    res = obj.res
    return res.send(obj.ip);
})

module.exports = router;
