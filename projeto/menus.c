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
#include "general.h"

//COMPANY MENU

void company_menu(Companies *companies) {

    int flag = 0, option = 0, companyPosition = -1;

    companyPosition = selectCompany(*companies);

    if (companyPosition != -1) {

        do {

            printf("\n----COMPANY MENU----\n"
                    "1 - Manage Company\n"
                    "2 - View Comments \n" //Adicionar o ocultar comments neste
                    "3 - See Reports\n\n"

                    "0 - Back\n"
                    "\n");

            option = getInt(0, 3, OPTION_MESSAGE);

            switch (option) {

                case 1:
                    updateCompany(&companies->companies[companyPosition]);
                    break;

                case 2:
                    //View comments e info function
                    break;

                case 3:
                    //View Reports function
                    break;

                default:
                    flag = 1;
                    break;

            }


        } while (flag != 1);

    } else {

        return;

    }




}


//USER MENUS

void search_company_menu(Companies *companies, ActivityBranchs *branchs) {

    int flag = 0, option = 0;

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
                listCompaniesByName(*companies);
                break;

            case 2:
                listCompaniesByCategory(*companies);
                break;

            case 3:
                listCompaniesByLocality(*companies);
                break;

            default:
                flag = 1;
                break;

        }

    } while (flag != 1);

}

void user_menu(Companies *companies, ActivityBranchs *branchs) {

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
                search_company_menu(companies, branchs);
                break;

            case 2:
                //Classify Company Menu
                break;

            case 3:
                //Comment Company Menu
                //addComments(&companies);
                break;

            default:
                flag = 1;
                break;

        }

    } while (flag != 1);

}


//ADMIN MENUS

void company_manage_menu(Companies *companies, ActivityBranchs *branchs) {

    int flag = 0, option = 0;

    do {

        printf("\n----COMPANY MANAGE MENU----\n"
                "1 - Create Company\n"
                "2 - List Companys\n"
                "3 - Update Company\n"
                "4 - Delete Company\n\n"

                "0 - Back\n");
        printf("Companies: %d/%d\n\n", companies->counter, MAX_COMPANIES);

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                createCompanies(companies, branchs);
                break;

            case 2:
                listCompanies(*companies);
                break;

            case 3:
                updateCompanies(companies);
                break;

            case 4:
                deleteCompanies(companies);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

void manage_activity_branch_menu(ActivityBranchs *branchs) {

    int flag = 0, option = 0;

    do {

        printf("\n----ACTIVITY BRANCH MANAGE MENU----\n"
                "1 - Create Activity Branch\n"
                "2 - List Activity Branch\n"
                "3 - Update Activity Branch\n"
                "4 - Delete Activity Branch\n\n"

                "0 - Back\n");
        printf("Activity Branchs: %d/%d\n\n", branchs->counter, MAX_ACTIVITY_BRANCHS);

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                createActivityBranchs(branchs);
                break;

            case 2:
                listActivityBranchs(*branchs);
                break;

            case 3:
                updateActivityBranchs(branchs);
                break;

            case 4:
                deleteActivityBranchs(branchs);
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

void admin_menu(Companies *companies, ActivityBranchs *branchs) {

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
                company_manage_menu(companies, branchs);
                break;

            case 2:
                manage_activity_branch_menu(branchs);
                break;

            case 3:
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

    Companies *companies;
    companies = (Companies*) malloc(MAX_COMPANIES * sizeof (Companies));

    ActivityBranchs *branchs;
    branchs = (ActivityBranchs*) malloc(MAX_ACTIVITY_BRANCHS * sizeof (ActivityBranchs));

    loadCompanies(companies, COMPANIES_FILE);
    
    //martelaDados(companies, branchs); //SÓ PARA TESTES (ESCREVE DADOS NO PROGRAMA)

    int flag = 0, option = 0;

    do {

        printf("\n----MAIN MENU----\n"
                "1 - Admin Panel\n"
                "2 - User Panel\n"
                "3 - Company Panel\n"
                "4 - Save Data to File\n\n"
                "0 - Quit\n"
                "\n");

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                admin_menu(companies, branchs);
                break;

            case 2:
                user_menu(companies, branchs);
                break;

            case 3:
                company_menu(companies);
                break;

            case 4:
                saveCompanies(companies, COMPANIES_FILE);
                saveBranchs(branchs, BRANCHS_FILE);
                break;

            default:
                flag = 1;
                freeCompanies(companies);
                freeBranchs(branchs);
                break;
        }

    } while (flag != 1);
}