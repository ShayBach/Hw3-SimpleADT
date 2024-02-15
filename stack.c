#include <stddef.h>  /* size_t type */
#include <stdio.h>   /* printf etc. */
#include <stdlib.h>  /* malloc etc. */
#include <stdbool.h> /* bool type */
#include "stack.h"

struct stack {
    elem_t *top;
    size_t max_size;
    size_t location;
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
};

pstack_t stack_create(size_t max_size, clone_t clone_func,
                      destroy_t destroy_func, print_t print_func) {
    if (max_size <= 0) {
        fprintf(stderr, "Stack creation faild -stack size is invalid\n");
        return NULL;
    }
    if (clone_func == NULL) {
        fprintf(stderr, "Stack creation faild - clone function points to \
        Null\n");
        return NULL;
    }
    if (destroy_func == NULL) {
        fprintf(stderr, "Stack creation faild -destroy function points to \
        Null\n");
        return NULL;
    }
    if (print_func == NULL) {
        fprintf(stderr, "Stack creation faild - print function points to \
        Null\n");
        return NULL;
    }
    /* stack_p just points to the fields of the stack */
    pstack_t stack_p =(pstack_t) malloc(sizeof(struct stack));
    /* stack_p.top points to the elements in the stack */
    stack_p->top = malloc(sizeof(elem_t)*max_size);
    if (stack_p == NULL || stack_p->top == NULL) {
        fprintf(stderr, "Stack creation faild - stack top allocation faild\n");
        free (stack_p->top);
        free (stack_p);
        return NULL;
    }
    stack_p->max_size = max_size;
    stack_p->location = 0;
    stack_p->clone_func = clone_func;
    stack_p->destroy_func = destroy_func;
    stack_p->print_func = print_func;
    return stack_p;
}

enum result stack_destroy(pstack_t stack_p) {
    if (stack_p == NULL) {
        fprintf(stderr, "Stack destroy faild - \
        stack pointer points to NULL\n");
        return FAIL;
    }
    /* deleting each element of the stack */
    while (stack_p->location > 0) {
        stack_pop(stack_p);
    }
    free (stack_p->top);
    free (stack_p);
    return SUCCESS;
}

enum result stack_push (pstack_t stack_p, elem_t new_elem) {
    if (stack_p == NULL) {
        fprintf(stderr, "Stack push faild - \
        stack pointer points to NULL\n");
        return FAIL;
    }
    if (new_elem == NULL) {
        fprintf(stderr, "Stack push faild - new element points to NULL\n");
        return FAIL;
    }
    /* Check if we are not overstepping the max size (realloc?) */
    if (stack_p->location == stack_p->max_size) {
        fprintf(stderr, "Stack push faild - stack is full\n");
        return FAIL;
    }
    /* create a copy of the new element */
    elem_t cloned_elem = stack_p->clone_func(new_elem);
    if (cloned_elem == NULL){
        fprintf(stderr, "Stack push faild - new element cloning failed\n");
        return FAIL;
    }
    /* first we point the new top and then increment the location by 1 */
    stack_p->top[stack_p->location] = cloned_elem;
    stack_p->location++;
    return SUCCESS;
}

void stack_pop (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack pop faild - \
        stack pointer points to NULL\n");
        return;
    }
    /* Check if the stack is empty before popping */
    if (stack_p->location == 0) {
        fprintf(stderr, "Stack pop faild - stack is empty\n");
        return;
    }
    /* creating a pointer to the last element in the stack */
    elem_t elem_to_delete = stack_p->top[stack_p->location-1];
    /* Deleting the value it points to */
    /* destory_func frees each stack element */
    stack_p->destroy_func(elem_to_delete);
    stack_p->location--;
}

elem_t stack_peek (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack peek faild - \
        stack pointer points to NULL\n");
        return NULL;
    }
    /* Check if the stack is empty before peeking */
    if (stack_p->location == 0) {
        fprintf(stderr, "Stack peek faild - stack is empty\n");
        return NULL;
    }
    return stack_p->top[stack_p->location-1];
}

size_t stack_size (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack size faild - \
        stack pointer points to NULL\n");
        return 0;
    }
    return stack_p->location; 
}

bool stack_is_empty (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack is empty faild - \
        stack pointer points to NULL\n");
        return false;
    }
    return (stack_p->location == 0); 
}

size_t stack_capacity (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack capacity faild - \
        stack pointer points to NULL\n");
        return 0;
    }
    return stack_p->max_size - stack_p->location;
}

void stack_print (pstack_t stack_p) {
    /* Check if stack points to null */
    if (stack_p == NULL) {
        fprintf(stderr, "Stack print faild - \
        stack pointer points to NULL\n");
        return;
    }
    for (int i = stack_p->location - 1; i >= 0; i--) {
        stack_p->print_func(stack_p->top[i]);
    }
}