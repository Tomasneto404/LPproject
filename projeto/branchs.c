#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "branchs.h"
#include "companys.h"

char convertLowercase(ActivityBranchs *branchs) {
    int counter, i;

    while ((branchs->branchs[branchs->counter].name)[counter] != '\0') {
        counter++;
    }

    if ((branchs->branchs[branchs->counter].name)[counter - 1] == '\n') {
        (branchs->branchs[branchs->counter].name)[--counter] = '\0';
    }

    for (i = 0; i < counter; i++) {
        if (branchs->branchs[branchs->counter].name[i] >= 65 && branchs->branchs[branchs->counter].name[i] <= 90) {

            return branchs->branchs[branchs->counter].name[i] += 32;
        }
    }

    return 0;
}

void expandBranchsCapacity(ActivityBranchs *branchs) {
    int tam = (branchs->size) == 0 ? MAX_ACTIVITY_BRANCHS : branchs->size * 2;
    ActivityBranch *tmp = (ActivityBranch*) realloc(branchs->branchs, sizeof (ActivityBranchs)*(tam));

    if (tmp != NULL) {
        branchs->size = tam;
        branchs->branchs = tmp;
    }
}

int verifyABName(ActivityBranchs branchs, char *name) {

    int i;

    for (i = 0; i < branchs.counter; i++) {

        if (strcmp(branchs.branchs[i].name, name) == 0) {
            return 0;
        }

    }
    return -1;
}

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

void printActivityBranch(ActivityBranch branch) {

    printf("%-5d %-15s", branch.code, branch.name);

    if (branch.state == 1) {
        printf("%-10s\n", "Active");
    } else {
        printf("%-10s\n", "Inactive");
    }
}

void updateActivityBranchs(ActivityBranchs *branchs) {

    int code = searchActivityBranch(*branchs, getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG));

    if (code != -1) {
        updateActivityBranch(&branchs->branchs[code]);
    } else {
        puts(AB_DOES_NOT_EXIST);
    }

}

void updateActivityBranch(ActivityBranch *branch) {

    branch->state = getInt(MIN_STATE_VALUE, MAX_STATE_VALUE, STATE_MSG);

}

int hasCompany(ActivityBranch branch, Companies companies) {
    
    int i, counter = 0;
    
    for (i = 0; i < companies.counter; i++) {
        
        if (companies.companies[i].branch == branch.code){   
            companies.companies[i].state = 0;   
            counter++;
        }
        
    }
    
    if (counter > 0) {
        return 0;
    }
    
    return -1;
}

void deleteActivityBranchs(ActivityBranchs *branchs, Companies *companies) {
    
    int i, code = 0, companyCode = 0; 

    if (branchs->counter > 0) {
        code = searchActivityBranch(*branchs, getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG));
                
        if (code != -1) {

            if ( hasCompany(branchs->branchs[code], *companies) == -1) {
                
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

void deleteActivityBranch(ActivityBranch *branch) {
    branch->code = 0;
    strcpy(branch->name, "");
    branch->state = 0;
}

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

    fwrite(&branchs->counter, sizeof (int), 1, fp);

    for (i = 0; i < branchs->counter; i++) {
        fwrite(&branchs->branchs[i], sizeof (ActivityBranch), 1, fp);
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
        
        fread(&branchs->counter, sizeof (int), 1, fp);

        if (branchs->counter > 0) {
            branchs->size = branchs->counter;
            branchs->branchs = (ActivityBranch*) malloc(branchs->counter * sizeof (ActivityBranch));
            for (i = 0; i < branchs->counter; i++) {
                fread(&branchs->branchs[i], sizeof (ActivityBranch), 1, fp);
            }
            sucesso = 1;
        }

        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(file, "wb");
        if (fp != NULL) {

            branchs->branchs = (ActivityBranch*) malloc(MAX_ACTIVITY_BRANCHS * sizeof (ActivityBranch));
            branchs->counter = 0;
            branchs->size = MAX_ACTIVITY_BRANCHS;

            fclose(fp);
        }
    }
}

int isActive(ActivityBranch branch){
    
    if (branch.state == 1) {
        return 0;
    }
    
    return -1;
}
