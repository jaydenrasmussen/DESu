// J. Ramussen 2017

const reqIP = require('request-ip');

module.exports = {
    getIP
}

function getIP(req, res) {
    const ip = reqIP.getClientIp(req);
    return {
        req: req,
        res: res,
        ip: ip
    }
}
