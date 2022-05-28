/* C program to sum two matrices using multi-threading.
For each row present in the two input matrices, there
will be a separete thread created to handle the summations
of that row.

Written by
    - Arman Rezaei (9723034)
    - Shirin Mohammadi (9712046)
    - Mahboubeh Enayati (9713025)
Amirkabir University of Technology
May 18, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 2 // row size
#define N 4 // col size


// function (prototype) to sum two matrices
void* sumarr(void* arrays);
void* printarr(int arr[M][N]);

// structure for passing arguments to the function call
struct args {
    int* a_row;
    int* b_row;
    int* c_row;
};


int main() {
    // arrays used in the summation process
    int a[M][N] = {{0, 1, 2, 3},
                   {4, 5, 6, 7}};

    int b[M][N] = {{10, 11, 12, 13},
                   {14, 15, 16, 17}};

    int c[M][N];

    // threads used for summation of rows
    pthread_t tid[M];

    // create threads
    for (int i = 0; i < M; i++) {
        struct args* arrays = (struct args*) malloc(sizeof(struct args));
        arrays->a_row = a[i];
        arrays->b_row = b[i];
        arrays->c_row = c[i];

        pthread_create(&tid[i], NULL, sumarr, (void*) arrays);
    }

    // join threads
    for (int i = 0; i < M; i++) {
        void** result;
        pthread_join(tid[i], result);

        // always free allocated memory!
        free(result);
    }

    // print the result
    printarr(c);

    return 0;
}


// function to sum two matrices
void* sumarr(void* arrays) {
    int* a = ((struct args*) arrays)->a_row;
    int* b = ((struct args*) arrays)->b_row;
    int* c = ((struct args*) arrays)->c_row;

    for (int j = 0; j < N; j++)
        c[j] = a[j] + b[j];

    return arrays;
}

// aux function for printing arrays
void* printarr(int arr[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return NULL;
}
