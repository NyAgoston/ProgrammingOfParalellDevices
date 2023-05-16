#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

double mapping(double x,double res,double min, double max);

int main(int argc, char* argv[])
{
    //0.27085 0.27100 0.004640 0.004810
    double xmin = -2.0;
    double xmax = -2.0;
    double ymin = 2.0;
    double ymax = 2.0;
    int maxiter = 1000;
    int res = 1000;
    
    FILE * fp = fopen("test.ppm","wb");

    fprintf(fp,"P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n", xmin, xmax, ymin, ymax, maxiter, res, res, (maxiter < 256 ? 256 : maxiter));
    unsigned char black[] = {0, 0, 0, 0, 0, 0};
    unsigned char white[] = {8, 255, 8, 255, 8, 255}; 

    for(int k = 0; k < res; k++){
        for(int i = 0; i < res; i++){

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

                if(abs(a + b) > 4){
                    break;
                }

                n++;
            }
            if(n >= maxiter){
                fwrite(black, 6, 1, fp); 
                
            }else{
                unsigned char color[6];
                color[0] = k >> 8;
                color[1] = k & 255;
                color[2] = k >> 8;
                color[3] = k & 255;
                color[4] = k >> 8;
                color[5] = k & 255;
                fwrite(color, 6, 1, fp);
                
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
