const { execSync } = require("child_process");

if (process.argv[2]) {
    execSync("git add -A");
    execSync(`git commit -m "${process.argv[2]}"`);
    execSync("git push -u origin main --force");
} else {
    console.log("Please provide a commit message.");
}