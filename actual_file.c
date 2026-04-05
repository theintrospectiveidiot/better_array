#include "interesting.h"

int main() {
	int *numbrs = init(2);
	
	/*for(int i=0;i<((god_stuff *)numbrs - 1)->total;i++) {
		push(numbrs,i+2);
	}*/

	push(numbrs,1,2,3);
	push(numbrs,4,5);

	god_stuff *headr = (god_stuff *)numbrs - 1;
	/*for (int k=0;k<((god_stuff *)numbrs - 1)->traverse[0];k++) {
		for(int j=0;j<((god_stuff *)numbrs - 1)->traverse[1];j++) {
			for(int i=0;i<((god_stuff *)numbrs - 1)->traverse[2];i++) {
				printf("numbrs[%d][%d][%d] = %d\t",k,j,i,numbrs[k*(((god_stuff *)numbrs - 1)->traverse[2]*((god_stuff *)numbrs - 1)->traverse[1]) + j*(((god_stuff *)numbrs - 1)->traverse[2]) + i]);
			}
			printf("\n");
		}
		printf("\n\n");
	}*/

	printf("desired num = %d\n",summon(numbrs,1,1));
}
