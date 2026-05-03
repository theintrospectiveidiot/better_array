#include<stdio.h>
#include<math.h>
#include<time.h>
#include "haha.h"

void Square_Trick(double* m1,double *m2,double* c,double* z,double* rmse,int y,double eta,int x1,int x2)
{
*z = *m1*(x1) + *m2*(x2) + *c;
*m1 += eta*((double)y - *z)*x1;
*m2 += eta*((double)y - *z)*x2;
*c += eta*(y - *z);
}

int main()
{

f = fopen("logs.txt","w");

clock_t start,end;
double time;

start = clock();
int *X = init(2,(int[]){4,2});
int *l1 = init(1,(int[]){4});

push(X,5,4,2,3,8,6,6,5);
push(l1,67,47,84,71);

printf("%d\n",summon(X,2,1));

//printf("%d\n",((god_stuff *)f - 1)->traverse[0]);
//printf("%d\n",((god_stuff *)l1 - 1)->traverse[0]);
//
//for(int i=0;i<6;i++) {
//	printf("%f ",summon(f,i));
//}
//
//printf("\n");
//
//for(int i=0;i<6;i++) {
//	printf("%f ",summon(l1,i));
//}
//
//printf("\n");

double m1=0,m2=0,c=0,eta=0.01,rmse=0,z=0;
//FILE *g;
//FILE *h;
//FILE *p;
//h = popen("gnuplot -persist","w");
//g = popen("gnuplot -persist","w");
int i,j,k;


//fprintf(g,"set title 'RMSE vs Iterations'\n");
//fprintf(g,"set xlabel 'No. of Iterations'\n");
//fprintf(g,"set ylabel 'RMSE'\n");
//fprintf(g,"plot '-' with linespoints title 'Error'\n");
//
//
//fprintf(h,"set title 'Linear Regression'\n");
//fprintf(h,"set xlabel 'No. of Rooms'\n");
//fprintf(h,"set ylabel 'Predicted Price'\n");
//fprintf(h,"set key off\n");
//fprintf(h,"plot (%f*x)+%f with line linewidth 4\n",m,c);


for(i=0;i<5;i++)
{for(k=0;k<200;k++){
rmse = 00;
 for(j=0;j<4;j++){Square_Trick(&m1,&m2,&c,&z,&rmse,summon_by_array(l1,(int[]){j}),eta,summon(X,j,0),summon(X,j,1));
                   rmse += (summon(l1,j)-z)*(summon(l1,j)-z);}
 //fprintf(g,"%d %f\n",(i+1)*(k+1),sqrtf(rmse/6));
 }

 printf("\nAfter %04d iterations, m1 = %f\t m2 = %f\t c = %f\nrmse = %f\n",200*(i+1),m1,m2,c,sqrt(rmse/4));
 //fprintf(h,"replot (%f*x)+%f with line linewidth 4\n",m,c);
}

end = clock();

time = ((double)(end - start))/CLOCKS_PER_SEC;

//fprintf(g,"e\n");
//pclose(g);
//fprintf(h,"e\n");
//pclose(h);
printf("Time Taken: %f seconds\n",time);

printf("\n%f\n",(m1*5) + (m2*4) + (c));
printf("%f\n",(m1*2) + (m2*3) + (c));
printf("%f\n",(m1*8) + (m2*6) + (c));
printf("%f\n",(m1*6) + (m2*5) + (c));

//i love making u believe what u get is what u see, but i am so fake happy, i feel so fake happy, i bet everybody here is just as insincere, we're all so fake happy, i know fake happy...

}
