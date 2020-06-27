#include <kernel/physm.h>

Block PhysM::blocks[MEM_SIZE / BLOCK_SIZE];
uint32_t PhysM::total_blocks;
void* PhysM::memory;

/* very naive implementaiton, temp */

int PhysM::print_debug(void)
{
    printf("-------------------------\n");
    printf("mem starts at: %p\n", (void*)memory);
    for(size_t i = 0; i < total_blocks; i++)
    {
        printf("block: %d - ", i);
        printf("used: %d - ", blocks[i].used);
        printf("blockid: %d - ", blocks[i].allocate_id);
        printf("block at: %p\n", (void*)blocks[i].memory);
    }
    printf("++++++++++++++++++++++++++\n");

    return 0;
}

int PhysM::init(void)
{
    total_blocks = MEM_SIZE / BLOCK_SIZE;
    memory = memset((void*)(&end), 0, total_blocks * BLOCK_SIZE);

    /* Init memory in blocks */
    for(size_t i = 0; i < total_blocks; i++)
    {
        blocks[i].memory = (char*)memory + (i * BLOCK_SIZE);
    }

    return 0;
}

void* PhysM::malloc(size_t size, bool calloc)
{
    if(!size)
        return NULL;

    uint32_t num = size / BLOCK_SIZE;
    if(num * BLOCK_SIZE < size)
        num++;
    return allocate_blocks(num, calloc);
}

void* PhysM::realloc(void* oldmem, size_t size)
{
    void* newmem = malloc(size, false);
    size_t oldsize = get_blocks_num(oldmem) * BLOCK_SIZE;

    memcpy(newmem, oldmem, oldsize);
    free(oldmem);

    return newmem;
}

void PhysM::free(void* ptr)
{
    if(!ptr)
        return;

    Block& block = find_block_from_memory(ptr);
    free_all_blocks_from(block);
}

void* PhysM::allocate_blocks(uint32_t num, bool calloc)
{
    int first_block_index = find_best_block(num);
    if(first_block_index == -1)
        return NULL;

    uint32_t id = Timer::get_ms_from_boot();

    for(unsigned int i = first_block_index; i < (first_block_index + num); i++)
    {
        Block* block = &blocks[i];
        block->used = 1;
        block->allocate_id = id;
        if(calloc)
            memset(block->memory, 0, BLOCK_SIZE);
    }

    return blocks[first_block_index].memory;
}

int PhysM::free_all_blocks_from(Block& block)
{
    uint32_t id = block.allocate_id;
    for(uint32_t i = 0; i < total_blocks; i++)
    {
        Block* blk = &blocks[i];
        if(blk->allocate_id == id)
            blk->used = 0;
    }

    return 0;
}

Block& PhysM::find_block_from_memory(void* memory_from_block)
{
    int index = ((char*)memory_from_block - (char*)memory) / BLOCK_SIZE;//calculate block num from addr
    //printf("freeing block %d\n", index);
    return blocks[index];
}

bool PhysM::is_suitable_block(uint32_t block_index, uint32_t block_num)
{
    //printf("finding mem for %d blocks\n", block_num);
    for(size_t i = 0; i < block_num; i++)
    {
        Block* examining_block = &blocks[block_index++];
        if(block_index  > total_blocks || examining_block->used)
            return false;
    }

    return true;
}

int PhysM::find_best_block(uint32_t num)
{
    for(size_t i = 0; i < total_blocks; i++)
    {
        if(is_suitable_block(i, num))
            return i;
    }

    printf("Run out of heap memory!\n");
    return -1;
}

int PhysM::get_blocks_num(void* example_block_mem_ptr)
{
    int num = 0;
    Block& block = find_block_from_memory(example_block_mem_ptr);
    uint32_t id = block.allocate_id;

    for(size_t i = 0; i < total_blocks; i++)
    {
        if(blocks[i].allocate_id == id)
            num++;
    }

    return num;
}
