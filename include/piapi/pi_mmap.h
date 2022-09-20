#ifndef PI_MMAP_H
#define PI_MMAP_H

void *get_mmap_ptr();

void free_mmapbuf();

void write_mmapbuf(int pos, void *data, int len);

void init_mmapbuf();

#endif