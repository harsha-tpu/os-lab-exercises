#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], 
                   int max[MAX_PROCESSES][MAX_RESOURCES], 
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], 
                   int numProcesses, int numResources) {
    // Calculate the need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int available[MAX_RESOURCES], 
           int max[MAX_PROCESSES][MAX_RESOURCES], 
           int allocation[MAX_PROCESSES][MAX_RESOURCES], 
           int numProcesses, int numResources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, numProcesses, numResources);

    int finish[MAX_PROCESSES] = {0};  // To track finished processes
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];  // Work vector to simulate availability

    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses) {
        int found = 0;
        for (int i = 0; i < numProcesses; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == numResources) {
                    // Process can finish
                    for (int k = 0; k < numResources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in a safe state!\n");
            return 0;
        }
    }

    // If the system is in a safe state, print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int numProcesses = 5;
    int numResources = 3;

    int available[MAX_RESOURCES] = {3, 3, 2};  // Available resources

    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},  // Maximum resource needs for P0
        {3, 2, 2},  // Maximum resource needs for P1
        {9, 0, 2},  // Maximum resource needs for P2
        {2, 2, 2},  // Maximum resource needs for P3
        {4, 3, 3}   // Maximum resource needs for P4
    };

    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},  // Resources allocated to P0
        {2, 0, 0},  // Resources allocated to P1
        {3, 0, 2},  // Resources allocated to P2
        {2, 1, 1},  // Resources allocated to P3
        {0, 0, 2}   // Resources allocated to P4
    };

    isSafe(available, max, allocation, numProcesses, numResources);

    return 0;
}
