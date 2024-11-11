#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int arr[MAX];
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

void push(Stack* s, int value) {
    if (!isFull(s)) {
        s->arr[++(s->top)] = value;
    }
}

int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1;
}

int evaluatePostfix(char* exp) {
    Stack s;
    initStack(&s);
    int i, op1, op2, result;
    
    for (i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');
        } else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (exp[i]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}

int main() {
    char exp[MAX];
    printf("Enter postfix expression: ");
    scanf("%s", exp);
    printf("Postfix evaluation result: %d\n", evaluatePostfix(exp));
    return 0;
}

// example:
// Postfix expression: 23*54*+
// Postfix evaluation result: 17
// 2 * 3 + 5 * 4 = 17