#ifndef STUDENT_H
#define STUDENT_H

/**
 * @file student.h
 * @brief Definition of the student structure and related functions.
 */

#include <stdio.h>   /**< Include printf etc. */
#include <stdlib.h>  /**< Include malloc etc. */
#include "stack.h"

/** 
 * @struct student
 * @brief Represents a student with name, age, and ID.
 */
struct student {
    char *name; /**< Pointer to the name of the student. */
    int age;    /**< Age of the student. */
    int id;     /**< ID of the student. */
};

/** 
 * @typedef pstudent_t
 * @brief Typedef for a pointer to a student structure.
 */
typedef struct student *pstudent_t;

/** 
 * @brief Clone function for a student.
 * 
 * @param student_p Pointer to the student structure to clone.
 * @return Pointer to the cloned student structure.
 */
elem_t student_clone (elem_t student_p);

/** 
 * @brief Destroy function for a student.
 * 
 * @param student_p Pointer to the student structure to destroy.
 */
void student_destroy (elem_t student_p);

/** 
 * @brief Print function for a student.
 * 
 * @param student_p Pointer to the student structure to print.
 */
void student_print (elem_t student_p);

#endif //STUDENT_H
