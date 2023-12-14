/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "admin.h"
#include "menus.h"
#include "user.h"

//USER MENUS

void search_company_menu() {

    int flag = 0, option = 0;
    
    /*APENAS PARA TESTE*/
    Companies companies = {.counter = 2}; //só para teste
    companies.companies[0].nif = 123456789;
    companies.companies[0].branch = 1;
    companies.companies[0].category = 1;
    strcpy(companies.companies[0].name, "worten");
    companies.companies[0].postalCode = 1234123;
    strcpy(companies.companies[0].street, "worten");
    companies.companies[0].views = 10;
    strcpy(companies.companies[0].locality, "Pacos de Ferreira");
    
    companies.companies[1].nif = 123456789;
    companies.companies[1].branch = 2;
    companies.companies[1].category = 0;
    strcpy(companies.companies[1].name, "Fnac");
    companies.companies[1].postalCode = 1234123;
    strcpy(companies.companies[1].street, "worten");
    companies.companies[1].views = 10;
    strcpy(companies.companies[1].locality, "Pacos de Ferreira");
    /*APENAS PARA TESTE*/

    do {

        printf("\n----SEARCH COMPANY MENU----\n"
                "1 - Search By Name\n"
                "2 - Search By Category\n"
                "3 - Search By Location\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 3, OPTION_MESSAGE);

        switch (option) {

            case 1:
                listCompaniesByName(companies);
                break;

            case 2:
                listCompaniesByCategory(companies);
                break;

            case 3:
                listCompaniesByLocality(companies);
                break;

            default:
                flag = 1;
                break;

        }

    } while (flag != 1);

}

void user_menu() {

    int flag = 0, option = 0;

    do {

        printf("\n----USER MENU----\n"
                "1 - Search Company\n"
                "2 - Classify Company\n"
                "3 - Comment Company\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 3, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Search Companys menu
                search_company_menu();
                break;

            case 2:
                //Classify Company Menu
                break;

            case 3:
                //Comment Company Menu
                break;

            default:
                flag = 1;
                break;

        }

    } while (flag != 1);

}


//ADMIN MENUS

void company_manage_menu() {

    Companies companies = {.counter = 0};
    int flag = 0, option = 0;

    do {

        printf("\n----COMPANY MANAGE MENU----\n"
                "1 - Create Company\n"
                "2 - List Companys\n"
                "3 - Update Company\n"
                "4 - Delete Company\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                createCompanies(&companies);
                break;

            case 2:
                listCompanies(companies);
                break;

            case 3:
                updateCompanies(&companies);
                break;

            case 4:
                //Delete Company function
                deleteCompanies(&companies);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

void manage_activity_branch_menu() {

    int flag = 0, option = 0;

    ActivityBranchs branchs = {.counter = 0};

    do {

        printf("\n----ACTIVITY BRANCH MANAGE MENU----\n"
                "1 - Create Activity Branch\n"
                "2 - List Activity Branch\n"
                "3 - Update Activity Branch\n"
                "4 - Delete Activity Branch\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Create Activity Branch  function
                createActivityBranchs(&branchs);
                break;

            case 2:
                //List Activity Branchs function
                listActivityBranchs(branchs);
                break;

            case 3:
                //Update Activity Branch function
                updateActivityBranchs(&branchs);
                break;

            case 4:
                //Delete Activity Branch function
                deleteActivityBranchs(&branchs);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}

void reports_menu() {

    int flag = 0, option = 0;

    do {

        printf("\n----REPORTS MENU----\n"
                "1 - Most Viewed Company\n"
                "2 - Meter outro \n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 2, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Most viewed company function
                
                break;

            case 2:
                //Meter outro
               
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}

void admin_menu() {

    int flag = 0, option = 0;

    do {

        printf("\n----ADMIN MENU----\n"
                "1 - Manage Companys\n"
                "2 - Manage Activity Branchs \n"
                "3 - See Reports\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 3, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Manage Companys menu
                company_manage_menu();
                break;

            case 2:
                //Manage Activity Branchs menu
                manage_activity_branch_menu();
                break;

            case 3:
                //Reports menu
                reports_menu();
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

//MAIN MENU
void main_menu() {
    
    Companies companies = {.counter = 0};
    ActivityBranchs branchs = {.counter = 0};
    
    int flag = 0, option = 0;

    do {

        printf("\n----MAIN MENU----\n"
                "1 - Admin Panel\n"
                "2 - User Panel\n"
                "3 - Company Panel\n\n"
                "4 - Load Data\n"
                "5 - Save Data\n"
                "0 - Quit\n"
                "\n");

        option = getInt(0, 5, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Admin Menu
                admin_menu();
                break;

            case 2:
                //User Menu
                user_menu();
                break;

            case 3:
                //Company Menu
                break;

            case 4:
                //Load Data Function
                break;

            case 5:
                //Save Data Function
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);
}