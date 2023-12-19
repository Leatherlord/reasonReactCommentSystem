const path = require('path');

module.exports = {
  mode: 'development',
  entry: './_build/default/src/output/src/ReactApp.js',
  output: {
    path: path.resolve(__dirname, 'public'),
    publicPath: "/",
  },
  devServer: {
    open: true,
    historyApiFallback: true,
  },
};