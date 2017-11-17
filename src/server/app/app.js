// J. Rasmussen 2017
const express = require('express');
const app = express();
const http = require('http');

// routes
const route = require('../routes/app.route');

module.exports = (() => {
    // Port
    let port = 3000;
    app.set('port', port);
    // Routes
    app.use('/', route);
    // Start Server
    return Promise.resolve()
        .then(() => http.createServer(app))
        .then(server => server.listen(port))
        .then(() => console.log('App listening on port: ' + port))
        .catch(console.log);
})();
