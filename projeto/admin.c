/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "activityBranch.h"

#define OPTION_MESSAGE "Option > "

void company_manage_menu() {

    int flag = 0, option = 0;

    do {

        printf("1 - Create Company\n"
                "2 - List Companys\n"
                "3 - Update Company\n"
                "4 - Delete Company\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Create Company  function
                
                break;

            case 2:
                //List Companys function
                break;

            case 3:
                //Update Company function
                break;

            case 4:
                //Delete Company function
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);

}

void manage_activity_branch_menu() {
    
    int flag = 0, option = 0;

    do {

        printf("1 - Create Activity Branch\n"
                "2 - List Activity Branch\n"
                "3 - Update Activity Branch\n"
                "4 - Delete Activity Branch\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 4, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Create Activity Branch  function
                createActivityBranch();
                break;

            case 2:
                //List Activity Branchs function
                listActivityBranch();
                break;

            case 3:
                //Update Activity Branch function
                updateActivityBranch();
                break;

            case 4:
                //Delete Activity Branch function
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

        printf("1 - Manage Companys\n"
                "2 - Manage Activity Branchs \n\n"

                "0 - Back\n"
                "\n");

        option = getInt(0, 2, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Manage Companys menu
                company_manage_menu();
                break;

            case 2:
                //Manage Activity Branchs menu
                manage_activity_branch_menu();
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}