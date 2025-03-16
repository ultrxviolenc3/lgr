#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double factorial(int n) {
double result = 1.0;
 for(int i=2;i<=n;i++) 
 {
      result*=i;
    }
    return result;
}
double lagr(double *x,double *f,double t,int n) {
    double result=0.0;
    for (int i=0; i <n;i++) 
    {
        double term=f[i];
        for (int j=0;j<n;j++) 
        {
            if(i!=j) {
                term*=(t-x[j])/(x[i]-x[j]);
            }
        }
        result+=term;
    }
    return result;
}
int main() {
    int n_values[]={2,3,4,5,6,7,8,9,10,11,12,13,14,17,33,65,101};
    int num_tests=sizeof(n_values)/sizeof(n_values[0]);
    int M=100000; 
     
    FILE*file=fopen("output.txt","w");
    if (file==NULL) {
        printf("Ошибка при открытии файла!\n");
        return 1;
    }
    fprintf(file," n\tПогрешность\t\tТеоретическая оценка\n");
    for (int test=0;test<num_tests;test++) {
        int n=n_values[test];
       double  *x=(double *)malloc(n*sizeof(double));
       double  *f=(double *)malloc(n*sizeof(double));
       double a=0.0;
       double b=1.0;
  double step=(b-a)/(n-1);
 for(int i=0;i<n;i++){
    x[i]=a+i*step;
    f[i]=sin(x[i]);
   }
double max_error=0.0;
for(int j=0;j<=M;j++){
    double t=(double)j/M;
    double exact=sin(t);
    double interp=lagr(x,f,t,n);
    double error=fabs(exact-interp);
    if(error>max_error){
        max_error=error;
    }
} 
double power_of_2=1.0;
for (int i=0; i<n;i++) {
    power_of_2*=2;
}
 double th=1.0/(factorial(n)*power_of_2);
 fprintf(file,"%2d\t%.10e\t%.10e\n",n,max_error,th);
}
    return 0;
}
