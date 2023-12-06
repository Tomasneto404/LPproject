/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "activityBranch.h"

#define FILENAME "company.txt"
#define OPTION_MESSAGE "Option > "

int verifyNif(int *nif, char *filename) {
    int readNif;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    while (fscanf(fp, "%d", &readNif) == 1) {
        if (nif == &readNif) {
            printf("This NIF already exist!\n");
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int verify_PostalCode(int *postalCode) {
   int i;
    FILE* fp = fopen(FILENAME, "w");
    
    if (fp == NULL) {
        exit(EXIT_FAILURE);
        return 0;
    }
    
    for (i = 0; i < 8; i++) {
        if (i == 4) {
            if (postalCode[i] != '-') {
                for (i = 7; i >=4; i--) {
                    postalCode[i] = postalCode[i - 1];
                }
                postalCode[i] = '-';
            }
        }
        fprintf(fp, "%d", postalCode[i]);
    }
    
    fclose(fp);
    return 1;
}

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
    
    //ActivityBranchs branchs = {.contador = 0};

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