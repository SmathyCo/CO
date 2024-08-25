const { execSync } = require("child_process");

execSync("gcc -c ./src/lexer/lexer.c -o ./src/bin/lexer.o");
execSync("gcc -c ./src/entry/main.c -o ./src/bin/main.o");
execSync("gcc ./src/bin/lexer.o ./src/bin/main.o -o ./out/co.exe");