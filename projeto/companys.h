/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   companys.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 2 de janeiro de 2024, 15:05
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

#define ERROR_COMPANY_NOT_FOUND "Company not found!\n"

#define MIN_NIF 100000000
#define MAX_NIF 999999999
#define MIN_POSTALCODE 4000000
#define MAX_POSTALCODE 9999999
#define MAX_COMPANIES 10
#define MAX_COMPANY_NAME_SIZE 100
#define MAX_COMPANY_LOCALITY_SIZE 100

#define MSG_NAME_COMP "Company name.\n"

#define MIN_RATING 0
#define MAX_RATING 5
#define MSG_RATING "Please, rate the Company!\n"

#define MSG_SEARCH_COMPANY "\n Please put the company name\n > "

#define MAX_COMMENTS_SIZE 100
#define MAX_COMMENT_CARACTER 300
#define MSG_COMMENT "Comment \n > "

#define MAX_NAME 256
#define MSG_NAME_USER "Please, insert your name!\n > "

#define MAX_EMAIL 256
#define MSG_EMAIL "Please, insert your email\n > "

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
int createCompany(Companies *companies, ActivityBranchs *branchs);

/**
 * @brief This function is used to create several companies and check if the list
 *  is full or if the company exists
 * @param receives as a parameter a pointer of type Companies
 */
void createCompanies(Companies *companies, ActivityBranchs *branchs);

/**
 * @brief The function aims to print all company data
 * @param receives as parameter a variable calls company of type company
 */
void printCompany(Company company, ActivityBranchs branchs);

/**
 * @brief aims to print all companies, if they exist, if it does not display an error message
 * @param receives as parameter a variable calls company of type company
 */
void listCompanies(Companies companies, ActivityBranchs branchs);

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

/**
 * @brief This function displays the names of the top 5 most viewed companies 
 * based on the number of views stored in the 'Companies' structure.
 *
 * @param companies A pointer to the 'Companies' structure containing the company data.
 */
void top5lookedCompanies(Companies *companies);

/**
 * @brief This function sorts the list of companies based on their ratings and displays
 * the names of the top 5 best-rated companies.
 * 
 * @param companies A pointer to the 'Companies' structure containing company data.
 *                  The function uses the 'counter' field to determine the number of companies.
 *                  The 'companies' array is sorted based on the ratings of each company.
 */
void top5bestCompanies(Companies *companies);


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
 * Falta documentar
 * @param companies
 * @return 
 */
int selectCompany(Companies companies);

/**
 * Falta documentar - Guardar dados de memoria para ficheiro
 * @param companies
 * @param file
 */
void saveCompanies(Companies *companies, char *file);

/**
 * Falta documentar
 * @param companies
 */
void freeCompanies(Companies *companies);

/**
 * Falta documentar
 * @param companies
 * @param file
 */
void loadCompanies(Companies *companies, char *file);
#endif /* COMPANYS_H */

