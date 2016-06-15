/*
 * An implementation of KMP matching for this problem: http://vn.spoj.com/problems/SUBSTR/
 *
 *  Created on: Jul 13, 2015
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
int  S[28][MAX];
char Alph[29] = " abcdefghijklmnopqrstuvwxyz{"; // the alphabet

void compute_backup(int m);
void KMPmatcher(int n, int m);

int main() {
    cin >> T >> P;

    int n=T.size(), m=P.size();
    T = " " + T;
    P = " " + P + "{"; // add a dummy symbol to P, that is convenient to discover multiple pattern P in T
    KMPmatcher(n,m+1);
}

void KMPmatcher(int n, int m){
	compute_backup(m);
	int i = 1, j = 1;
	int p = 0;
	for(i = 1; i <= n; i++){
		if(T[i] != P[j]){
			p = T[i]-96;
			j = S[p][j];
		}
		else j++;
		if(j == m){  // P[m] = '}' which is a dummy symbol
			printf("%d ",i-(m-1)+1);
		}
	}

}

void compute_backup(int m){
	int X = -1;
	int j = 0 ,k = 0;
	int p = 0;
	for(k = 0; k <28 ; k ++){
		S[k][0] = 1;
	}
	for(j = 1; j <= m ; j++){
		for(k = 1; k < 28; k++){
			S[k][j] = S[k][X+1];
		}
		p = P[j]-96;
		S[p][j] = j+1;
		X = S[p][X+1]-1;
	}
}



