#include "foo.h"

#include <stdio.h>
#include <stdlib.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_types.h>

void check_error(cudaError_t status) {
    if (status != cudaSuccess) {
        const char *s = cudaGetErrorString(status);
        printf("CUDA Error: %s\n", s);
    }
    status = cudaDeviceSynchronize();
    if (status != cudaSuccess)
        printf("CUDA status = cudaDeviceSynchronize() Error\n");
}

void bar() {
    cudaError_t status = cudaSetDevice(0);
    if(status != cudaSuccess) check_error(status);
    cudaSetDeviceFlags(cudaDeviceScheduleBlockingSync);
    printf("this is bar, after setting CUDA device\n");
}
