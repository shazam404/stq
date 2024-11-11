#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, char value) {
    if (!isFull(s)) {
        s->arr[++(s->top)] = value;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1;
}

char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->arr[s->top];
    }
    return -1;
}

int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[j++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

void infixToPrefix(char* infix, char* prefix) {
    Stack s;
    initStack(&s);
    int len = strlen(infix);
    char reversedInfix[MAX], reversedPrefix[MAX];
    int i, j = 0;
    for (i = len - 1; i >= 0; i--) {
        if (infix[i] == '(') {
            reversedInfix[j++] = ')';
        } else if (infix[i] == ')') {
            reversedInfix[j++] = '(';
        } else {
            reversedInfix[j++] = infix[i];
        }
    }
    reversedInfix[j] = '\0';
    infixToPostfix(reversedInfix, reversedPrefix);
    len = strlen(reversedPrefix);
    for (i = len - 1, j = 0; i >= 0; i--) {
        prefix[j++] = reversedPrefix[i];
    }
    prefix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    return 0;
}

// example of infix expression: (A+B)*C
// expected postfix expression: AB+C*
// expected prefix expression: *+ABC
