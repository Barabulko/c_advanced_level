#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int priority(char ch) {
    if (ch == '^') return 3;
    else if (ch == '&' || ch == '|') return 2;
    return 1;
}

void infixToPostfix(char* infix) {
    int i, k;
    char stack[MAX_SIZE], postfix[MAX_SIZE];
    int top = -1;

    for (i = 0, k = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (ch == ' ') {
            continue;
        } else if (ch == '(') {
            stack[++top] = ch;
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
                postfix[k++] = ' ';
            }
            if (top != -1) {
                top--;
            }
        } else if (ch == '&' || ch == '|' || ch == '^') {
            while (top != -1 && priority(stack[top]) >= priority(ch)) {
                postfix[k++] = stack[top--];
                postfix[k++] = ' ';
            }
            stack[++top] = ch;
        } else {
            while (infix[i] >= '0' && infix[i] <= '9') {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        }
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';

    printf("%s\n", postfix);
}

int main() {
    char infix1[] = "( 3 & 5 ) ^ 4 | 9";
    char infix2[] = "8 ^ 2 & 5 | ( 6 & 1 )";

    printf("Данные на вход: %s, Данные на выход: ", infix1);
    infixToPostfix(infix1);

    printf("Данные на вход: %s, Данные на выход: ", infix2);
    infixToPostfix(infix2);

    return 0;
}