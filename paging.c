#include<stdio.h>

int main()
{
    int memory_size, page_size, total_pages, num_processes, remaining_pages;
    int process, page, frame_number, offset, physical_address;
    int page_table[10], frame_table[10][20];  // Adjusted array names for clarity

    // Input for memory size and page size
    printf("\nEnter the memory size: ");
    scanf("%d", &memory_size);

    printf("\nEnter the page size: ");
    scanf("%d", &page_size);

    total_pages = memory_size / page_size;  // Total number of pages
    printf("\nThe number of pages available in memory are: %d", total_pages);

    // Input for number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &num_processes);

    remaining_pages = total_pages;

    // Loop through each process to assign pages
    for(int i = 1; i <= num_processes; i++) {
        printf("\nEnter the number of pages required for process P[%d]: ", i);
        scanf("%d", &page_table[i]);

        // Check if memory is sufficient for the process
        if(page_table[i] > remaining_pages) {
            printf("\nMemory is Full");
            break;
        }

        remaining_pages -= page_table[i];  // Update remaining pages

        printf("\nEnter the page table for process P[%d]:\n", i);
        for(int j = 0; j < page_table[i]; j++) {
            printf("Frame number for page %d: ", j);
            scanf("%d", &frame_table[i][j]);
        }
    }

    // Input for logical address (process number, page number, and offset)
    printf("\nEnter Logical Address to find Physical Address");
    printf("\nEnter process number, page number, and offset: ");
    scanf("%d %d %d", &process, &page, &offset);

    // Validation for process number, page number, and offset
    if(process > num_processes || page >= page_table[process] || offset >= page_size) {
        printf("\nInvalid Process, Page Number, or Offset");
    } else {
        // Calculate the physical address
        physical_address = frame_table[process][page] * page_size + offset;
        printf("\nThe Physical Address is: %d", physical_address);
    }

    return 0;
}
