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

int createActivityBranch(ActivityBranchs *branchs) {

    FILE *file = fopen(ACTIVITY_BRANCH_FILE, "ab");

    if (file == NULL) {
        
        printf("ERROR: Unable to open file.\n");
        
    } else {

        readString(branchs->branchs[branchs->contador].name, 50, "Name: ");
        branchs->branchs[branchs->contador].state = getInt(0, 1, "State (0 - Inactive | 1 - Active): ");
        branchs->branchs[branchs->contador].code = 1; //autoIncrementCode();

        fwrite(&branchs->branchs[branchs->contador], sizeof (ActivityBranch), 1, file);

        fclose(file);
        return branchs->contador++;
        
    }
    fclose(file);
    return -1;

}


void listActivityBranch() {
    ActivityBranch branch;

    FILE *file;
    file = fopen(ACTIVITY_BRANCH_FILE, "r");

    puts("\n------- Activity Branchs -------");
    while (fread(&branch, sizeof (ActivityBranch), 1, file)) {

        printf("%-5d %-15s", branch.code, branch.name);

        if (branch.state) {
            puts("Active");
        } else {
            puts("Inactive");
        }
    }
    puts("--------------------------------");

    fclose(file);
}

void updateActivityBranch() {


}

void deleteActivityBranch() {
    
}