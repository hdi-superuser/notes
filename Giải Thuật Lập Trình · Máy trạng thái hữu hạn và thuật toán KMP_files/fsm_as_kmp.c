/*
 * An implementation of the kmp string search algorithm as a finite state machine
 * Warning: this implementation is not fully tested, used at your own risk
 * See http://www.giaithuatlaptrinh.com/?p=687 for more details.
 *
 *  Created on: Dec 29, 2015
 *      Author: hunglv
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



void print_array(int *A, int N);
int *constructFSM(char *P);
int  kmp_as_fsm(char *T, char *P);

int main(){	
	char *T = " bacbabababacaab";
	char *P = " ababaca";
	printf("length of the text : %d\n",strlen(T)-1);
	printf("length of the pattern : %d\n",strlen(P)-1);
	constructFSM(P);
	printf("the pattern  appears at %d\n", kmp_as_fsm(T,P));
	return 0;
}

int * constructFSM(char *P){
	int m = strlen(P)-1; // the first char of P is empty
	int *F = (int *)malloc(m*sizeof(int));
	F[0] = -1;
	int i = 1, j = 0;
	for(; i < m; i++){
		j = F[i-1];
		while(P[j+1] != P[i]&& j >= 0){
			j = F[j];
		}
		F[i] = j +1;
	}
//	print_array(F,m-1);
	return F;
}

// since string in C is indexed from 0, to be consistent with the pseudocode, I put
// a space character in T[0] and P[0] and the real strings are  T[1,...,n] and P[1,....,m]
int  kmp_as_fsm(char *T, char *P){
	int n = strlen(T)-1; // the first character of T is empty
	int m = strlen(P)-1; // the first character of P is empty
	int *F = constructFSM(P);
	int i = 1, j = 0;
	for(; i <= n; i++){
		while(T[i] != P[j+1] && j >= 0){
			j = F[j];
		}
		j++;
		if(j == m){
			return i-m+1;
		}
	}
	return -1;
}


void  print_array(int *A, int N){
	int i = 0;
	for(; i <= N; i++){
		printf("%d ", A[i]);	
	}
	printf("\n");
}

