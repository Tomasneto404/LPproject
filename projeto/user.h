/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   user.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 10 de dezembro de 2023, 14:40
 */

#ifndef USER_H
#define USER_H


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
void listCompaniesByName(Companies companies);

/**
 * @brief This function promps the user to introduce a Category and lists the details of the provided data that has a matching Category field
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByCategory(Companies companies);

/**
 * @brief This function promps the user to introduce a Locality and lists the details of the provided data that has a matching Locality field
 * @param companies The variable containing the details to be listed
 */
void listCompaniesByLocality(Companies companies);

/**
 * Falta documentar
 * @param companies
 * @return 
 */
int selectCompany(Companies companies);

/**
 * @brief this function aims to add comments, that is, if the list of comments 
 * is full, it allocates more memory, in addition, it checks if it is possible 
 * to insert comments in that company
 * 
 * @param receives a parameter called companies of companies type
 */
void addComments (Companies *companies);

#endif /* USER_H */

