const { execSync } = require("child_process");

if (process.argv[2]) {
    execSync("git add -A");
    try {
        execSync(`git commit -m "${process.argv[2]}"`);
    } catch(err) {
        console.error("Error committing changes:", err);
        process.exit(1);
    }
    execSync("git push -u origin main --force");
} else {
    console.log("Please provide a commit message.");
}