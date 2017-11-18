// J. Ramussen 2017

const fs = require('fs-extra');

module.exports = {
    getFiles,
    saveUploadData,
    moveUploadData
};
async function getFiles() {
    let files = {};

    if (fs.pathExistsSync('./uploads/uploads.json')) {
        files = await fs.readJson('./uploads/uploads.json');
    }
    return files;
}
async function saveUploadData(filename, num) {
    let uploads = {};
    if (fs.pathExistsSync('./upload/uploads.json')) {
        uploads = await fs.readJson('./uploads/');
    }
    uploads[filename] = num;
    await fs.writeJson('./uploads/uploads.json', uploads);
}
async function moveUploadData(filename, num) {
    await fs.ensureDir('./uploads/' + filename);
    await fs.move('./uploads/' + num, './uploads/' + filename + '/' + num);
}
