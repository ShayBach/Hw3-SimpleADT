#ifndef STACK_H
#define STACK_H

#include <stddef.h>  /**< Include size_t type */
#include <stdio.h>   /**< Include printf etc. */
#include <stdlib.h>  /**< Include malloc etc. */
#include <stdbool.h> /**< Include bool type */
#include "common.h" /**result typedef, elem_t typdef  */

typedef struct stack *pstack_t;
/*clone_t is a function pointer type that points to a function taking
an elem_t parameter and returning an elem_t value. */
typedef elem_t (*clone_t) (elem_t e);
typedef void (*destroy_t) (elem_t e);
typedef void (*print_t) (elem_t e);

/**
 * @brief Creates a new stack.
 * @param max_size The maximum size of the stack.
 * @param clone A function pointer for cloning elements.
 * @param destroy A function pointer for deleting elements.
 * @param print A function pointer for printing elements.
 * @return A pointer to the newly created stack.
 */
pstack_t stack_create(size_t max_size, clone_t clone, 
                      destroy_t destroy, print_t print);

/**
 * @brief Destroys a stack and frees memory.
 * @param stack The stack to be destroyed.
 * @return SUCCESS if successful, otherwise FAIL.
 */
enum result stack_destroy(pstack_t stack);

/**
 * @brief Pushes an element onto the stack.
 * @param stack The stack to push onto.
 * @param elem The element to push onto the stack.
 * @return SUCCESS if successful, otherwise FAIL.
 */
enum result stack_push(pstack_t stack, elem_t elem);

/**
 * @brief Pops an element from the stack.
 * @param stack The stack to pop from.
 */
void stack_pop(pstack_t stack);

/**
 * @brief Returns the top element of the stack.
 * @param stack The stack to peek.
 * @return The top element of the stack.
 */
elem_t stack_peek(pstack_t stack);

/**
 * @brief Returns the size of the stack.
 * @param stack The stack.
 * @return The size of the stack.
 */
size_t stack_size(pstack_t stack);

/**
 * @brief Checks if the stack is empty.
 * @param stack The stack.
 * @return true if the stack is empty, false otherwise.
 */
bool stack_is_empty(pstack_t stack);

/**
 * @brief Returns the capacity of the stack.
 * @param stack The stack.
 * @return The capacity of the stack.
 */
size_t stack_capacity(pstack_t stack);

/**
 * @brief Prints the elements of the stack.
 * @param stack The stack to print.
 */
void stack_print(pstack_t stack);

#endif /* STACK_H */
