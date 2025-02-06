Design decisions:

Comments are ignored

Nested comments are not supported

Counter for counting new lines in a multi-line comment

Two-character lookahead for correct comment detection

Test cases: 

Inputs:

"123 + 456 - 789",

"int x = 42; y = x + 10;",

"123 ++ 456",

"x@ = 10;",

"\"Hello\"",

"/* comment */ x = 10; // line",

"123 + 456 - 789\n1 ++ 2",

"\"Lorem ipsum dolor sit amet, \nconsectetur adipiscing elit. Sed nunc orci, interdum at imperdiet ut, 
fringilla\"",

"\"This vallidates\tspacing escape\nsequences\"",

"\"String with \\\"quotes\\\"\"",

"\"Unterminated string",

"/* Unterminated comment\n"

Expected outputs:

"NUMBER 123, OPERATOR +, NUMBER 456, OPERATOR -, NUMBER 789",

"KEYWORD int, IDENTIFIER x, OPERATOR =, NUMBER 42, DELIMITER ;, IDENTIFIER y, OPERATOR =, IDENTIFIER x, OPERATOR +, NUMBER 10, DELIMITER ;",

"NUMBER 123, ERROR ++",

"IDENTIFIER x, ERROR @, OPERATOR =, NUMBER 10, DELIMITER ;",

"STRING \"Hello\"",

"IDENTIFIER x, OPERATOR =, NUMBER 10, DELIMITER ;",

"NUMBER 123, OPERATOR +, NUMBER 456, OPERATOR -, NUMBER 789, NUMBER 1, ERROR ++, NUMBER 2",

"ERROR String too Long",

"New Line operator",

"STRING \"String with \\\"quotes\\\"\"",

"ERROR Unterminated string",

"ERROR Unterminated comment"