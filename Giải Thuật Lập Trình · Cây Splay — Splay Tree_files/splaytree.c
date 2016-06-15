#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define null 0
#define TRUE 1
#define FALSE 0

typedef struct Node{
	int key;
	int value;
	struct Node *left, *right, *parent;
} Node;

Node *create_node(int k, int v);
void left_rotate(Node *x);
void right_rotate(Node *x);
void left_zig_zag(Node *z);
void right_zig_zag(Node *z);
void left_roller_coaster(Node *x);
void right_roller_coaster(Node *z);
void splay(Node* x);
Node *find_without_splay(Node *r, int K);
int find(int K);
Node *insert_without_splay(Node *r, int K, int V);
void insert(int K, int V);
void delete(int K);

Node *root; //the root of the splay tree

int main(){
	root = create_node(5,5);
	insert(9,9);	
	print_tree(root);
	insert(13,13);		
	print_tree(root);	
	insert(11,11);		
	print_tree(root);
	insert(1,1);		
	print_tree(root);
	find(9);
	print_tree(root);
	delete(5);
	print_tree(root);
	find(13);
	print_tree(root);
}


// find a key K
int find(int K){
	Node *x = find_without_splay(root,K);
	splay(x);
	root = x;
	if(root->key == K) return TRUE;
	else return FALSE;
}

// find without splay a key K
Node *find_without_splay(Node *r, int K){
	if (r->key == K) return r;
	else if (r->key < K){
		if(r->right == null) return r;
		else return find_without_splay(r->right,K);	
	} else {
		if(r->left == null) return r;
		else return find_without_splay(r->left,K);		
	}
}

//insert a (key,value) pair

void insert(int K, int V){
	Node *x = insert_without_splay(root,K,V);
	splay(x);
	root = x;
}

//insert a (key,value) pair without splay

Node *insert_without_splay(Node *r, int K, int V){
	if (r->key == K){
		r->value = V;
 		return r;
	}
	else if (r->key < K){
		if(r->right == null) {
			Node*x = create_node(K,V);
			r->right = x;
			x->parent = r;
			return x;
		}
		else return insert_without_splay(r->right,K,V);	
	} else {
		if(r->left == null) {
			Node*x = create_node(K,V);
			r->left = x;
			x->parent = r;
			return x;
		}
		else return insert_without_splay(r->left,K,V);		
	}
}


// delete a node with key K
void delete(int K){
	if(find(K) == FALSE) return;
	Node *y = root->left;
	y->parent = null;
	if(y->right != null){
		Node *w = y->right;
		while(w->right != null) w = w->right;
		splay(w);
		w->right = root->right;
		if(root->right != null) root->right->parent = w;
		root = w;	
	}else {
		y->right = root->right;	 
		if(root->right != null) root->right->parent = y;
		root = y;
	}
}


// splay

void splay(Node *x){
	if(x->parent == null) return;
	Node *y = x->parent;
	if(y->parent == null){ // y is the root
		if(y->left != null && y->left->key == x->key){
//			printf("I am doing right rotate at %d\n", y->key);
			right_rotate(y);		
		} else {
//			printf("I am doing left rotate at %d\n", y->key);
			left_rotate(y);
		}
	} else {
		Node *z = y->parent;
		if(z->left != null &&z->left->key  == y->key){
			if(y->left != null && y->left->key == x->key){
//				printf("I am doing right_roller_coaster at %d\n",z->key);
				right_roller_coaster(z);			
			}else {
//				printf("I am doing left zig-zag at %d\n",z->key);
				left_zig_zag(z);
			}		
		} else {
			if(y->right != null && y->right->key == x->key){
//				printf("I am doing left_roller_coaster at %d\n",z->key);
				left_roller_coaster(z);			
			}else {
//				printf("I am doing right zig-zag at %d\n",z->key);
				right_zig_zag(z);			
			}		
		}
	}
	splay(x);
}
// left zig-zag at z

void left_zig_zag(Node *z){
	Node *y = z->left;
	left_rotate(y);
	right_rotate(z);
}

// right zig-zag at z

void right_zig_zag(Node *z){
	Node *y = z->right;
	right_rotate(y);
	left_rotate(z);
}

// right roller-coaster at z

void right_roller_coaster(Node *z){
	Node *y = z->left;
	right_rotate(z);
	right_rotate(y);	
}


// left roller-coaster at x

void left_roller_coaster(Node *x){
	Node *y = x->right;
	left_rotate(x);
	left_rotate(y);	
}


// right rotation at y
void right_rotate(Node *y){
	Node* x = y->left;
	Node* w = y->parent;
	Node* z = x->right;
	if(w != null){
		if(w->left!= null && w->left->key == y->key){
			w->left = x;
		}else {
			w->right = x;		
		}	
	}
	if(z != null)z->parent = y;
	y->left = z;
	x->parent = w;	
	x->right = y;
	y->parent = x;
}

// left rotation at x
void left_rotate(Node *x){
	Node* y = x->right;
	Node *w = x->parent;
	Node *z = y->left;
	if(w != null){
		if(w->left != null && w->left->key == x->key){
			w->left = y;
		}else {
			w->right = y;		
		}	
	}
	if(z != null) z->parent = x;
	x->right = z;
	y->left = x;
	y->parent = w;
	x->parent = y;
}

// create a new node
Node *create_node(int k, int v){
	Node *x = (Node *)malloc(sizeof(Node));
	x->key = k; x->value = v;
	x->left = null; x->right = null; x->parent = null;
	return x;
}

print_tree(Node *root){
	printf("Node: %d ",root->key);
	if(root->parent != null) 	printf("Parent: %d ",root->parent->key);
	if(root->left != null)	printf("Left: %d ",root->left->key);
	if(root->right != null)	printf("Right: %d ",root->right->key);
	printf("\n");
	if(root->left != null)	print_tree(root->left);
	if(root->right != null)	print_tree(root->right);
}

