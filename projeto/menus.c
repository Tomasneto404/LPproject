/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "companys.h"
#include "menus.h"
#include "branchs.h"
#include "general.h"
#include "comments.h"

void company_menu(Companies *companies, Comments *comments) {

    int flag = 0, option = 0, companyPosition = -1;

    companyPosition = selectCompany(*companies);

    if (companyPosition != -1) {

        do {

            printf("\n----COMPANY MENU----\n"
                    "1 - Manage Company\n"
                    "2 - View Comments \n"
                    "3 - Hide Comment \n"
                    "4 - See Reports\n\n"

                    "0 - Back\n"
                    "\n");

            option = getInt(0, 4, OPTION_MESSAGE);

            switch (option) {

                case 1:
                    updateCompany(&companies->companies[companyPosition]);
                    break;

                case 2:
                    listComments(comments, companies->companies[companyPosition]);
                    break;

                case 3:
                    hideComment(companies->companies[companyPosition], comments);
                    break;
                    
                case 4:
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

    if (companies->counter > 0){
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
                    listCompaniesByName(companies, *branchs);
                    break;

                case 2:
                    listCompaniesByCategory(companies, *branchs);
                    break;

                case 3:
                    listCompaniesByLocality(companies, *branchs);
                    break;

                default:
                    flag = 1;
                    break;

            }

        } while (flag != 1);
    } else {
        puts("ERROR: lista vazia de companies");
    }

}

void user_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments) {

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
                rate_company(companies);
                break;

            case 3:
                createComments(comments, *companies);
                break;

            default:
                flag = 1;
                break;

        }

    } while (flag != 1);

}


//ADMIN MENUS

void company_manage_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments) {

    int flag = 0, option = 0;

    do {

        printf("\n----COMPANY MANAGE MENU----\n"
                "1 - Create Company\n"
                "2 - List Companys\n"
                "3 - Update Company\n"
                "4 - Delete Company\n\n"

                "0 - Back\n");
        printf("Companies: %d/%d\n\n", companies->counter, companies->size);

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                createCompanies(companies, branchs);
                break;

            case 2:
                listCompanies(*companies, *branchs);
                break;

            case 3:
                updateCompanies(companies);
                break;

            case 4:
                deleteCompanies(companies, comments);

                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

void manage_activity_branch_menu(ActivityBranchs *branchs, Companies *companies) {

    int flag = 0, option = 0;

    do {

        printf("\n----ACTIVITY BRANCH MANAGE MENU----\n"
                "1 - Create Activity Branch\n"
                "2 - List Activity Branch\n"
                "3 - Update Activity Branch\n"
                "4 - Delete Activity Branch\n\n"

                "0 - Back\n");
        printf("Activity Branchs: %d/%d\n\n", branchs->counter, branchs->size);

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
                deleteActivityBranchs(branchs, companies);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}

void reports_menu(Companies *companies) {

    int flag = 0, option = 0;

    do {

        printf("\n----REPORTS MENU----\n"
                "1 - Most Viewed Company\n"
                "2 - Top 5 Companys \n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 2, OPTION_MESSAGE);

        switch (option) {

            case 1:
                top5lookedCompanies(companies);
                break;

            case 2:
                top5bestCompanies(companies);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}

void admin_menu(Companies *companies, ActivityBranchs *branchs, Comments *comments) {

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
                company_manage_menu(companies, branchs, comments);
                break;

            case 2:
                manage_activity_branch_menu(branchs, companies);
                break;

            case 3:
                reports_menu(companies);
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

void main_menu() {
    Companies companies;
    ActivityBranchs branchs;
    Comments comments;

    loadCompanies(&companies, COMPANIES_FILE);
    loadBranchs(&branchs, BRANCHS_FILE);
    loadComments(&comments, COMMENTS_FILE);

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
                admin_menu(&companies, &branchs, &comments);
                break;

            case 2:
                user_menu(&companies, &branchs, &comments);
                break;

            case 3:
                company_menu(&companies, &comments);
                break;

            case 4:
                saveCompanies(&companies, COMPANIES_FILE);
                saveBranchs(&branchs, BRANCHS_FILE);
                saveComments(&comments, COMMENTS_FILE);
                break;

            default:
                flag = 1;
                break;
        }

    } while (flag != 1);

    freeCompanies(&companies);
    freeBranchs(&branchs);
    freeComments(&comments);
}