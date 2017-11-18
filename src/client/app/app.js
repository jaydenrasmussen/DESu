// J. Rasmussen 2017

const express = require('express');
const app = express();
const http = require('http');

const route = require('../routes/app.route');

module.exports = (() => {
    let port = 3001;
    app.set('port', port);

    app.use('/', route);

    return Promise.resolve()
        .then(() => http.createServer(app))
        .then(server => server.listen(port))
        .then(() => console.log('App listening on port: ' + port))
        .catch(console.log);
})();
