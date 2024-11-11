#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
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

int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int checkBalancedBrackets(char* exp) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') {
            push(&s, exp[i]);
        } else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(&s) || !isMatchingPair(pop(&s), exp[i])) {
                return 0;
            }
        }
    }
    return isEmpty(&s);
}

int main() {
    char exp[MAX];
    printf("Enter the expression: ");
    scanf("%s", exp);

    if (checkBalancedBrackets(exp)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return 0;
}
