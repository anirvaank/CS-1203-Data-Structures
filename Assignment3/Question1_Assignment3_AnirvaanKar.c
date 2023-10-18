#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(struct Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

struct Node *createNode(int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalanceFactor(struct Node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}

struct Node *insert(struct Node *node, int key)
{
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    // Left Left Case
    if (bf > 1 && key < node->left->key)
    {
        return rightRotate(node);
    }
    // Right Right Case
    if (bf < -1 && key > node->right->key)
    {
        return leftRotate(node);
    }
    // Left Right Case
    if (bf > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (bf < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with the given key from the AVL tree
struct Node *deleteNode(struct Node *root, int key)
{
    if (root == NULL)
        return root;

    // Standard delete operation
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // Node with only one child or no child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            struct Node *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root;
            root = root->left;
            free(temp);
        }
        else
        {
            // Node with two children
            struct Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor of this node to check for imbalance
    int bf = getBalanceFactor(root);

    // Perform rotations based on the balance factor to balance the tree
    if (bf > 1 && getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (bf > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }
    if (bf < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void displayTree(struct Node *root, int space)
{
    int i;

    if (root == NULL)
        return;

    space += 10;

    displayTree(root->right, space);

    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    displayTree(root->left, space);
}

int main()
{
    struct Node *root = NULL;

    // Insert nodes into the tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);

    // Print the tree in preorder and inorder
    printf("Preorder traversal: ");
    preOrder(root);
    printf("\n");

    printf("Inorder traversal: ");
    inOrder(root);
    printf("\n");

    // Display the tree structure
    printf("Tree structure:\n");
    displayTree(root, 10);
    printf("\n");

    // Take user input for the key to delete
    int keyToDelete;
    printf("Enter the key to delete: ");
    scanf("%d", &keyToDelete);

    // Delete the specified node
    root = deleteNode(root, keyToDelete);

    // Print the tree after deletion in preorder and inorder
    printf("Preorder traversal after deletion: ");
    preOrder(root);
    printf("\n");

    printf("Inorder traversal after deletion: ");
    inOrder(root);
    printf("\n");

    // Display the tree structure after deletion
    printf("Tree structure after deletion:\n");
    displayTree(root, 10);
    printf("\n");

    return 0;
}