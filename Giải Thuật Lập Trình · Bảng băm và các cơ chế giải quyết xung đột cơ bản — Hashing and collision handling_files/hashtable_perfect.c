/*
 * An implementation of hashtable using perfect hashing. 
 *
 * Warning: this implementation is not fully tested, use at your own risk.
 * See http://www.giaithuatlaptrinh.com/?p=967 for more details.
 *
 *  Created on: April 13, 2016
 *  Author: Hung Le
 */  
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define YES 1
#define NO 0


// Hash function specification
// We use binary multiplicative hash function
// For more details see http://www.giaithuatlaptrinh.com/?p=967
int  l = 10;
int w = 20;
int r_h;
int r_g;				
int m;		// the table has size 2^10	

// Linked list for chaining 
typedef struct llnode{	// define a linked list node 
		int x;
		struct llnode *next;
}llnode;

llnode ***T;	// the hash table
int *C;			// the counters 

int n;	// the number of items to be stored in the table is 2^9; the load factor is 50%
int *A;				// data to be hashed
void read();		// generating random data

int random_hash_ft();	// generate a random hash function
int hash(int i, int x);
void put_to_table(int *A, int n);	
int lookup(int x);

// interface to operate on a linked list
llnode *add_to_list(llnode *head, int a);
void print_llist(llnode *head);

int main(){
	r_h = random_hash_ft();	// choosing a random binary hash function  h by choosing r_h
	do{
		r_g = random_hash_ft();	// choosing a different random binary hash function  g by choosing r_g
	}while(r_g == r_h);	
	printf("r_h = %d, r_g = %d\n", r_g,r_h);
	
	m =  1 << l;			// the size of the hashtale is 2^l0
	n  = (1 << (l-1));			// the load factor is 0.5
	read();
	T = (llnode ***)malloc(m*sizeof(llnode**));	// allocate m slots of memory for T
	put_to_table(A,n);
	lookup(A[400]);
	lookup(10000);
	
}

// put a key x into the table and return the location of the table that stores x
void put_to_table(int *A, int n){
	C = (int *)malloc(m*sizeof(int));
	memset(C, 0, m*sizeof(int));
	int i = 0;
	for(; i < n; i++){
		C[hash(r_h,A[i])]++;
	}
	for(i = 0; i < m; i++){
		if(C[i] != 0){
			//printf("allocating memory\n");
			T[i] = (llnode **)malloc((C[i]*C[i])*sizeof(llnode*));
		}
	}
	int j = -1;
	int k = -1;
	for(i = 0; i < n; i++){
		j = hash(r_h,A[i]);
		k = hash(r_g,A[i])%(C[j]*C[j]);
		//printf("j = %d\n",j);
		T[j][k] = add_to_list(T[j][k], A[i]);
	}
}

int lookup(int x){
	int i = hash(r_h,x);
	if(T[i] == NULL) {
		printf("Not found %d!\n",x);
		return NO;
	}
	int j = hash(r_g,x)%(C[i]*C[i]);
	llnode *L = T[i][j];
	while(L != NULL){
		if(L->x == x){
			printf("Found %d at location (%d,%d)!\n",x,hash(r_h,x),j);
			return YES;
		}
		L = L->next;
	}
	printf("Not found %d!\n",x);
	return NO;
}

// we use binary multiplicative hash function
// parameter r_h define h(x), r_g define g(x)
int hash(int r, int x){
	return ((r*x)&((1<<w)-1))>>(w-l);
}



// Since we use binary mutlipcative hashing, choosing a random hash function get down to choose an odd number r less than 2^w
int random_hash_ft(){
		
		int r = rand()%(1<<w);
		while((r&1) == 0){	// if r is even, choose again
			r = rand()%(1<<w);
		}
		return r;
}


// add an element to the head of a linked list
llnode* add_to_list(llnode *head, int a){
	llnode *node = (llnode *)malloc(sizeof(llnode));
	node->x = a;
	node->next = head;
	head = node;
	return head;
}

// print a linked list given a head pointer;

void print_llist(llnode *head){
	llnode *runner = head;
	while(runner != NULL){
		printf("%d ", runner->x);
		runner = runner->next;
	}	
	printf("\n");
}
// we generate n random numbers of size at most 2^31
void read(){
	A = (int *)malloc(n*sizeof(int));
	int i = 0;
	int max = (1<<31);
	for(; i < n; i++){
		A[i] = rand()%max;
	}
}