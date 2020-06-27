#ifndef _PHYSM_H_
#define _PHYSM_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <kernel/timer.h>

#define BLOCK_SIZE 20

extern uint32_t end;

struct Block
{
    uint32_t allocate_id;
    int used;
    void* memory;
};

class PhysM
{
public:
    static int init(void);
    static void* malloc(size_t size, bool calloc);
    static void* realloc(void* oldmem, size_t size);
    static void free(void* ptr);
    static int print_debug(void);
private:
    static void* allocate_blocks(uint32_t num, bool calloc);
    static int free_all_blocks_from(Block& block);
    static Block& find_block_from_memory(void* memory_from_block);
    static bool is_suitable_block(uint32_t block_index, uint32_t block_num);
    static int find_best_block(uint32_t num);
    static int get_blocks_num(void* example_block_mem_ptr);

    static Block blocks[MEM_SIZE / BLOCK_SIZE];
    static uint32_t total_blocks;
    static void* memory;
};

#endif
