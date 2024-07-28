# CO: A New Programming Language

Welcome to CO, an open-source programming language that's currently in development!

## What is CO?

CO is an innovative programming language designed to unify various programming languages into a single, versatile platform. Our goal is to create a language that balances high-level readability with low-level control, offering a syntax that is intuitive and human-readable. Whether you're coding complex applications or scripting simple tasks, CO aims to provide a flexible environment that supports a wide range of programming needs.

## How Will CO Achieve This?

You might be wondering how CO will integrate multiple programming languages. Our approach involves using a powerful interpreter that dynamically handles different programming languages based on your requirements. When you need a compiler for specific tasks, you can easily switch configurations using `coe init` to adjust the `settings.co.json` file. This flexibility ensures that CO can adapt to various programming paradigms, making it a robust tool for diverse projects.

## How Are We Going to Make This Performant?

To ensure CO delivers high performance, we are adopting a modular approach. The language will support a "plugins" folder where you can add and manage different components. Simply place the relevant files into this folder, and you're set! This modular system allows you to include only the features and functionalities you need, minimizing overhead and optimizing performance.

## Why Use Node.js as a Backend?

We chose Node.js for our backend due to its seamless integration with the C programming language. Since Node.js itself is built on C, leveraging it allows us to take advantage of its performance and simplicity. This choice streamlines our development process, enabling more efficient interaction between CO and Node.js, and ultimately enhancing the overall system's effectiveness.

# How to install everything?

1. Open a command prompt as administrator.
2. Navigate inside the ./src/ folder of the project.
3. Run the ./index.bat file that is inside the ./src/ folder.
4. It should open a command prompt window and you just need to wait for it to install the dependencies.
5. Close the command prompts you are using and reopen the ones that you will use for the project.
6. Now you can use `co ./index.co` to run a co file!
