// Immediately execute a function to process the data when the module is loaded
(function() {

    const fs = require("fs");
    const path = require("path");

    // Access data from global context or modify this to receive data differently
    const data = global.__lexerData; // Using a global variable for simplicity

    if (data) {
        
        // Making arrays for each code line & removing empty arrays of lines & spliting on } also disabling ; inside of {}
        let dataNextLine = data.replace(/\r\n/g, '').split(/\n;/).map(chunk => {
            const regex = /(?<=\})(?![^{}]*\{)/g;
            return chunk.split(regex).filter(array => array.length > 0);
        });

        // Lexer
        let tokens = [];
        for (let i = 0; i < dataNextLine.length; i++) {
            for (let i2 = 0; i2 < dataNextLine[i].length; i2++) {
                if (dataNextLine[i][i2].startsWith("function")) {
                    let cFunctionFirstSpace = dataNextLine[i][i2].indexOf(" ");
                    let cFunctionFirstOpenParen = dataNextLine[i][i2].indexOf("(");
                    let cFunctionName = dataNextLine[i][i2].substring(cFunctionFirstSpace + 1, cFunctionFirstOpenParen); // Getting the function name from the function declaration line
                    let cFunctionFirstClosingParen = dataNextLine[i][i2].indexOf(")");
                    let cFunctionParams = dataNextLine[i][i2].substring(cFunctionFirstOpenParen + 1, cFunctionFirstClosingParen).split(',').map(param => param.trim()); // Getting the function parameters from the function declaration line
                    let cFunctionOpeningBrace = dataNextLine[i][i2].indexOf("{");
                    let cFunctionClosingBrace = dataNextLine[i][i2].indexOf("}");
                    let cFunctionBody = dataNextLine[i][i2].substring(cFunctionOpeningBrace + 1, cFunctionClosingBrace);

                    tokens.push(
                        {
                            'Type': "functionCreation",
                            'Name': cFunctionName,
                            'Params': cFunctionParams,
                            'Body': cFunctionBody
                        }
                    )
                }

                let startParen = dataNextLine[i][i2].indexOf("("); // Getting where is the starting paren
                let endParen = dataNextLine[i][i2].indexOf(")"); // Getting where is the ending paren
                let firstBrace = dataNextLine[i][i2].indexOf("{");
                let secondBrace = dataNextLine[i][i2].indexOf("}");

                if (!(endParen >= startParen && endParen <= secondBrace)) {
                    if (endParen > startParen) { // This is so it doesn't scan )( instead of ()
                        if (typeof dataNextLine[i][i2] === 'string') {
                            let element = dataNextLine[i][i2];
                            if (startParen >= 0 && endParen <= element.length) {
                                let functionName = dataNextLine[i][i2].match(/^[a-z][a-z0-9]*/)[0];

                                if (functionName !== "function") {
                                    let functionValue = element.substring(startParen + 1, endParen);
                                    let functionType;
                                    if (functionValue.startsWith("'") && functionValue.endsWith("'") || functionValue.startsWith('"') && functionValue.endsWith('"')) {
                                        functionType = "string";
                                    } else if (/[0-9]/.test(functionValue)) {
                                        functionType = "integer";
                                    } else if (/true|false/.test(functionValue)) {
                                        functionType = "boolean";
                                    } else if (/[A-Za-z]/.test(functionValue)) {
                                        functionType = "variable";
                                    }
                                    if (functionType === undefined) {
                                        console.log(`
        ${'\x1b[31m'}Error: Function Type Undefined${'\x1b[0m'}
        
        ${'\x1b[33m'}Details:${'\x1b[0m'}
        Unable to find what type of value is inside the function.
        
        ${'\x1b[36m'}Example Fix:${'\x1b[0m'}
        ${'\x1b[32m'}  // Before${'\x1b[0m'}
        ${'\x1b[32m'}  ${functionName}(${functionValue}) // This could be undefined${'\x1b[0m'}
        
        ${'\x1b[32m'}  // After${'\x1b[0m'}
        ${'\x1b[32m'}  ${functionName}(1) // Assign it with a good type of value${'\x1b[0m'}
        ${'\x1b[32m'}
        /* Types of valid value type
        Boolean
        String
        Integer
        Variable
        */
        ${'\x1b[0m'}
                                        `);
                                        process.exit(1);
                                    }
                                    tokens.push({
                                        'Type': "FunctionExecution",
                                        'Name': functionName,
                                        'Value': functionValue,
                                        'ValueType': functionType
                                    });
                                }
                            } else {
                                console.log(`
    ${'\x1b[31m'}Error: Missing Parenthesis${'\x1b[0m'}
    
    ${'\x1b[33m'}Location: Line ${i + 1}
    
    ${'\x1b[31m'}A opening parenthesis '(' is missing. Please check the indicated position and ensure all parentheses are properly matched.${'\x1b[0m'}
    
    ${'\x1b[36m'}Example Fix:${'\x1b[0m'}
    ${'\x1b[32m'}  // Before${'\x1b[0m'}
    ${'\x1b[32m'}  print"Hello World");${'\x1b[0m'}
    ${'\x1b[32m'}  // After${'\x1b[0m'}
    ${'\x1b[32m'}  print("Hello World");${'\x1b[0m'}
                                    `);
                                process.exit(1);
                            }
                        }
                    } else {
                        console.log(`
    ${'\x1b[31m'}Error: Missing Parenthesis${'\x1b[0m'}
    
    ${'\x1b[33m'}Location: Line ${i + 1}
    
    ${'\x1b[31m'}A closing parenthesis ')' is missing. Please check the indicated position and ensure all parentheses are properly matched.${'\x1b[0m'}
    
    ${'\x1b[36m'}Example Fix:${'\x1b[0m'}
    ${'\x1b[32m'}  // Before${'\x1b[0m'}
    ${'\x1b[32m'}  print("Hello World";${'\x1b[0m'}
    ${'\x1b[32m'}  // After${'\x1b[0m'}
    ${'\x1b[32m'}  print("Hello World");${'\x1b[0m'}
                            `);
                            process.exit(1);
                        }
                    }
                }
                
            }
            console.log(tokens);
    } else {
        console.log("No data provided to lexer.");
    }
})();