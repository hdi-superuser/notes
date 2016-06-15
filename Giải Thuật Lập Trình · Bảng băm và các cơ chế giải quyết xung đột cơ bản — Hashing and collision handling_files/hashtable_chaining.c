/*
 * An implementation of hashtable using chaining for collision resolution.
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
#define YES 1
#define NO 0

// Hash function specification
// We use binary multiplicative hash function
// See see http://www.giaithuatlaptrinh.com/?p=967 for more details.
int  l = 10;
int w = 20;
int r;					
int m;		// the table has size 2^10	


int n;	// the number of items to be stored in the table is 2^9; the load factor is 50%
int *A;				// data to be hashed
void read();		// generating random data

// Linked list for chaining 
typedef struct llnode{	// define a linked list node 
		int x;
		struct llnode *next;
}llnode;

llnode **T;	// the hash table
int random_hash_ft();	// generate a random hash function
int hash(int x);
void put_to_table(int x);
int lookup(int x);

// interface to operate on a linked list
llnode *add_to_list(llnode *head, int a);
void print_llist(llnode *head);
int main(){
	r = random_hash_ft();	// choosing a random hash function by choosing r
	m =  1 << l;			// the size of the hashtale is 2^l0
	n  = (1 << 9);			// the load factor is 0.5
	T = (llnode **)malloc(m*sizeof(llnode*));	// allocate m slots for the hashtable
	read();
	int i = 0;
	for(; i < n; i++){
		put_to_table(A[i]);
	}
	lookup(A[3]);
	lookup(10000);	
}

void put_to_table(int x){
	T[hash(x)] = add_to_list(T[hash(x)],x);
}

int lookup(x){
	llnode *L = T[hash(x)];
	while(L != NULL){
		if(L->x  == x) {
			printf("%d is at location %d of the table\n", x, hash(x));
			return YES;
		}
		L = L->next;
	}
	printf("%d Not found!\n",x);
	return NO;
}

// we use binary multiplicative hash funciton.
int hash(int x){
	return ((r*x)&((1<<w)-1))>>(w-l);
}

// add an element to the head of a linked list
llnode* add_to_list(llnode *head, int a){
	llnode *node = (llnode *)malloc(sizeof(llnode));
	node->x = a;
	node->next = head;
	head = node;
	return head;
}


// Since we use binary mutlipcative hashing, choosing a random hash function get down to choose an odd number r less than 2^w
int random_hash_ft(){	
		int r = rand()%(1<<w);
		while((r&1) == 0){	// if r is even, choose again
			r = rand()%(1<<w);
		}
		return r;
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