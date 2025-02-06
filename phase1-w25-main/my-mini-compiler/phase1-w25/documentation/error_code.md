# Lexer Error Codes and Handling

New error codes were added to allow handling of string and comment errors

**ERROR_NONE**
- No errors (default state)

**ERROR_INVALID_CHAR**
- Detection: When the lexer encounters an unknown character that is not part of any valid token
- Recovery: Lexer reports the invalid character and continues scanning the next character
  - Type: Panic Mode 

**ERROR_INVALID_NUMBER**
- Detection: When a number contains invalid characters, like letters mixed with digits
- Recovery: The lexer will return an error token and skip to the next valid token
  - Type: Panic Mode 
  
**ERROR_CONSECUTIVE_OPERATORS**
- Detection: When the lexer finds two consecutive operators that are not part of a valid compound operator
- Recovery: The lexer will report the error and skip the second operator
  - Type: Panic Mode 

**ERROR_UNTERMINATED_COMMENT**
- Detection: When EOF is reached before a closing comment indicator (*/)
- Recovery: Lexer will skip to EOF after error detection
  - Type: Panic Mode 

**ERROR_UNTERMINATED_STRING**
- Detection: When EOF is reached before a closing double quote ("), indicating unfinished string literal
- Recovery: Lexer will skip to EOF and report an unterminated string
  - Type: Panic Mode 

**ERROR_INVALID_IDENTIFIER**
- Detection: When an identifier starts with an invalid character
- Recovery: The lexer will report the invalid identifier and skip the invalid character
  - Type: Panic Mode 

**ERROR_STRING_BUFFER_OVERFLOW**
- Detection: When a string literal exceeds the maximum buffer size
- Recovery: The lexer will report a buffer overflow error and then skip the entire string
  - Type: Panic Mode 