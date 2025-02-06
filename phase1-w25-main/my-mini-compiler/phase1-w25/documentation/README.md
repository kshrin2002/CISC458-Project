# Design Decisions

- **Comment Handling**
  - Comments are ignored in tokenization
  - Nested comments are not supported
  - Maintains counter for newlines in multi-line comments
  - Uses two-character lookahead for accurate comment detection

- **String Handling**
  - Each string must start with and be terminated by `"`
  - It supports escape characters but `\n` & `\t` are deafultly handled by lexer and space is displayed in token
  - Strings with quotes and backslash are displayed with their esacpe sequences
  - If string overflows the buffer error is displayed and panic mode used skipping string
  - If string overflows & unterminated defaults to unterminated error
  - Handles unterminated strings by looking for closing quotes

- **Error Codes** and decesions can be found in `error_code.md`
- **Grammer Rules** and decesions can be found in `grammar_rules.md`

### Token Types Added:

The lexer supports the following added token types from the base:

| Token Type | Description | Examples |
|------------|-------------|----------|
| `TOKEN_IDENTIFIER` | Variable and function names | `x`, `varName`, `myFunction` |
| `TOKEN_ASSIGN` | Assignment operator | `=` |
| `TOKEN_KEYWORD` | Reserved language keywords | `if`, `repeat`, `while` |
| `TOKEN_STRING` | String literals | `"hello"`, `"world"` |
| `TOKEN_DELIMITER` | Syntax delimiters | `,`, `;`, `{`, `}`, `(`, `)` |
| `TOKEN_COMMENT` | Single and multi-line comments | `// comment`, `/* block comment */` |

</br></br>

# Test Cases and Expected Outputs

## Test 1: Basic Arithmetic
- Input: `"123 + 456 - 789"`
- Output: `"NUMBER 123, OPERATOR +, NUMBER 456, OPERATOR -, NUMBER 789"`

## Test 2: Variable Declaration and Assignment
- Input: `"int x = 42; y = x + 10;"`
- Output: `"KEYWORD int, IDENTIFIER x, OPERATOR =, NUMBER 42, DELIMITER ;, IDENTIFIER y, OPERATOR =, IDENTIFIER x, OPERATOR +, NUMBER 10, DELIMITER ;"`

## Test 3: Invalid Consecutive Operators
- Input: `"123 ++ 456"`
- Output: `"NUMBER 123, ERROR ++"`

## Test 4: Invalid Identifier Character
- Input: `"x@ = 10;"`
- Output: `"IDENTIFIER x, ERROR @, OPERATOR =, NUMBER 10, DELIMITER ;"`

## Test 5: Basic String
- Input: `"\"Hello\""`
- Output: `"STRING \"Hello\""`

## Test 6: Comments
- Input: `"/* comment */ x = 10; // line"`
- Output: `"IDENTIFIER x, OPERATOR =, NUMBER 10, DELIMITER ;"`

## Test 7: Multi-line Input with Error
- Input: `"123 + 456 - 789\n1 ++ 2"`
- Output: `"NUMBER 123, OPERATOR +, NUMBER 456, OPERATOR -, NUMBER 789, NUMBER 1, ERROR ++, NUMBER 2"`

## Test 8: String Buffer Overflow
- Input: `"\"Lorem ipsum dolor...\""`
- Output: `"ERROR String too Long"`

## Test 9: Escape Sequence Validation
- Input: `"\"This vallidates\tspacing escape\nsequences\""`
- Output: `"New Line operator"`

## Test 10: Escaped Quotes
- Input: `"\"String with \\\"quotes\\\"\""`
- Output: `"STRING \"String with \\\"quotes\\\"\""`

## Test 11: Unterminated String
- Input: `"\"Unterminated string"`
- Output: `"ERROR Unterminated string"`

## Test 12: Unterminated Comment
- Input: `"/* Unterminated comment\n"`
- Output: `"ERROR Unterminated comment"`