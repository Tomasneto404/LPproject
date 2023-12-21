#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "admin.h"
#include "user.h"

int searchCompanyByName(Companies companies, char *name) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if (strcmp(companies.companies[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

float company_average(Company *company, float rate) {
    float media;

    media = (company->rate + rate) / 2;

    return media;
}

void rate_company(Companies *companies) {
    char name[MAX_NAME];
    float rate;
    int code;

    readString(name, MAX_NAME, MSG_NAME_COMP);

    code = searchCompanyByName(*companies, name);
    
    if (code != -1) {

        rate = getFloat(MIN_RATING, MAX_RATING, MSG_RATING);
        if (companies->companies[code].rate == 0) {
            companies->companies[code].rate = rate;
        } else {
            companies->companies[code].rate = company_average(&companies->companies[code], rate);
        }
        printf("%.2f", companies->companies[code].rate);
    } else {
        puts(ERROR_COMPANY_NOT_FOUND);
    }
}

void listCompaniesByName(Companies companies) {

    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(companies, name);

    if (companyCode != -1) {
        printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "STATE");
        printCompany(companies.companies[companyCode]);

    } else {

        puts("ERROR: Company not found.");

    }

}

int searchCompanyByCategory(Companies companies, int category) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if (companies.companies[i].category == category) {
            return i;
        }
    }
    return -1;
}

void listCompaniesByCategory(Companies companies) {

    int i = 0, category = 0, counter = 0;

    category = getInt(0, 2, MSG_CATEGORY);

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "STATE");
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

void listCompaniesByLocality(Companies companies) {

    int i, counter = 0;
    char locality[MAX_COMPANY_LOCALITY_SIZE];
    readString(locality, MAX_COMPANY_LOCALITY_SIZE, MSG_LOCALITY);

    for (i = 0; i < companies.counter; i++) {
        if (strcmp(companies.companies[i].locality, locality) == 0) {
            printCompany(companies.companies[i]);
            counter++;
        }
    }

    if (!counter) {
        puts("No companies found.");
    }

}

/**
 * @brief 
 * @param email
 * @return 
 */
int verifyEmail(char *email) {
    int i, tam, x;
    char *atSign = NULL, *point = NULL;

    tam = strlen(email);

    for (i = 0; i < tam; i++) {
        if (email[i] == '@') {
            atSign = email + i;
            x = i;
            break;
        }
    }

    if (atSign == NULL) {
        return 0;
    }

    for (i = x; i < tam; i++) {
        if (email[i] == '.') {
            point = email + i;
            break;
        }
    }

    if (point == NULL) {
        return 0;
    }
    if (point == atSign + 1) {
        return 0;
    }

    if (point + 1 == email + tam) {
        return 0;
    }

    return 1;
}

void addComment(Company *company) {
    
    //char email[MAX_EMAIL], name[MAX_NAME], comment[MAX_COMMENT_CARACTER];
    
//    if (company->last_comment_position < MAX_COMMENTS_SIZE) {
//        readString(company->comments[company->last_comment_position].email, MAX_EMAIL, MSG_EMAIL);
//        readString(company->comments[company->last_comment_position].name, MAX_NAME, MSG_NAME);
//        readString(company->comments[company->last_comment_position].comment, MAX_COMMENT_CARACTER, MSG_COMMENT);
//        
//        company->last_comment_position++;
//    } else {
//        puts("ERROR: Maximum of comments reached.");
//    }
    
}

void expandCommentsCapacity(Comments *comments) {
    int tam = (comments->size) == 0 ? MAX_COMMENTS_SIZE : comments->size * 2;
    Comment *temp = (Comment*) realloc(comments->comments, sizeof (Comment) * (tam));
    if (temp != NULL) {
        comments->size = tam;
        comments->comments = temp;
    }
}

void addComments(Companies *companies) {
    
    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(*companies, name);

    if (companyCode != -1) {
        addComment(&companies->companies[companyCode]);
    } else {
        puts("ERROR: Company not found.");
    }
}

int selectCompany(Companies companies) {
    
    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(companies, name);

    if (companyCode != -1) {

        return companyCode;

    } else {

        puts("ERROR: Company not found.");

    }
    return -1;
}