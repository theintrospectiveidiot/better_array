#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include "colors.h"

typedef struct {
	int *traverse;
	int *strides;
	int dim;
	int count;
	int total;
	int capacity;
	long make_sure;
} god_stuff;

#define push(numbrs,...) push_with_size(numbrs,sizeof((int[]){__VA_ARGS__})/sizeof(int),__VA_ARGS__)

#define CAPACITY 1024

int push_with_size(int *numbrs,int wow,...);

#define edd(a,b) _Generic((a), \
	int: _Generic((b), \
		int: edd_num, \
		int*: edd_num_array), \
	int*: _Generic((b), \
		int: edd_array_num, \
		int*: edd_array) \
)(a,b)

int *init(int dim,int *shape);

int *edd_array(int *a,int *b);
int *edd_num_array(int a,int *b);
int *edd_array_num(int *a,int b) {
	return edd_num_array(b,a);
}

int edd_num(int a,int b) {
	return a + b;
}

int *edd_num_array(int a,int *b) {
	god_stuff *headr = (god_stuff *)b - 1;

	if(headr->make_sure != 28602529) {
		ERROR("can't vectorize standard C arrays");
		NOTE("enter god_stuff arrays as arguments instead");
		exit(1);
	}
	
	int *numbrs = init(headr->dim,headr->traverse);
	god_stuff *sum_headr = (god_stuff *)numbrs - 1;
	
	for (int i=0;i<headr->count;i++) {
		push(numbrs,b[i] + a);
	}

	return numbrs;
}

int check_shape (int *a,int *b) {
	god_stuff *headr1 = (god_stuff *)a - 1;
	god_stuff *headr2 = (god_stuff *)b - 1;

	int shape = 1;

	if (headr1->make_sure != 28602529 || headr2->make_sure != 28602529) {
		shape = -1;
		return shape;
	}

	if (headr1->dim != headr2->dim) {
		shape = 0;
		return shape;
	}
	
	for(int i=0;i<headr1->dim;i++) {
		if(shape == 0) {
			break;
		}
		shape = (headr1->traverse[i] == headr2->traverse[i]);
	}
	return shape;
}

int min(int a,int b) {
	return (((a-b) >= 0) ? b:a);
}

int *edd_array(int *a,int *b){
	god_stuff *headr1 = (god_stuff *)a - 1;
	god_stuff *headr2 = (god_stuff *)b - 1;

	if (check_shape(a,b) == 0) {
		ERROR("can't add two god_stuff arrays of different shapes");
		exit(1);
	}

	else if (check_shape(a,b) == -1) {
		ERROR("can't perform 'edd' operation on standard C arrays");
		NOTE("enter god_stuff arrays as arguments instead");
	}

	int *sum = init(headr1->dim,headr1->traverse);
	god_stuff *sum_headr = (god_stuff *)sum -1;
	
	for(int i=0;i<min(headr1->count,headr2->count);i++) {
		push(sum,a[i]+b[i]);
	}
	
	return sum;
}

void init_to_num(int *A,int size,int num);

int *init(int dim,int *shape) {																				
	god_stuff *headr = malloc(sizeof(god_stuff) + (sizeof(int)*CAPACITY));  
	headr->make_sure = 28602529;
	headr->count = 0;	
	headr->dim = dim;	
	headr->total = 1;														
	headr->traverse = malloc(sizeof(int)*headr->dim);	
	headr->strides = malloc(sizeof(int)*headr->dim);	
	init_to_num(headr->strides,headr->dim,1);	
	headr->capacity = CAPACITY;	
	//printf("shape >> ");							
	for (int i=0;i<headr->dim;i++) {			
		//scanf("%d",&headr->traverse[i]);	
		//getchar();
		headr->traverse[i] = shape[i];										
		headr->total *= headr->traverse[i];			
	}			
																
	for (int i=0;i<headr->dim;i++) {								
		for(int j=headr->dim - 1;j>=1+i;j-- ) {				
			*(headr->strides + i) *= *(headr->traverse + j);	
		}	
	}																														
	if(headr->total > headr->capacity) {					
		while (headr->total > headr->capacity) {	
			headr->capacity *= 2;	
		}																							
		headr = realloc(headr,sizeof(god_stuff) + (sizeof(int)*headr->capacity));	
	}										
	int *numbrs = (int *)(headr + 1);	
    return numbrs;	
}

int push_with_size(int *numbrs,int wow,...) {
	va_list arg;
	god_stuff *headr = (god_stuff *)numbrs - 1;
	
	va_start(arg,wow);
	
	for(int i=0;i<wow;i++) {
		if(headr->count >= headr->total) {
			printf("\nFull!\n");
			return 1;
		}
		
		numbrs[headr->count] = va_arg(arg,int);
		//printf("%d ",numbrs[headr->count]);
		headr->count += 1;
	}

	va_end(arg);
	return 0;
}

int summon_by_array(int *numbrs,int *location) {
	god_stuff *headr = (god_stuff *)numbrs - 1;
	int *traversal = headr->traverse;
	
	int val = 0;

	for(int i=0;i<headr->dim;i++) {
		//printf("%d + %d = ",val,location[i]);
		val += location[i]*headr->strides[i];
		//printf("%d  ",val);
	}
	//printf("\n");
	return numbrs[val];
}

int summon(int *numbrs,...) {
	va_list arg;
	god_stuff *headr = (god_stuff *)numbrs - 1;
	int location[headr->dim];

	va_start(arg,numbrs);
	for(int i=0;i<headr->dim;i++) {
		location[i] = va_arg(arg,int);
	}
	va_end(arg);
	int val = 0;
	for(int i=0;i<headr->dim;i++) {
		val += location[i]*headr->strides[i];
	}
	return numbrs[val];
}

void print_row(int *numbrs,int *stuff) {
	god_stuff *headr = (god_stuff *)numbrs - 1;
	for(int i=0;i<stuff[headr->dim - 1];i++) {
		int *temp = stuff;
		temp[headr->dim - 1] = i;
		printf("%d\t",numbrs[summon_by_array(numbrs,temp)]);
	}
}

void init_to_num(int *A,int size,int num) {
	for(int i=0;i<size;i++) {
		A[i] = num;
	}
}



