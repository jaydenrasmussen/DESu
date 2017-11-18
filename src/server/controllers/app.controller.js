// J. Ramussen 2017

const reqIP = require('request-ip');
const fs = require('fs-extra');
const hasha = require('hasha');

module.exports = {
    getIP,
    savefilename,
    findFile
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

async function findFile(file) {
    let current = {};
    if (fs.pathExistsSync('./uploads/uploads.json')) {
        current = await fs.readJson('./uploads/uploads.json');
    }
    if (current[file.filename] === undefined) {
        return false;
    } else {
        // return file
        return true;
    }
}

async function getClients() {
    if (fs.pathExistsSync('./clients.json')) {
        let clients = await fs.readJson('./clients.json');
        return clients;
    } else {
        return null;
    }
}
