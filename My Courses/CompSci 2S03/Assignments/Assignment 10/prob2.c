// Author: Jatin Chowdhary chowdhaj

#include <stdio.h> 
#include <stdlib.h> 
 
// self referential struct that will act as a tree 
struct tree {

     char number; // tree that stores number
     struct tree* leftTree; // left pointer
     struct tree* rightTree; // right pointer
};

// function prototypes
struct tree* addtree(char number); 
void inOrder(struct tree* tree);
void preOrder(struct tree* tree);

int main() {

    struct tree *root  = addtree('A'); // create tree struct with 'A' at the top
    (*root).leftTree = addtree('B'); // 'B' is on the left side
    (*root).rightTree = addtree('C'); // 'C' is on the right side
    (*(*root).leftTree).leftTree = addtree('D'); // 'D' is on the left-left side
    (*(*root).leftTree).rightTree = addtree('E'); // 'E' is on the left-right side
    (*(*root).rightTree).leftTree = addtree('F'); // 'F' is on the right-left side

    printf("\nThe Inserted Elements Are:\nA, B, C, D, E, F,\n"); // prints the elements that were inserted into the tree

    puts("\nPREODER:"); // text
    preOrder(root); // prints the tree in preoder format

    puts("\n\nINORDER:"); // text
    inOrder(root); // prints the tree in inorder format

    puts("\n"); // prints newlines

    return 0; 
} 
  
// this function adds data to the tree
struct tree* addtree(char number) { 

     struct tree* tree = (struct tree*) malloc(sizeof(struct tree)); // allocates memory space to tree
     
     tree->number = number; // assigns 'number' to the parent node
     tree->leftTree = NULL; // sets left leaf to null
     tree->rightTree = NULL; // sets right leaf to null
  
     return(tree); // returns tree
}
  
// this function prints the tree (recursively) using inOrder format
void inOrder(struct tree* tree) { 
     
    if (tree == NULL) return; // if tree is null [empty] return 
    inOrder(tree->leftTree); // prints the left nodes first using recursion
    printf("%c, ", tree->number); // print the value at the relative parent node
    inOrder(tree->rightTree); // prints the right nodes using recursion
} 

// this function prints the tree (recursively) using preOrder format
void preOrder(struct tree* tree) { 
     
    if (tree == NULL) return; // if tree is null [empty] return 
    printf("%c, ", tree->number); // print the value at the relative parent node
    preOrder(tree->leftTree); // prints the left nodes using recursion
    preOrder(tree->rightTree); // prints the right nodes using recursion
}     

// Reference: C How To Program By Deital