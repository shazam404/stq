#include <stdio.h>
#include <stdlib.h>

#define MAX 100 

typedef struct {
    int *arr;
    int top;
    int maxSize; 
} ArrayStack;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} LinkedListStack;

void initArrayStack(ArrayStack* s, int size) {
    s->arr = (int *)malloc(size * sizeof(int)); 
    s->top = -1;
    s->maxSize = size;
}

int isFullArrayStack(ArrayStack* s) {
    return s->top == s->maxSize - 1;
}

int isEmptyArrayStack(ArrayStack* s) {
    return s->top == -1;
}

void pushArrayStack(ArrayStack* s, int value) {
    if (isFullArrayStack(s)) {
        printf("Stack overflow\n");
    } else {
        s->arr[++(s->top)] = value;
        printf("Pushed %d to the stack (Array)\n", value);
    }
}

void popArrayStack(ArrayStack* s) {
    if (isEmptyArrayStack(s)) {
        printf("Stack underflow\n");
    } else {
        printf("Popped %d from the stack (Array)\n", s->arr[(s->top)--]);
    }
}

void displayArrayStack(ArrayStack* s) {
    if (isEmptyArrayStack(s)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements (Array):\n");
        for (int i = s->top; i >= 0; i--) {
            printf("%d\n", s->arr[i]);
        }
    }
}

void initLinkedListStack(LinkedListStack* s) {
    s->top = NULL;
}

int isEmptyLinkedListStack(LinkedListStack* s) {
    return s->top == NULL;
}

void pushLinkedListStack(LinkedListStack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    printf("Pushed %d to the stack (Linked List)\n", value);
}

void popLinkedListStack(LinkedListStack* s) {
    if (isEmptyLinkedListStack(s)) {
        printf("Stack underflow\n");
    } else {
        Node* temp = s->top;
        s->top = s->top->next;
        printf("Popped %d from the stack (Linked List)\n", temp->data);
        free(temp);
    }
}

void displayLinkedListStack(LinkedListStack* s) {
    if (isEmptyLinkedListStack(s)) {
        printf("Stack is empty\n");
    } else {
        Node* temp = s->top;
        printf("Stack elements (Linked List):\n");
        while (temp != NULL) {
            printf("%d\n", temp->data);
            temp = temp->next;
        }
    }
}

int main() {
    int stackType, size, choice, value;
    ArrayStack arrayStack;
    LinkedListStack linkedListStack;

    printf("Choose stack type:\n1. Array-based stack\n2. Linked list-based stack\n");
    scanf("%d", &stackType);

    if (stackType == 1) {
        printf("Enter the size of the stack: ");
        scanf("%d", &size);
        if (size > MAX) {
            printf("Size exceeds the maximum allowed (%d)\n", MAX);
            return 0;
        }
        initArrayStack(&arrayStack, size);
    } else if (stackType == 2) {
        initLinkedListStack(&linkedListStack);
    } else {
        printf("Invalid stack type\n");
        return 0;
    }

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                if (stackType == 1) {
                    pushArrayStack(&arrayStack, value);
                } else if (stackType == 2) {
                    pushLinkedListStack(&linkedListStack, value);
                }
                break;
            case 2:
                if (stackType == 1) {
                    popArrayStack(&arrayStack);
                } else if (stackType == 2) {
                    popLinkedListStack(&linkedListStack);
                }
                break;
            case 3:
                if (stackType == 1) {
                    displayArrayStack(&arrayStack);
                } else if (stackType == 2) {
                    displayLinkedListStack(&linkedListStack);
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
