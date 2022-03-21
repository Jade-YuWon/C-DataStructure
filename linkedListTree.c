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

//// root init
//tree->root->data = 1;
//tree->root->Lptr = NULL;
//tree->root->Rptr = NULL;
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

// Traverse functions
/*
void preorder(tree_ptr ptr)
{
	if (ptr) {
		(visit node);
		preorder(ptr->left_child);
		preorder(ptr->right_child);
	}
}
void inorder(tree_ptr ptr)
{
	if (ptr) {
		preorder(ptr->left_child);
		(visit node);
		preorder(ptr->right_child);
	}
}
void postorder(tree_ptr ptr)
{
	if (ptr) {
		preorder(ptr->left_child);
		preorder(ptr->right_child);
		(visit node);
	}
}
*/

void preorder(NODE* ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->Lptr);
		preorder(ptr->Rptr);
	}
}
void postorder(NODE* ptr) {
	if (ptr) {
		postorder(ptr->Lptr);
		postorder(ptr->Rptr);
		printf("%d ", ptr->data);
	}
}
void inorder(NODE* ptr) {
	if (ptr) {
		inorder(ptr->Lptr);
		printf("%d ", ptr->data);
		inorder(ptr->Rptr);
	}
}


int main() {
	TREE* tree = NULL;
	//NODE* rootNode = NULL;

	// tree and root malloc
	tree = (TREE*)malloc(sizeof(TREE));
	//rootNode = (NODE*)malloc(sizeof(NODE));
	
	// defensive coding
	if (!tree) {
		printf("malloc failed\n");
		exit(1);
	}

	// tree init
	//tree->root = rootNode;
	tree->root = addNewNode(1);
		//// root init
		//tree->root->data = 1;
		//tree->root->Lptr = NULL;
		//tree->root->Rptr = NULL;
	tree->root->Lptr = addNewNode(2);
	tree->root->Rptr = addNewNode(3);
	tree->root->Lptr->Lptr = addNewNode(4);
	tree->root->Lptr->Rptr = addNewNode(5);
	tree->root->Rptr->Lptr = addNewNode(6);
	tree->root->Rptr->Rptr = addNewNode(7);
	tree->root->Rptr->Rptr->Lptr = addNewNode(8);

	printf("\n\nPreorder traversal: ");
	preorder(tree->root);
	printf("\n\nInorder traversal: ");
	inorder(tree->root);
	printf("\n\nPostorder traversal: ");
	postorder(tree->root);

	return 0;
}
