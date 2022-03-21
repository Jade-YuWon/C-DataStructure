#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* Lptr;	// left child
	struct Node* Rptr; // right child
} NODE;

typedef struct Tree {
	struct Node* root;
} TREE;

NODE* addNewNode(const int val) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if (!newNode) {
		printf("malloc failed\n");
		return NULL;
	}
	printf("%d added.. ", val);
	newNode->data = val;
	newNode->Lptr = NULL;
	newNode->Rptr = NULL;
	return newNode;
}

// Traverse functions - preorder, inorder, postorder
void preorder(NODE* ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->Lptr);
		preorder(ptr->Rptr);
	}
}
void inorder(NODE* ptr) {
	if (ptr) {
		inorder(ptr->Lptr);
		printf("%d ", ptr->data);
		inorder(ptr->Rptr);
	}
}
void postorder(NODE* ptr) {
	if (ptr) {
		postorder(ptr->Lptr);
		postorder(ptr->Rptr);
		printf("%d ", ptr->data);
	}
}

int main() {
	TREE* tree = NULL;

	// tree malloc
	tree = (TREE*)malloc(sizeof(TREE));
	
	// defensive coding
	if (!tree) {
		printf("malloc failed\n");
		exit(1);
	}

	// tree initialization (assign root node)
	tree->root = addNewNode(1);
	// Fill every nodes of tree with values
	tree->root->Lptr = addNewNode(2);
	tree->root->Rptr = addNewNode(3);
	tree->root->Lptr->Lptr = addNewNode(4);
	tree->root->Lptr->Rptr = addNewNode(5);
	tree->root->Rptr->Lptr = addNewNode(6);
	tree->root->Rptr->Rptr = addNewNode(7);
	tree->root->Rptr->Rptr->Lptr = addNewNode(8);

	// Traverse tree
	printf("\n\nPreorder traversal: ");
	preorder(tree->root);
	printf("\n\nInorder traversal: ");
	inorder(tree->root);
	printf("\n\nPostorder traversal: ");
	postorder(tree->root);

	return 0;
}
