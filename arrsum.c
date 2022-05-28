/* C program to sum two matrices using single-threading.
This code is used to demonstrate the correctness of the
functions that will be used in the next section for
multi-threading (04-pthread-sum.c).

Written by
    - Arman Rezaei (9723034)
    - Shirin Mohammadi (9712046)
    - Mahboubeh Enayati (9713025)
Amirkabir University of Technology
May 18, 2022
*/

#include <stdio.h>
#include <stdlib.h>

#define M 2 // row size
#define N 4 // col size


// function (prototype) to sum two matrices
void* sumarr(void* arrays);
void* printarr(int arr[M][N]);

// structure for passing arguments to the function call
struct args {
    int* a_arr;
    int* b_arr;
    int* c_arr;
};


int main() {
    // arrays used in the summation process
    int a[M][N] = {{0, 1, 2, 3},
                   {4, 5, 6, 7}};

    int b[M][N] = {{10, 11, 12, 13},
                   {14, 15, 16, 17}};

    int c[M][N];
    struct args* arrays = (struct args*) malloc(sizeof(struct args));

    // commence the sum operation
    for (int i = 0; i < M; i++) {
        arrays->a_arr = a[i];
        arrays->b_arr = b[i];
        arrays->c_arr = c[i];
        sumarr((void*) arrays);
    }

    // print the arrays
    printarr(a);
    printarr(b);
    printarr(c);

    return 0;
}


// function to sum two matrices
void* sumarr(void* arrays) {
    int* a = ((struct args*) arrays)->a_arr;
    int* b = ((struct args*) arrays)->b_arr;
    int* c = ((struct args*) arrays)->c_arr;

    for (int j = 0; j < N; j++)
        c[j] = a[j] + b[j];

    return NULL;
}

// aux function for printing arrays
void* printarr(int arr[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("---\n");

    return NULL;
}
