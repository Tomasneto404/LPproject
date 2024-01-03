/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   branchs.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 2 de janeiro de 2024, 15:07
 */

#ifndef BRANCHS_H
#define BRANCHS_H

#define MAX_ACTIVITY_BRANCHS 30
#define MAX_AB_NAME_SIZE 100
#define NAME_MSG "Name > "

#define STATE_MSG "State [1 - Active | 0 - Inactive] > "
#define MIN_STATE_VALUE 0
#define MAX_STATE_VALUE 1

#define CODE_MSG "Code > "
#define MIN_AB_CODE_VALUE 0
#define MAX_AB_CODE_VALUE 1000

#define AB_DOES_NOT_EXIST "ERROR: This Activity Branch does not exist."
#define AB_ALREADY_EXISTS "ERROR: This activity branch already exists."

#define EMPTY_LIST "ERROR: List is empty."
#define FULL_LIST "ERROR: List is full."

#define BRANCHS_FILE "branchs.bin"

typedef struct ActivityBranch {
    int code, state;
    char name[MAX_AB_NAME_SIZE];
} ActivityBranch;

typedef struct ActivityBranchs {
    int counter, size;
    ActivityBranch *branchs;
} ActivityBranchs;


/**
 * @brief This function is used to convert the entire string to lowercase
 * @param receives a pointer of type ActivityBranchs called name
 * @return zero in the end of function
 */
char convertLowercase(ActivityBranchs *name);

/**
 * @brief Creates a new activity branch and adds it to the collection of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void createActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Creates a new activity branch and adds it to the collection if the code is unique.
 * @param branchs A pointer to the structure containing the array of activity branches.
 * @return The index of the newly created activity branch if successful, or -1 if the code already exists.
 */
int createActivityBranch(ActivityBranchs *branchs);

/**
 * @brief Searches for an activity branch with a specific code within an array of activity branches.
 * @param branchs The structure containing the array of activity branches.
 * @param code The code to search for within the activity branches.
 * @return The index of the activity branch if found, or -1 if not found.
 */
int searchActivityBranch(ActivityBranchs branchs, int code);

/**
 * @brief Lists the details of all activity branches in the provided array.
 * @param branchs The structure containing the array of activity branches to be listed.
 */
void listActivityBranchs(ActivityBranchs branchs);

/**
 * @brief Prints the details of an individual activity branch.
 * @param branch The activity branch to be printed.
 */
void printActivityBranch(ActivityBranch branch);

/**
 * @brief Updates the details of an activity branch within an array of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void updateActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Updates the state of an individual activity branch.
 * @param branch A pointer to the specific activity branch to be updated.
 */
void updateActivityBranch(ActivityBranch *branch);

/**
 * @brief Deletes an activity branch from the array of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void deleteActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Deletes an individual activity branch by resetting its attributes.
 * @param branch A pointer to the specific activity branch to be deleted.
 */
void deleteActivityBranch(ActivityBranch *branch);

/*
 Falta documentar
 */
int verifyAbName(ActivityBranchs branchs, char *name);

/**
 * Falta documentar
 * @param branchs
 * @param file
 */
void saveBranchs(ActivityBranchs *branchs, char *file);

/**
 * Falta documentar
 * @param branchs
 */
void freeBranchs(ActivityBranchs *branchs);

/**
 * Falta documentar
 * @param branchs
 * @param file
 */
void loadBranchs(ActivityBranchs *branchs, char *file);

#endif /* BRANCHS_H */

