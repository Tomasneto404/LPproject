/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   admin.h
 * Author: tomas
 *
 * Created on 29 de novembro de 2023, 18:13
 */

#ifndef ADMIN_H
#define ADMIN_H

#include "activityBranch.h"

#define MAX_COMPANIES 300


typedef enum{
    MICRO,SME,BIG_COMPANY
}Category;

typedef struct{
    int nif;
    char name[50];
    Category category;
    int branch;
    char street[50];
    char locality[50];
    int postalCode;
}Company;

typedef struct {
    int counter;
    Company companies[MAX_COMPANIES];
} Companies;

/**
 * @brief This function is used to analyze whether there is already a company with the same NIF
 * @param receives an integer pointer called nif
 * @param receives a pointer to a file
 * @return 1 if it already exists and 0 if it does not exist 
 */
int verifyNif(int *nif, char *filename);

/**
 * @brief checks if there is a '-' character between the code and the postal code, if not, add it
 * @param receives a pointer to characters called postal code that is found inside the struct
 * @return 
 */
int verify_PostalCode(int *PostalCode);



/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Companys. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the company manage menu, asks the user for an option and executes a function associated with the chosen option.
 */
void company_manage_menu();

/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Activity Branchs. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the activity branch manage menu, asks the user for an option and executes a function associated with the chosen option.
 */
void manage_activity_branch_menu();

/**
 * @brief This function shows the admin's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the admin's menu, asks the user for an option and executes a function associated with the chosen option.
 */
void admin_menu();


#endif /* ADMIN_H */

