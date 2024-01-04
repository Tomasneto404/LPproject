/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   menus.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 6 de dezembro de 2023, 18:27
 */

#ifndef MENUS_H
#define MENUS_H

#include "companys.h"
#include "branchs.h"
#include "comments.h"

#define OPTION_MESSAGE "Option > "

/**
 * @brief This function shows the company's profile menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal company's profile menu, asks the user for an option and executes a function associated with the chosen option.
 */
void company_menu();

/**
 * @brief This function shows the search company menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the search company menu, asks the user for an option and executes a function associated with the chosen option.
 */
void search_company_menu();

/**
 * @brief This function shows the users's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the users's menu, asks the user for an option and executes a function associated with the chosen option.
 */
void user_menu();

/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Companys. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the company manage menu, asks the user for an option and executes a function associated with the chosen option.
 */
void company_manage_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments);

/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Activity Branchs. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the activity branch manage menu, asks the user for an option and executes a function associated with the chosen option.
 */
void manage_activity_branch_menu();

/**
 * @brief This function shows the reports's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the reports's menu, asks the user for an option and executes a function associated with the chosen option.
 */
void reports_menu(Companies *companies);

/**
 * @brief This function shows the admin's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the admin's menu, asks the user for an option and executes a function associated with the chosen option.
 */
void admin_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments);

/**
 * @brief This function shows the application's main menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @return This functions does not return a value. Prints in the terminal the main menu, asks the user for an option and executes a function associated with the chosen option.
 */
void main_menu();
#endif /* MENUS_H */

