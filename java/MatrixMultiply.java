

class MatrixMultiply implements Runnable {

    private static int M = 3;
    private static int K = 2;
    private static int N = 3;
    private static int NUM_THREADS = M * N;
    
    private static int[][] A = new int[][]{
        {1, 4},
        {2, 5},
        {3, 6}
    };

    private static int[][] B = new int[][]{
        {8, 7, 6},
        {5, 4, 3}
    };

    private static int[][] C = new int[M][N];

    private static Thread workers[] = new Thread[NUM_THREADS];

    public static void main(String[] args) {
        int thread_count = 0;

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                workers[thread_count] = new Thread(new MatrixMultiply(i, j));
                workers[thread_count].start();
                thread_count++;
            }
        }

        //Join threads
        try {
            for (int i = 0; i < NUM_THREADS; i++) {
                workers[i].join();
            }
        } catch (InterruptedException e) {
            System.err.println("Error joining threads");
        }

        //Print Results
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                System.out.format("%d ", C[i][j]);
            }
            System.out.println();
        }
    }

    private int i;
    private int j;

    MatrixMultiply(int i, int j) {
        this.i = i;
        this.j = j;
    }

    //Function called by each thread
    @Override
    public void run() {

        int sum = 0; 

        for (int n = 0; n < K; n++) {
            sum += A[i][n] * B[n][j];
        } 

        C[i][j] = sum;
        
    }

}
