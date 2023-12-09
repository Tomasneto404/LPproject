/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        //listActivityBranch();
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
    printf("\n%5d %10s ", company.nif, company.name);

    switch (company.category) {
        case MICRO:
            printf("MICRO");
            break;
        case SME:
            printf("SME");
            break;
        case BIG_COMPANY:
            printf("BIG COMPANY");
            break;
    }
    printf("%5d %10s %10s %5d", company.branch, company.street, company.locality, company.postalCode);

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
    verify_PostalCode(&company->postalCode);
}

void updateCompanies(Companies *companies) {

    int i, nif = verifyNif(*companies, getInt(MIN_NIF, MAX_NIF, MSG_NIF));

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

    int i, nif = verifyNif(*companies, getInt(MIN_NIF, MAX_NIF, MSG_NIF));

    if (nif != -1) {
        for (i = nif; i < companies->counter - 1; i++) {
            companies->companies[i] = companies->companies[i + 1];
        }

        deleteCompanyData(&companies->companies[i]);

        companies->counter--;
    } else {
        puts("ERROR");
    }
}

/**********************************ACTIVITY BRANCH************************************/


char convertLowercase(ActivityBranchs *name) {
    int counter, i;

    while ((name->branchs[name->counter].name)[counter] != '\0') {
        counter++;
    }

    if ((name->branchs[name->counter].name)[counter - 1] == '\n') {
        (name->branchs[name->counter].name)[--counter] = '\0';
    }

    for (i = 0; i < counter; i++) {
        if (name->branchs[name->counter].name[i] >= 65 && name->branchs[name->counter].name[i] <= 90) {

            name->branchs[name->counter].name[i] += 32;
        }
    }

    return 0;
}

void createActivityBranchs(ActivityBranchs *branchs){
    
    if (branchs->counter < MAX_ACTIVITY_BRANCHS) {
        
        if (createActivityBranch(branchs) == -1) {
            puts("ERROR: This activity branch already exists.");
        } 
        
    } else {
        puts("ERROR: List full.");
    }
    
}

int createActivityBranch(ActivityBranchs *branchs){
    
    int code = getInt(0, 100, "Code [1-1000] > ");
    
    if (searchActivityBranch(*branchs, code) == -1) {
        branchs->branchs[branchs->counter].code = code;
        
        readString(branchs->branchs[branchs->counter].name, 100, "Name > ");
        
        branchs->branchs[branchs->counter].state = getInt(0, 1, "State [1 - Active | 0 - Inactive] > ");
        
        return branchs->counter++;
    }
    return -1;
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

void listActivityBranchs(ActivityBranchs branchs){
    if (branchs.counter > 0) {
        int i;
        printf("%-5s %-15s %-10s\n", "CODE", "NAME", "STATE");
        for (i = 0; i < branchs.counter; i++) {
            printActivityBranch(branchs.branchs[i]);
        }
    } else {
        puts("ERROR: List empty.");
    }
}

void printActivityBranch(ActivityBranch branch){
    
    printf("%-5d %-15s", branch.code, branch.name);
    
    if (branch.state == 1) {
        printf("%-10s\n", "Active");
    } else {
        printf("%-10s\n", "Inactive");
    }
}

void updateActivityBranchs(ActivityBranchs *branchs){
    
    int code = searchActivityBranch(*branchs, getInt(0, 100, "Code [1-1000] > "));
    
    if (code != -1) {
        updateActivityBranch(&branchs->branchs[code]);
    } else {
        puts("ERROR: This Activity Branch does not exist.");
    }
    
}

void updateActivityBranch(ActivityBranch *branch){
    
    branch->state = getInt(0, 1, "State [1 - Active | 0 - Inactive] > ");
    
}

void deleteActivityBranchs(ActivityBranchs *branchs){
    int i, code = searchActivityBranch(*branchs, getInt(0, 100, "Code [1-1000] > "));
    
    if (code != -1) {
        
        for (i = code; i < branchs->counter - 1; i++) {
            branchs->branchs[i] = branchs->branchs[i + 1];
        }
        
        deleteActivityBranch(&branchs->branchs[i]);
        
        branchs->counter--;
        
    } else {
        puts("ERROR: This Activity Branch does not exist.");
    }
    
}

void deleteActivityBranch(ActivityBranch *branch){
    branch->code = 0;
    strcpy(branch->name, "");
    branch->state = 0;
}