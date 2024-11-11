#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int arr[MAX];
    int front, rear;
} ArrayQueue;

void initArrayQueue(ArrayQueue* q) {
    q->front = q->rear = -1;
}

int isFullArrayQueue(ArrayQueue* q) {
    return (q->front == (q->rear + 1) % MAX);
}

int isEmptyArrayQueue(ArrayQueue* q) {
    return (q->front == -1);
}

void enqueueArray(ArrayQueue* q, int value) {
    if (isFullArrayQueue(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmptyArrayQueue(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = value;
    printf("Enqueued %d (Array)\n", value);
}

void dequeueArray(ArrayQueue* q) {
    if (isEmptyArrayQueue(q)) {
        printf("Queue underflow\n");
        return;
    }
    printf("Dequeued %d (Array)\n", q->arr[q->front]);
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void displayArrayQueue(ArrayQueue* q) {
    if (isEmptyArrayQueue(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements (Array):\n");
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("%d\n", q->arr[i]);
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} LinkedListQueue;

void initLinkedListQueue(LinkedListQueue* q) {
    q->front = q->rear = NULL;
}

int isEmptyLinkedListQueue(LinkedListQueue* q) {
    return q->front == NULL;
}

void enqueueLinkedList(LinkedListQueue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    if (isEmptyLinkedListQueue(q)) {
        newNode->next = newNode;
        q->front = q->rear = newNode;
    } else {
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued %d (Linked List)\n", value);
}

void dequeueLinkedList(LinkedListQueue* q) {
    if (isEmptyLinkedListQueue(q)) {
        printf("Queue underflow\n");
        return;
    }
    Node* temp = q->front;
    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
        q->rear->next = q->front;
    }
    printf("Dequeued %d (Linked List)\n", temp->data);
    free(temp);
}

void displayLinkedListQueue(LinkedListQueue* q) {
    if (isEmptyLinkedListQueue(q)) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = q->front;
    printf("Queue elements (Linked List):\n");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

int main() {
    ArrayQueue arrayQueue;
    LinkedListQueue linkedListQueue;
    int queueType, choice, value;

    printf("Choose queue type:\n1. Array-based circular queue\n2. Linked list-based circular queue\n");
    scanf("%d", &queueType);

    if (queueType == 1) {
        initArrayQueue(&arrayQueue);
    } else if (queueType == 2) {
        initLinkedListQueue(&linkedListQueue);
    } else {
        printf("Invalid queue type\n");
        return 0;
    }

    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                if (queueType == 1) {
                    enqueueArray(&arrayQueue, value);
                } else if (queueType == 2) {
                    enqueueLinkedList(&linkedListQueue, value);
                }
                break;
            case 2:
                if (queueType == 1) {
                    dequeueArray(&arrayQueue);
                } else if (queueType == 2) {
                    dequeueLinkedList(&linkedListQueue);
                }
                break;
            case 3:
                if (queueType == 1) {
                    displayArrayQueue(&arrayQueue);
                } else if (queueType == 2) {
                    displayLinkedListQueue(&linkedListQueue);
                }
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
