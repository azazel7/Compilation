#include <stdlib.h>
#include <stdio.h>

void printint(int x) {
    printf("%d\n", x);
}
int* malloc_int(int x) {
	return malloc(x*sizeof(int));
}
float* malloc_float(int x) {
	return malloc(x*sizeof(float));
}
void printfloat(float x) {
    printf("%f\n", x);
}
