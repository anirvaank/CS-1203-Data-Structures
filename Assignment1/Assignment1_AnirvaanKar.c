#include <stdio.h>
#include <stdlib.h>
#define BADVAL -9999

struct node {
    int info;
    struct node *next;
};

typedef struct node Node;
//Creating a struct Queue to encapsulate the front and rear of Node//
struct Queue {
    Node *front, *rear;
};

typedef struct Queue Queue;
// Creating a Queue q with the front and rear set to their default values//
Queue createQueue() {
    Queue q;
    q.front = q.rear = NULL;
    return q;
}

Node* createNode(int val) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->info = val;
    p->next = NULL;
    return p;
}
//Instead of having to refer to the node struct we can now refer to the queue struct with the front and rear which will refer to the node struct//
void insert(Queue *q, int elm) {
    Node *temp = createNode(elm);
    if (q->rear == NULL) { //The queue struct is referring to the rear which needs us to use the node struct//
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

int delete(Queue *q) {
    if (q->front == NULL) {
        return BADVAL;
    } else {
        Node *temp = q->front;
        int val = temp->info;
        q->front = q->front->next;
        free(temp);
        if (q->front == NULL) {
            q->rear = NULL;
        }
        return val;
    }
}
//As we do not need to modify the queue to print it we can just give it the contents of the queue//
void printQueue(Queue q) {
    Node *temp = q.front;
    if (temp == NULL) {
        printf("Queue empty\n");
        return;
    }
    printf("<- F ");
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->next;
    }
    printf("<- R\n");
}

int main() {
    Queue q;
    int elm, menu;
    while (1) {
        printf("0. exit, 1. initialize, 2. delete, 3. insert, 4. print. Input Choice: ");
        scanf("%d", &menu);
        switch (menu) {
            case 0:exit(0);
            case 1: q = createQueue();
                   break;
            case 2:printf("Popped Value %d\n", delete(&q));
                   break;
            case 3:printf("Give element: ");
                   scanf("%d", &elm);
                   insert(&q, elm);
                   break;
            case 4:printQueue(q);
                   break;
            default:printf("Wrong choice\n");
        }
    }
}