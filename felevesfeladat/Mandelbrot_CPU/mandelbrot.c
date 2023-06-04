#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

void mandelbrot(int iterations, int res, double xmax, double xmin, double ymax, double ymin);

int main()
{   
    //Zoom point 
    double xmax = -1.2576470439074896;
    double xmin = -1.2576470439078538;
    double ymax = 0.3780652779240597;
    double ymin = 0.3780652779236957;

    //Number of image renders
    int renders = 10;
    
    //Maxinum number of iterations
    int iterations[10] = {100,500,1000,5000,10000,20000,30000,40000,50000,60000};

    //Image size
    int res = 1000;

    for(int i = 0; i < renders; i++){

        clock_t start,end;
        double time_taken;

        start = clock();
        mandelbrot(iterations[i],res,xmax,xmin,ymax,ymin);

        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Iterations: %d, time taken: %lf\n",iterations[i],time_taken);

        //Creating the .csv file
        FILE *fp;
        fp = fopen("data.csv","a");

        fprintf(fp,"%d %d %lf\n",0,iterations[i],time_taken);

        fclose(fp);

    }
    
    return 0;
}

void mandelbrot(int iterations, int res, double xmax, double xmin, double ymax, double ymin)
{
    char filename[20];
    sprintf(filename,"%d.ppm",iterations);
    FILE * fp = fopen(filename,"wb");

    //PPM file header
    fprintf(fp,
            "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, iterations=%d\n%d\n%d\n%d\n",
            xmin, xmax, ymin, ymax, iterations, res, res, (iterations < 256 ? 256 : iterations));

    // Pixel width and height
    double dx=(xmax-xmin)/res;
    double dy=(ymax-ymin)/res;

    double x, y;
    double u, v; 
    //black color
    unsigned char black[] = {0, 0, 0, 0, 0, 0};

    int k;
    for (int i = 0; i < res; i++) {

        y = ymax - i * dy;

        for(int j = 0; j < res; j++) {

        double u = 0.0;
        double v= 0.0;
        double u2 = u * u;
        double v2 = v * v;

        x = xmin + j * dx;

        //Given point iteration
        for (k = 1; k < iterations && (u2 + v2 < 4.0); k++) {
                v = 2 * u * v + y;
                u = u2 - v2 + x;
                u2 = u * u;
                v2 = v * v;
        }

        //Print black
        if (k >= iterations) {   
            
            fwrite (black, 6, 1, fp);
        }
        //Print Color, shifting it according to k iteration number
        else {
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
}