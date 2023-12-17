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


int addComment(Comments *comments){
    Companies companies;
    char companyName[MAX_COMPANY_NAME_SIZE];
   
    readString(companyName,MAX_COMPANY_NAME_SIZE, MSG_SEARCH_COMPANY);
    
    if(searchCompanyByName(companies, companyName)){
        
       readString(comments->comments[comments->counter].name,MAX_NAME,MSG_NAME_USER);
       readString(comments->comments[comments->counter].email,MAX_EMAIL,MSG_EMAIL);
       readString(comments->comments[comments->counter].comment,MAX_CARACTER,MSG_COMMENT);
       
       return comments->counter++;
    }
    return -1;
}

void expandCommentsCapacity(Comments *comments) {
    int tam = (comments->size) == 0 ? MAX_COMMENTS_SIZE: comments->size * 2;
    Comment *temp = (Comment*) realloc(comments->comments, sizeof (Comment) * (tam));
    if (temp != NULL) {
        comments->size = tam;
        comments->comments = temp;
    }
}

void addComments (Comments *comments){
    
    if(comments->counter==comments->size){
       expandCommentsCapacity(comments);
    }
    
    if(comments->counter < comments->size){
        if(addComment(comments)==-1){
            puts("The company doesn't exist\n");
        }
    }else{
        puts("Ins't possible to insert the new comment");
    }
}