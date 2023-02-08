#include <stdio.h>
#include <stdlib.h>

__global__ void kernel(double *arr, double *arr2, unsigned long n) {
	unsigned long idx = blockIdx.x * blockDim.x + threadIdx.x;
	unsigned long offset = blockDim.x * gridDim.x;
//	printf("%d %d %d\n", blockIdx.x, threadIdx.x, idx);
	while (idx < n) {
		arr[idx] += arr2[idx];
		idx += offset;
	}
}

int main() {
	unsigned long i, n;
	scanf("%lu", &n);
	double *arr = (double *)malloc(sizeof(double) * n);
	double *arr2 = (double *)malloc(sizeof(double) * n);
	for (i = 0; i < n; i++)
		scanf("%lf", &arr[i]);
	for (i = 0; i < n; i++)
		scanf("%lf", &arr2[i]);
	double *dev_arr;
	double *dev_arr2;
	cudaMalloc(&dev_arr, sizeof(double) * n);
	cudaMalloc(&dev_arr2, sizeof(double) * n);
	cudaMemcpy(dev_arr, arr, sizeof(double) * n, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_arr2, arr2, sizeof(double) * n, cudaMemcpyHostToDevice);

	kernel<<<32, 32>>>(dev_arr, dev_arr2, n);

	cudaMemcpy(arr, dev_arr, sizeof(double) * n, cudaMemcpyDeviceToHost);
	cudaMemcpy(arr2, dev_arr2, sizeof(double) * n, cudaMemcpyDeviceToHost);
	for(i = 0; i < n; i++)
		printf("%.10e ", arr[i]);
	printf("\n");

	cudaFree(dev_arr);
	cudaFree(dev_arr2);
	free(arr);
	free(arr2);
	return 0;
}