/**
 * Educational Memory Allocator Concepts
 * 
 * This demonstrates core memory allocation concepts learned from building
 * a custom malloc implementation. Not the actual assignment code.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ============================================================================
// DEMONSTRATION 1: Block Header/Footer Structure
// ============================================================================

typedef struct {
    size_t size;      // Block size
    int allocated;    // 1 if allocated, 0 if free
} BlockInfo;

/**
 * Demonstrates how allocators use headers/footers for block metadata
 */
void demo_block_structure() {
    printf("=== Memory Block Structure Demo ===\n");
    
    // Simulate a 32-byte block
    char simulated_block[32];
    BlockInfo *header = (BlockInfo *)simulated_block;
    
    // Set header
    header->size = 32;
    header->allocated = 1;
    
    // Footer is at end of block (size - sizeof(BlockInfo))
    BlockInfo *footer = (BlockInfo *)(simulated_block + 32 - sizeof(BlockInfo));
    footer->size = 32;
    footer->allocated = 1;
    
    printf("Block size: %zu bytes\n", header->size);
    printf("Header at offset: 0\n");
    printf("Footer at offset: %zu\n", 32 - sizeof(BlockInfo));
    printf("Payload area: %zu bytes\n", 32 - 2*sizeof(BlockInfo));
    printf("\n");
}

// ============================================================================
// DEMONSTRATION 2: Coalescing Algorithm
// ============================================================================

typedef enum {
    BOTH_ALLOCATED,
    NEXT_FREE,
    PREV_FREE,
    BOTH_FREE
} CoalesceCase;

/**
 * Demonstrates the four cases of block coalescing logic
 */
void demo_coalescing() {
    printf("=== Block Coalescing Logic Demo ===\n");
    
    // Simulate three consecutive blocks
    int prev_allocated = 0;
    int next_allocated = 0;
    size_t current_size = 64;
    size_t prev_size = 32;
    size_t next_size = 48;
    
    printf("Current block: %zu bytes\n", current_size);
    printf("Testing different neighbor scenarios:\n\n");
    
    // Case 1: Both neighbors allocated
    prev_allocated = 1; next_allocated = 1;
    printf("Case 1 - Both neighbors allocated:\n");
    printf("  Result: Keep block as-is (%zu bytes)\n", current_size);
    printf("  Action: Add to free list\n\n");
    
    // Case 2: Next free, prev allocated
    prev_allocated = 1; next_allocated = 0;
    printf("Case 2 - Next neighbor is free:\n");
    printf("  Result: Merge with next (%zu + %zu = %zu bytes)\n", 
           current_size, next_size, current_size + next_size);
    printf("  Action: Remove next from free list, add merged block\n\n");
    
    // Case 3: Prev free, next allocated
    prev_allocated = 0; next_allocated = 1;
    printf("Case 3 - Previous neighbor is free:\n");
    printf("  Result: Merge with previous (%zu + %zu = %zu bytes)\n",
           prev_size, current_size, prev_size + current_size);
    printf("  Action: Remove prev from free list, add merged block\n\n");
    
    // Case 4: Both free
    prev_allocated = 0; next_allocated = 0;
    printf("Case 4 - Both neighbors are free:\n");
    printf("  Result: Merge all three (%zu + %zu + %zu = %zu bytes)\n",
           prev_size, current_size, next_size, 
           prev_size + current_size + next_size);
    printf("  Action: Remove both neighbors from free list, add merged block\n\n");
}

// ============================================================================
// DEMONSTRATION 3: Explicit Free List Operations
// ============================================================================

typedef struct FreeBlock {
    size_t size;
    struct FreeBlock *next;
    struct FreeBlock *prev;
} FreeBlock;

/**
 * Demonstrates doubly-linked free list operations
 */
void demo_free_list() {
    printf("=== Explicit Free List Demo ===\n");
    
    // Simulate a small free list
    FreeBlock blocks[4];
    
    // Initialize blocks
    for (int i = 0; i < 4; i++) {
        blocks[i].size = (i + 1) * 64;
        blocks[i].next = (i < 3) ? &blocks[i + 1] : NULL;
        blocks[i].prev = (i > 0) ? &blocks[i - 1] : NULL;
    }
    
    FreeBlock *head = &blocks[0];
    
    // Print initial list
    printf("Initial free list:\n");
    FreeBlock *current = head;
    int pos = 0;
    while (current != NULL) {
        printf("  Block %d: %zu bytes\n", pos++, current->size);
        current = current->next;
    }
    
    printf("\nList traversal demonstrates:\n");
    printf("  - Each free block stores pointers to prev/next free blocks\n");
    printf("  - O(n) search where n = number of FREE blocks only\n");
    printf("  - Much faster than scanning entire heap\n\n");
}

// ============================================================================
// DEMONSTRATION 4: First-Fit Search Algorithm
// ============================================================================

/**
 * Demonstrates first-fit placement policy
 */
void demo_first_fit() {
    printf("=== First-Fit Search Demo ===\n");
    
    size_t free_sizes[] = {32, 128, 64, 256, 48};
    int num_blocks = 5;
    size_t requested = 80;
    
    printf("Free blocks available: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%zu ", free_sizes[i]);
    }
    printf("\nRequested size: %zu bytes\n\n", requested);
    
    // First-fit search
    int found_index = -1;
    for (int i = 0; i < num_blocks; i++) {
        if (free_sizes[i] >= requested) {
            found_index = i;
            break;
        }
    }
    
    if (found_index >= 0) {
        printf("First-fit found: Block %d (%zu bytes)\n", 
               found_index, free_sizes[found_index]);
        
        size_t remaining = free_sizes[found_index] - requested;
        printf("After allocation:\n");
        printf("  - Allocated: %zu bytes\n", requested);
        printf("  - Remaining: %zu bytes\n", remaining);
        
        if (remaining >= 16) {
            printf("  - Action: Split block (remainder >= 16 bytes)\n");
        } else {
            printf("  - Action: Use entire block (remainder too small)\n");
        }
    }
    printf("\n");
}

// ============================================================================
// DEMONSTRATION 5: Alignment Requirements
// ============================================================================

/**
 * Demonstrates 8-byte alignment calculations
 */
void demo_alignment() {
    printf("=== Memory Alignment Demo ===\n");
    
    size_t requests[] = {1, 7, 8, 15, 16, 23, 100};
    size_t header_footer = 8; // 4 bytes each
    
    printf("Request | With Header | Aligned | Total Block\n");
    printf("--------|-------------|---------|------------\n");
    
    for (int i = 0; i < 7; i++) {
        size_t req = requests[i];
        size_t with_overhead = req + header_footer;
        size_t aligned = ((with_overhead + 7) / 8) * 8;
        
        printf("%7zu | %11zu | %7zu | %7zu\n", 
               req, with_overhead, aligned, aligned);
    }
    
    printf("\nAlignment ensures:\n");
    printf("  - Efficient memory access (hardware requirement)\n");
    printf("  - All blocks start at 8-byte boundaries\n");
    printf("  - Pointers in free blocks are properly aligned\n\n");
}

// ============================================================================
// DEMONSTRATION 6: Realloc Optimization Strategies
// ============================================================================

/**
 * Demonstrates different realloc scenarios
 */
void demo_realloc_strategies() {
    printf("=== Realloc Optimization Strategies ===\n");
    
    size_t current_size = 128;
    size_t current_payload = current_size - 8;
    
    // Scenario 1: Shrinking
    printf("Scenario 1 - Shrinking (128 -> 64 bytes):\n");
    size_t new_size = 64;
    if (new_size < current_size) {
        printf("  Strategy: Shrink in-place\n");
        size_t freed = current_size - new_size;
        printf("  Free %zu bytes at end\n", freed);
        printf("  No data copy needed!\n\n");
    }
    
    // Scenario 2: Growing with free next block
    printf("Scenario 2 - Growing with free next block (128 -> 192 bytes):\n");
    size_t next_free_size = 80;
    size_t needed = 192;
    if (current_size + next_free_size >= needed) {
        printf("  Strategy: Absorb next block\n");
        printf("  Current: %zu, Next: %zu, Total: %zu\n", 
               current_size, next_free_size, current_size + next_free_size);
        printf("  No data copy needed!\n\n");
    }
    
    // Scenario 3: Must relocate
    printf("Scenario 3 - Must relocate (128 -> 512 bytes):\n");
    needed = 512;
    printf("  Strategy: Allocate new block\n");
    printf("  Copy %zu bytes of data\n", current_payload);
    printf("  Free old block\n\n");
}

// ============================================================================
// Main demonstration program
// ============================================================================

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║  Dynamic Memory Allocator - Core Concepts Demonstration   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    demo_block_structure();
    demo_coalescing();
    demo_free_list();
    demo_first_fit();
    demo_alignment();
    demo_realloc_strategies();
    
    printf("These demonstrations show understanding of:\n");
    printf("  ✓ Block metadata management (headers/footers)\n");
    printf("  ✓ Coalescing algorithms (4 cases)\n");
    printf("  ✓ Explicit free list data structures\n");
    printf("  ✓ Placement policies (first-fit)\n");
    printf("  ✓ Memory alignment requirements\n");
    printf("  ✓ Realloc optimization techniques\n");
    printf("\n");
    
    return 0;
}