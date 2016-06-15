/*
 * An implementation of hashtable using open addressing for collision resolution. 
 * Three modes of addressing are: linear probing, quadratic probing and binary probing
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

#define LINEAR_PROBING 1
#define QUADRATIC_PROBING 2
#define BINARY_PROBING 3

int probing_mode = LINEAR_PROBING;
// Hash function specification
// We use binary multiplicative hash function
// See http://www.giaithuatlaptrinh.com/?p=967 for more details.
int  l = 10;
int w = 20;
int r;				
int m;		// the table has size 2^10	


int n;	// the number of items to be stored in the table is 2^9; the load factor is 50%
int *A;				// data to be hashed
void read();		// generating random data

int* T;
int random_hash_ft();	// generate a random hash function
int hash(int i, int x);
void put_to_table(int x);
int lookup(int x);

int main(){
	r = random_hash_ft();	// choosing a random binary hash function by choosing r
	m =  1 << l;			// the size of the hashtale is 2^l0
	n  = (1 << 9);			// the load factor is 0.5
	read();
	T = (int *)malloc(m*sizeof(int));	// allocate m slots of memory for T
	memset(T,-1,m*sizeof(int));			// set everything to -1
	int i = 0;
	for(; i < n; i++){
		put_to_table(A[i]);
		//printf("%d -- ", T[i]);
	}
	lookup(A[400]);
	lookup(10000);
	
	// print out the hashtable
	for(i = 0; i < m; i++){
	//	printf("%d : %d\n", i, T[i]);
	}
}

// put a key x into the table 
void put_to_table(int x){
	int i = 0;
	while(T[hash(i,x)] != -1){
		i++;
	}
	T[hash(i,x)]  = x;
}

int lookup(x){
	int i = 0;
	while(T[hash(i,x)] != x){
			if(T[hash(i,x)] == -1){
				printf("%d is not in the table\n",x);
				return NO;
			}else i++;
	}
	if(i <= m-1){
		printf("%d is at location %d of the table\n", x, hash(i,x));
		printf("the number of probing is %d \n", (i+1));
		return hash(i,x);
	}
	return NO;
}

int hash(int i, int x){
	switch(probing_mode){
		case LINEAR_PROBING:
			return ((((r*x)&((1<<w)-1))>>(w-l))+i)&(m-1);				// since m is a power of 2 => x mod m =  x&(m-1)
			break;
		case QUADRATIC_PROBING:
			return ((((r*x)&((1<<w)-1))>>(w-l))+i*i)&(m-1);
			break;
		case BINARY_PROBING:
			return (((r*x)&((1<<w)-1))>>(w-l))^i;
			break;
		default:
			printf("No default provided!\n");
			break;
	}
}



// Since we use binary mutlipcative hashing, choosing a random hash function get down to choose an odd number r less than 2^w
int random_hash_ft(){
		
		int r = rand()%(1<<w);
		while((r&1) == 0){	// if r is even, choose again
			r = rand()%(1<<w);
		}
		return r;
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