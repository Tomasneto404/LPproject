/**
 * @file menus.h
 * @author Tania, Gonçalo, Tomas
 * @date 11-01-2024
 * @version 1
 *
 * @copyright Copyright (C) Tania, Gonçalo, Tomas 2023. All Rights MIT Licensed.
 *
 * @brief A header file that provides menu functions.
 * 
 */

#ifndef MENUS_H
#define MENUS_H

#include "companys.h"
#include "branchs.h"
#include "comments.h"

#define OPTION_MESSAGE "Option > "

/**
 * @brief This function shows the company's profile menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 * @param comments Comments pointer to pass to other functions
 * @param branchs ActivityBranchs pointer to pass to other functions
 */
void company_menu(Companies *companies, Comments *comments, ActivityBranchs *branchs);

/**
 * @brief This function shows the search company menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 * @param branchs Activity branchs pointer to pass to other functions
 */
void search_company_menu(Companies *companies, ActivityBranchs *branchs);

/**
 * @brief This function shows the users's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 * @param branchs Activity branchs pointer to pass to other functions
 * @param comments Comments pointer to pass to other functions
 */
void user_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments);

/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Companys. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 * @param branchs Activity branchs pointer to pass to other functions
 * @param comments Comments pointer to pass to other functions
 */
void company_manage_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments);

/**
 * @brief This function shows the menu that will allow to execute manage functions related with the Activity Branchs. It asks the user for an option and then executes the function associated with the chosen option.
 * @param branchs Activity branchs pointer to pass to other functions
 * @param companies Companies pointer to pass to other functions
 */
void manage_activity_branch_menu(ActivityBranchs *branchs, Companies *companies);

/**
 * @brief This function shows the reports's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 */
void reports_menu(Companies *companies);

/**
 * @brief This function shows the admin's menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * @param companies Companies pointer to pass to other functions
 * @param branchs Activity branchs pointer to pass to other functions
 * @param comments Comments pointer to pass to other functions
 */
void admin_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments);

/**
 * @brief This function shows the application's main menu on the terminal. It asks the user for an option and then executes the function associated with the chosen option.
 * In this function is also called the functions to read and write data in files and free memory in the end of it.
 */
void main_menu();
#endif /* MENUS_H */

