#include "header.h"

void *addToArchive(t_llist **head, void *new_data, size_t data_size) {
    t_llist *new_node = (t_llist*)malloc(sizeof(t_llist));

    new_node->data  = malloc(data_size);
    new_node->next = (*head);

    int i;
    for (i = 0; i < data_size; i++) {
      *(char *)(new_node->data + i) = *(char *)(new_data + i);
    }

    (*head) = new_node;
};
