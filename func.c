#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "symbol_table.h"

int main() {
    FILE *inputFile, *outputFile;
    Token token;
    int terminateIdentification = 0;  

    inputFile = fopen("sample.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening sample.txt");
        return 1;
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error creating output.txt");
        fclose(inputFile);
        return 1;
    }

    initialize_symbol_table();

    // Initialize the lexer
    initialize_lexer(inputFile);
    fprintf(outputFile,"------Expected Outcome------\n");
    fprintf(outputFile,"Lexer             Token\n");
    fprintf(outputFile,"----------------------------\n");

    do {
        token = next_token(inputFile);

        if (terminateIdentification) {  
            break;
        }

        switch (token.type) {
            case TOKEN_ERROR:
                fprintf(outputFile, "Error: Invalid token '%s' found.\n", token.value);
                break;
            case TOKEN_IDENTIFIER:
                if (find_symbol(token.value) == NULL) {
                    insert_symbol(token.value, TOKEN_IDENTIFIER); 
                }
                fprintf(outputFile, "\"%s\"            identifier\n", token.value);
                break;
            case TOKEN_LITERAL:
                fprintf(outputFile, "\"%d\"               literal\n", token.literalValue);
                break;
            case TOKEN_BOOLEAN_LITERAL:
                fprintf(outputFile, "\"%c\"               literal(Boolean)\n", token.boolValue);
                break;
            case TOKEN_KEYWORD:
                fprintf(outputFile, "\"%s\"             keyword\n", token.value);
                break;
            case TOKEN_OPERATOR:
                fprintf(outputFile, "\"%s\"             operator\n", token.value);
                break;
            case TOKEN_PUNCTUATOR:
                fprintf(outputFile, "\"%s\"             punctuator\n", token.value);
                break;
            case TOKEN_FUN:
                fprintf(outputFile, "\"%s\"             fun\n", token.value);
                break;
            case TOKEN_NAT:
                fprintf(outputFile, "\"%s\"             nat\n", token.value);
                break;
            case TOKEN_ARROW:
                fprintf(outputFile, "\"%s\"              ->\n", token.value);
                break;
            case TOKEN_QUESTION:
                fprintf(outputFile, "\"%s\"               ?\n", token.value);
                break;
            case TOKEN_PLUS:
                fprintf(outputFile, "\"%s\"               +\n", token.value);
                break;
            case TOKEN_COLON:
                fprintf(outputFile, "\"%s\"               :\n", token.value);
                break;
            case TOKEN_SEMICOLON:
                fprintf(outputFile, "\"%s\"               ;\n", token.value);
                break;
            case TOKEN_EQUAL:
                fprintf(outputFile, "\"%s\"               =\n", token.value);
                break;
            case TOKEN_UNKNOWN:
                fprintf(outputFile, "\"%s\"               Lexical error\n", token.value);
                terminateIdentification = 1;  
                break;
        }

    } while (token.type != TOKEN_EOF);

    fprintf(outputFile,"----------------------------\n");
    fclose(inputFile);
    fclose(outputFile);

    printf("Analysis complete. Check output.txt for results.\n");

    return 0;
}
