#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "bst.h"


/* 
   Returns the parent of an either existing or hypotetical node with the given data  
 */
Node * find_parent(Node * root, int data) {
  assert(root != NULL);
  assert(data != root->data);

  Node * next = data < root->data ? root->left : root->right;

  if (next == NULL || next->data == data)
    return root;
  else
    return find_parent(next, data);
}

/* 
   Constructs a new node
 */
Node * mk_node(int data) {
  Node * node = (Node *) malloc(sizeof(Node));
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

Node * insertNode(Node * root, int data) {
  if (root == NULL)
    return mk_node(data);

  if (data == root->data)
    return NULL;

  Node * parent = find_parent(root, data);
  Node * child = data < parent->data ? parent->left : parent->right;
  assert(child == NULL || child->data == data);

  if (child == NULL) {
    // data not found, then insert and return node   
    child = mk_node(data);
    if (data < parent->data)
      parent->left = child;
    else
      parent->right = child;

    return root;
  } else {
    // data found, then return null
    return NULL;
  } 
}

bool is_ordered(Node * root) {
  if (root == NULL)
    return true;
  if (root->left && root->left->data > root->data)
    return false;
  if (root->right && root->right->data < root->data)
    return false;
  return true;
}

Node * deleteNode(Node * root, int data) {
  assert(is_ordered(root));

  // empty tree
  if (root == NULL)
    return NULL;

  // find node with data 'data' and its parent node 
  Node * parent, * node;
  if (root->data == data) {
    parent = NULL;
    node = root;
  } else {
    parent = find_parent(root, data);
    node = data < parent->data ? parent->left : parent->right;
  }
  assert(node == NULL || node->data == data);

  // data not found
  if (node == NULL)
    return root;

  // re-establish consistency
  Node * new_node;
  if (node->left == NULL) {
    // node has only right child, then make right child the new node
    new_node = node->right;
  } else {
    // otherwise make right child the rightmost leaf of the subtree rooted in the left child
    // and make the left child the new node
    Node * rightmost = new_node = node->left;
    while (rightmost->right != NULL)
      rightmost = rightmost->right;
    rightmost->right = node->right;
  }

  free(node);

  Node * new_root;
  if (parent == NULL) {
    // if deleted node was root, then return new node as root 
    new_root = new_node;
  } else {
    // otherwise glue new node with parent and return old root
    new_root = root;
    if (data < parent->data) 
      parent->left = new_node;
    else 
      parent->right = new_node;
  }

  assert(is_ordered(new_root));

  return new_root;
}

void printSubtree(Node * N) {
  if (N == NULL) return;

  printSubtree(N->left);
  printf("%d \n", N->data);
  printSubtree(N->right);
}

int countLeaves(Node * N) {
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;
  
  return countLeaves(N->left) + countLeaves(N->right);
}

/* 
   Frees the entire subtree rooted in 'root' (this includes the node 'root')
 */
void free_subtree(Node * root) {
  if (root == NULL)
    return;

  free_subtree(root->left);
  free_subtree(root->right);
  free(root);
}

Node * freeSubtree(Node* N){
  free_subtree(N);
  return NULL;
}

/* 
   Deletes all nodes that belong to the subtree (of the tree of rooted in 'root') 
   whose root node has data 'data'
 */
Node * deleteSubtree(Node * root, int data) {
  assert(is_ordered(root));

  // empty tree
  if (root == NULL)
    return NULL;

  // entire tree
  if (root->data == data) {
    free_subtree(root);
    return NULL;
  }

  // free tree rooted in the left or right node and set the respective pointer to NULL 
  Node * parent = find_parent(root, data);
  if (data < parent->data) {
    assert(parent->left == NULL || parent->left->data == data);
    free_subtree(parent->left);
    parent->left = NULL;
  } else {
    assert(parent->right == NULL || parent->right->data == data);
    free_subtree(parent->right);
    parent->right = NULL;
  }

  return root;
}

/* 
   Compute the depth between root R and node N 

   Returns the number of edges between R and N if N belongs to the tree rooted in R,
   otherwise it returns -1
 */



int countNodes(Node *root){
	int sum =0;
	if (root == NULL){
		return 0;
	}
	else{
		sum = countNodes(root->right)+ 1+countNodes(root->left);
	}
	return sum;
	

}

int insertNodestoArray(Node * root, int arr[], int pos){
	if (root == NULL) return pos;
	if (root->left != NULL){
    pos = insertNodestoArray(root->left, arr ,pos);
	}

	arr[pos++] = root->data;
  //printf("datas is %d \n" ,root->data);
  if (root->right != NULL){
    pos = insertNodestoArray(root->right, arr ,pos);
	}
	return pos;
}

Node * createBST(int arr[], int start, int end, Node*root){
	if(end <= start) return NULL;
	int mid = (start + end) /2;
 
	

	Node * new = (Node *) malloc(sizeof(Node));
	new->data= arr[mid];
	new->left= NULL;
	new->right = NULL;
	root= new;

	root->left = createBST( arr,  start, mid, root->left);
	root->right= createBST(arr, mid+1, end, root->right);
	return root;
	//useinsertNOde
	
}
// This functions converts an unbalanced BST to a balanced BST 
Node* balanceTree(Node* root) 
{
	int size = countNodes(root);
	int arr[size];
	

	insertNodestoArray(root, arr ,0);

	
	
	Node * newroot = NULL;

 
	newroot = createBST(arr,0, size, newroot);

 
	return newroot;

	// TODO: Implement this function

} 



int sumSubtree(Node * N){
	int sum;

	if (N == NULL){
		return 0;
	}

	sum = sumSubtree(N->left) + N->data + sumSubtree(N->right);
	return sum;
}


