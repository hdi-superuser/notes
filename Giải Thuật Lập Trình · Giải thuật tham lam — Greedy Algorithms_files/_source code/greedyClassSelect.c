/*
 * An implementation of greedy algorithm for class selection problem
 *
 *  Created on: Jul 2, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<string.h>
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) < (y)) ? (y) : (x))
#define is_equal(x,y) (((x) - (y) == 0) ? 1 : 0)
#define MAX 1000000
#define INFTY 100000000

typedef struct {
	int id;
	int s;
	int f;
} course;

course A[MAX];
int X[MAX];

int compare_finish(const void *a, const void *b);

void main (void){
	int n = 4;
	A[0].id = 0; A[0].s = 0; A[0].f = 2;
	A[1].id = 1; A[1].s = 2; A[1].f = 3;
	A[2].id = 2; A[2].s = 0; A[2].f = 1;
	A[3].id = 3; A[3].s = 1; A[3].f = 2;
	int k = greedy_class_selection(n);
	int i = 0;
	printf("selected jobs:\n");
	for(i = 0; i < k; i++){
		printf("(%d,%d,%d)  ", A[X[i]].id, A[X[i]].s, A[X[i]].f);
	}
	printf("\n");

}

int greedy_class_selection(int n){
	qsort(A, n, sizeof(*A), compare_finish);
	int i = 0;
	int count = 0;
	X[0] = 0;
	for(i = 1; i < n; i++){
		if(A[X[count]].f <= A[i].s){
			count++;
			X[count] = i;
		}
	}
	return count+1;
}


int compare_finish(const void *a, const void *b){
	course *c_a = (course *)a;
	course *c_b = (course *)b;
	return c_a->f - c_b->f;
}

void printCourseArr(course A[], int n){
	int i = 0;
	for(i = 0; i < n; i++){
		printf("(%d,%d,%d)  ", A[i].id, A[i].s, A[i].f);
	}
	printf("\n");
}
