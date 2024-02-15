
#include <stdio.h>   /**< Include printf etc. */
#include <string.h>  /**< Include strcpy etc. */
#include <stdlib.h>  /**< Include malloc etc. */
#include "student.h"

/**
 * @brief Checks if a name is valid.
 * 
 * This function checks if a given name contains only 
 * alphabetic characters.
 * @param name Pointer to the name string to validate.
 * @return 0 if the name is valid, 1 otherwise.
 */
static int check_name_validation(char *name);

elem_t student_clone (elem_t student_p) {
    if (student_p == NULL) {
        fprintf(stderr, "Student clone faild - \
        student points to NULL\n");
        return NULL;
    }
    pstudent_t cloned_student_p = (pstudent_t)malloc(sizeof(struct student));
    if (cloned_student_p == NULL) {
        fprintf(stderr, "Student clone faild - \
        cloned student allocation failed\n");
        return NULL;
    }
    /* casting student_p - treat elem_t type as pstudent_t type */
    pstudent_t casted_student_p = (pstudent_t)student_p;
    if ((check_name_validation(casted_student_p->name)) || (casted_student_p->age <=0) \
    || (casted_student_p->id < 0)) {
        fprintf(stderr, "Student clone faild -\
        student's paramenters are wrong\n");
        return NULL;
    } 
    /* strlen returns size_t type and +1 to include space for 
    null-terminator character '\O' */
    size_t name_length = strlen(casted_student_p->name) + 1;
    cloned_student_p->name = (char*)malloc(sizeof(char) * name_length);
    if (cloned_student_p->name == NULL) {
        free(cloned_student_p); // Free previously allocated memory
        fprintf(stderr, "Student clone failed - name allocation failed\n");
        return NULL;
    }
    strcpy(cloned_student_p->name,casted_student_p->name);
    cloned_student_p->age = casted_student_p->age;
    cloned_student_p->id = casted_student_p->id;
    return cloned_student_p;
}

void student_destroy (elem_t student_p) {
    if (student_p == NULL) {
        fprintf(stderr, "Student destroy faild - \
        student points to NULL\n");
        return;
    }
    pstudent_t casted_student_p = (pstudent_t)student_p;
    free (casted_student_p->name);
    free (casted_student_p);
}

void student_print (elem_t student_p) {
    if (student_p == NULL) {
        fprintf(stderr, "Student print faild - \
        student points to NULL\n");
        return;
    }
    pstudent_t casted_student_p = (pstudent_t)student_p;
    printf("student name: %s, age: %d, id: %d.\n",\
    casted_student_p->name,casted_student_p->age,casted_student_p->id);
}

static int check_name_validation(char *name){
    if (strlen(name) == 0) {
        return 1;
    }
    for (int i=0; i < strlen(name); i++) {
        if (!(name[i] >= 'a' && name[i] <= 'z') ||\
        (name[i] >= 'A' && name[i] <= 'Z')) {
            return 1;
        }
    } 
    return 0;
}