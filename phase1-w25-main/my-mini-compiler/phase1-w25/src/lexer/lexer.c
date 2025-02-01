/* lexer.c */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../../include/tokens.h"

// Line tracking
static int current_line = 1;
static char last_token_type = 'x'; // For checking consecutive operators

/* Print error messages for lexical errors */
void print_error(ErrorType error, int line, const char *lexeme) {
    printf("Lexical Error at line %d: ", line);
    switch (error) {
        case ERROR_INVALID_CHAR:
            printf("Invalid character '%s'\n", lexeme);
            break;
        case ERROR_INVALID_NUMBER:
            printf("Invalid number format\n");
            break;
        case ERROR_CONSECUTIVE_OPERATORS:
            printf("Consecutive operators not allowed\n");
            break;
        case ERROR_UNTERMINATED_COMMENT:
            printf("Unterminated comment, check EOL\n");
            break;
        default:
            printf("Unknown error\n");
    }
}

/* Print token information
 *
 *  TODO Update your printing function accordingly
 */

void print_token(Token token) {
    if (token.error != ERROR_NONE) {
        print_error(token.error, token.line, token.lexeme);
        return;
    }

    printf("Token: ");
    switch (token.type) {
        case TOKEN_NUMBER:
            printf("NUMBER");
            break;
        case TOKEN_OPERATOR:
            printf("OPERATOR");
            break;
        case TOKEN_EOF:
            printf("EOF");
            break;
        default:
            printf("UNKNOWN");
    }
    printf(" | Lexeme: '%s' | Line: %d\n",
           token.lexeme, token.line);
}

/* Get next token from input */
Token get_next_token(const char *input, int *pos) {
    Token token = {TOKEN_ERROR, "", current_line, ERROR_NONE};
    char c;

    // Skip whitespace and track line numbers
    while ((c = input[*pos]) != '\0' && (c == ' ' || c == '\n' || c == '\t')) {
        if (c == '\n') {
            current_line++;
        }
        (*pos)++;
    }

    if (input[*pos] == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    c = input[*pos];

    // TODO: Add comment handling here
    // Added by Lucy
    // Handle comments
    if (c == "/" && input[*pos + 1] == "/") {
        while (input[*pos] != '\n' && input[*pos] != '\0') {
            (*pos)++; // skip everything in the comment
        }
        return get_next_token(input, pos); // get next token
    }

    // Block comment handling by yash
    if (c = '/' && input [*pos + 1] == '*') { // start of a block comment, edge case noted- ensure only enter block when you have sequence /*.
        (*pos) += 2; // skip the opening comment
        int comment_check = 0; // here we can simply make a flag to check if the comment is closed or not

        // keep going until we reach the end of comment
        while (input[*pos] != '\0') {
            if (input[*pos] == '\n') {
                current_line++;
            }
            if (input[*pos] == '*' && input[*pos + 1] == '/') {
                (*pos) += 2; // skip the closing comment
                comment_check = 1;
                break;
            }
            (*pos)++;
        }
        if (comment_check == 0) {
            token.error = ERROR_UNTERMINATED_COMMENT;
            return token;
            }
        return get_next_token(input, pos); // grab next token after the comment
    }
    // end yash block comment stuff

    // Handle numbers
    if (isdigit(c)) {
        int i = 0;
        do {
            token.lexeme[i++] = c;
            (*pos)++;
            c = input[*pos];
        } while (isdigit(c) && i < sizeof(token.lexeme) - 1);

        token.lexeme[i] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // TODO: Add keyword and identifier handling here
    // Hint: You'll have to add support for keywords and identifiers, and then string literals
    // Added by Lucy
    // Handle keywords and identifiers
    if (isalpha(c) || c == '_') { // variable names start with a letter or _
        int i = 0;
        do {
            token.lexeme[i++] = c;
            (*pos)++;
            c = input[*pos];
        } while ((isalnum(c) || c == '_') && i < sizeof(token.lexeme) - 1);
        token.lexeme[i] = '\0';
        // check for keyword
        if (strcmp(token.lexeme, "if") == 0 ||
            strcmp(token.lexeme, "repeat") == 0 ||
            strcmp(token.lexeme, "until") == 0) {
            token.type = TOKEN_KEYWORD;
            } else {
                token.type = TOKEN_IDENTIFIER;
            }
        return token;
    }


    // TODO: Add string literal handling here
    // Added by Lucy
    // Handle string literals
    if (c == '"') {
        int i = 0;
        (*pos)++; // skip opening quote
        c = input[*pos];
        while (c != '"' && c != '\0' && i < sizeof(token.lexeme) - 1) {
            token.lexeme[i++] = c;
            (*pos)++;
            c = input[*pos];
        }
        // check for closing quote
        if (c == '"') {
            token.lexeme[i] = '\0';
            token.type = TOKEN_STRING;
            (*pos)++;
        } else {
            token.error = ERROR_UNTERMINATED_STRING;
        }
        return token;
    }

    // Handle operators
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') { // *, /, % added by Lucy
        // if (last_token_type == 'o') {
        if (input[*pos + 1] == c) {
            // Check for consecutive operators
            token.error = ERROR_CONSECUTIVE_OPERATORS;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            (*pos)++;
            return token;
        }
        token.type = TOKEN_OPERATOR;
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        last_token_type = 'o';
        (*pos)++;
        return token;
    }

    // Added by Lucy
    // Handle assignment and comparison operators
    if (c == '=') {
        token.type = TOKEN_ASSIGN;
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        (*pos)++;

        // Check for "==" (comparison operator)
        if (input[*pos] == '=') {
            token.type = TOKEN_OPERATOR;
            token.lexeme[1] = '=';
            token.lexeme[2] = '\0';
            (*pos)++;
        }

        return token;
    }


    // TODO: Add delimiter handling here
    // Added by Lucy
    // Handle delimiters
    if (strchr(";(),{}", c)) {
        token.type = TOKEN_DELIMITER;
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        (*pos)++;
        return token;
    }


    // Handle invalid characters
    token.error = ERROR_INVALID_CHAR;
    token.lexeme[0] = c;
    token.lexeme[1] = '\0';
    (*pos)++;
    return token;
}

// This is a basic lexer that handles numbers (e.g., "123", "456"), basic operators (+ and -), consecutive operator errors, whitespace and newlines, with simple line tracking for error reporting.

int main() {
    const char *input = "123 + 456 - 789\n1 ++ 2"; // Test with multi-line input
    int position = 0;
    Token token;

    printf("Analyzing input:\n%s\n\n", input);

    do {
        token = get_next_token(input, &position);
        print_token(token);
    } while (token.type != TOKEN_EOF);

    return 0;


    // comment tests [yash]
    const char *input = 
    "// Line comment\n"
    "123\n"
    "/* comment block */-456\n"
    "/* Unterminated comment\n"
    "789";
    int position = 0;
    Token token;

    printf("testing comments:\n");
    do {
        token = get_next_token(input, &position);
        print_token(token);
    } while (token.type != TOKEN_EOF);

}
