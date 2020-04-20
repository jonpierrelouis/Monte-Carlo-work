#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

double Pi = 3.14159265359; //pi

//Step 1: Code in the formula that will be integrated.
//This answer will be compared to the summ of the monte carlo integral
double int_func(double x){//this is the function that will be integrated
    //return 1;
    //return 1/(1+x*x);
    return x*x;
}


//Step 2: Set up a random number to be generated from intervals -1 to 1
//these numbers will be used to compute the equation at different points
double rand_number(){
    double rn = ((double)rand())/((double) RAND_MAX);
    rn = 2*rn-1.;
    return rn;
}

int main(int argc, char **argv){
    srand(time(NULL)); //generation starting seed
    FILE *fp; //opens file
    //fp = fopen("/home/jpl/mc_err.dat", "a");
    fp = fopen("/home/jpl/mc_mean.dat","a" );

    int N = atoi( argv[1] );
    //printf("x=%f\n",integration(N));
    
    double v = 2.0;//v is the volume of the integral (1-(-1))
    double mc = 0.0;
    //Step 3: Set up the integration for the summation for the monte carlo integration
    //this will be done with a for loop
    for(int i=0;i<N;i++){
        //Step 4:Set up the Monte Carlo integration in the for-loop
        mc = mc + (v/N)*int_func(rand_number());
    }
    printf("Monte Carlo Integration: %f\n", mc);
    //printf("Trapazoid Rule Integration: %f\n", integration(N));

    double abs_err = fabs(Pi/2.- mc);
  
    printf("%e\n", abs_err);//put data in a file
    fprintf(fp,"%e\n", abs_err);
    fclose(fp);
}

