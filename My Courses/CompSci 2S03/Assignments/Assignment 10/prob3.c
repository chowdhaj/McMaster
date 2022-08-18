// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// self referential struct that acts as tree data struct.
struct treeNode {

	int data; // parent node that holds data
	struct treeNode *leftPtr; // left leaf node pointer
	struct treeNode *rightPtr; // right leaf node pointer
};

// typedef statements for reference
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

// function prototypes
void insert(TreeNodePtr *treePtr, char value);
void inOrder(TreeNodePtr treePtr, int k1, int k2);
void preOrder(TreeNodePtr treePtr);
void preOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);

int main() {

	TreeNodePtr rootPtr = NULL; // create new tree, set it to null

	insert(&rootPtr, 20); // add 20 to tree [left]
	insert(&rootPtr, 8); // add 8 to tree [right]
	insert(&rootPtr, 22); // add 22 to tree [left-left]
	insert(&rootPtr, 4); // add 4 to tree [left-right]
	insert(&rootPtr, 12); // add 12 to tree [right-left]

	int k1 = 10; // key 1
	int k2 = 22; // key 2

	// prints the tree in a graphical format via CL
	printf("\n----\nTREE\n----  \n");
	puts("           20         \n"
		 "     |           |    \n" 
		 "     8           22   \n"
		 "  |     |      |    | \n"
		 "  4     12            \n");

	printf("The keys are: %d & %d\n", k1, k2); // prints values of keys

	printf("\nThe numbers between %d and %d [inclusive] are: \n", k1, k2); // print text
	inOrder(rootPtr, k1, k2); // print the parent nodes between key1 and key2, using inOrder sequencing

	puts("\n"); // print newline

	return 0;
}

// inserts nodes in tree
void insert(TreeNodePtr	*treePtr, char value) {

	if (*treePtr == NULL) { // if tree is null
		*treePtr = malloc(sizeof(TreeNode)); // allocate memory for tree

		if (*treePtr != NULL) { // if tree is not null
			(*treePtr)->data = value; // parent node gets 'value'
			(*treePtr)->leftPtr = NULL; // set left leaf to null
			(*treePtr)->rightPtr = NULL; // set right leaf to null
		} else {
			printf("%d not inserted. No memory available.\n", value); // value not inserted due to insuf. memory
		}
	} else {
		if (value < (*treePtr)->data) { // if value is less than the parent node
			insert(&((*treePtr)->leftPtr), value); // insert value to left leaf node
		} else if (value > (*treePtr)->data) { // else:
			insert(&((*treePtr)->rightPtr), value); // insert value to right leaf node
		} else {
			printf("%s\n", "Duplicate"); // otherwise, print duplicate
		}
	}
}

// prints binary tree using inOrder sequencing
void inOrder(TreeNodePtr treePtr, int k1, int k2) {

	if (treePtr != NULL) { // if tree is not null
		inOrder(treePtr->leftPtr, k1, k2); // start from left leaf(s)
		
		// if value of left leaf nodes are between the keys, then print the value at the node
		if (treePtr->data >= k1 && treePtr->data <=k2)
			printf("%d, ",treePtr->data); // print node

		inOrder(treePtr->rightPtr, k1, k2); // recurse on the right nodes and print them
	}
}

// Reference: C How To Program By Deital