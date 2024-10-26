#include <stdio.h>

int mark[20];  // Marks if a process is completed or not
int num_processes, num_resources;  // Number of processes and resources

int main() {
    int allocation[10][10], request[10][10], available[10], total_resources[10], work[10];

    // Input number of processes and resources
    printf("\nEnter the number of processes: ");
    scanf("%d", &num_processes);
    printf("\nEnter the number of resources: ");
    scanf("%d", &num_resources);

    // Input the total resources for each resource type
    for (int i = 0; i < num_resources; i++) {
        printf("Total amount of resource R%d: ", i + 1);
        scanf("%d", &total_resources[i]);
    }

    // Input the request matrix
    printf("\nEnter the request matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input the allocation matrix
    printf("\nEnter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate available resources
    for (int j = 0; j < num_resources; j++) {
        available[j] = total_resources[j];
        for (int i = 0; i < num_processes; i++) {
            available[j] -= allocation[i][j];
        }
    }

    // Mark processes with zero allocation
    for (int i = 0; i < num_processes; i++) {
        int zero_allocation = 1;
        for (int j = 0; j < num_resources; j++) {
            if (allocation[i][j] != 0) {
                zero_allocation = 0;
                break;
            }
        }
        mark[i] = zero_allocation;  // Mark process if it has zero allocation
    }

    // Initialize work array with available resources
    for (int j = 0; j < num_resources; j++) {
        work[j] = available[j];
    }

    // Process unmarked processes whose requests can be satisfied
    for (int i = 0; i < num_processes; i++) {
        if (!mark[i]) {  // Only check unmarked processes
            int can_be_processed = 1;
            for (int j = 0; j < num_resources; j++) {
                if (request[i][j] > work[j]) {
                    can_be_processed = 0;
                    break;
                }
            }
            if (can_be_processed) {
                mark[i] = 1;  // Mark process as completed
                for (int j = 0; j < num_resources; j++) {
                    work[j] += allocation[i][j];  // Release its allocated resources
                }
            }
        }
    }

    // Check for unmarked processes indicating deadlock
    int deadlock = 0;
    for (int i = 0; i < num_processes; i++) {
        if (!mark[i]) {
            deadlock = 1;
            break;
        }
    }

    // Output result
    if (deadlock) {
        printf("\nDeadlock detected.\n");
    } else {
        printf("\nNo deadlock detected. The system is in a safe state.\n");
    }

    return 0;
}
