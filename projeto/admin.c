/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "admin.h"

/**********************************COMPANY********************************************/
int verifyNif(int *nif) {
    int readNif;

    while (fscanf(fp, "%d", &readNif) == 1) {
        if (nif == &readNif) {
            printf("This NIF already exist!\n");
            fclose(fp);
            return 1;
        }
    }
    return 0;
}

int verify_PostalCode(int *postalCode) {
    int i;

    for (i = 0; i < 8; i++) {
        if (i == 4) {
            if (postalCode[i] != '-') {
                for (i = 7; i >= 4; i--) {
                    postalCode[i] = postalCode[i - 1];
                }
                postalCode[i] = '-';
            }
        }
        fprintf(fp, "%d", postalCode[i]);
    }

    fclose(fp);
    return 1;
}

int createCompany(Companies *companies) {
    int nif;

    nif = getInt(MIN_NIF, MAX_NIF, MSG_NIF);

    if (verifyNif(&nif, COMPANY_FILE) == 0) {
        companies->companies[companies->counter].nif = nif;

        readString(companies->companies[companies->counter].name, 50, MSG_NAME);

        companies->companies[companies->counter].category = getInt(0, 3, MSG_CATEGORY);

        listActivityBranch();
        companies->companies[companies->counter].branch = getInt(0, 3, MSG_BRANCH); //adicionar o contador e trocar o 3

        readString(companies->companies[companies->counter].street, 50, MSG_STREET);
        readString(companies->companies[companies->counter].locality, 50, MSG_LOCALITY);

        companies->companies[companies->counter].postalCode = getInt(MIN_POSTALCODE, MAX_POSTALCODE, MSG_POSTALCODE);
        verify_PostalCode(&(companies->companies[companies->counter].postalCode));


        return companies->counter++;
    }
    return -1;
}

/**********************************ACTIVITY BRANCH************************************/


char convertLowercase(ActivityBranchs *name){
    int counter,i;
    
    while((name->branchs[name->contador].name)[counter]!='\0'){
        counter++;
    }
    
    if((name->branchs[name->contador].name)[counter-1]=='\n'){
        (name->branchs[name->contador].name)[--counter]='\0';
    }
    
    for(i=0;i<counter;i++){
        if(name->branchs[name->contador].name[i]>=65&& name->branchs[name->contador].name[i]<=90){
            name->branchs[name->contador].name[i] += 32;
        }
    }
    
    return 0;
}

int createActivityBranch(ActivityBranchs *branchs) {

    ActivityBranchs name;
    
    FILE *file = fopen(ACTIVITY_BRANCH_FILE, "ab");

    if (file == NULL) {

        printf("ERROR: Unable to open file.\n");

    } else {

        readString(branchs->branchs[branchs->contador].name, 50, "Name: ");
        
        branchs->branchs[branchs->contador].state = getInt(0, 1, "State (0 - Inactive | 1 - Active): ");
        branchs->branchs[branchs->contador].code = //autoIncrementID();

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
    //Teste

}

void deleteActivityBranch() {

}

