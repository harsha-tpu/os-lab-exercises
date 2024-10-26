#include <stdio.h>

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("\n");
}

int isPresent(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) return 1;  // Page is in frames
    }
    return 0;  // Page is not in frames
}

void fifo(int pages[], int total_pages, int frames[], int n) {
    int front = 0, faults = 0;
    for (int i = 0; i < total_pages; i++) {
        if (!isPresent(frames, n, pages[i])) {  // If page is not present
            frames[front] = pages[i];  // Replace oldest page
            front = (front + 1) % n;   // Move the front pointer circularly
            faults++;
        }
        printFrames(frames, n);  // Print current state of frames
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int total_pages, n;

    // Input the number of pages and reference string
    printf("Enter total number of pages: ");
    scanf("%d", &total_pages);
    int pages[total_pages];
    printf("Enter page reference string: ");
    for (int i = 0; i < total_pages; i++) scanf("%d", &pages[i]);

    // Input the number of frames
    printf("Enter number of frames: ");
    scanf("%d", &n);
    int frames[n];
    for (int i = 0; i < n; i++) frames[i] = -1;  // Initialize frames

    fifo(pages, total_pages, frames, n);

    return 0;
}
