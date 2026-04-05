#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

typedef struct {
	int *traverse;
	int dim;
	int count;
	int total;
	int capacity;
} god_stuff;

#define push(numbrs,...) push_with_size(numbrs,sizeof((int[]){__VA_ARGS__})/sizeof(int),__VA_ARGS__)

#define CAPACITY 1024

int *init(int dim) {
	god_stuff *headr = malloc(sizeof(god_stuff) + (sizeof(int)*CAPACITY));  
	headr->count = 0;
	headr->dim = dim;
	headr->total = 1;
	headr->traverse = malloc(sizeof(int)*headr->dim);
	headr->capacity = CAPACITY;
	for (int i=0;i<headr->dim;i++) {
		scanf("%d",&headr->traverse[i]);
		getchar();
		headr->total *= headr->traverse[i];
	}

	if(headr->total > headr->capacity) {
		headr->capacity *= 2;
		headr = realloc(headr,sizeof(god_stuff) + (sizeof(int)*headr->capacity));
	}
	int *numbrs = (int *)(headr + 1);
    return numbrs;
}

int push_with_size(int *numbrs,...) {
	va_list arg;
	god_stuff *headr = (god_stuff *)numbrs - 1;
	
	va_start(arg,numbrs);
	int wow = va_arg(arg,int);
	
	for(int i=0;i<wow;i++) {
		if(headr->count >= headr->total) {
			printf("\nFull!\n");
			return 1;
		}
		
		numbrs[headr->count] = va_arg(arg,int);
		headr->count += 1;
		printf("%d ",numbrs[i]);
	}

	printf("\n%d\n",headr->count);

	va_end(arg);
	return 0;
}

int summon_by_array(int *numbrs,int *location) {
	god_stuff *headr = (god_stuff *)numbrs - 1;
	int *traversal = headr->traverse;
	
	int val = 0;

	for(int i=0;i<headr->dim;i++) {
		for(int j=headr->dim - 1;j>=1+i;j-- ) {
			*(location + i) *= *(traversal + j);
		}
		//printf("%d + %d = ",val,location[i]);
		val += *(location + i);
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

	int *traversal = headr->traverse;

	int val = 0;

	for(int i=0;i<headr->dim;i++) {
		for(int j=headr->dim - 1;j>=1+i;j-- ) {
			*(location + i) *= *(traversal + j);
		}
		//printf("%d + %d = ",val,location[i]);
		val += *(location + i);
		//printf("%d  ",val);
	}
	//printf("\n");
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

void init_to_zero(int *A,int size) {
	for(int i=0;i<size;i++) {
		A[i] = 0;
	}
}
