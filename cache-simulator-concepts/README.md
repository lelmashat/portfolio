# Cache Simulator Concepts

An educational demonstration of cache memory simulation principles and eviction policies. This project showcases understanding of computer architecture concepts learned through building a cache simulator.

**Note**: This is an educational demonstration of concepts, not production cache simulation software.

## Project Overview

This program demonstrates the fundamental concepts behind cache memory simulators, including:
- How memory addresses map to cache locations
- Set-associative cache organization
- LRU (Least Recently Used) and FIFO (First-In-First-Out) eviction policies
- Cache performance metrics (hit rate, miss rate)
- Multi-block memory access handling

## Technical Concepts

### Cache Organization
- **Sets**: Cache is divided into multiple sets
- **Associativity**: Each set can hold multiple cache lines (K-way associative)
- **Block Size**: Each line stores a block of contiguous bytes

### Address Decomposition
Every memory address is broken into three parts:
```
|-------- Tag ---------|-- Set Index --|-- Block Offset --|
```
- **Tag**: Identifies which memory block is cached
- **Set Index**: Determines which cache set to check
- **Block Offset**: Byte position within the cache line

### Eviction Policies

**FIFO (First-In-First-Out)**
- Evicts the oldest inserted line
- Tracks insertion timestamp for each line

**LRU (Least Recently Used)**
- Evicts the line that hasn't been accessed longest
- Tracks last access timestamp for each line
- Better performance for programs with temporal locality

## Building and Running

### Compile
```bash
make
```

### Run the demo
```bash
./cache_demo
```

### Output
The program runs six demonstrations:
1. Address Decomposition - Shows tag/set/offset extraction
2. Cache Line Structure - Metadata stored per line
3. LRU vs FIFO Policies - Side-by-side comparison
4. Cache Lookup Process - Step-by-step lookup walkthrough
5. Multi-Block Access - Handling large memory operations
6. Performance Metrics - Hit rate and speedup calculations

## Key Insights

### Why Caches Work
Programs exhibit locality of reference:
- **Temporal locality**: Recently accessed data likely accessed again soon
- **Spatial locality**: Nearby addresses likely accessed together

### Cache Performance Example
With 85% hit rate:
- Cache hit time: 1 cycle
- Memory access time: 100 cycles
- Average access time: 0.85(1) + 0.15(100) = 15.85 cycles
- Without cache: Every access = 100 cycles
- **Speedup: 6.3x**

## Skills Demonstrated

**Computer Architecture**
- Cache memory hierarchy and set-associative organization
- Eviction policy algorithms
- Performance analysis

**C Programming**
- Pointer manipulation and bit operations
- Dynamic memory management
- Efficient algorithm implementation

**Systems Thinking**
- Understanding hardware-software interface
- Performance optimization techniques
- Trade-off analysis

## Background

These demonstrations are based on concepts from Computer Systems: A Programmer's Perspective (CS:APP), specifically Chapter 6: The Memory Hierarchy.

## Academic Integrity Note

This project demonstrates understanding of cache simulation concepts through educational examples. It does not contain assignment solutions or code from course materials.