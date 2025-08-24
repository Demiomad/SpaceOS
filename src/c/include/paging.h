#ifndef PAGING_H
#define PAGING_H

extern void loadPageDir(unsigned int*);
extern void enablePaging();

void paging_init();

#endif