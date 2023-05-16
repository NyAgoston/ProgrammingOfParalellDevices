#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(){

    int height = 800;
    int width = 800;

    // Maximum number of iterations for each point on the complex plane
    int maxiterations = 1000;

    float xmin = -2.0;
    float ymin = -2.0;
    float xmax = 2.0;
    float ymax = 2.0;

    float zoom = 2.0;
    float zoom_rate = 1.1;
    int num_zooms = 30;

    // Perform multiple zooms into the Mandelbrot set
    for (int zoom_level = 0; zoom_level < num_zooms; zoom_level++){
        
        float dx = (xmax - xmin) / width;
        float dy = (ymax - ymin) / height;

        float dxt = (xmax - xmin) / zoom;
        float dyt = (ymax - ymin) / zoom;
        xmin += dxt / 2.0;
        xmax -= dxt / 2.0;
        ymin += dyt / 2.0;
        ymax -= dyt / 2.0;
        zoom *= zoom_rate;

        //ZOOM

        char filename[20];
        sprintf(filename, "./images/test_%d.ppm", zoom_level);

        FILE * fp = fopen(filename,"wb");

        fprintf(fp,"P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n", xmin, xmax, ymin, ymax, maxiterations, height, width, (maxiterations < 256 ? 256 : maxiterations));
        unsigned char black[] = {0, 0, 0, 0, 0, 0};
        unsigned char white[] = {8, 255, 8, 255, 8, 255};

        // Start y
        float y = ymin;
        for (int j = 0; j < height; j++) {
            // Start x
            float x = xmin;
            for (int i = 0; i < width; i++) {

            // Now we test, as we iterate z = z^2 + cm does z tend towards infinity?
            float a = x;
            float b = y;
            int n = 0;
            while (n < maxiterations) {
                float aa = a * a;
                float bb = b * b;
                float twoab = 2.0 * a * b;
                a = aa - bb + x;
                b = twoab + y;
                // Infinty in our finite world is simple, let's just consider it 16
                if (a*a + b*b > 16.0) {
                break;  // Bail
                }
                n++;
            }

            // We color each pixel based on how long it takes to get to infinity
            // If we never got there, let's pick the color black
            if (n == maxiterations) {
                fwrite(black, 6, 1, fp);


            } else {
                
                fwrite(white, 6, 1, fp);

            }
            x += dx;
            }
            y += dy;
        }

        fclose(fp);

        printf("%d: xmin%f, xmax%f, ymin%f, ymax%f\n",zoom_level,xmin,xmax,ymin,ymax);
    }


    return 0;
}