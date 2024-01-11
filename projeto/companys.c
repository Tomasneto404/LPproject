#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "branchs.h"
#include "companys.h"
#include "comments.h"

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

void expandCompaniesCapacity(Companies *companies) {
    int tam = (companies->size) == 0 ? MAX_COMPANIES : companies->size * 2;
    Company *tmp = (Company*) realloc(companies->companies, sizeof (Company)*(tam));

    if (tmp != NULL) {
        companies->size = tam;
        companies->companies = tmp;
    }
}

int verifyName(Companies companies, char *name) {

    int i;

    for (i = 0; i < companies.counter; i++) {

        if (strcmp(companies.companies[i].name, name) == 0) {
            return 0;
        }

    }
    return -1;
}


int createCompany(Companies *companies, ActivityBranchs *branchs) {
    int nif;
    char name[MAX_NAME];

    nif = getInt(MIN_NIF, MAX_NIF, MSG_NIF);

    if (verifyNif(*companies, nif) == -1) {

        readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

        if (verifyName(*companies, name) == -1) {
            companies->companies[companies->counter].nif = nif;

            strcpy(companies->companies[companies->counter].name, name);

            companies->companies[companies->counter].category = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_CATEGORY);

            listActivityBranchs(*branchs);
            companies->companies[companies->counter].branch = getBranch(branchs);

            readString(companies->companies[companies->counter].street, MAX_STREET, MSG_STREET);
            readString(companies->companies[companies->counter].locality, MAX_LOCALITY, MSG_LOCALITY);

            companies->companies[companies->counter].postalCode = getInt(MIN_POSTALCODE, MAX_POSTALCODE, MSG_POSTALCODE);
            verify_PostalCode(&(companies->companies[companies->counter].postalCode));

            companies->companies[companies->counter].state = getInt(MIN_STATE, MAX_STATE, MSG_STATE);
            companies->companies[companies->counter].views = 0;
            companies->companies[companies->counter].rate = 0;

            companies->counter++;

            return 0;

        } else {
            return 1;
        }

    } else {
        return 2;
    }


    return -1;
}

void createCompanies(Companies *companies, ActivityBranchs *branchs) {

    if (branchs->counter > 0) {
        if (companies->counter == companies->size) {
            expandCompaniesCapacity(companies);
        }

        if (companies->counter < companies->size) {

            switch (createCompany(companies, branchs)) {

                case -1:
                    puts(ERROR_IMPOSSIBLE_COMPANY);
                    break;
                case 1:
                    puts(ERROR_NAME_COMPANY);
                    break;

                case 2:
                    puts(ERROR_NIF_COMPANY);
                    break;

                default:
                    puts(SUCCESS_COMPANY_CREATE);
                    break;
            }


        } else {
            puts(FULL_LIST_COMPANY);
        }
    } else {
        puts(ERROR_NO_BRANCHS);
    }

}

void printCompany(Company company, ActivityBranchs branchs) {
    int i;

    printf("\n%-10d %-20s ", company.nif, company.name);

    switch (company.category) {
        case MICRO:
            printf("%-15s", "MICRO");
            break;
        case SME:
            printf("%-15s", "SME");
            break;
        case BIG_COMPANY:
            printf("%-15s", "BIG COMPANY");
            break;
    }

    for (i = 0; i < branchs.counter; i++) {

        if (company.branch == branchs.branchs[i].code) {
            printf("%-15s ", branchs.branchs[i].name);
        }

    }

    printf("%-20s %-20s %-15d %-15.2f %-15d", company.street, company.locality, company.postalCode, company.rate, company.views);

    if (company.state == 0) {
        printf("%-10s", "Inactive\n");
    } else {
        printf("%-10s", "Active\n");
    }

}

void listCompanies(Companies companies, ActivityBranchs branchs) {
    int i;

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
    if (companies.counter > 0) {
        for (i = 0; i < companies.counter; i++) {
            printCompany(companies.companies[i], branchs);
        }
    } else {
        puts(EMPTY_LIST);
    }
}

void updateCompany(Company *company) {
    ActivityBranchs* branchs;

    readString(company->name, MAX_COMPANY_NAME_SIZE, MSG_NAME);
    company->category = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_CATEGORY);

    listActivityBranchs(*branchs);
    company->branch = getInt(MIN_AB_CODE_VALUE, MAX_AB_CODE_VALUE, CODE_MSG);

    readString(company->street, MAX_STREET, MSG_STREET);
    readString(company->locality, MAX_LOCALITY, MSG_LOCALITY);
    company->postalCode = getInt(MIN_POSTALCODE, MAX_POSTALCODE, MSG_POSTALCODE);
    verify_PostalCode(&company->postalCode);
    company->state = getInt(MIN_STATE, MAX_STATE, MSG_STATE);
}

void updateCompanies(Companies *companies) {
    char name[MAX_NAME];
    int code;
    readString(name, MAX_NAME, MSG_NAME_COMP);

    code = searchCompanyByName(*companies, name);

    if (code != -1) {
        updateCompany(&companies->companies[code]);
    } else {

        puts(ERROR);
    }
}

void deleteCompanyData(Company *company) {

    company->nif = 0;
    strcpy(company->name, "");
    company->category = 0;
    company ->branch = 0;
    strcpy(company->street, "");
    strcpy(company->locality, "");
    company->postalCode = 0;
}

void deleteCompanies(Companies *companies, Comments *comments) {

    char name[MAX_NAME];
    int code, i;

    readString(name, MAX_NAME, MSG_NAME_COMP);

    code = searchCompanyByName(*companies, name);

    if (!hasComments(companies->companies[code], comments)) {
        if (code != -1) {
            for (i = code; i < companies->counter - 1; i++) {
                companies->companies[i] = companies->companies[i + 1];
            }

            deleteCompanyData(&companies->companies[i]);

            companies->counter--;
        } else {
            puts(ERROR_COMPANY_NOT_FOUND);
        }
    } else {
        companies->companies[code].state = 0;
        puts(ERROR_DELETE_COMPANY);
    }
}

/**
 * @brief Comparison function for sorting companies by number of views.
 *
 * This function is used as a comparison function for sorting an array of 'Company' structures
 * in descending order based on the number of views. It is intended to be used with the
 * qsort function or similar sorting algorithms.
 *
 * @param a Pointer to the first company structure to compare.
 * @param b Pointer to the second company structure to compare.
 * @return An integer value representing the comparison result:
 *         - Negative value if 'b' has more views than 'a'.
 *         - Zero if 'a' and 'b' have the same number of views.
 *         - Positive value if 'a' has more views than 'b'.
 */

int compare_company(const void *a, const void *b) {
    const Company *companyA = (const Company *) a;
    const Company *companyB = (const Company *) b;
    return companyB->views - companyA->views;
}

void top5lookedCompanies(Companies *companies) {
    if (companies->counter > 0) {
        // Sorting the list of companies in descending order based on views using quicksort
        qsort(companies->companies, companies->counter, sizeof (Company), compare_company);

        printf(VIEW_COMPANY);

        int numPrinted = 0;
        for (int i = 0; i < companies->counter && numPrinted < TOP_5; i++) {
            printf("%s\n", companies->companies[i].name);
            numPrinted++;
        }
    } else {
        puts(ERROR_EMPTY_LIST);
    }
}

int compare_rate(const void *a, const void *b) {
    const Company *companyA = (const Company *) a;
    const Company *companyB = (const Company *) b;

    if (companyA->rate < companyB->rate) return 1;
    if (companyA->rate > companyB->rate) return -1;
    return 0;
}

void top5bestCompanies(Companies *companies) {
    if (companies->counter > 0) {
        // Sorting the list of companies in descending order based on rate using quicksort
        qsort(companies->companies, companies->counter, sizeof (Company), compare_rate);

        printf(TOP_FIVE);

        int numPrinted = 0;
        for (int i = 0; i < companies->counter && numPrinted < TOP_5; i++) {
            printf("%s\n", companies->companies[i].name);
            numPrinted++;
        }
    } else {
        puts(ERROR_EMPTY_LIST);
    }
}

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
    } else {
        puts(ERROR_COMPANY_NOT_FOUND);
    }
}

void listCompaniesByName(Companies *companies, ActivityBranchs branchs) {

    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];



    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(*companies, name);

    if (companyCode != -1) {
        printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
        companies->companies[companyCode].views++;
        printCompany(companies->companies[companyCode], branchs);

    } else {

        puts(ERROR_COMPANY_NOT_FOUND);

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

void listCompaniesByCategory(Companies *companies, ActivityBranchs branchs) {

    int i = 0, category = 0, counter = 0;


    category = getInt(0, 2, MSG_CATEGORY);

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
    for (i = 0; i < companies->counter; i++) {
        if (companies->companies[i].category == category) {
            companies->companies[i].views++;
            printCompany(companies->companies[i], branchs);
            counter++;
        }
    }

    if (!counter) {
        puts(ERROR_COMPANY_NOT_FOUND);
    }

}

void listCompaniesByLocality(Companies *companies, ActivityBranchs branchs) {

    int i, counter = 0;
    char locality[MAX_COMPANY_LOCALITY_SIZE];
    readString(locality, MAX_COMPANY_LOCALITY_SIZE, MSG_LOCALITY);

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
    for (i = 0; i < companies->counter; i++) {
        if (strcmp(companies->companies[i].locality, locality) == 0) {
            companies->companies[i].views++;
            printCompany(companies->companies[i], branchs);
            counter++;
        }
    }

    if (!counter) {
        puts(ERROR_COMPANY_NOT_FOUND);
    }


}

int selectCompany(Companies companies) {

    int companyCode = 0;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(companies, name);

    if (companyCode != -1) {
        return companyCode;
    }
    return -1;
}

void saveCompanies(Companies *companies, char *file) {
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&(companies->counter), sizeof (int), 1, fp);

    for (i = 0; i < companies->counter; i++) {
        fwrite(&(companies->companies[i]), sizeof (Company), 1, fp);
    }

    fclose(fp);
}

void freeCompanies(Companies *companies) {
    if (companies->companies) {
        free(companies->companies);
        companies->companies = NULL;
    }

    companies = NULL;
}

void loadCompanies(Companies *companies, char *file) {
    int i, success = 0;

    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        companies->counter = 0;

        fread(&(companies->counter), sizeof (int), 1, fp);

        if (companies->counter > 0) {
            companies->size = companies->counter;
            companies->companies = (Company*) malloc(companies->counter * sizeof (Company));
            for (i = 0; i < companies->counter; i++) {
                fread(&(companies->companies[i]), sizeof (Company), 1, fp);
            }
            success = 1;
        }

        fclose(fp);
    }

    if (!success) {
        companies->companies = (Company*) malloc(MAX_COMPANIES * sizeof (Company));
        companies->counter = 0;
        companies->size = MAX_COMPANIES;

    }

}

int hasComments(Company company, Comments comments) {

    int i;

    for (i = 0; i < comments.counter; i++) {
        if (comments.comments[i].company_nif == company.nif) {
            return 1;
        }
    }
    return 0;
}