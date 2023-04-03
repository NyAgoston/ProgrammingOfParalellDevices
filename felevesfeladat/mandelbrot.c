#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

double mapping(double x,double res,double min, double max);

int main(int argc, char* argv[])
{
    const double xmin = -2.0;
    const double xmax = 2.0;
    const double ymin = -2.0;
    const double ymax = 2.0;
    const int maxiter = 1000;
    const int xres = 1024;
    const int yres = (xres*(ymax-ymin))/(xmax-xmin);


    FILE * fp = fopen("test.ppm","wb");

   fprintf(fp,
          "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));
    unsigned char black[] = {0, 0, 0, 0, 0, 0};
    unsigned char white[] = {8, 255, 8, 255, 8, 255};
        

    for(int k = 0; k < xres; k++){
        for(int i = 0; i < yres; i++){

            double a = mapping(k,maxiter,xmin,ymax);
            double b = mapping(i,maxiter,xmin,ymax);

            double ca = a;
            double cb = b;

            int n = 0;
            

            while(n < maxiter)
            {
                double aa = a * a - b * b;
                double bb = 2 * a * b;

                a = aa + ca;
                b = bb + cb;

                if(abs(a + b) > 16){
                    break;
                }

                n++;
            }

            if(n == maxiter){
                fwrite(white, 6, 1, fp);
                
            }else{
                fwrite(black, 6, 1, fp);
                
            }
        }        
    }
    
    fclose(fp);

    return 0;
}
double mapping(double x,double res,double min,double max){
    double prop = (x - 0) / (res - 0);
    double a = min + (max - (min)) * prop;

    return a;
}
