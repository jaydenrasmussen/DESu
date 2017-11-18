// J. Ramussen 2017

const reqIP = require('request-ip');
const fs = require('fs-extra');
const hasha = require('hasha');
const execa = require('execa');

module.exports = {
    getIP,
    savefilename,
    findFile,
    getClients,
    splitFile,
    sendToClients,
    encryptFile
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
    await fs.rename('./uploads/' + file, './uploads/' + current[file]);
    return current[file];
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

async function splitFile(filename) {
    // find number of clients
    let clients = await getClients();
    clients = clients.length;
    // Pass the length and the filename
    await execa.shell(
        'uploads/fileIO ' +
            './uploads/' +
            filename +
            '.enc ' +
            clients +
            ' split/' +
            filename
    );
}

async function getClients() {
    if (fs.pathExistsSync('./clients.json')) {
        let clients = await fs.readJson('./clients.json');
        return clients;
    } else {
        return null;
    }
}

async function sendToClients(filename) {
    let clients = await getClients();
    for (let i = 0; i < clients.length; i++) {
        await execa(
            'http -f POST http://localhost:3000/file/' +
                filename +
                i +
                ' hash@./split/' +
                filename +
                '/' +
                filename +
                i
        );
    }
}
async function genKeys() {
    return execa.shell('./enc/bitcrypt -g -b 2048 -p ./enc/ ')
        .catch(console.log);
}
async function encryptFile(filename) {
    // // generate keys
    await genKeys();
    // // perform encryption
    await execa.shell(
        './enc/bitcrypt -e -f ./uploads/' + filename + ' -k ./enc/public.pem'
    );
    await fs.remove('./uploads/' + filename);
    await fs.remove('./enc/public.pem');
    // // store the key
    await fs.move('./enc/private.pem', './keys/' + filename + '.key');
}
