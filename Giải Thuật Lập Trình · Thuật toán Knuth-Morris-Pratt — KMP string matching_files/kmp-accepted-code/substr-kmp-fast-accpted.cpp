/*
 *  An implementation of KMP matching for this problem: http://vn.spoj.com/problems/SUBSTR/
 *
 *  Created on: Jul 18, 2015
 *      Author: hunglv
 */


#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string.h>

using namespace std;

#define MAX 1000005
string T, P;
int  F[MAX];

void compute_failure(int m);
void fastKMPmatcher(int n, int m);

int main() {
    cin >> T >> P;

    int n=T.size(), m=P.size();
    T = " " + T;
    P = " " + P + "{"; // add a dummy symbol to P, that is convenient to discover multiple pattern P in T
    fastKMPmatcher(n,m+1);
}

void fastKMPmatcher(int n, int m){
	compute_failure(m);
	int i = 1, j = 1;
	for(i = 1; i <=n ; i++){
		while(T[i] != P[j] && j > 0){ // found a mismatch
			j = F[j];   // backup the pattern
		}
		if(j == m-1){ // P[m] = '}' which is a dummy symbol
			printf("%d ",i-(m-1)+1);
		}
		j++;
	}
}

void compute_failure(int m){
	int k = 0, j = 1;
	F[1] = 0;
	for(j=1 ; j < m; j++){
		while(P[j] != P[k] && k > 0){
			k =  F[k];
		}
		k++;
		F[j+1] = k;
	}
}







