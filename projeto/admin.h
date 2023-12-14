/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   admin.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 29 de novembro de 2023, 18:13
 */

#ifndef ADMIN_H
#define ADMIN_H

#define MSG_NIF "Please, insert your nif!\n> "
#define MSG_NAME "Please, insert company's name\n> "
#define MSG_CATEGORY "Choose the category:\n0.MICRO\n1.SME\n2.BIG_COMPANY\n> "
#define MSG_BRANCH "Choose Activity Branch\n> "
#define MSG_STREET "Put the name's street\n> "
#define MSG_LOCALITY "Put the company's locality\n> "
#define MSG_POSTALCODE "Insert postal code\n> "

#define ERROR_EMPTY_LIST "The Company list is empty."
#define TOP_5 5

#define MIN_NIF 100000000
#define MAX_NIF 999999999
#define MIN_POSTALCODE 4000000
#define MAX_POSTALCODE 9999999
#define MAX_COMPANIES 300
#define MAX_COMPANY_NAME_SIZE 100
#define MAX_COMPANY_LOCALITY_SIZE 100



#define MAX_ACTIVITY_BRANCHS 30
#define MAX_AB_NAME_SIZE 100
#define NAME_MSG "Name > "

#define STATE_MSG "State [1 - Active | 0 - Inactive] > "
#define MIN_STATE_VALUE 0
#define MAX_STATE_VALUE 1

#define CODE_MSG "Code > "
#define MIN_AB_CODE_VALUE 0
#define MAX_AB_CODE_VALUE 1000

#define AB_DOES_NOT_EXIST "ERROR: This Activity Branch does not exist."
#define AB_ALREADY_EXISTS "ERROR: This activity branch already exists."

#define EMPTY_LIST "ERROR: List is empty."
#define FULL_LIST "ERROR: List is full."

/**********************************COMPANY********************************************/
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
} Company;

typedef struct {
    int counter;
    Company companies[MAX_COMPANIES];
} Companies;

/**
 * @brief This function is used to analyze whether there is already a company with the same NIF
 * @param receives an Companies's type called companies
 * @param receives an integer called nif
 * @return i if it already exists and -1 if it does not exist 
 */
int verifyNif(Companies companies, int nif);

/**
 * @brief checks if there is a '-' character between the code and the postal code, if not, add it
 * @param receives a pointer to characters called postal code that is found inside the struct
 * @return 1 if was very successfuly
 */
int verify_PostalCode(int *PostalCode);

/**
 * @brief serves to obtain the necessary data for the creation of a company
 * @param receives as a parameter a pointer of type Companies
 * @return counter if successful, returns -1 if not
 */
int createCompany(Companies *companies);

/**
 * @brief This function is used to create several companies and check if the list
 *  is full or if the company exists
 * @param receives as a parameter a pointer of type Companies
 */
void createCompanies(Companies *companies);

/**
 * @brief The function aims to print all company data
 * @param receives as parameter a variable calls company of type company
 */
void printCompany(Company company);

/**
 * @brief aims to print all companies, if they exist, if it does not display an error message
 * @param receives as parameter a variable calls company of type company
 */
void listCompanies(Companies companies);

/**
 * @brief aims to update all of a company's data, except the NIF
 * @param receives as a parameter a pointer of type Companies
 */
void updateCompany(Company *company);

/**
 * @brief aims to update the NIF, if it is correctly inserted it allows you to 
 * update the remaining information
 * @param receives as a parameter a pointer of type Companies
 */
void updateCompanies(Companies *companies);

/**
 * @brief delete all data relating to a company, if it does not have comments,
 * if it does, make it inactive
 * @param receives as a parameter a pointer of type Companies
 */
void deleteCompanyData(Company *company);

/**
 * @brief deletes data from a specific company
 * @param receives as a parameter a pointer of type Companies
 */
void deleteCompanies(Companies *companies);
/**********************************ACTIVITY BRANCH**************************************/

typedef struct ActivityBranch {
    int code, state;
    char name[MAX_AB_NAME_SIZE];
} ActivityBranch;

typedef struct ActivityBranchs {
    int counter;
    ActivityBranch branchs[MAX_ACTIVITY_BRANCHS];
} ActivityBranchs;

/**
 * @brief This function is used to convert the entire string to lowercase
 * @param receives a pointer of type ActivityBranchs called name
 * @return zero in the end of function
 */
char convertLowercase(ActivityBranchs *name);

/**
 * @brief Creates a new activity branch and adds it to the collection of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void createActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Creates a new activity branch and adds it to the collection if the code is unique.
 * @param branchs A pointer to the structure containing the array of activity branches.
 * @return The index of the newly created activity branch if successful, or -1 if the code already exists.
 */
int createActivityBranch(ActivityBranchs *branchs);

/**
 * @brief Searches for an activity branch with a specific code within an array of activity branches.
 * @param branchs The structure containing the array of activity branches.
 * @param code The code to search for within the activity branches.
 * @return The index of the activity branch if found, or -1 if not found.
 */
int searchActivityBranch(ActivityBranchs branchs, int code);

/**
 * @brief Lists the details of all activity branches in the provided array.
 * @param branchs The structure containing the array of activity branches to be listed.
 */
void listActivityBranchs(ActivityBranchs branchs);

/**
 * @brief Prints the details of an individual activity branch.
 * @param branch The activity branch to be printed.
 */
void printActivityBranch(ActivityBranch branch);

/**
 * @brief Updates the details of an activity branch within an array of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void updateActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Updates the state of an individual activity branch.
 * @param branch A pointer to the specific activity branch to be updated.
 */
void updateActivityBranch(ActivityBranch *branch);

/**
 * @brief Deletes an activity branch from the array of activity branches.
 * @param branchs A pointer to the structure containing the array of activity branches.
 */
void deleteActivityBranchs(ActivityBranchs *branchs);

/**
 * @brief Deletes an individual activity branch by resetting its attributes.
 * @param branch A pointer to the specific activity branch to be deleted.
 */
void deleteActivityBranch(ActivityBranch *branch);

/*
 Falta documentar
 */
int verifyAbName(ActivityBranchs branchs, char *name);
#endif /* ADMIN_H */

