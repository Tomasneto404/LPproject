/**
 * @file branchs.c
 * @author Tania, Gonçalo, Tomas
 * @date 11-01-2024
 * @version 1
 *
 * @copyright Copyright (C) Tania, Gonçalo, Tomas 2023. All Rights MIT Licensed.
 *
 * @brief Contains functions related to activity branchs.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "branchs.h"
#include "companys.h"

/**
 * @brief This function aims to expand the allocated memory, using the realloc function
 * @param branchs receives a pointer named branchs of type ActivityBranchs
 */
void expandBranchsCapacity(ActivityBranchs *branchs) {
    int tam = (branchs->size) == 0 ? MAX_ACTIVITY_BRANCHS : branchs->size * 2;
    ActivityBranch *tmp = (ActivityBranch*) realloc(branchs->branchs, sizeof (ActivityBranchs)*(tam));

    if (tmp != NULL) {
        branchs->size = tam;
        branchs->branchs = tmp;
    }
}

/**
 * @brief This function if an activity branch is already using a specified name
 * @param branchs Variable of activity branchs 
 * @param name The name to be compared if is in use
 * @return 0 If the name is already in use. -1 If the name is not in use.
 */
int verifyABName(ActivityBranchs branchs, char *name) {
    int i;

    for (i = 0; i < branchs.counter; i++) {

        if (strcmp(branchs.branchs[i].name, name) == 0) {
            return 0;
        }

    }
    return -1;
}

/**
 * @brief Creates a new activity branch and adds it to the collection of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 * @return 0 if successful,
 *  returns -1 if not,
 *  returns 1 if the name is already being used by other activity branch,
 *  returns 2 if the code is already being used by other activity branch.
 */
int createActivityBranch(ActivityBranchs *branchs) {

    int code = getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG);
    char name[MAX_NAME];


    if (searchActivityBranch(*branchs, code) == -1) {

        readString(name, MAX_COMPANY_NAME_SIZE, NAME_MSG);

        if (verifyABName(*branchs, name) == -1) {

            branchs->branchs[branchs->counter].code = code;

            strcpy(branchs->branchs[branchs->counter].name, name);

            branchs->branchs[branchs->counter].state = getInt(MIN_STATE_VALUE, MAX_STATE_VALUE, STATE_MSG);

            branchs->counter++;

            return 0;
        } else {
            return 1;
        }

    } else {
        return 2;
    }
    return -1;
}

void createActivityBranchs(ActivityBranchs *branchs) {

    if (branchs->counter == branchs->size) {
        expandBranchsCapacity(branchs);
    }

    if (branchs->counter < branchs->size) {

        switch (createActivityBranch(branchs)) {
            case -1:
                puts(ERROR_BRANCH);
                break;
                
            case 1:
                puts(ERROR_NAME);
                break;

            case 2:
                puts(ERROR_CODE);
                break;

            default:
                puts(SUCCESS_BRANCH);
                break;
        }

    } else {
        puts(ERROR_SPACE);
    }

}

int searchActivityBranch(ActivityBranchs branchs, int code) {
    int i;
    for (i = 0; i < branchs.counter; i++) {
        if (branchs.branchs[i].code == code) {
            return i;
        }
    }
    return -1;
}

void listActivityBranchs(ActivityBranchs branchs) {
    if (branchs.counter > 0) {
        int i;
        printf("\n%-5s %-15s %-10s\n", "CODE", "NAME", "STATE");
        for (i = 0; i < branchs.counter; i++) {
            printActivityBranch(branchs.branchs[i]);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

/**
 * @brief Prints the details of an individual activity branch.
 * @param branch The activity branch to be printed.
 */
void printActivityBranch(ActivityBranch branch) {

    printf("%-5d %-15s", branch.code, branch.name);

    if (branch.state == 1) {
        printf("%-10s\n", "Active");
    } else {
        printf("%-10s\n", "Inactive");
    }
}

void updateActivityBranchs(ActivityBranchs *branchs, Companies *companies) {
    int i, code = 0, newState = 0;
    
    code = searchActivityBranch(*branchs, getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG));

    if (code != -1) {
        newState = getInt(MIN_STATE_VALUE, MAX_STATE_VALUE, STATE_MSG);
        if (newState == 0) {
            for (i = 0; i < companies->counter; ++i) {
                if (companies->companies[i].branch == branchs->branchs[code].code) {
                    companies->companies[i].state = 0;
                }
            }
        }
        branchs->branchs[code].state = newState;
    } else {
        puts(AB_DOES_NOT_EXIST);
    }
}

/**
 * @brief This function verifies if a specified activity branch is active or not.
 * @param branch The activity branch to verify if is active or not.
 * @return 0 If is active. -1 If is not active.
 */
int isActive(ActivityBranch branch) {

    if (branch.state == 1) {
        return 0;
    }

    return -1;
}

int getBranch(ActivityBranchs *branchs) {
    int branchCode = -1, branchPosition = 0, flag = 0;
    do {
        branchCode = getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG);

        branchPosition = searchActivityBranch(*branchs, branchCode);

        if (branchPosition != -1) {

            if (isActive(branchs->branchs[branchPosition]) != -1) {

                return branchCode;

            } else {
                puts("ERROR: This branch is inactive.");
            }

        } else {
            puts("ERROR: Activity branch not found.");

        }

    } while (flag != 1);
    return -1;
}

/**
 * @brief This function verifies if an activity branch is being used by any company.
 * @param branch The specified activity branch.
 * @param companies The companies variable to check if any is using the specified activity branch.
 * @return 0 If the activity branch is not being used. -1 If the activity branch is being used.
 */
int hasCompany(ActivityBranch branch, Companies companies) {

    int i, counter = 0;

    for (i = 0; i < companies.counter; i++) {

        if (companies.companies[i].branch == branch.code) {
            companies.companies[i].state = 0;
            counter++;
        }

    }

    if (counter > 0) {
        return 0;
    }

    return -1;
}

/**
 * @brief Deletes an individual activity branch by reseting its attributes.
 * @param branch A pointer to the specific activity branch to be deleted.
 */
void deleteActivityBranch(ActivityBranch *branch) {
    branch->code = 0;
    strcpy(branch->name, "");
    branch->state = 0;
}

/**
 * @brief This function removes a specific activity branch from the memory.
 * @param branchs The activity branchs pointer to remove a specific one
 * @param companies The companies pointer to verify if any is using the specific activity branch
 */
void deleteActivityBranchs(ActivityBranchs *branchs, Companies *companies) {

    int i, code = 0;

    if (branchs->counter > 0) {
        code = searchActivityBranch(*branchs, getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG));

        if (code != -1) {

            if (hasCompany(branchs->branchs[code], *companies) == -1) {

                for (i = code; i < branchs->counter - 1; i++) {
                    branchs->branchs[i] = branchs->branchs[i + 1];
                }

                deleteActivityBranch(&branchs->branchs[i]);

                branchs->counter--;

                puts(SUCCESS_DELETE);

            } else {
                branchs->branchs[code].state = 0;
                puts(ERROR_DELETE);
            }

        } else {
            puts(AB_DOES_NOT_EXIST);
        }
    } else {
        puts(EMPTY_LIST);
    }

}


/**
 * @brief This functions search and activity branch by a specified name.
 * @param branchs The variable to look for.
 * @param name The specified name to look for int the activity branchs.
 * @return Activity branch position if found. -1 if activity branch was not found.
 */
int searhAbName(ActivityBranchs branchs, char *name) {

    int i;

    for (i = 0; i < branchs.counter; i++) {

        if (branchs.branchs[i].name == name) {
            return i;
        }

    }
    return -1;
}

void saveBranchs(ActivityBranchs *branchs, char *file) {
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&(branchs->counter), sizeof (int), 1, fp);

    for (i = 0; i < branchs->counter; i++) {
        fwrite(&(branchs->branchs[i]), sizeof (ActivityBranch), 1, fp);

    }

    fclose(fp);
}

void freeBranchs(ActivityBranchs *branchs) {
    if (branchs->branchs) {
        free(branchs->branchs);
        branchs->branchs = NULL;
    }

    branchs = NULL;
}

void loadBranchs(ActivityBranchs *branchs, char *file) {
    int i, sucesso = 0;

    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        branchs->counter = 0;

        fread(&(branchs->counter), sizeof (int), 1, fp);

        if (branchs->counter > 0) {
            branchs->size = branchs->counter;
            branchs->branchs = (ActivityBranch*) malloc(branchs->counter * sizeof (ActivityBranch));
            for (i = 0; i < branchs->counter; i++) {
                fread(&(branchs->branchs[i]), sizeof (ActivityBranch), 1, fp);
            }
            sucesso = 1;
        }

        fclose(fp);
    }

    if (!sucesso) {
        branchs->branchs = (ActivityBranch*) malloc(MAX_ACTIVITY_BRANCHS * sizeof (ActivityBranch));
        branchs->counter = 0;
        branchs->size = MAX_ACTIVITY_BRANCHS;

    }
}
