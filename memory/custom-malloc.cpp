#include <iostream>
#include <sys/types.h>
#include <unistd.h>

struct Header {
    size_t size;
    bool free;
    Header* next;
};

Header* ptr_list = nullptr;

Header* search_free_block(size_t size) {
    Header* current = ptr_list;
    while (current != nullptr) {
        if (current->free == true && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void* my_malloc(size_t size) {
    if (size == 0) return nullptr;

    Header* block = search_free_block(size);
    if (block) {
        block->free = false;
        return (void*)(block + 1);
    }

    size_t total_size = size + sizeof(Header);
    void* new_space = sbrk(total_size);

    if (new_space == (void*)-1) return nullptr;

    block = (Header*) new_space;
    block->size = size;
    block->free = false;
    block->next = nullptr;

    if (ptr_list == nullptr) {
        ptr_list = block;
    } else {
        Header* temp = ptr_list;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = block;
    }

    return (void*)(block + 1); 
}

void my_free(void* ptr) {
    if (!ptr) return;
    
    Header* block = (Header*)ptr - 1;
    block->free = true; 
}

int main() {
    std::cout << "teste de alocação\n";
    
    int* a = (int*) my_malloc(sizeof(int));
    *a = 100;
    std::cout << "endereço a alocado em: " << a << " (valor " << *a << ")\n";

    my_free(a);
    std::cout << "'a' foi liberado com my_free().\n";

    int* b = (int*) my_malloc(sizeof(int));
    *b = 200;
    std::cout << "endereço b alocado em: " << b << " (valor: " << *b << ")\n";

    if (a == b) {
        std::cout << "b reutilizou fisicamente o endereço do a\n";
    }
    return 0;
}
