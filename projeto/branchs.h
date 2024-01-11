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

#define MAX_ACTIVITY_BRANCHS 10
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

#define ERROR_BRANCH "ERROR: Was not possible to create a new branch."
#define ERROR_NAME "ERROR: Name is already in use."
#define ERROR_CODE "ERROR: Code is already in use."
#define ERROR_SPACE "ERROR: No Space available to create new branch."
#define SUCCESS_BRANCH "SUCCESS: Activity Branch created"

#define SUCCESS_DELETE "SUCCESS: Activity Branch deleted."
#define ERROR_DELETE "WARNING: There are companies with this branch in use. Activity Branch's and Company's state have been changed to Inactive."

#define BRANCHS_FILE "branchs.bin"

typedef struct {
    int code, state;
    char name[MAX_AB_NAME_SIZE];
} ActivityBranch;

typedef struct {
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
 * @brief This prompts until he selects an available activity branch (An activity branch that is neither inactive nor nonexistent). 
 * @param branchs The pointer to find an available activity branch.
 * @return Activity branch code if found an availabe one. -1 If it didn´t.
 */
int getBranch(ActivityBranchs *branchs);

/**
 * @brief Deletes an activity branch from the array of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void deleteActivityBranchs();

/**
 * @brief Deletes an individual activity branch by resetting its attributes.
 * @param branch A pointer to the specific activity branch to be deleted.
 */
void deleteActivityBranch(ActivityBranch *branch);

/**
 * @brief This functions search and activity branch by a specified name.
 * @param branchs The variable to look for.
 * @param name The specified name to look for int the activity branchs.
 * @return Activity branch position if found. -1 if activity branch was not found.
 */
int searhAbName(ActivityBranchs branchs, char *name);

/**
 * @brief This function writes the data of Activity Branchs that is in memory pointed by the first argument to the specified file.
 * @param branchs The pointer of the data memory.
 * @param file The file where the data will be stored.
 */
void saveBranchs(ActivityBranchs *branchs, char *file);

/**
 * @brief This function frees the memory that was allocated for the Activity Branchs pointer given in the argument that was being used to store the data. After freeing the memory in puts all the values to NULL.
 * @param branchs The pointer where data was being stored.
 */
void freeBranchs(ActivityBranchs *branchs);

/**
 * @brief This function reads the data from the file that is given in the second argument and allocs memmory with the size of the Activity Branchs struct for the data data was read. 
 * If the file does not exist it allocs a default size of memory for the future data.
 * @param branchs The pointer where the memmory will be allocated
 * @param file The file that the function will read
 */
void loadBranchs(ActivityBranchs *branchs, char *file);

/**
 * @brief This function verifies if a specified activity branch is active or not.
 * @param branch The activity branch to verify if is active or not.
 * @return 0 If is active. -1 If is not active.
 */
int isActive(ActivityBranch branch);

#endif /* BRANCHS_H */

