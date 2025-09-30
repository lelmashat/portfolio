/**
 * Educational Cache Simulator Concepts
 * 
 * This demonstrates core cache simulation concepts learned from building
 * a cache memory simulator. Not the actual assignment code.
 * 
 * Demonstrates:
 * - Cache organization (sets, lines, blocks)
 * - Address decomposition (tag, set index, block offset)
 * - LRU and FIFO eviction policies
 * - Hit/miss/eviction counting
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// DEMONSTRATION 1: Address Decomposition
// ============================================================================

/**
 * Shows how a memory address is broken into tag, set index, and block offset
 */
void demo_address_decomposition() {
    printf("=== Cache Address Decomposition Demo ===\n\n");
    
    // Example cache configuration
    int S = 4;  // 4 sets
    int B = 16; // 16 bytes per block
    
    // Calculate bit counts
    int s_bits = 2;  // log2(4) = 2 bits for set index
    int b_bits = 4;  // log2(16) = 4 bits for block offset
    int t_bits = 64 - s_bits - b_bits;  // remaining bits for tag
    
    printf("Cache Configuration:\n");
    printf("  Sets (S): %d (needs %d bits)\n", S, s_bits);
    printf("  Block size (B): %d bytes (needs %d bits)\n", B, b_bits);
    printf("  Address size: 64 bits\n");
    printf("  Tag bits: %d\n\n", t_bits);
    
    // Example addresses
    unsigned long addresses[] = {0x400050, 0x400150, 0x400058, 0x400250};
    
    printf("Address Breakdown:\n");
    printf("%-12s | %-16s | Set  | Offset\n", "Address", "Tag");
    printf("-------------|------------------|------|--------\n");
    
    for (int i = 0; i < 4; i++) {
        unsigned long addr = addresses[i];
        unsigned long tag = addr >> (s_bits + b_bits);
        unsigned long set = (addr >> b_bits) & ((1UL << s_bits) - 1);
        unsigned long offset = addr & ((1UL << b_bits) - 1);
        
        printf("0x%-10lx | 0x%-14lx | %-4lu | %-4lu\n", 
               addr, tag, set, offset);
    }
    
    printf("\nKey Insight:\n");
    printf("  - Tag: Identifies which memory block\n");
    printf("  - Set: Determines which cache set to check\n");
    printf("  - Offset: Position within the cache line\n\n");
}

// ============================================================================
// DEMONSTRATION 2: Cache Line Structure
// ============================================================================

typedef struct {
    int valid;           // Is this line occupied?
    unsigned long tag;   // Tag bits from address
    int timestamp;       // For LRU policy
    int insert_time;     // For FIFO policy
} DemoCacheLine;

/**
 * Demonstrates cache line metadata
 */
void demo_cache_line_structure() {
    printf("=== Cache Line Structure Demo ===\n\n");
    
    printf("Each cache line stores:\n");
    printf("  1. Valid bit - is the line occupied?\n");
    printf("  2. Tag - which memory block is cached here?\n");
    printf("  3. Timestamp - when was it last accessed? (for LRU)\n");
    printf("  4. Insert time - when was it first loaded? (for FIFO)\n\n");
    
    // Simulate a cache set with 2 lines
    DemoCacheLine lines[2] = {
        {.valid = 1, .tag = 0x400, .timestamp = 5, .insert_time = 1},
        {.valid = 1, .tag = 0x500, .timestamp = 3, .insert_time = 2}
    };
    
    printf("Example cache set (2-way associative):\n");
    printf("Line | Valid | Tag    | Last Used | Inserted\n");
    printf("-----|-------|--------|-----------|----------\n");
    for (int i = 0; i < 2; i++) {
        printf("  %d  |   %d   | 0x%-4lx |     %d     |    %d\n",
               i, lines[i].valid, lines[i].tag, 
               lines[i].timestamp, lines[i].insert_time);
    }
    
    printf("\nIf we need to evict:\n");
    printf("  - LRU: Evict line 1 (timestamp = 3, oldest access)\n");
    printf("  - FIFO: Evict line 0 (insert_time = 1, oldest insertion)\n\n");
}

// ============================================================================
// DEMONSTRATION 3: LRU vs FIFO Policies
// ============================================================================

typedef struct {
    int valid;
    int tag;
    int timestamp;
    int insert_time;
} SimLine;

/**
 * Simulates cache behavior under LRU and FIFO policies
 */
void demo_eviction_policies() {
    printf("=== LRU vs FIFO Eviction Policy Demo ===\n\n");
    
    // 2-way set associative cache, single set
    SimLine lru_cache[2] = {{0, 0, 0, 0}, {0, 0, 0, 0}};
    SimLine fifo_cache[2] = {{0, 0, 0, 0}, {0, 0, 0, 0}};
    
    int access_sequence[] = {1, 2, 3, 1, 4};
    int time = 0;
    
    printf("Access sequence: 1, 2, 3, 1, 4\n");
    printf("Cache capacity: 2 lines\n\n");
    
    printf("%-8s | %-20s | %-20s\n", "Access", "LRU Cache State", "FIFO Cache State");
    printf("---------|----------------------|----------------------\n");
    
    for (int i = 0; i < 5; i++) {
        int tag = access_sequence[i];
        time++;
        
        // LRU simulation
        int lru_hit = -1;
        for (int j = 0; j < 2; j++) {
            if (lru_cache[j].valid && lru_cache[j].tag == tag) {
                lru_hit = j;
                lru_cache[j].timestamp = time;
                break;
            }
        }
        
        if (lru_hit == -1) {
            int victim = 0;
            if (!lru_cache[0].valid) victim = 0;
            else if (!lru_cache[1].valid) victim = 1;
            else {
                victim = (lru_cache[0].timestamp < lru_cache[1].timestamp) ? 0 : 1;
            }
            lru_cache[victim].valid = 1;
            lru_cache[victim].tag = tag;
            lru_cache[victim].timestamp = time;
            if (!lru_cache[victim].insert_time) lru_cache[victim].insert_time = time;
        }
        
        // FIFO simulation
        int fifo_hit = -1;
        for (int j = 0; j < 2; j++) {
            if (fifo_cache[j].valid && fifo_cache[j].tag == tag) {
                fifo_hit = j;
                break;
            }
        }
        
        if (fifo_hit == -1) {
            int victim = 0;
            if (!fifo_cache[0].valid) victim = 0;
            else if (!fifo_cache[1].valid) victim = 1;
            else {
                victim = (fifo_cache[0].insert_time < fifo_cache[1].insert_time) ? 0 : 1;
            }
            fifo_cache[victim].valid = 1;
            fifo_cache[victim].tag = tag;
            fifo_cache[victim].insert_time = time;
        }
        
        // Print state
        char lru_state[30], fifo_state[30];
        sprintf(lru_state, "[%d,%d] %s", 
                lru_cache[0].valid ? lru_cache[0].tag : 0,
                lru_cache[1].valid ? lru_cache[1].tag : 0,
                lru_hit != -1 ? "HIT" : "MISS");
        sprintf(fifo_state, "[%d,%d] %s",
                fifo_cache[0].valid ? fifo_cache[0].tag : 0,
                fifo_cache[1].valid ? fifo_cache[1].tag : 0,
                fifo_hit != -1 ? "HIT" : "MISS");
        
        printf("   %d    | %-20s | %-20s\n", tag, lru_state, fifo_state);
    }
    
    printf("\nKey Difference at access 4:\n");
    printf("  - LRU: Evicts 2 (accessed at time 2, not used since)\n");
    printf("  - FIFO: Evicts 1 (inserted first, even though recently used)\n\n");
}

// ============================================================================
// DEMONSTRATION 4: Set-Associative Cache Lookup
// ============================================================================

/**
 * Demonstrates the lookup process in a set-associative cache
 */
void demo_cache_lookup() {
    printf("=== Cache Lookup Process Demo ===\n\n");
    
    printf("Configuration: 4 sets, 2-way associative, 16-byte blocks\n\n");
    
    unsigned long address = 0x400150;
    
    printf("Step 1: Parse address 0x%lx\n", address);
    
    // Decompose
    int s_bits = 2, b_bits = 4;
    unsigned long tag = address >> (s_bits + b_bits);
    unsigned long set = (address >> b_bits) & 0x3;
    unsigned long offset = address & 0xF;
    
    printf("  Tag:    0x%lx\n", tag);
    printf("  Set:    %lu\n", set);
    printf("  Offset: %lu\n\n", offset);
    
    printf("Step 2: Look up in Set %lu (check all %d lines)\n", set, 2);
    
    // Simulate cache state
    DemoCacheLine simulated_set[2] = {
        {.valid = 1, .tag = 0x400, .timestamp = 5, .insert_time = 1},
        {.valid = 1, .tag = 0x500, .timestamp = 3, .insert_time = 2}
    };
    
    printf("  Line 0: Valid=%d, Tag=0x%lx %s\n", 
           simulated_set[0].valid, simulated_set[0].tag,
           (simulated_set[0].tag == tag) ? "MATCH!" : "");
    printf("  Line 1: Valid=%d, Tag=0x%lx %s\n\n",
           simulated_set[1].valid, simulated_set[1].tag,
           (simulated_set[1].tag == tag) ? "MATCH!" : "");
    
    printf("Step 3: Result\n");
    if (tag == simulated_set[0].tag) {
        printf("  HIT on line 0!\n");
        printf("  Update timestamp for LRU\n");
    } else {
        printf("  MISS - tag not found in set\n");
        printf("  Need to load from memory\n");
        printf("  May need to evict a line\n");
    }
    printf("\n");
}

// ============================================================================
// DEMONSTRATION 5: Multi-Block Access
// ============================================================================

/**
 * Shows how large memory accesses can span multiple cache blocks
 */
void demo_multiblock_access() {
    printf("=== Multi-Block Memory Access Demo ===\n\n");
    
    int B = 16;  // 16-byte blocks
    
    printf("Block size: %d bytes\n", B);
    printf("Block boundaries at: 0x0, 0x10, 0x20, 0x30, ...\n\n");
    
    // Example: 20-byte read starting at 0x18
    unsigned long start = 0x18;
    int size = 20;
    unsigned long end = start + size - 1;
    
    printf("Memory access: Read %d bytes from 0x%lx to 0x%lx\n\n", 
           size, start, end);
    
    unsigned long start_block = start & ~(B - 1);
    unsigned long end_block = end & ~(B - 1);
    
    printf("Block analysis:\n");
    printf("  Start address 0x%lx is in block 0x%lx\n", start, start_block);
    printf("  End address 0x%lx is in block 0x%lx\n", end, end_block);
    
    if (start_block == end_block) {
        printf("  → Access contained in ONE block\n");
        printf("  → Requires 1 cache access\n");
    } else {
        printf("  → Access spans TWO blocks\n");
        printf("  → Requires 2 cache accesses\n");
        
        int blocks = (end_block - start_block) / B + 1;
        printf("  → Total blocks touched: %d\n", blocks);
        
        printf("\n  Block accesses needed:\n");
        for (unsigned long b = start_block; b <= end_block; b += B) {
            printf("    - 0x%lx\n", b);
        }
    }
    printf("\n");
}

// ============================================================================
// DEMONSTRATION 6: Cache Performance Metrics
// ============================================================================

/**
 * Demonstrates hit rate calculation and performance impact
 */
void demo_performance_metrics() {
    printf("=== Cache Performance Metrics Demo ===\n\n");
    
    int hits = 850;
    int misses = 150;
    int total = hits + misses;
    
    printf("Simulation results:\n");
    printf("  Hits:   %d\n", hits);
    printf("  Misses: %d\n", misses);
    printf("  Total:  %d\n\n", total);
    
    double hit_rate = (double)hits / total * 100;
    double miss_rate = (double)misses / total * 100;
    
    printf("Performance:\n");
    printf("  Hit rate:  %.1f%%\n", hit_rate);
    printf("  Miss rate: %.1f%%\n\n", miss_rate);
    
    // Timing example
    int cache_time = 1;   // 1 cycle
    int mem_time = 100;   // 100 cycles
    
    double avg_time = hit_rate/100 * cache_time + miss_rate/100 * mem_time;
    
    printf("With cache hit time = %d cycles, miss penalty = %d cycles:\n", 
           cache_time, mem_time);
    printf("  Average access time: %.1f cycles\n\n", avg_time);
    
    printf("Cache impact:\n");
    printf("  Without cache: Every access takes %d cycles\n", mem_time);
    printf("  With cache:    Average of %.1f cycles (%.1fx speedup!)\n", 
           avg_time, (double)mem_time / avg_time);
    printf("\n");
}

// ============================================================================
// Main demonstration program
// ============================================================================

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║     Cache Memory Simulator - Core Concepts Demo           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    demo_address_decomposition();
    demo_cache_line_structure();
    demo_eviction_policies();
    demo_cache_lookup();
    demo_multiblock_access();
    demo_performance_metrics();
    
    printf("These demonstrations show understanding of:\n");
    printf("  ✓ Cache organization (sets, associativity, blocks)\n");
    printf("  ✓ Address parsing (tag, set index, block offset)\n");
    printf("  ✓ Eviction policies (LRU vs FIFO)\n");
    printf("  ✓ Cache lookup algorithms\n");
    printf("  ✓ Multi-block memory access handling\n");
    printf("  ✓ Performance analysis (hit rate, speedup)\n");
    printf("\n");
    
    return 0;
}