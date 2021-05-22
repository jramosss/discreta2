/*
set ADT for binary trees
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

struct tree_node {
	struct tree_node *left;
	struct tree_node *right;
	unsigned int val;
};

/* typedef struct set set_t is defined in set.h */
struct set {
	struct tree_node *root;
	unsigned int len;
};

set_t *set_create(void)
{
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	new_set->root = NULL;	
	new_set->len = 0;
	return new_set;
}

static void leaf_destroy(struct tree_node *node) 
{
	if(node == NULL) return;
	
	leaf_destroy(node->left);
	leaf_destroy(node->right);
	free(node);
}

void set_destroy(set_t *set)
{
	leaf_destroy(set->root);
	free(set);
	return;	
}

static int leaf_insert(struct tree_node *node, unsigned int new_val)
{
	if (node->val == new_val){
		return 0;
	}
	if (node->val > new_val) { 
		if(node->left != NULL){
			return leaf_insert(node->left, new_val);
		}
		else{
			node->left = safe_malloc(sizeof(struct tree_node));
			node->left->val = new_val;
			node->left->left = node->left->right = NULL;
		}
	} 
	else{ 
		if(node->right != NULL){
			return leaf_insert(node->right, new_val);
		}
		else{
			node->right = safe_malloc(sizeof(struct tree_node));
			node->right->val = new_val;
			node->right->left = node->right->right = NULL;
		}		
	}
	return 1;
}

int set_insert(set_t *set, unsigned int new_val)
{
	if(set->root != NULL){
		int res = leaf_insert(set->root, new_val);
		if (res) {
			set->len++;
			//printf("Agregando %u al conjunto, nuevo len = %u\n",new_val,set->len);
		}
		return res;
	}
	else{ 
		set->root = safe_malloc(sizeof(struct tree_node));
		set->root->val = new_val;
		set->root->left = set->root->right = NULL;
		set->len++;
		//printf("Agregando %u al conjunto, nuevo len = %u\n",new_val,set->len);
		return 1;
	}
}
/*
static int leaf_delete(struct tree_node *node, int del_val)
{
	if(node == NULL){
		return 0;
	}	
	if (node->left && node->left->val == del_val) { 
		struct tree_node *temp;
		temp = node->left;
		node->left = temp->left;
		if (node->left == NULL){
			node->left = temp->right;
		}
		else{
			struct tree_node *curr;
			curr = node->left;
			while (curr->right != NULL){
				curr = curr->right;
			}
			curr->right = temp->right;
		}
		free(temp);
		return 1;
	} 
	if (node->right && node->right->val == del_val) {
		struct tree_node *temp;
		temp = node->right;
		node->right = temp->right;
		if (node->right == NULL){
			node->right = temp->left;
		}
		else{
			struct tree_node *curr;
			curr = node->right;
			while (curr->left != NULL) {
				curr = curr->left;
			}
			curr->left = temp->left;
		}
		free(temp);
		return 1;
	}
	if (node->val > del_val){
		return leaf_delete(node->left, del_val);
	}
	else{
		return leaf_delete(node->right, del_val);
	}
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	if(set->root == NULL){
		return 0;
	}
	if (set->root->val == del_val) {
		struct tree_node *temp;
		temp = set->root;
		set->root = temp->left;
		if (set->root == NULL) {
			set->root = temp->right;
		} 
		else{
			struct tree_node *curr;
			curr = set->root->left;
			while (curr->right != NULL) {
				curr = curr->right;
			}
			curr->right = temp->right;			
		}
		return 1;
	}
	else{
		return leaf_delete(set->root, del_val);
	}
}

static int leaf_search(struct tree_node *node, int search_val)
{
	if(node == NULL){
		return 0;
	}
	if(node->val == search_val){
		return 1;
	}
	if(node->val > search_val){
		return leaf_search(node->left, search_val);
	}
	else{
		return leaf_search(node->right, search_val);
	}
}

int set_search(set_t *set, int search_val)
{
	return leaf_search(set->root, search_val);
}

*/
static void tree_inOrder(struct tree_node *node)
{
	if(node == NULL){ 
		return;
	}
	tree_inOrder(node->left);
	printf("%d",node->val);
	printf("->");
	tree_inOrder(node->right);
}

void set_print(set_t *set)
{
	if(set->root == NULL){
		return;
	}	
	tree_inOrder(set->root);
}

unsigned int set_length (set_t *set) {
	return set->len;
}