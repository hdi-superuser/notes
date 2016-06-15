/*
 * An implementation for testing bit manipulation
 * See http://www.giaithuatlaptrinh.com/?p=515 for details
 *
 *  Created on: Sep 14, 2015
 *      Author: hunglv
 */

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

typedef unsigned long long int LLU;

int B[255];// the lookup table for counting bits
unsigned int m0 = 0x55555555; // a magic mask
unsigned int m1 = 0x33333333; // a magic mask
unsigned int m2 = 0x0f0f0f0f; // a magic mask
unsigned int m3 = 0x00ff00ff; // a magic mask
unsigned int m4 = 0x0000ffff; // a magic mask

int is_power_of_2A(LLU x);
int is_power_of_2B(LLU x);
int is_diff_signA(int x, int y);
int is_diff_signB(int x, int y);
int absa(int x);
int absb(int x);
int absc(int x);
int sign_extA(int x, int  b);
int sign_extB(int x, int  b);
int sign_extC(int x, int  b);
void exchange_add(int *x, int *y);
void exchange_xor(int *x, int *y);
int minA(int x, int y );
int minB(int x, int y );
int cond_negationA(int x, int f);
int cond_negationB(int x, int f);
void build_lookup_table();
int count_onesA(unsigned int x);
int count_onesB(unsigned int x);
int count_onesC(unsigned int x);
int bf_count_zeros(unsigned int x);
int dc_count_zeros(unsigned int x);
int mm_count_zeros(unsigned int x);
unsigned int bit_reversalA(unsigned int x);
unsigned int bit_reversalB(unsigned int x);
unsigned int swap_bitsA(unsigned int x, int i, int j);
unsigned int swap_bitsB(unsigned int x, int i, int j);

void is_power_of_2_test();
void is_diff_sign_test();
void abs_test();
void sign_ext_test();
void exchange_test();
void min_test();
void cond_negation_test();
void count_ones_test();
void count_zeros_test();
void bit_reversal_test();
void bit_swap_test();


int is_power_of_2A(LLU x){
	LLU yy = 1, y = 0;
	for(y = 0; y < 64; y++){
		if(yy == x){
			return TRUE;
		}
		yy = yy << 1;
	}
	return FALSE;

}
/*
 * Note: this method is only correct for x != 0
 * For x = 0, we need to modify this method a bit.
 */
int is_power_of_2B(LLU x){
	if( (x&(x-1)) == 0){
		return TRUE;
	}else {
		return FALSE;
	}
}

int is_diff_signA(int x, int y){
	return (x^y) < 0;
}
int is_diff_signB(int x, int y){
	return ((unsigned)(x^y))>> (31);
}


int absa(int x){
	int m = x >> 31; // the sign mask
	return x - ((2*x)&m);
}

int absb(int x){
	int m = x >> 31; // the sign mask
	return (x^m) - m;
}

int absc(int x){
	int m = x >> 31; // the sign mask
	return (x+m)^m;
}

int sign_extA(int x, int  b){
	return (x << (32-b)) >> (32-b);
}

int sign_extB(int x, int  b){
	int m = 1 << (b-1); // the signed bit
	x = x&((1<<b)-1); // clear k-b leading bits
	return (-(x&m))|x;
}

int sign_extC(int x, int b){
	int m = 1 << (b-1);
	x = x&((1<<b)-1); // clear k-b leading bits
	return (x^m)-m;
}

void exchange_add(int *x, int *y){
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}

void exchange_xor(int *x, int *y){
	*x = *x^*y;
	*y = *x^*y;
	*x = *x^*y;
}

int minA(int x, int y ){
	int m = -(x<y);
	return y^((x^y)&m);
}

int minB(int x, int y ){
	int m = -(x<y);
	return y + ((x-y)&m);
}

/*x is negated or not depends on the flag f that only has value 0/1*/
int cond_negationA(int x, int f){
	return (x^(-f))+f;
}

int cond_negationB(int x, int f){
	return (x-f)^(-f);
}

int count_onesA(unsigned int x){
	int c  = 0, i = 0;
	for(i = 0; i < 32; i++){
		c += (x&1);
		x  >>= 1;
	}
	return c;
}

void build_lookup_table(){
	B[0] = 0; B[1] = 1;
	int i = 0, j = 0,s = 0, t = 0;
	for( i = 1; i <= 8; i++){
		s = 1 <<i; t = (1 << (i+1))-1;
		for(j = s; j <= t; j++){
			B[j] =B[j& ((1 <<i)-1)] + (j >> i);
		}
	}
}
/* Remember to build the lookup table before using this method for counting 1s */
int count_onesB(unsigned int x){
	int c  = 0;
	c+= B[x&0x000000ff];
	x >>= 8;
	c+= B[x&0x000000ff];
	x >>= 8;
	c+= B[x&0x000000ff];
	x >>= 8;
	c+= B[x&0x000000ff];
	return c;
}

int count_onesC(unsigned int x){
	int c  = 0;
	while(x != 0){
		c++;
		x = x&(x-1);
	}
	return c;
}

int bf_count_zeros(unsigned int x){
	int c = 0;
	while((x&1) == 0 && c!= 32){
		c++;
		x >>= 1;
	}
	return c;
}

/* this method doesn't work for x = 0, readers must be careful when using it*/

int dc_count_zeros(unsigned int x){
	if( (x&1) != 0){
		return 0;
	}
	int c = 0;
	if((x& 0x0000ffff) == 0){
		c+= 16;
		x >>= 16;
	}
	if((x & 0x000000ff )== 0){
		c+= 8;
		x >>= 8;
	}
	if((x & 0x0000000f) == 0){
		c += 4;
		x >>= 4;
	}
	if((x & 0x00000003) == 0){
		c += 2;
		x >>= 2;
	}
	c+= 1 - (x&1);
	return c;
}

/* this method doesn't work for x = 0, readers must be careful when using it*/

int mm_count_zeros(unsigned int x){
	x &= -x;
	int c  = 0;
	if((x&m4) == 0) c+= 16;
	if((x&m3) == 0) c+= 8;
	if((x&m2) == 0) c+= 4;
	if((x&m1) == 0) c+= 2;
	if((x&m0) == 0) c+= 1;
	return c;
}

unsigned int bit_reversalA(unsigned int x){
	int s = 32;
	unsigned int y = 0;
	while( x!= 0){
		y <<=1;
		y |= (x&1);
		x >>= 1;
		s--;
	}
	y <<= s;
	return y;
}

unsigned int bit_reversalB(unsigned int x){
	x = ((x>>1)&m0)|(((x&m0)<<1));
	x = ((x>>2)&m1)|(((x&m1)<<2));
	x = ((x>>4)&m2)|(((x&m2)<<4));
	x = ((x>>8)&m3)|(((x&m3)<<8));
	x = (x >> 16)|(x << 16);
	return x;
}

/* Swap x_i and x_j (32 > i > j) of an unsigned integer x
 * Note x = x_31 x_30 .... x_1 x_0*/
unsigned int swap_bitsA(unsigned int x, int i, int j){
	int delta = i - j;
	unsigned int y = (x >> delta)& (1 << j);
	unsigned int z = (x << delta)&(1<< i);
	unsigned int m = ~((1<<i) | (1<<j));
	x = (x&m)|y|z;
	return x;
}
/* Swap x_i and x_j (32 > i > j) of an unsigned integer x
 * Note x = x_31 x_30 .... x_1 x_0*/

unsigned int swap_bitsB(unsigned int x, int i, int j){
	int delta = i - j;
	unsigned int y = (x ^(x>>delta))&(1<<j);
	x = x^y^(y<< delta);
	return x;
}

int main (void){
	int i = 0;
	is_power_of_2_test();
	is_diff_sign_test();
	abs_test();
	sign_ext_test();
	exchange_test();
	min_test();
	cond_negation_test();
	build_lookup_table();
	count_ones_test();
	count_zeros_test();
	bit_reversal_test();
	bit_swap_test();
}
void is_power_of_2_test(){
	LLU x = (LLU)1125899906842626;
	printf("test #1A: is %llu a power of 2? Answer  = %d\n",x, is_power_of_2A(x));
	printf("test #1B: is %llu a power of 2? Answer  = %d\n",x, is_power_of_2B(x));
	LLU y = (LLU) 524288;
	printf("test #2A: is %llu a power of 2? Answer  = %d\n",y, is_power_of_2A(y));
	printf("test #2B: is %llu a power of 2? Answer  = %d\n",y , is_power_of_2B(y));

}
void is_diff_sign_test(){
	int x = 336217884;
	int y = 1003744891;
	printf("test #1A: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signA(x,y));
	printf("test #1B: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signB(x,y));
	x = -872994028;
	y = -784041101;
	printf("test #2A: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signA(x,y));
	printf("test #2B: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signB(x,y));
	x = 43400794;
	y = -905739579;
	printf("test #3A: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signA(x,y));
	printf("test #3B: does %d and %d has different signs ? Answer  = %d\n",x,y, is_diff_signB(x,y));

}

void sign_ext_test(){
	int x = 1875335928;
	int b = 10;
	printf("test #1A: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extA(x,b));
	printf("test #1B: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extB(x,b));
	printf("test #1C: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extC(x,b));
	x = 1957747793;
	b = 6;
	printf("test #2A: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extA(x,b));
	printf("test #2B: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extB(x,b));
	printf("test #2C: the signed extension of ");
	display_bit_int(x);
	printf("\t\t at %d-th bit is: ",b);
	display_bit_int(sign_extC(x,b));
}

void abs_test(){
	int x = -129794085;
	printf("test #1A: the abstract value of %d is: %d\n",x, absa(x));
	printf("test #1B: the abstract value of %d is: %d\n",x, absb(x));
	printf("test #1C: the abstract value of %d is: %d\n",x, absc(x));
	x = 910468188;
	printf("test #2A: the abstract value of %d is: %d\n",x, absa(x));
	printf("test #2B: the abstract value of %d is: %d\n",x, absb(x));
	printf("test #2C: the abstract value of %d is: %d\n",x, absc(x));
}

void exchange_test(){
	int x = -923618978;
	int y = -634248373;
	int z = x; int t  = y;
	printf("test #1A: exchange x = %d  y = %d\n",x, y);
	exchange_add(&x,&y);
	printf("\t result: x = %d    y = %d\n",x,y);
	printf("test #1B: exchange x = %d  y = %d\n",z, t);
	exchange_xor(&z,&t);
	printf("\t result: x = %d    y = %d\n",z,t);
	x = 607950953;
	y = 640895091;
	z = x; t  = y;
	printf("test #2A: exchange x = %d  y = %d\n",x, y);
	exchange_add(&x,&y);
	printf("\t result: x = %d    y = %d\n",x,y);
	printf("test #2B: exchange x = %d  y = %d\n",z, t);
	exchange_xor(&z,&t);
	printf("\t result: x = %d    y = %d\n",z,t);
	x = 884005969;
	y = -649503489;
	z = x; t  = y;
	printf("test #3A: exchange x = %d  y = %d\n",x, y);
	exchange_add(&x,&y);
	printf("\t result: x = %d    y = %d\n",x,y);
	printf("test #3B: exchange x = %d  y = %d\n",z, t);
	exchange_xor(&z,&t);
	printf("\t result: x = %d    y = %d\n",z,t);
}

void min_test(){
	int x = 299484516;
	int y = 557776325;
	printf("test #1A: min(%d,%d) = %d\n",x, y, minA(x,y));
	printf("test #1B: min(%d,%d) = %d\n",x, y, minB(x,y));
	x = -872994028;
	y = -784041101;
	printf("test #2A: min(%d,%d) = %d\n",x, y, minA(x,y));
	printf("test #2B: min(%d,%d) = %d\n",x, y, minB(x,y));
	x = 1069015210;
	y = -957654060;
	printf("test #3A: min(%d,%d) = %d\n",x, y, minA(x,y));
	printf("test #3B: min(%d,%d) = %d\n",x, y, minB(x,y));
}

void cond_negation_test(){
	int x = 403429263;
	int f = 0;
	printf("test #1A:x = %d  f = %d result = %d\n",x, f, cond_negationA(x,f));
	printf("test #1B:x = %d  f = %d result = %d\n",x, f, cond_negationB(x,f));
	x = -128624548;
	f = 0;
	printf("test #2A:x = %d  f = %d result = %d\n",x, f, cond_negationA(x,f));
	printf("test #2B:x = %d  f = %d result = %d\n",x, f, cond_negationB(x,f));
	x =-582036421 ;
	f = 1;
	printf("test #3A:x = %d  f = %d result = %d\n",x, f, cond_negationA(x,f));
	printf("test #3B:x = %d  f = %d result = %d\n",x, f, cond_negationB(x,f));
	x = 395606270;
	f = 1;
	printf("test #4A:x = %d  f = %d result = %d\n",x, f, cond_negationA(x,f));
	printf("test #4B:x = %d  f = %d result = %d\n",x, f, cond_negationB(x,f));

}

void count_ones_test(){
	unsigned int x = -226810938;
	display_bit_int(x);
	printf("test #1A: #1 = %d\n",count_onesA(x));
	printf("test #1B: #1 = %d\n",count_onesB(x));
	printf("test #1C: #1 = %d\n",count_onesC(x));
	x = 607950953;
	display_bit_int(x);
	printf("test #2A: #1 = %d\n",count_onesA(x));
	printf("test #2B: #1 = %d\n",count_onesB(x));
	printf("test #2C: #1 = %d\n",count_onesC(x));

}
void count_zeros_test(){
	unsigned int x = -113246208;
	display_bit_int(x);
	printf("test #1A: #0 = %d\n",bf_count_zeros(x));
	printf("test #1B: #0 = %d\n",dc_count_zeros(x));
	printf("test #1C: #0 = %d\n",mm_count_zeros(x));
	x = 724303872;
	display_bit_int(x);
	printf("test #2A: #0 = %d\n",bf_count_zeros(x));
	printf("test #2B: #0 = %d\n",dc_count_zeros(x));
	printf("test #2C: #0 = %d\n",mm_count_zeros(x));


}

void bit_reversal_test(){
	unsigned int x = 640895091;
	display_bit_int(x);
	printf("test #1A: ");
	display_bit_int(bit_reversalA(x));
	printf("test #1B: ");
	display_bit_int(bit_reversalB(x));
	x =-218105598;
	display_bit_int(x);
	printf("test #2A: ");
	display_bit_int(bit_reversalA(x));
	printf("test #2B: ");
	display_bit_int(bit_reversalB(x));

}

void bit_swap_test(){
	unsigned int x = -136371661;
	int i = 28,j = 21;
	display_bit_int(x);
	printf("test #1A: ");
	display_bit_int(swap_bitsA(x,i,j));
	printf("test #1B: ");
	display_bit_int(swap_bitsB(x,i,j));
	x =273069481;
	i = 15,j = 11;
	display_bit_int(x);
	printf("test #2A: ");
	display_bit_int(swap_bitsA(x,i,j));
	printf("test #2B: ");
	display_bit_int(swap_bitsB(x,i,j));
	x =-328316163;
	i = 9,j = 7;
	display_bit_int(x);
	printf("test #3A: ");
	display_bit_int(swap_bitsA(x,i,j));
	printf("test #3B: ");
	display_bit_int(swap_bitsB(x,i,j));
}

void display_bit_int(int n){
	int bit[32];
	int i = 0;
	for(i = 0; i < 32; i++){
		bit[31-i] = (n& 1);
		n = n >> 1;
	}
	for(i = 0; i < 32;i ++){
		printf("%d", bit[i]);
	}
	printf("\n");
}

