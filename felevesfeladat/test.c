#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

void draw(float zoom,int iter);

int main(){

  float zoom = 0.0;
  for(int i = 0; i <= 10; i++){
    zoom += 0.1;
    draw(zoom, i);  
  }


  return 0;
}

void draw(float zoom, int iter){
  int height = 800;
  int width = 800;

  // Maximum number of iterations for each point on the complex plane
  int maxiterations = 100;

  float xmin = -2.0;
  float ymin = -2.0;
  float xmax = 2.0;
  float ymax = 2.0;

   // Calculate amount we increment x,y for each pixel
  float dx = (xmax - xmin) / (width);
  float dy = (ymax - ymin) / (height);

  //ZOOM

  char filename[20];
  sprintf(filename, "./images/test_%d.ppm", iter);

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

  printf("%d: xmin%f, xmax%f, ymin%f, ymax%f\n",iter,xmin,xmax,ymin,ymax);
}
