var ansi = require("ansi"),
  cursor = ansi(process.stdout),
  summary = "";

var Printer = {
  cursor: cursor,

  begin: (msg1, msg2) => {
  },

  finishGreen: msg1 => {
  },

  finishRed: msg1 => {
  },

  printError: msg => {
    cursor.red();
    console.log(msg);
    cursor.reset();
  }
};

module.exports = Printer;
