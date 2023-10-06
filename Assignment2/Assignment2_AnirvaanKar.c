#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node* left, *right;
};

// Structure for stack node
struct StackNode {
    struct node* data;
    struct StackNode* next;
};

// Stack structure
struct Stack {
    struct StackNode* top;
};

struct node* createNode(int k) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = k;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to create a new stack node
struct StackNode* createStackNode(struct node* data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

// Initialize a stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Push a node to the stack
void push(struct Stack* stack, struct node* data) {
    struct StackNode* stackNode = createStackNode(data);
    stackNode->next = stack->top;
    stack->top = stackNode;
}

// Pop a node from the stack
struct node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    struct node* popped = temp->data;
    free(temp);
    return popped;
}

    void displayNode(struct node *temp){

        if (temp == NULL)
            printf("Node does not exist\n");
        else
                printf("%x %d\n", (unsigned int) temp, temp->key);

    }

    void displayTree(struct node* root, int space)
    {
        int i;

        if (root == NULL) return;
    
        space += 10;
    
        // Process right child first
        displayTree(root->right, space);
    
        // Print current node after space count
        printf("\n");
        for (i = 10; i < space; i++)
            printf(" ");
        printf("%d\n", root->key);
    
        // Process left child
        displayTree(root->left, space);
    }
    
    struct node * search(struct node * anode, int k){

        struct node *temp, *parent;
        
        if (anode == NULL) return NULL;
        
        temp = anode;
        while (temp != NULL){
        if (temp->key == k){
        return temp;
            }

            if (k < temp->key){
                temp = temp->left;
            }
            else{
            temp = temp->right;
            }
        }
        return NULL;
    }
            
    struct node * insert(struct node * anode, int k){

        struct node *temp, *parent;
        int direction;
        
        if (anode == NULL){
            anode = createNode(k);
        return anode;
        }
        
        temp = anode;
        while (temp != NULL){
        if (temp->key == k){
        printf("node with value %d exists\n", k);
        return temp;
            }

            if (k < temp->key){
            parent = temp;
                temp = temp->left;
                direction = 0;
            }
            else{
            parent = temp;
            temp = temp->right;
                direction = 1;
            }
        }
        temp = createNode(k);
        if (direction == 0)
            parent->left = temp;
        else
            parent->right = temp;
            
    return temp; 
    }

    struct node * delete (struct node * anode, int k){

        struct node *temp, *parent, *intemp, *inparent;
        int direction, flag = 0, val;
        
        if (anode == NULL){ 
        printf("Tree empty\n");
            return NULL;
        }
    
        parent = NULL; 
        temp = anode;

        while (temp != NULL){
        if (temp->key == k){
            flag = 1;
        break;
            }
            if (k < temp->key){
            parent = temp;
                temp = temp->left;
                direction = 0;
            }
            else{
            parent = temp;
            temp = temp->right;
                direction = 1;
            }
        }

        if (flag == 0){
        printf("Node not found\n");
            return NULL;
        }

        if ((temp->left == NULL) && (temp->right == NULL)){
            if (direction == 0) parent->left = NULL;
            else parent->right = NULL;
            return temp;
        }

        if ((temp->left != NULL) && (temp->right == NULL)){
        if (parent == NULL){
            anode = temp->left;
            return temp;
            }
            if (direction == 0) parent->left = temp->left;
            else parent->right = temp->left;
            return temp;
        }

        if ((temp->left == NULL) && (temp->right != NULL)){
        if (parent == NULL){
            anode = temp->right;
            return temp;
            }
            if (direction == 0) parent->left = temp->right;
            else parent->right = temp->right;
            return temp;
        }

        if ((temp->left != NULL) && (temp->right != NULL)){
            inparent = temp;	
            intemp = temp->right;
            printf("%d %d\n", inparent->key, intemp->key);

            while(intemp->left != NULL){ 
        inparent = intemp;
            intemp = intemp->left;
            }
            printf("%d %d\n", inparent->key, intemp->key);

        val = temp->key;
        temp->key = intemp->key;
            intemp->key = val;

            printf("%d %d\n", temp->key, intemp->key);

        if ((intemp->left == NULL) && (intemp->right == NULL))
            inparent->right = NULL;
        else
                inparent->left = intemp->right;

        return intemp;
        }

        return NULL;
    }

void iterativeInorder(struct node* root) {
    struct Stack* stack = createStack();
    struct node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            // Push the current node onto the stack
            push(stack, current);
            current = current->left;
        }

        // Current is NULL at this point
        current = pop(stack);
        printf("%d ", current->key);

        // Move to the right subtree
        current = current->right;
    }
}




    void preorder(struct node * anode){
        if (anode != NULL) {
            printf("%d ", anode->key);
            preorder(anode->left);
            preorder(anode->right);
        }
    }

    void postorder(struct node * anode){
        if (anode != NULL) {
            postorder(anode->left);
            postorder(anode->right);
            printf("%d ", anode->key);
        }
    }

    void freeTree(struct node * anode){
        if (anode != NULL) {
            freeTree(anode->left);
            freeTree(anode->right);
            free(anode);
        }
    }

    int main()
    {
        struct node * root = NULL, *temp;
        int elm, menu;

        while(1){
        printf("\n0. exit, 1. initialize, 2. search, 3. insert, 4. delete,\n ");
        printf("5. inorder, 6. preorder, 7. postorder, 8. free tree, 9. display. Input Choice: ");
            scanf("%d", &menu);

            switch(menu){
            case 0: exit(0);

            case 1: root = NULL;
                    break;

            case 2: printf("Give element to search: ");
                    scanf("%d", &elm);
            temp = search(root, elm);
            displayNode(temp);
                    break;

            case 3: printf("Give element to insert: ");
                    scanf("%d", &elm);
            if (root == NULL)
                temp = root = insert(root, elm);
            else
                temp = insert(root, elm);
            displayNode(temp);
                    break;

            case 4: printf("Give element to delete: ");
                    scanf("%d", &elm);
            if (root == NULL)
                        printf("Tree empty\n");
            else if ((root->key == elm) && (root->left == NULL) && (root->right == NULL)){
                temp = root;
                        root = NULL;
            }
            else if ((root->key == elm) && (root->left != NULL) && (root->right == NULL)){
                temp = root;
                root = root->left;
            }
            else if ((root->key == elm) && (root->left == NULL) && (root->right != NULL)){
                temp = root;
                root = root->right;
            }
            else
                temp = delete(root, elm);

            displayNode(temp);
                    break;

            case 5: iterativeInorder(root);
            printf("\n");
                    break;

            case 6: preorder(root);
                    printf("\n");
                    break;

            case 7: postorder(root);
                    printf("\n");
                    break;

            case 8: freeTree(root);
                    root = NULL;
                    break;

            case 9: if (root == NULL) printf("Tree empty\n");
            displayTree(root, 0);
                    break;

            default: printf("Wrong choice\n");
            }
            }

        return 0;
    }
