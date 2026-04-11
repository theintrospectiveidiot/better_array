#include "interesting.h"

int main() {
	printf("dim >> ");
	int dim;
	scanf("%d",&dim);
	int *numbrs = init(dim,(int[]){3,3,3});

	push(numbrs,1,2,3);
	push(numbrs,4,5);
	push(numbrs,6,7,8,9);

	god_stuff *headr = (god_stuff *)numbrs - 1;
	/*for (int k=0;k<((god_stuff *)numbrs - 1)->traverse[0];k++) {
		for(int j=0;j<((god_stuff *)numbrs - 1)->traverse[1];j++) {
			for(int i=0;i<((god_stuff *)numbrs - 1)->traverse[2];i++) {
				printf("numbrs[%d][%d][%d] = %d\t",k,j,i,numbrs[k*headr->strides[0] + j*headr->strides[1] + i*headr->strides[2]]);
			}
			printf("\n");
		}
		printf("\n\n");
	}*/

	printf("desired num = %d\n",summon(numbrs,0,1,1));
}
