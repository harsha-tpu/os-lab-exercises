#include <stdio.h>
#include <stdlib.h>

struct Request {
    int position;
    int visited;
} requests[40];

void fcfs(int queue[], int n, int head) {
    int seek = 0, diff;
    printf("\n*** FCFS Disk Scheduling ***\n");
    for (int i = 0; i < n; i++) {
        diff = abs(queue[i] - head);
        seek += diff;
        printf("Move from %d to %d with Seek %d\n", head, queue[i], diff);
        head = queue[i];
    }
    printf("Total Seek Time: %d\n", seek);
}

void scan(int no, int present, int previous, int first, int last) {
    int sum = 0, i, current, direction = (present - previous > 0) ? 1 : -1;
    for (i = 0; i < no; i++) requests[i].visited = -1;

    printf("\n*** SCAN Disk Scheduling ***\n");
    for (i = 0; i < no; i++) {
        if (direction == 1 && requests[i].position >= present) {
            current = requests[i].position;
            break;
        } else if (direction == -1 && requests[i].position <= present) {
            current = requests[i].position;
        }
    }

    printf("Sequence: ");
    if (direction == 1) {
        for (i = 0; i < no; i++)
            if (requests[i].position >= current)
                printf("%d ", requests[i].position);
        printf("%d %d\n", last, first);
        sum = (last - present) + (last - requests[0].position);
    } else {
        for (i = no - 1; i >= 0; i--)
            if (requests[i].position <= current)
                printf("%d ", requests[i].position);
        printf("%d %d\n", first, last);
        sum = (present - first) + (requests[no - 1].position - first);
    }
    printf("Total Arm Movement: %d\n", sum);
}

void cscan(int no, int present, int first, int last) {
    int sum = 0, i;
    printf("\n*** C-SCAN Disk Scheduling ***\nSequence: ");
    for (i = 0; i < no; i++) requests[i].visited = -1;

    for (i = 0; i < no; i++)
        if (requests[i].position >= present) {
            printf("%d ", requests[i].position);
            requests[i].visited = 1;
        }
    printf("%d %d ", last, first);
    for (i = 0; i < no; i++)
        if (requests[i].visited == -1)
            printf("%d ", requests[i].position);

    sum = (last - present) + (last - first) + (requests[no - 1].position - first);
    printf("\nTotal Arm Movement: %d\n", sum);
}

void sstf(int no, int present) {
    int sum = 0, i, j, min, current;
    printf("\n*** SSTF Disk Scheduling ***\nSequence: ");
    for (i = 0; i < no; i++) requests[i].visited = -1;

    for (i = 0; i < no; i++) {
        min = 99999;
        for (j = 0; j < no; j++)
            if (!requests[j].visited && abs(present - requests[j].position) < min) {
                min = abs(requests[j].position - present);
                current = j;
            }
        requests[current].visited = 1;
        sum += min;
        present = requests[current].position;
        printf("%d(%d) ", requests[current].position, min);
    }
    printf("\nTotal Arm Movement: %d\n", sum);
}

int main() {
    int n, head, choice, first, last, previous;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i].position);
        requests[i].visited = -1;
    }

    printf("Enter disk boundaries (first and last): ");
    scanf("%d%d", &first, &last);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter previous head position: ");
    scanf("%d", &previous);

    printf("\nChoose Disk Scheduling Algorithm:\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. SSTF\nChoice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs((int[]) { head, requests[0].position, requests[1].position, ... , requests[n-1].position }, n + 1, head);
            break;
        case 2:
            scan(n, head, previous, first, last);
            break;
        case 3:
            cscan(n, head, first, last);
            break;
        case 4:
            sstf(n, head);
            break;
        default:
            printf("Invalid choice!\n");
    }
    return 0;
}
