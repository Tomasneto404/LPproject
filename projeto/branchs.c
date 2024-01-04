#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "branchs.h"

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

int createActivityBranch(ActivityBranchs *branchs) {

    int code = getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG);

    if (searchActivityBranch(*branchs, code) == -1) {
        branchs->branchs[branchs->counter].code = code;

        readString(branchs->branchs[branchs->counter].name, MAX_AB_NAME_SIZE, NAME_MSG);

        branchs->branchs[branchs->counter].state = getInt(MIN_STATE_VALUE, MAX_STATE_VALUE, STATE_MSG);

        return branchs->counter++;
    }
    return -1;
}

void createActivityBranchs(ActivityBranchs *branchs) {

    if (branchs->counter == branchs->size) {
        expandBranchsCapacity(branchs);
    }

    if (branchs->counter < branchs->size) {
        if (createActivityBranch(branchs) == -1) {
            puts("Branch DOESN'T EXIST\n");
        }
    } else {
        puts("ERROR: No Activity Branchs created.");
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

void deleteActivityBranchs(ActivityBranchs *branchs) {
    int i, code = searchActivityBranch(*branchs, getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG));

    if (code != -1) {

        for (i = code; i < branchs->counter - 1; i++) {
            branchs->branchs[i] = branchs->branchs[i + 1];
        }

        deleteActivityBranch(&branchs->branchs[i]);

        branchs->counter--;

    } else {
        puts(AB_DOES_NOT_EXIST);
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

