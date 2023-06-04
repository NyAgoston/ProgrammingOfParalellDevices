#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>
#include <time.h>
#include "kernel_loader.h"

int main()
{
    cl_int err;
    cl_platform_id platform_id;
    cl_device_id device_id;
    cl_context context;
    cl_program program;
    cl_kernel kernel;
    cl_command_queue queue;

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
    
    clGetPlatformIDs(1, & platform_id, NULL);
    clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, & device_id, NULL);
    //Creating context and command queue
    context = clCreateContext(NULL, 1, & device_id, NULL, NULL, & err);
    if (err != CL_SUCCESS) {
        printf("Error creating context: %d\n", err);
        return -1;
    }
    queue = clCreateCommandQueue(context, device_id, 0, & err);
    if (err != CL_SUCCESS) {
        printf("Error creating command queue: %d\n", err);
        return -1;
    }

    //Creating the program from kernel code
    const char * kernel_code = load_kernel_source("kernel.cl", & err);
    if (err != 0) {
        printf("Cannot create program %d\n", err);
        return -1;
    }
    program = clCreateProgramWithSource(context, 1, & kernel_code, NULL, & err);
    if (err != CL_SUCCESS) {
        printf("Cannot create program %d\n", err);
        return -1;
    }
    //Building the program
    clBuildProgram(program, 1, & device_id, NULL, NULL, NULL);

    // Createing the kernel
    kernel = clCreateKernel(program, "kernel", & err);
    if (err != CL_SUCCESS) {
        printf("Error creating kernel: %d\n", err);
        return -1;
    }

    for(int i = 0; i < renders; i++)
    {
        clock_t start,end;
        double time_taken;

        start = clock();

        //Setting kernel arguments
        err = clSetKernelArg(kernel, 0, sizeof(int), & iterations);
        err |= clSetKernelArg(kernel, 1, sizeof(int), & res);
        err |= clSetKernelArg(kernel, 2, sizeof(double), & xmax);
        err |= clSetKernelArg(kernel, 3, sizeof(double), & xmin);
        err |= clSetKernelArg(kernel, 4, sizeof(double), & ymax);
        err |= clSetKernelArg(kernel, 5, sizeof(double), & ymin);
        if (err != CL_SUCCESS) {
            printf("Error setting kernel arguments: %d\n", err);
            return -1;
        }

        size_t global_res = res;
        err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, & global_res, NULL, 0, NULL, NULL);
        if (err != CL_SUCCESS) {
            printf("Error enqueuing kernel: %d\n", err);
            return -1;
        }
        
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Iterations: %d, time taken: %lf\n",iterations[i],time_taken);

        //Creating the .csv file
        FILE *fp;
        fp = fopen("data.csv","a");

        fprintf(fp,"%d %d %lf\n",1,iterations[i],time_taken);

        fclose(fp);
    }
    //Releasing resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}
