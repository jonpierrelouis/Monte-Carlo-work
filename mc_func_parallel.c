#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<omp.h>

double func(unsigned int myseed){//this is the function that will be integrated
    double total = 1;
    double x[10] = {0.};
    //double test[10] = {.1, .2, .3, .4, .5, .6, .7, .8, .9, 1.};
    for(int i =0; i<10;i++){
        double rn = ((double)rand_r(&myseed))/((double) RAND_MAX);
        rn = 2*rn-1.;
        x[i] = rn;  
    }
    for(int j = 0; j<9;j++){
        double num = pow(1-x[j],2); 
        double ber  = 100*pow( x[j+1] - pow(x[j],2),2 );
        total = total + num + ber;
    }
    total = total*-1;
    return exp(total);
}
//rand_r reenterent 
//mpi reduction
int main(int argc, char **argv){
    double start = omp_get_wtime();
    omp_set_num_threads(2);
    srand(time(NULL));
    unsigned long long int N = atoi( argv[1] );
    double v = 1024.;//v is the volume of the integral (1-(-1))**10
    double mc = 0.0;
    double f;
    int k = 2;
    #pragma omp parallel for private(f) shared (mc)
        for(unsigned long long int i=1;i<N+1;i++){
       // unsigned int id = omp_get_thread_num();//tread number
        unsigned int seed = rand();
        f = func(seed);//different seed for each thread
        mc = mc + f;
        if(pow(4,k) == i){//print condition
            printf("%llu %e\n", i, (v/i)*mc);
            k++;
        }
    }
    
    printf("%llu %e\n",N, mc*(v/N));
    double end = omp_get_wtime();
    double cputime = end - start;
    printf("Total Time: %f\n", cputime);
}

