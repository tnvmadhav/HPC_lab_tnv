#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define PI 3.1415926538837211
#define S_SIZE 10000000

int intervals, num_threads;

double calculate_pi() {
    double sum = 0.0;
    double step = 1.0 / intervals;
    double x;
    int i;

    #pragma omp parallel for private(x) reduction(+:sum)
    for (i=1; i < intervals; i++) {
        x = step * (i+0.5); // We take 0.5 as we are taking middle point of rectangular area
        sum += 4.0 / (1.0 + x * x);
    }

    return sum * step;
}

double calculate_pi_tnv_parallel(){
int seed = 0;
int i = 0;
float x,y;
int count = 0;
double pi = 0;
double start , end;
start = omp_get_wtime();
#pragma omp parallel for private(x,y) firstprivate(seed) reduction(+:count)
for(i= 0; i < S_SIZE ; i++){
	x = (float)(rand_r(&i))/RAND_MAX;
	y = (float)(rand_r(&i))/RAND_MAX;

if ( x*x + y*y <= 1){
	count++;
}
}
end = omp_get_wtime();
pi = (float)count / S_SIZE;
printf(" Parallel PI : %lf \n",pi*4);
printf(" Actual PI : %lf \n",PI);
printf("Time: %lf \n",(double)(end-start));
} 


double calculate_pi_tnv_serial(){
int seed = 0;
int i = 0;
float x,y;
int count = 0;
double pi = 0;
double start , end;
start = omp_get_wtime();
for(i= 0; i < S_SIZE ; i++){
	x = (float)(rand_r(&seed))/RAND_MAX;
	y = (float)(rand_r(&seed))/RAND_MAX;

if ( x*x + y*y <= 1){
	count++;
}
}
end = omp_get_wtime();
pi = (float)count / S_SIZE;
printf("Serial PI : %lf \n",pi*4);
printf("Actual PI  :%lf \n",PI);
printf("Time: %lf \n",(double)(end-start));
}

int main(int argc, char const *argv[]) {

    intervals = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    omp_set_num_threads(num_threads);

    double t1 = omp_get_wtime();
    double pi_result = calculate_pi_tnv_parallel();
    double t2 = omp_get_wtime();

    double ts1 = omp_get_wtime();
    double pi_result2 = calculate_pi_tnv_serial();
    double ts2 = omp_get_wtime();
    return 0;
}
