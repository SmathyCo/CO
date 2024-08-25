const { execSync } = require("child_process");

if (process.argv[2]) {
    const commitMessage = process.argv[2].replace(/"/g, '\\"');
    
    execSync("git add -A");
    execSync(`git commit -m "${commitMessage}"`);
    execSync("git push -u origin main --force");
} else {
    console.log("Please provide a commit message.");
}