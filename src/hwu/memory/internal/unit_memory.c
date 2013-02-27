#include "hwu/memory/internal/unit_memory.h"
#include "hwu/debug/assert.h"

typedef struct tag_block_header_t
{
	struct tag_block_header_t* next;
} block_header_t;

void hwuL_unit_memory_initialize(void* memory, int unit_size, int unit_num, void* append_unit_memory)
{
	int					i	  = 0;
    block_header_t*		block = memory;

    /* NULLチェック */
    HWU_NULL_ASSERT(memory);

    /* ゼロサイズは作らない */
    HWU_ASSERT(unit_size > sizeof(block_header_t));
    HWU_ASSERT(unit_num > 0);

    /* メモリをブロックに分けてリンク */
    for(i = 0; i < (unit_num - 1); ++i) {
		block->next = (block_header_t*)((char*)block + unit_size);
		block = block->next;
    }

    /* 末尾に指定の他のユニットメモリをつなげる */
    /* なければNULL */
    block->next = append_unit_memory;
}

void* hwuL_unit_memory_pop(void* head, void** new_head)
{
    block_header_t* head_block = NULL;
    if(head != NULL){
		head_block = (block_header_t*)head;
		*new_head = head_block->next;
    }
	
    return head_block;
}

void hwuL_unit_memory_push(void* head, void* memory, void** new_head)
{
    if(head != NULL) {
		block_header_t* head_block = (block_header_t*)head;
		block_header_t* push_block = (block_header_t*)memory;

		push_block->next = head_block;
		*new_head        = push_block;
    }
}

hwbool hwuL_unit_memory_empty(void* head)
{
    return ((block_header_t*)head)->next == NULL;
}

int hwuL_unit_memory_calculate_need_size(int unit_size, int unit_num)
{
	return unit_size * unit_num;
}

