const fs = require("fs");
const { spawnSync } = require("child_process");

if (process.argv[2] === "init") {
    fs.writeFileSync("./settings.co.json", `{
    "src": "./index.co"
}`);
} else if (process.argv[2] === "run") {
    if (!fs.existsSync("./settings.co.json")) {
        console.log(`
${'\x1b[31m'}Error: Missing Initialization${'\x1b[0m'}

${'\x1b[33m'}It looks like the initialization step has not been completed.${'\x1b[0m'}

${'\x1b[36m'}To get started, please run the following command:${'\x1b[0m'}
${'\x1b[32m'}co init${'\x1b[0m'}

${'\x1b[33m'}This will create the necessary configuration file for your project.${'\x1b[0m'}
${'\x1b[36m'}Once initialization is complete, you can run the settings using:${'\x1b[0m'}
${'\x1b[32m'}co run${'\x1b[0m'}
        `);
        process.exit(1);        
    }
    let settings = JSON.parse(fs.readFileSync("./settings.co.json", "utf-8"));
    
    const coPath = "C:\\Users\\HP\\Downloads\\A programming language\\src\\scripts\\co.bat";
    const srcPath = settings['src'];
    
    const result = spawnSync(coPath, [srcPath], { stdio: 'inherit' });
    
    if (result.error) {
        console.error(`Error executing command: ${result.error.message}`);
        process.exit(1);
    }
} else {
    console.error("Invalid command. Use 'init' to create a settings.co.json file.");
    process.exit(1);
}