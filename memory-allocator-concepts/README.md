# Dynamic Memory Allocator Concepts

An educational demonstration of dynamic memory allocation principles. This project showcases understanding of low-level memory management concepts learned through building a custom memory allocator.

**Note**: This is an educational demonstration of concepts, not production memory allocation software.

## Project Overview

This program demonstrates the fundamental concepts behind dynamic memory allocators (malloc, free, realloc), including:
- Block header/footer metadata management
- Explicit free list implementation
- Block coalescing algorithms
- First-fit placement policy
- Memory alignment requirements
- Realloc optimization strategies

## Technical Concepts

### Block Structure
Each memory block contains:
- **Header** (4 bytes): Stores size and allocation status
- **Footer** (4 bytes): Duplicate of header for bidirectional traversal
- **Payload**: Actual user data
- Minimum block size: 16 bytes (header + footer + 8-byte payload minimum)

### Explicit Free List
- Doubly-linked list connecting only free blocks
- Free blocks store forward/backward pointers in their payload area
- Provides O(n) free block search where n = number of free blocks (not total blocks)

### Key Algorithms

**Memory Allocation (malloc)**
1. Calculate required block size (payload + 8 bytes overhead, rounded to 8-byte alignment)
2. Search free list for first-fit block
3. If found: split block if remainder >= 16 bytes, mark allocated
4. If not found: extend heap with sbrk system call
5. Return pointer to payload

**Memory Deallocation (free)**
1. Mark block as free
2. Coalesce with adjacent free blocks (four cases: both neighbors allocated, next free, previous free, both free)
3. Add final coalesced block to free list

**Memory Reallocation (realloc)**
- Shrinking: If new size fits in current block, split and free remainder
- In-place expansion: If next block is free and provides enough space, absorb it
- New allocation: Otherwise allocate new block, copy data, free old block

## Building and Running

### Compile
```bash
make
```

### Run the demo
```bash
./allocator_demo
```

### Output
The program runs six demonstrations:
1. Block Structure - Header/footer layout
2. Coalescing Logic - Four cases of neighbor combinations
3. Explicit Free List - Doubly-linked list operations
4. First-Fit Search - Placement policy walkthrough
5. Alignment Requirements - 8-byte alignment calculations
6. Realloc Strategies - Optimization scenarios

## Key Insights

### Memory Layout
```
Heap Structure:
[Padding][Prologue][Regular Blocks...][Epilogue]

Free Block Format:
[Header: size|0][prev_free ptr][next_free ptr][unused][Footer: size|0]

Allocated Block Format:
[Header: size|1][payload...][Footer: size|1]
```

### Coalescing Cases
The allocator handles four scenarios when freeing a block:
1. Both neighbors allocated → Add block to free list
2. Next neighbor free → Merge with next, add to free list
3. Previous neighbor free → Merge with previous, add to free list
4. Both neighbors free → Merge all three, add to free list

### Alignment Importance
All blocks must be 8-byte aligned for:
- Efficient memory access (hardware requirement)
- Proper pointer alignment in free blocks
- Standard compliance

## Skills Demonstrated

**Low-level Memory Management**
- Direct heap manipulation
- Pointer arithmetic
- Understanding of memory alignment

**Data Structure Design**
- Explicit free list with doubly-linked pointers
- Efficient block metadata storage

**Algorithm Optimization**
- First-fit placement policy
- Immediate coalescing to reduce fragmentation
- In-place realloc when possible

**Systems Programming**
- Understanding of heap layout and OS interface
- Bitwise operations for flags
- Struct casting and type punning

## Background

These demonstrations are based on concepts from Computer Systems: A Programmer's Perspective (CS:APP), specifically Chapter 9: Virtual Memory.

## Academic Integrity Note

This project demonstrates understanding of memory allocation concepts through educational examples. It does not contain assignment solutions or code from course materials.