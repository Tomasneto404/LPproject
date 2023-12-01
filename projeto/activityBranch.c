/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "activityBranch.h"

#define ACTIVITY_BRANCH_FILE  "activityBranchs.txt"

int autoIncrementCode() {
    //Para a Tania
    
}

void registerActivityBranch(FILE *file, struct ActivityBranch *branch) {
    
    if (file == NULL) { //este codigo não funciona, simplesmente cria um ficheiro novo
        printf("ERROR: File not found.\n");
    } else {
        fprintf(file, "%d, %s, %d;\n", branch->code, branch->name, branch->state);
        fclose(file);
    }
    
}

void createActivityBranch() {
    
    struct ActivityBranch branch;
    FILE *file = fopen(ACTIVITY_BRANCH_FILE, "a");
    
    readString(branch.name, 50, "Name: ");
    branch.state = getInt(0, 1, "State (0 - Inactive | 1 - Active): ");
    branch.code = 1; //adicionar função de auto_increment   
    
    registerActivityBranch(file, &branch);
    
}

void updateActivityBranch() {
    
}

void readActivityBranch() {
    
}