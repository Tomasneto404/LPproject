#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "admin.h"
#include "user.h"

int rating(Companies *companies) {
    int rate;
    
//    //FILE* fp = fopen(COMPANY_FILE, "ab");
//
//    if (fp == NULL) {
//        exit(EXIT_FAILURE);
//        return 0;
//    }
//    
//    rate = getInt(MIN_RATING, MAX_RATING, MSG_RATING);
//    
//    
//    
//    //if (companies->companies[companies->counter].rate >= MIN_RATING && companies->companies[companies->counter].rate <= MAX_RATING) {
//        
//    //}
//    
//    fclose(fp);
//    return -1;
}

int searchCompanyByName(Companies companies, char *name) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if ( strcmp(companies.companies[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void listCompaniesByName(Companies companies){
    
    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);
    
    companyCode = searchCompanyByName(companies, name);
    
    if (companyCode != -1) {
        
        printCompany(companies.companies[companyCode]);
        
    } else {
        
        puts("ERROR: Company not found.");
        
    }
    
}


int searchCompanyByCategory(Companies companies, int category) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if ( companies.companies[i].category == category) {
            return i;
        }
    }
    return -1;
}

void listCompaniesByCategory(Companies companies){
    
    int i = 0, category = 0, counter = 0;
    
    category = getInt(0, 2, MSG_CATEGORY);
    
    for (i = 0; i < companies.counter; i++) {
        if (companies.companies[i].category == category) {
            printCompany(companies.companies[i]);
            counter++;
        }
    }
    
    if (!counter) {
        puts("No companies found.");
    }
    
}


void listCompaniesByLocality(Companies companies){
    
    int i, counter = 0;
    char locality[MAX_COMPANY_LOCALITY_SIZE];
    readString(locality, MAX_COMPANY_LOCALITY_SIZE, MSG_LOCALITY);
    
    for (i = 0; i < companies.counter; i++) {
        if ( strcmp(companies.companies[i].locality, locality) == 0) {
            printCompany(companies.companies[i]);
            counter++;
        }
    }
    
    if (!counter) {
        puts("No companies found.");
    }
    
}