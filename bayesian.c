#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>


double lfunc1(double x1, double x2){
    double inner = -pow(1-x1,2) - 100*pow(x2-pow(x1,2),2);
    double ans = exp(inner);
    return ans;
}

double lfunc1_inner(double x1, double x2){
    double inner = -pow(1-x1,2) - 100*pow(x2-pow(x1,2),2);
    return inner;
}

double rand_number(){
    double rn = ((double)rand())/((double) RAND_MAX);//going from 0 to 1
    rn = 10*rn-5.;//going from -5 to 5 //this is the domain of the square
    return rn; 
}


void lfunc_plot(){
    FILE *fp; //opens file
    fp = fopen("/home/jpl/bpoints.dat","a" );
    
    for(double x1=-5;x1<=5;x1=x1+0.01){
        for(double x2=-5; x2 <= 5; x2=x2+0.01){
            double a = lfunc1_inner(x1, x2);
            fprintf(fp,"%f %f %e\n", x1, x2, a);
           
        }
    }
    fclose(fp);
}

double lfunc1_integral(double N){
    double v = 100.0;//the volume of the double integral: (5--5)*(5--5) = 100
    double ans = 0.0;

    for(int i=0; i<N; ++i){//iteration from -5 to 5
        double x1 = rand_number();
        double x2 = rand_number();
        double func = lfunc1(x1,x2);
        ans = ans + func;
    }
    return ans*v/N;
}

int main(){
    srand(time(NULL));//generate seed
    //lfunc_plot();
    double integral = lfunc1_integral(pow(10,8));
    //printf("%f\n", integral);
    
    clock_t start = clock();
    for(int k=2;k<=9;k++){
        double N = pow(10, k);
        double ln_func = lfunc1_integral(N);
        ln_func = log(ln_func);
        clock_t end = clock();
        double cputime = ((double) end - start)/CLOCKS_PER_SEC;
        printf("%f %f\n", ln_func, cputime);
    }
    return 0;
}

