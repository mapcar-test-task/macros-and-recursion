#include <stdio.h>
#include <stdlib.h>

#define NODE_DEF(T) struct Node_##T { T data; struct Node_##T* next; }
#define NODE(T) struct Node_##T
// #define NODE(T) struct Node_##T { T data; struct Node_##T* next; }
#define MAPCAR(T, head, func) mapcar_##T(head, func)

NODE_DEF(int);

NODE(int)* mapcar_int(NODE(int)* head, int (*func)(int)) {
    if (head == NULL) {
        return NULL;
    }

    NODE(int)* new_head = (NODE(int)*) malloc(sizeof(NODE(int)));
    new_head->data = func(head->data);
    new_head->next = mapcar_int(head->next, func);
    return new_head;
}

NODE(int)* create_node_int(int data) {
    NODE(int)* node = (NODE(int)*) malloc(sizeof(NODE(int)));
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list_int(NODE(int)* head) {
    NODE(int)* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int square(int x) {
    return x * x;
}

void free_list_int(NODE(int)* head) {
    NODE(int)* current = head;
    while (current != NULL) {
        NODE(int)* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    NODE(int)* list = create_node_int(1);
    list->next = create_node_int(2);
    list->next->next = create_node_int(3);

    printf("Original list: ");
    print_list_int(list);

    NODE(int)* new_list = MAPCAR(int, list, square);
    printf("New list: ");
    print_list_int(new_list);

    free_list_int(list);
    free_list_int(new_list);

    return 0;
}
