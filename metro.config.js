// Learn more https://docs.expo.io/guides/customizing-metro
const { getDefaultConfig } = require('expo/metro-config');

const path = require('path');
const root = path.join(__dirname, '../react-native-android-encoder/');

/** @type {import('expo/metro-config').MetroConfig} */
// const config = getDefaultConfig(__dirname);
const config = getDefaultConfig(__dirname);
config.watchFolders = [root];

module.exports = config;
