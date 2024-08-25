# Function execution
```
<Function name>(<Variable | String | Char | Boolean | Integer | Array>);
```

# Function creation
```
func <Function name>(<Arguments seperated by commas>) {<Code to execute>}
```

# If statement
```
if (<Check something that returns>) {<Code to execute if true or 0>} alt if (<Check something that returns>) {<Code to execute if true or 0>} alt {<code to execute if false or 1>}
```

# Switch Case
```
switch (<Variable | String | Char | Boolean | Integer>) {
    case (<Value of variable to check>) {
        <Code to run if case is correct>
        break;

    }
    case (<Another value of variable to check>) {
        <Code to run if case is correct>
        break;
    }
}
```

# While
```
while (<Check something that returns>) {<Code to execute if true or 0>}
```

# Variables
## Declaration of imports
```
decl <Variable name> = <Import name in a String type>;
```
## Declaration of imports in a scope
```
decl let <Variable name> = <Import name in a String type>;
```
## Declaration of variables in scopes
```
let <Variable name> = <Variable | String | Char | Boolean | Integer | Array>;
```
## Const declaration
```
const <Variable name> = <Variable | String | Char | Boolean | Integer | Array>;
```

## Try Catch
```
try {<Code to try>} catch (<Name of scope variable>) {<Code to run instead of the error>}
```