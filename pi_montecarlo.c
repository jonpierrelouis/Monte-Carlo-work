#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

double rand_number(){
    double rn = ((double)rand())/((double) RAND_MAX);//going from 0 to 1
    rn = 2*rn-1.;//going from -1 to 1 //this is the domain of the square
    return rn;
}


double montecarlo(long long int N){
    double D1 = 0;
    //the summation
    for(long long int i = 0; i<N;i++){
        double x1 = rand_number();
        double x2 = rand_number();
        //printf("%i\n",i);

        //printf("%f %f\n",x1, x2);
        if(pow(x1,2)+pow(x2,2) <=1){//the domain of the circle
            D1 = D1 + 1;//if in domain add 1
        }
    }

    double pi_n = 4*D1/N;
    //printf("%f\n",pi_n);

    return pi_n;
}


int main(){
    //FILE *fp; //opens file
    //fp = fopen("/home/jpl/eas520_hw2/pi_calc9.dat","a" );
    srand(time(NULL));//generate seed
    double cpu_time;
    const double pi = 3.141592653589793;

    //double ans = 0;
    for(int k = 1; k<11;k++){
        clock_t start = clock();
        long long int N = pow(10, k);
        double ans = montecarlo(N);
        
        clock_t end = clock();
        cpu_time = ((double) (end - start))/CLOCKS_PER_SEC;
        double err = fabs(ans - pi);
        //fprintf(fp,"%d %f %f %f\n", k, ans, err, cpu_time);
        printf("%d %f %f %f\n", k, ans, err, cpu_time);
    }
    //fclose(fp);
}
