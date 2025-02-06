//error codes
ERROR_NONE
No errors (default)

ERROR_INVALID_CHAR
Detection: When the lexer encounters an unknown character that is not part of any valid token
Recovery: Lexer reports the invalid character and continues scanning the next character

ERROR_INVALID_NUMBER
Detection: When a number contains invalid characters, like letters mixed with digits
Recovery: The lexer will return an error token and skip to the next valid token

ERROR_CONSECUTIVE OPERATORS
Detection: When the lexer finds two consecutive operators that are not part of a valid compound operator 
Recovery: The lexer will report the error and skip the second operator

ERROR_UNTERMINATED_COMMENT
Detection: when EOF is reach before a closing comment indicator (*/)
Recovery: Lexer will skip to EOF after error detection

ERROR_UNTERMINATED_STRING
Detection: When EOF is reached before a closing double quote (“), indicating unfinished string literal
Recovery: Lexer will skip to EOF and report an unterminated string

ERROR_INVALID_IDENTIFIER
Detection: When an identifier starts with an invalid character 
Recovery: The lexer will report the invalid identifier and skip the invalid character

ERROR_STRING_BUFFER_OVERFLOW
Detection: When a string literal exceeds the maximum buffer size
Recovery: The lexer will report a buffer overflow error

