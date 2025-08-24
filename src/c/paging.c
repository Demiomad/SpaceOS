#include <paging.h>
#include <stdint.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

void init_page_dir() {
    for (int i = 0; i < 1024; i++)
    {
        page_directory[i] = 0x00000002;
    }
}

void init_page_table() {
    for (unsigned int i = 0; i < 1024; i++)
    {
        first_page_table[i] = (i * 0x1000) | 3;
    }
}

void paging_init() {
    init_page_dir();
    init_page_table();
    page_directory[0] = ((unsigned int)first_page_table) | 3;
    loadPageDir(page_directory);
    enablePaging();
}