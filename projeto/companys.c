/**
 * @file companys.c
 * @author Tania, Gonçalo, Tomas
 * @date 11-01-2024
 * @version 1
 *
 * @copyright Copyright (C) Tania, Gonçalo, Tomas 2023. All Rights MIT Licensed.
 *
 * @brief Contains functions related to companies.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "branchs.h"
#include "companys.h"
#include "comments.h"

/**
 * @brief This function is used to analyze whether there is already a company with the same NIF
 * @param companies receives an Companies's type called companies
 * @param nif receives an integer called nif
 * @return i if it already exists and -1 if it does not exist 
 */
int verifyNif(Companies companies, int nif) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if (companies.companies[i].nif == nif) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief checks if there is a '-' character between the code and the postal code, if not, add it
 * @param postalCode receives a pointer to characters called postal code that is found inside the struct
 * @return 1 if was very successfuly
 */
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

/**
 * @brief This function aims to expand the allocated memory, using the realloc function
 * @param companies receives a pointer named companies of type Companies struct
 */
void expandCompaniesCapacity(Companies *companies) {
    int tam = (companies->size) == 0 ? MAX_COMPANIES : companies->size * 2;
    Company *tmp = (Company*) realloc(companies->companies, sizeof (Company)*(tam));

    if (tmp != NULL) {
        companies->size = tam;
        companies->companies = tmp;
    }
}

/**
 * @brief This function aims to check whether the name entered already exists in a company or not.
 * @param companies receives a variable, named companies, of type Companies struct
 * @param name receives a pointer, called name, of char type
 * @return 0 if the name's exist, return -1 if doesn't
 */
int verifyName(Companies companies, char *name) {
    int i;

    for (i = 0; i < companies.counter; i++) {

        if (strcmp(companies.companies[i].name, name) == 0) {
            return 0;
        }

    }
    return -1;
}

/**
 * @brief serves to obtain the necessary data for the creation of a company
 * @param companies receives as a parameter a pointer of type Companies
 * @param branchs receives as parameter a pointer of type ActivityBranchs
 * @return 0 if successful,
 *  returns -1 if not,
 *  returns 1 if the name is already being used by other company,
 *  returns 2 if the nif is already being used by other company.
 */
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

/**
 * @brief This function is used to create several companies and check if the list
 *  is full or if the company exists
 * @param companies receives as a parameter a pointer of type Companies
 * @param branchs receives as a parameter a pointer of type ActivityBranchs
 */
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

/**
 * @brief This function prints in the screen the values of a specified company.
 * @param company The specified company to get it's values printed.
 * @param branchs The branchs variable to print it's name if match with the company.
 */
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

/**
 * @brief aims to print all companies, if they exist, if it does not display an error message
 * @param companies receives as parameter a variable calls company of type Company
 * @param branchs receives as parameter a variable calls company of type ActivityBranchs
 */
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

/**
 * @brief aims to update all of a company's data, except the NIF
 * @param company receives as a parameter a pointer of type Companies
 * @param branchs receives as a parameter a pointer of type ActivityBranchs
 */
void updateCompany(Company *company, ActivityBranchs *branchs) {

    readString(company->name, MAX_COMPANY_NAME_SIZE, MSG_NAME);
    company->category = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_CATEGORY);

    listActivityBranchs(*branchs);
    company->branch = getBranch(branchs);

    readString(company->street, MAX_STREET, MSG_STREET);
    readString(company->locality, MAX_LOCALITY, MSG_LOCALITY);
    company->postalCode = getInt(MIN_POSTALCODE, MAX_POSTALCODE, MSG_POSTALCODE);
    verify_PostalCode(&company->postalCode);
    company->state = getInt(MIN_STATE, MAX_STATE, MSG_STATE);
}

/**
 * @brief aims to update the NIF, if it is correctly inserted it allows you to 
 * update the remaining information
 * @param companies receives as a parameter a pointer of type Companies
 * @param branchs receives as a parameter a pointer of type ActivityBranchs
 */
void updateCompanies(Companies *companies, ActivityBranchs *branchs) {
    char name[MAX_NAME];
    int code;
    readString(name, MAX_NAME, MSG_NAME_COMP);

    code = searchCompanyByName(*companies, name);

    if (code != -1) {
        updateCompany(&companies->companies[code], branchs);
    } else {

        puts(ERROR);
    }
}

/**
 * @brief delete all data relating to a company, if it does not have comments,
 * if it does, make it inactive
 * @param company receives as a parameter a pointer of type Companies
 */
void deleteCompanyData(Company *company) {

    company->nif = 0;
    strcpy(company->name, "");
    company->category = 0;
    company ->branch = 0;
    strcpy(company->street, "");
    strcpy(company->locality, "");
    company->postalCode = 0;
}

/**
 * @brief Deletes data from a specific company
 * @param companies
 * @param comments
 */
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
 * @param firstCompany Pointer to the first company structure to compare.
 * @param secondCompany Pointer to the second company structure to compare.
 * @return An integer value representing the comparison result:
 *         - Negative value if 'b' has more views than 'a'.
 *         - Zero if 'a' and 'b' have the same number of views.
 *         - Positive value if 'a' has more views than 'b'.
 */
int compare_company(const void *firstCompany, const void *secondCompany) {
    const Company *companyA = (const Company *) firstCompany;
    const Company *companyB = (const Company *) secondCompany;
    return companyB->views - companyA->views;
}

/**
 * @brief This function sorts the views of companies using the quick sort algorithm.
 * @param companies Pointer to the Companies structure containing company data.
 */
void sortViews(Companies *companies) {
    qsort(companies->companies, companies->counter, sizeof (Company), compare_company);
}

/**
 * @brief This function sorts the list of companies in descending order based on views using quick sort.
 * It then prints the names of the top 5 most looked at companies if is state = 1 meaning that is active.
 * @param companies Pointer to the Companies structure containing the list of companies.
 */
void top5lookedCompanies(Companies *companies) {
    int i, numPrinted = 0, stateCompany = 0;

    if (companies->counter > 0) {
        sortViews(companies);

        printf("The most looked companies are:\n");

        for (i = 0; i < companies->counter && numPrinted < TOP_5; i++) {
            stateCompany = companies->companies[i].state;
            if (stateCompany == 1) {
                printf(" > %s - %d views.\n", companies->companies[i].name, companies->companies[i].views);
            }
            numPrinted++;
        }
    } else {
        puts(ERROR_COMPANY_NOT_FOUND);
    }
}

/**
 * @brief This function is a comparison function intended for use with qsort().
 * It compares two Company structures based on their rate field in descending order.
 *
 * @param firstCompany Pointer to the first Company structure to compare.
 *        It should not be NULL and should be castable to a const Company pointer.
 * @param secondCompany Pointer to the second Company structure to compare.
 *        It should not be NULL and should be castable to a const Company pointer.
 *
 * @return Returns an integer:
 *         - A positive value if the rate of Company B is greater than the rate of Company A.
 *         - A negative value if the rate of Company A is greater than the rate of Company B.
 *         - 0 if both rates are equal.
 */
int compare_rate(const void *firstCompany, const void *secondCompany) {
    const Company *companyA = (const Company *) firstCompany;
    const Company *companyB = (const Company *) secondCompany;

    return companyB->rate - companyA->rate;
}

/**
 * @brief This function sorts the companies by their rates using the qsort algorithm.
 * @param companies Pointer to the Companies structure containing company data.
 */
void sortRate(Companies *companies) {
    qsort(companies->companies, companies->counter, sizeof (Company), compare_rate);
}

/**
 * @brief This function sorts the list of companies in descending order based on their rates using quicksort.
 * It then prints the names of the top 5 companies with the best rates if the state = 1 meaning that is active.
 *
 * @param companies Pointer to the Companies structure containing the list of companies.
 */
void top5bestCompanies(Companies *companies) {
    int i, numPrinted = 0, stateCompany;
    if (companies->counter > 0) {
        sortRate(companies);

        printf("Top 5 best companies are:\n");

        for (i = 0; i < companies->counter && numPrinted < TOP_5; i++) {
            stateCompany = companies->companies[i].state;
            if (stateCompany == 1) {
                printf(" > %s - %.2f rate.\n", companies->companies[i].name, companies->companies[i].rate);
            }
            numPrinted++;
        }
    } else {
        puts(ERROR_COMPANY_NOT_FOUND);
    }
}

/**
 * @brief This function checks if a given company is present in the top 5 most viewed companies.
 * @param companies Pointer to the Companies structure containing the list of companies.
 * @param companyName Name of the company to be checked.
 * @return Returns 1 if the company is found in the top 5 most viewed companies, otherwise -1.
 */
int isInTop5MostViewed(Companies *companies, char *companyName) {
    int i;
    sortViews(companies);
    for (i = 0; i < TOP_5 && i < companies->counter; i++) {
        if (strcmp(companies->companies[i].name, companyName) == 0) {
            return 1;
        }
    }
    return -1;
}

/**
 * @brief This function checks if a given company is present in the top 5 companies with the best rates.
 * @param companies Pointer to the Companies structure containing the list of companies.
 * @param companyName Name of the company to be checked.
 * @return Returns 1 if the company is found in the top 5 companies with the best rates, otherwise -1.
 */
int isInTop5BestRated(Companies *companies, char *companyName) {
    int i;
    sortRate(companies);
    for (i = 0; i < TOP_5 && i < companies->counter; i++) {
        if (strcmp(companies->companies[i].name, companyName) == 0) {
            return 1;
        }
    }
    return -1;
}


/**
 * @brief This function creates and prints a report for a specific company, including the number of times the company has been searched,
 * its current rate, and whether it is in the top 5 most viewed or best rated companies.
 * @param companies Pointer to the Companies structure containing company data.
 * @param companyPosition Index of the company within the Companies structure.
 */
void creatCompanyReport(Companies *companies, int companyPosition) {   
    int mostViewed, bestRated;

    printf("Your Company have been search: %d\n", companies->companies[companyPosition].views);
    printf("Your Company rate is: %.2f\n", companies->companies[companyPosition].rate);

    mostViewed = isInTop5MostViewed(companies, companies->companies[companyPosition].name);
    if (mostViewed == 1) {
        printf("Your Company is in the top 5 most viewed.\n");
    } else {
        printf("Your Company is not in the top 5 most viewed.\n");
    }

    bestRated = isInTop5BestRated(companies, companies->companies[companyPosition].name);
    if (bestRated == 1) {
        printf("Your Company is in the top 5 best rated.\n");
    } else {
        printf("Your Company is not in the top 5 best rated.\n");
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

/**
 * @brief This function computes the average rate of a company by taking the sum of the current rate
 * and a new rate and then dividing it by 2.
 * @param company Pointer to the Company structure for which the average rate is calculated.
 * It should not be NULL and should contain a valid rate field.
 * @param rate The new rate to be added in the average calculation.
 * @return Returns the calculated average rate of the company.
 */
float company_average(Company *company, float rate) {
    float average;

    average = (company->rate + rate) / 2;

    return average;
}

/**
 * @brief This function allows the user to rate a company by providing a new rate. If the company is found
 * by its name in the Companies structure, it updates the rate of the company. If the company's rate
 * is initially 0, it directly assigns the new rate. Otherwise, it calculates the average of the
 * existing rate and the new rate.
 * Only does this if the company is active.
 *
 * @param companies Pointer to the Companies structure containing the list of companies.
 */
void rate_company(Companies *companies) {
    char name[MAX_NAME];
    float rate;
    int code, state;
    readString(name, MAX_NAME, MSG_NAME_COMP);

    code = searchCompanyByName(*companies, name);

    state = companies->companies[code].state;

    if (code != -1) {
        if (state == 1) {

            rate = getFloat(MIN_RATING, MAX_RATING, MSG_RATING);
            if (companies->companies[code].rate == 0) {
                companies->companies[code].rate = rate;
            } else {
                companies->companies[code].rate = company_average(&companies->companies[code], rate);
            }
        } else {
            puts(ERROR_NOT_ACTIVE);
        }
    } else {
        puts(ERROR_COMPANY_NOT_FOUND);
    }
}

/**
 * @brief This function lists the details of the provided data structer
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByName(Companies *companies, ActivityBranchs branchs) {
    int companyCode = 0, state;
    char name[MAX_COMPANY_NAME_SIZE];
    readString(name, MAX_COMPANY_NAME_SIZE, MSG_NAME);

    companyCode = searchCompanyByName(*companies, name);

    state = companies->companies[companyCode].state;

    if (companyCode != -1) {

        if (state == 1) {
            printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
            companies->companies[companyCode].views++;
            printCompany(companies->companies[companyCode], branchs);
        } else {
            puts(ERROR_NOT_ACTIVE);
        }
    } else {

        puts("ERROR: Company not found.");
    }
}

/**
 * @brief This fuction searchs the position of the provided companies data array that matches the provided category code.
 * @param companies The array to be searched.
 * @param category The category to check if matches.
 * @return i if it encounters a position that has an equal category, -1 if it doesn´t.
 */
int searchCompanyByCategory(Companies companies, int category) {
    int i;
    for (i = 0; i < companies.counter; i++) {
        if (companies.companies[i].category == category) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief This function promps the user to introduce a Category and lists the details of the provided data that has a matching Category field
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByCategory(Companies *companies, ActivityBranchs branchs) {
    int i = 0, category = 0, counter = 0, state;

    category = getInt(0, 2, MSG_CATEGORY);

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
    for (i = 0; i < companies->counter; i++) {
        state = companies->companies[i].state;
        if (state == 1) {
            if (companies->companies[i].category == category) {
                companies->companies[i].views++;
                printCompany(companies->companies[i], branchs);
                counter++;
            }
        }
    }
    if (!counter) {
        puts("No companies found.");
    }
}

/**
 * @brief This function promps the user to introduce a Locality and lists the details of the provided data that has a matching Locality field
 * @param companies The variable containing the details to be listed
 * @param branchs The variable to print the company's branch name.
 */
void listCompaniesByLocality(Companies *companies, ActivityBranchs branchs) {
    int i, counter = 0, state;
    char locality[MAX_COMPANY_LOCALITY_SIZE];
    readString(locality, MAX_COMPANY_LOCALITY_SIZE, MSG_LOCALITY);

    printf("\n%-10s %-20s %-15s %-15s %-20s %-20s %-15s %-15s %-15s %-10s\n", "NIF", "NAME", "CATEGORY", "BRANCH", "STREET", "LOCALITY", "POSTAL CODE", "RATE", "VIEWS", "STATE");
    for (i = 0; i < companies->counter; i++) {
        state = companies->companies[i].state;
        if (state == 1) {
            if (strcmp(companies->companies[i].locality, locality) == 0) {
                companies->companies[i].views++;
                printCompany(companies->companies[i], branchs);
                counter++;
            }
        }
    }
    if (!counter) {
        puts("No companies found.");
    }
}

/**
 * @brief This function selects the company that the user wnats to use and return its position.
 * @param companies The variable to look for the desired company
 * @return company postition in the memory if the company was found. -1 if the company was not found.
 */
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

/**
 * @brief This function verifies if a specified company has comments.
 * @param company The company to analize it has comments associated.
 * @param comments The comments to check in any is associeated to the specified company.
 * @return 1 if the company has comments. 0 if the company does not have comments.
 */
int hasComments(Company company, Comments comments) {

    int i;

    for (i = 0; i < comments.counter; i++) {
        if (comments.comments[i].company_nif == company.nif) {
            return 1;
        }
    }
    return 0;
}