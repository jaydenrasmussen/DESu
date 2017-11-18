// J. Ramussen 2017

const fs = require('fs-extra');

module.exports = {
    getFiles
};
async function getFiles() {
    let files = await fs.readJson('./uploads/uploads.json');
    return files;
}
