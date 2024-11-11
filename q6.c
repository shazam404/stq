#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isEmptyQueue(Queue* q) {
    return q->front == -1;
}

int isFullQueue(Queue* q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue* q, int value) {
    if (isFullQueue(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmptyQueue(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->arr[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmptyQueue(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

int peekQueue(Queue* q) {
    if (!isEmptyQueue(q)) {
        return q->arr[q->front];
    }
    return -1;
}

typedef struct {
    Queue q1, q2;
} Stack;

void initStack(Stack* s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

int isEmptyStack(Stack* s) {
    return isEmptyQueue(&s->q1);
}

void push(Stack* s, int value) {
    enqueue(&s->q2, value);
    while (!isEmptyQueue(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
    printf("Pushed %d\n", value);
}

void pop(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack underflow\n");
        return;
    }
    printf("Popped %d\n", dequeue(&s->q1));
}

void displayStack(Stack* s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = s->q1.front; i <= s->q1.rear; i++) {
        printf("%d ", s->q1.arr[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initStack(&s);
    int choice, value;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                displayStack(&s);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
