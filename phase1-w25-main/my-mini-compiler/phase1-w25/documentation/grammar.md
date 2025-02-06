# Grammar Rules

## Keywords

**if, int, repeat, until**
- Core control flow and variable declaration keywords used in the language
- Must be written exactly as specified, case-sensitive

## Identifiers
- Must start with a letter (a-z, A-Z)
- Can contain letters and digits (0-9) after the first character
- Used for variable names, function names, and other user-defined elements
- Example: `myVariable`, `count1`, `userName`

## Numbers
- Consists of one or more digits (0-9)
- Represents integer values in the language
- Example: `42`, `100`, `5280`

## Operators

### Arithmetic Operators
- `+` : Addition
- `-` : Subtraction
- `*` : Multiplication
- `/` : Division

### Assignment Operator
- `=` : Assigns a value to a variable
- Example: `x = 5`

## String Literals
- Must be enclosed in double quotes (`""`)
- Supports escape characters:
  - `\"` : Double quote
  - `\\` : Backslash
  - `\n` : Newline
  - `\t` : Tab Space
- Example: `"Hello\nWorld"`, `"Use \"quotes\" here"`

## Delimiters
- `:` : Used for declarations and labels
- `{` and `}` : Block delimiters
- `(` and `)` : Expression grouping
- Used to structure and organize code elements

## Comments

### Single-line Comments
- **Not Tokenized**
- Begin with `//`
- Continue until end of line
- Example: `// This is a single-line comment`

### Multi-line Comments
- **Not Tokenized**
- Begin with `/**`
- End with `**/`
- Can span multiple lines
- Example:
  ```
  /**
  This is a
  multi-line comment
  **/
  ```