#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3            // # of rows in Matrix A
#define K 2            // # of columns in Matrix A, # of rows in Matrix B
#define N 3            // # of columns in Matrix B
#define NUM_THREADS 10 // Maximum number of threads to be used

int A [M][K] = { {1,4}, {2,5}, {3,6}  }; // Matrix A 3 x 2
int B [K][N] = { {8,7,6}, {5,4,3}  };    // Matrix B 2 X 3
int C [M][N];                            // Matrix C 3 x 3

pthread_t workers[NUM_THREADS];

// Specifies the entry in C that we are calculating.
// Used to pass data to threads
struct v {
    int i; //row
    int j; //column
};

void *runner(void *param) {
	struct v *data = param; 
	int sum = 0; 

	//Row multiplied by column
	for(int n = 0; n< K; n++){
		sum += A[data->i][n] * B[n][data->j];
	}

	//assign the sum to its coordinate
	C[data->i][data->j] = sum;

	//Exit the thread
	pthread_exit(0);  
}

int main(int argc, char *argv[]) {

    int thread_count = 0;

    //Loop through rows
    for (int i = 0; i < M; i++) {
        //Loop through columns
        for (int j = 0; j < N; j++) {

            // Create data structure to pass to thread
            struct v *data = (struct v *) malloc(sizeof(struct v));
            data->i = i;
            data->j = j;

            pthread_create(&workers[thread_count], NULL, runner, data);
        }
    }

    //Join Threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(workers[i], NULL);
    }

    //Print Resulting Matrix

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}







