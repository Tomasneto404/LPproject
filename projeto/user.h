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

#define MIN_RATING 0
#define MAX_RATING 5
#define MSG_RATING "Please, rate the Company!\n"

#define MSG_SEARCH_COMPANY "\n Please put the company name\n"

#define MAX_COMMENTS_SIZE 100

#define MAX_NAME 256
#define MSG_NAME_USER "Please, insert your name!\n"

#define MAX_EMAIL 256
#define MSG_EMAIL "Please, insert your email\n"

#define MAX_CARACTER 300
#define MSG_COMMENT "Comment:\n\n"





/**
 * @brief This fuction searchs the position of the provided data array that matches the provided name
 * @param companies The array to be searched
 * @param name The name to see if matches
 * @return i if it encounters a position that has an equal name, -1 if not
 */
int searchCompanyByName(Companies companies, char *name);

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


//documentar
int addComment(Comments *comments);
void expandCommentsCapacity(Comments *comments);
void addComments (Companies *companies);

#endif /* USER_H */

