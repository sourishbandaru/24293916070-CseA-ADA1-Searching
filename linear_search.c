#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Linear Search with light artificial delay
int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        // small artificial delay (keeps graph smooth but not too slow)
        for (volatile int j = 0; j < 20; j++);
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    FILE *fp = fopen("linear_search_results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "size,avg_time\n");
    printf(" size\t avg_time (seconds)\n");
    printf("------------------------------\n");

    for (int n = 1000; n <= 100000; n += 5000) {
        int *arr = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr[i] = i;

        int target = n - 1; // worst case (last element)

        // Adjust number of iterations depending on n (to prevent lag)
        int iterations = (n <= 20000) ? 5000 : 500;

        clock_t start = clock();
        for (int i = 0; i < iterations; i++) {
            linear_search(arr, n, target);
        }
        clock_t end = clock();

        double total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time = total_time / iterations;

        fprintf(fp, "%d,%f\n", n, avg_time);
        printf("%6d\t %f\n", n, avg_time);

        free(arr);
    }

    fclose(fp);
    printf("\nResults written to linear_search_results.txt\n");
    return 0;
}