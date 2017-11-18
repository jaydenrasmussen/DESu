// J. Ramussen 2017

const reqIP = require('request-ip');
const fs = require('fs-extra');
const hasha = require('hasha');

module.exports = {
    getIP,
    savefilename
};

function getIP(req, res) {
    const ip = reqIP.getClientIp(req);
    return {
        req: req,
        res: res,
        ip: ip
    };
}

async function savefilename(file) {
    let current = {};
    if (fs.pathExistsSync('./uploads/uploads.json')) {
        current = await fs.readJson('./uploads/uploads.json');
    }
    current[file] = hasha(file);
    await fs.writeJson('./uploads/uploads.json', current);
}
