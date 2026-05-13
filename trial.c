#include "interesting.h" 

int main(int argc,char *argv[]) {
    
    how_many = 0;

    f = fopen("logs.txt","w");
    int cond;

    printf("Please: ");
    scanf("%d",&cond);
    
    int owl = 2;

    int c_better = /*hello*/ 5;

    printf("%d\n",c_better);

	int *numbrs = init(owl,(int[]){2,2});
    push(numbrs,1,2,3);

	int *stuff = init(2,(int[]){2,2});
    push(stuff,1,2,3,4);
	
	printf("%d\n",edd(1,9));

	int *sum = edd(2,numbrs);
	for(int i=0;i<4;i++) {
		printf("%d ",sum[i]);
	}
	printf("\n");

	printf("sum[1][1] = %d\n",summon(sum,1,1));

	int *sum2 = edd(numbrs,stuff);
	for(int i=0;i<4;i++) {
		printf("%d ",sum2[i]);
	}
	printf("\n");

	printf("sum2[0][1] = %d\n",summon(sum2,0,1));
	printf("count = %d\n",((god_stuff *)sum - 1)->count);
	printf("count = %d\n",((god_stuff *)sum2 - 1)->count);
	int *check = init(3,(int[]){3,3,3});
    int *hmm = init(4,(int[]){4,4,4,4}); 
   
    int *yes;
    int *no;

    if (cond == 1) {
        yes = init(2,(int[]){2,2});
    }
    else {no = init(3,(int[]){3,3,3});} 

    free_ptr(numbrs);
    free_ptr(stuff);
    /*free_ptr(sum);
    free_ptr(check);
    free_ptr(sum2);
    free_ptr(yes);*/
    printf("how_many = %d\n",how_many);
    goodbye_everybody();

    int a = 2;
	int *ptr = &a;
	int *sum4 = edd(2,ptr);
    

	int *sum3 = edd(stuff,check);

    int lmnop = 123;	
}
