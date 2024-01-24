/**
 * @file companys.h
 * @author Tania, Gonçalo, Tomas
 * @date 11-01-2024
 * @version 1
 *
 * @copyright Copyright (C) Tania, Gonçalo, Tomas 2023. All Rights MIT Licensed.
 *
 * @brief A header file that provides companies functions such as create, read, update and delete.
 * 
 */

#ifndef COMPANYS_H
#define COMPANYS_H

#include "branchs.h"


#define MSG_NIF "Please, insert your nif!\n> "
#define MSG_NAME "Please, insert company's name\n> "
#define MSG_CATEGORY "Choose the category:\n0.MICRO\n1.SME\n2.BIG_COMPANY\n> "
#define MSG_BRANCH "Choose Activity Branch\n> "
#define MSG_STREET "Put the name's street\n> "
#define MSG_LOCALITY "Put the company's locality\n> "
#define MSG_POSTALCODE "Insert postal code\n> "
#define MSG_STATE "State [1 - Active | 0 - Inactive] > "

#define ERROR_EMPTY_LIST "The Company list is empty.\n"
#define TOP_5 5

#define ERROR_NOT_ACTIVE "The Company is not active.\n"
#define ERROR_COMPANY_NOT_FOUND "Company not found!\n"
#define ERROR_DELETE_COMPANY "\n*ERROR: Can´t delete companies with comments. \nState was changed to Inactive.*\n"

#define VIEW_COMPANY "The most looked companies are:\n"
#define TOP_FIVE "Top 5 best companies are:\n"

#define MIN_NIF 100000000
#define MAX_NIF 999999999

#define MIN_CATEGORY 0
#define MAX_CATEGORY 2

#define MAX_STREET 50

#define MAX_LOCALITY 50

#define MIN_POSTALCODE 4000000
#define MAX_POSTALCODE 9999999

#define MIN_STATE 0
#define MAX_STATE 1

#define MAX_COMPANIES 10
#define MAX_COMPANY_NAME_SIZE 100
#define MAX_COMPANY_LOCALITY_SIZE 100

#define MSG_NAME_COMP "Company name > "

#define MIN_RATING 0
#define MAX_RATING 5
#define MSG_RATING "Please, rate the Company!\n"

#define MSG_SEARCH_COMPANY "Company name > "

#define MAX_COMMENTS_SIZE 100
#define MAX_COMMENT_CARACTER 300
#define MSG_COMMENT "Comment \n > "

#define MAX_NAME 256
#define MSG_NAME_USER "Please, insert your name!\n > "

#define MAX_EMAIL 256
#define MSG_EMAIL "Please, insert your email\n > "

#define ERROR_IMPOSSIBLE_COMPANY "ERROR: Was not possible to create a new company."
#define ERROR_NAME_COMPANY "ERROR: Name is already in use."
#define ERROR_NIF_COMPANY "ERROR: Nif is already in use."
#define SUCCESS_COMPANY_CREATE "SUCCESS: Company created"

#define FULL_LIST_COMPANY "ERROR: Companies List is Full."
#define ERROR_NO_BRANCHS "ERROR: Activity Branchs list is empty."

#define ERROR "ERROR"

#define COMPANIES_FILE "companies.bin"

typedef enum {
    MICRO, SME, BIG_COMPANY
} Category;

typedef struct {
    int nif;
    char name[MAX_COMPANY_NAME_SIZE];
    Category category;
    int branch;
    char street[50];
    char locality[50];
    int postalCode;
    int views;
    float rate;
    int state;
} Company;

typedef struct {
    int counter, size;
    Company *companies;
} Companies;

/**
 * @brief This function is used to create several companies and check if the list
 *  is full or if the company exists
 * @param receives as a parameter a pointer of type Companies
 */
void createCompanies(Companies *companies, ActivityBranchs *branchs);

/**
 * @brief aims to print all companies, if they exist, if it does not display an error message
 * @param receives as parameter a variable calls company of type company
 */
void listCompanies(Companies companies, ActivityBranchs branchs);

/**
 * @brief aims to update all of a company's data, except the NIF
 * @param receives as a parameter a pointer of type Companies
 * @param branchs receives as a parameter a pointer of type ActivityBranchs
 */
void updateCompany(Company *company, ActivityBranchs *branchs);

/**
 * @brief aims to update the NIF, if it is correctly inserted it allows you to 
 * update the remaining information
 * @param receives as a parameter a pointer of type Companies
 * @param branchs receives as a parameter a pointer of type ActivityBranchs
 */
void updateCompanies(Companies *companies, ActivityBranchs *branchs);


/**
 * @brief deletes data from a specific company
 * @param receives as a parameter a pointer of type Companies
 */
void deleteCompanies();

/**
 * @brief This function sorts the list of companies in descending order based on views using quicksort.
 * It then prints the names of the top 5 most looked at companies if is state = 1 meaning that is active.
 *
 * @param companies Pointer to the Companies structure containing the list of companies.
 */
void top5lookedCompanies(Companies *companies);

/**
 * @brief This function sorts the list of companies in descending order based on their rates using quicksort.
 * It then prints the names of the top 5 companies with the best rates if the state = 1 meaning that is active.
 *
 * @param companies Pointer to the Companies structure containing the list of companies.
 */
void top5bestCompanies(Companies *companies);

/**
 * @brief This function creates and prints a report for a specific company, including the number of times the company has been searched,
 * its current rate, and whether it is in the top 5 most viewed or best rated companies.
 * 
 * @param companies Pointer to the Companies structure containing company data.
 * @param companyPosition Index of the company within the Companies structure.
 */
void creatCompanyReport(Companies *companies, int companyPosition);

/**
 * @brief This fuction searchs the position of the provided data array that matches the provided name
 * @param companies The array to be searched
 * @param name The name to see if matches
 * @return i if it encounters a position that has an equal name, -1 if not
 */
int searchCompanyByName(Companies companies, char *name);

/**
 * @brief This function allows the user to rate a company and computes the average rating for the company. If the company does not exist, it adds it to the list of companies.
 * @param companies A pointer to the 'Companies' structure containing company data. The function uses this to search for and update the rating of a company.
 * @return An integer value:
 *         - The index of the rated company in the 'companies' array if successful.
 *         - '-1' if the company name already exists in the list or if there's an error.
 */
void rate_company(Companies *companies);

/**
 * @brief This function lists the details of the provided data structer
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByName(Companies *companies, ActivityBranchs branchs);

/**
 * @brief This function promps the user to introduce a Category and lists the details of the provided data that has a matching Category field
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByCategory(Companies *companies, ActivityBranchs branchs);

/**
 * @brief This function promps the user to introduce a Locality and lists the details of the provided data that has a matching Locality field
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByLocality(Companies *companies, ActivityBranchs branchs);

/**
 * This function selects the company that the user wnats to use and return its position.
 * @param companies The variable to look for the desired company
 * @return company postition in the memory if the company was found. -1 if the company was not found.
 */
int selectCompany(Companies companies);

/**
 * @brief This function writes the data of Companies that is in memory pointed by the first argument to the specified file.
 * @param companies The pointer of the data memory.
 * @param file The file where the data will be stored.
 */
void saveCompanies(Companies *companies, char *file);

/**
 * @brief This function frees the memory that was allocated for the Companies pointer given in the argument that was being used to store the data. After freeing the memory in puts all the values to NULL.
 * @param companies The pointer where data was being stored.
 */
void freeCompanies(Companies *companies);

/**
 * @brief This function reads the data from the file that is given in the second argument and allocs memmory with the size of the Companies struct and allocs memmory for the data data was read. 
 * If the file does not exist it allocs a default size of memory for the future data.
 * @param companies The pointer where the memmory will be allocated
 * @param file The file that the function will read
 */
void loadCompanies(Companies *companies, char *file);

/**
 * @brief This function verifies if a specified company has comments.
 * @param company The company to analize it has comments associated.
 * @param comments The comments to check in any is associeated to the specified company.
 * @return 1 if the company has comments. 0 if the company does not have comments.
 */
int hasComments();
#endif /* COMPANYS_H */

