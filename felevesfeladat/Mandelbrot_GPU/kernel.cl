__kernel void mandelbrot(int iterations, int res, double xmax, double xmin, double ymax, double ymin) {
	int i = get_global_id(0);

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
fclose(fp);
}