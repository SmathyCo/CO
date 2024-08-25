const { execSync } = require("child_process");

if (process.argv[2]) {
    let commitMessage = process.argv[2];

    if (/"/.test(commitMessage)) {
        console.error("Commit message contains double quotes, which is not allowed for security reasons.");
        process.exit(1);
    }

    try {
        execSync("git add -A");
        execSync(`git commit -m "${commitMessage}"`);
        execSync("git push -u origin main --force");
        console.log("Changes pushed successfully.");
    } catch (error) {
        console.error("An error occurred:", error.message);
        process.exit(1);
    }
} else {
    console.log("Please provide a commit message.");
}