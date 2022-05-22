#ifndef LUMALANG_LIST_H_
#define LUMALANG_LIST_H_

#pragma once

#include <cstddef>

class List
{
private:
    void **items;
    size_t size;
    size_t item_size;

public:
    List(size_t size);
    void list_push(void *item);
    void *get_items(int index);
    size_t get_size();
};

#endif