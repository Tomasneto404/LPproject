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

int verifyNif(Companies companies, int nif) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if (companies.companies[i].nif == nif) {
            return i;
        }
    }
    return -1;
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

    }

    return 1;
}

int createCompany(Companies *companies) {
    int nif;

    nif = getInt(MIN_NIF, MAX_NIF, MSG_NIF);

    if (verifyNif(*companies, nif) == -1) {
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

void createCompanies(Companies *companies) {
    if (companies->counter < MAX_COMPANIES) {
        if (createCompany(companies) == -1) {
            puts("COMPANIE DOESN'T EXIST\n");
        }
    } else {
        puts("FULL LIST\n");
    }
}

void printCompany(Company company) {
    printf("\n%3d %-30s %-20s %3d %-30s %-30s %3d", company.nif, company.name, company.category, company.branch, company.street, company.locality, company.postalCode);
}

void listCompanies(Companies companies) {
    int i;

    if (companies.counter > 0) {
        for (i = 0; i < companies.counter; i++) {
            printCompany(companies.companies[i]);
        }
    } else {
        puts("EMPTY LIST");
    }
}

void updateCompany(Company *company) {

    readString(company->name, 50, MSG_NAME);
    company->category = getInt(0, 3, MSG_CATEGORY);
    company->branch = getInt(0, 50, MSG_BRANCH); //alterar
    readString(company->street, 50, MSG_STREET);
    readString(company->locality, 50, MSG_LOCALITY);
    company->postalCode = getInt(MAX_POSTALCODE, MIN_POSTALCODE, MSG_POSTALCODE);
    verify_PostalCode(&company.postalCode);
}

void updateCompanies(Companies *companies) {

    int i, nif = verifyNif(*nif, getInt(MIN_NIF, MAX_NIF, MSG_NIF));

    if (nif != -1) {
        updateCompany(&companies->companies[nif]);
    } else {

        puts("ERROR");
    }
}

//alterar função quando houver comentarios de utilizadores

void deleteCompanyData(Company *company) {

    company->nif = 0;
    strcpy(company->name, "");
    company->category = 0;
    company ->branch = 0;
    strcpy(company->street, "");
    strcpy(company->locality, "");
    company->postalCode = 0;
}

//alterar função quando criarmos função para os comenatarios

void deleteCompanies(Companies *companies) {

    int i, nif = verifyNif(*nif, getInt(MIN_NIF, MAX_NIF, MSG_NIF));

    if (nif != -1) {
        for(i=nif;i<companies->counter-1;i++){
            companies->companies[i]=companies->companies[i+1];
        }
        
        deleteCompanyData(&companies->companies[i]);
        
        companies->counter--;
    }else{
        puts("ERROR");
    }
}

/**********************************ACTIVITY BRANCH************************************/


char convertLowercase(ActivityBranchs *name) {
    int counter, i;

    while ((name->branchs[name->contador].name)[counter] != '\0') {
        counter++;
    }

    if ((name->branchs[name->contador].name)[counter - 1] == '\n') {
        (name->branchs[name->contador].name)[--counter] = '\0';
    }

    for (i = 0; i < counter; i++) {
        if (name->branchs[name->contador].name[i] >= 65 && name->branchs[name->contador].name[i] <= 90) {

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

