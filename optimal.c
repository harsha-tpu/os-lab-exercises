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

int findOptimal(int pages[], int frames[], int n, int index, int total_pages) {
    int farthest = index, pos = -1;
    for (int i = 0; i < n; i++) {  // Find the page to replace
        int j;
        for (j = index; j < total_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == total_pages) return i;  // No further use for this page
    }
    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int total_pages, int frames[], int n) {
    int faults = 0;
    for (int i = 0; i < total_pages; i++) {
        if (!isPresent(frames, n, pages[i])) {  // If page is not present
            int pos = findOptimal(pages, frames, n, i + 1, total_pages);  // Find the optimal page to replace
            frames[pos] = pages[i];  // Replace the page
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

    optimal(pages, total_pages, frames, n);

    return 0;
}
