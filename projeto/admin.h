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

/**
 * @brief This function is used to analyze whether there is already a company with the same NIF
 * @param receives an integer pointer called nif
 * @param receives a pointer to a file
 * @return 1 if it already exists and 0 if it does not exist 
 */
int verifyNif(int *nif, char *filename);

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

