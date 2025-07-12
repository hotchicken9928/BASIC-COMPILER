#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void"
};

int isKeyword(char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
        ch == '<' || ch == '>' || ch == '!' || ch == '&' || ch == '|') {
        return 1;
    }
    return 0;
}

void analyzeFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char ch;
    char buffer[100];
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            buffer[index++] = ch;
        } else {
            if (index != 0) {
                buffer[index] = '\0';
                if (isKeyword(buffer)) {
                    printf("Token: %-10s Type: Keyword\n", buffer);
                } else if (isdigit(buffer[0])) {
                    printf("Token: %-10s Type: Constant\n", buffer);
                } else {
                    printf("Token: %-10s Type: Identifier\n", buffer);
                }
                index = 0;
            }

            if (isOperator(ch)) {
                char next = fgetc(file);
                if ((ch == '=' || ch == '!' || ch == '<' || ch == '>') && next == '=') {
                    printf("Token: %-10s Type: Operator\n", (char[]){ch, next, '\0'});
                } else if ((ch == '&' && next == '&') || (ch == '|' && next == '|')) {
                    printf("Token: %-10s Type: Operator\n", (char[]){ch, next, '\0'});
                } else {
                    ungetc(next, file);
                    printf("Token: %-10c Type: Operator\n", ch);
                }
            }
        }
    }

    if (index != 0) {
        buffer[index] = '\0';
        if (isKeyword(buffer)) {
            printf("Token: %-10s Type: Keyword\n", buffer);
        } else if (isdigit(buffer[0])) {
            printf("Token: %-10s Type: Constant\n", buffer);
        } else {
            printf("Token: %-10s Type: Identifier\n", buffer);
        }
    }

    fclose(file);
}

int main() {
    char filename[100];
    printf("Enter input filename: ");
    scanf("%s", filename);
    analyzeFile(filename);
    return 0;
}

