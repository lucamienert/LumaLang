#include <list.h>
#include <cstdlib>

List::List(size_t size)
{
    this->size = 0;
    this->item_size = size;
    this->items = 0;
}

void List::list_push(void *item)
{
    size++;
    if(items == nullptr)
        items = new void*;
    else
        items = (void**)realloc(items, (size * item_size));

    items[size - 1] = item;
}

void *List::get_items(int index)
{
    return items[index];
}

size_t List::get_size()
{
    return size;
}