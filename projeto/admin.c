/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "admin.h"
#include "activityBranch.h"

#define MSG_NIF "Please, insert your nif!\n"
#define MSG_NAME "Please, insert your nif\n"
#define MSG_CATEGORY "Choose the category:\n0.MICRO\n1.SME\n2.BIG_COMPANY\n"
#define MSG_BRANCH "Choose\n"
#define MSG_STREET "Put the name's street\n"

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
                for (i = 7; i >= 4; i--) {
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

int createCompany(Companies *companies) {
    int nif;

    nif = getInt(100000000, 999999999, MSG_NIF);

    if (verifyNif(&nif, FILENAME) == 0) {
        companies->companies[companies->counter].nif = nif;

        readString(companies->companies[companies->counter].name, 50, MSG_NAME);

        companies->companies[companies->counter].category = getInt(0, 3, MSG_CATEGORY);
       
        /*readString(companies->companies[companies->counter].branch, 50, MSG_BRANCH);*/

        readString(companies->companies[companies->counter].street, 50, MSG_STREET);
        readString(companies->companies[companies->counter].locality, 50, MSG_STREET);

        companies->companies[companies->counter].postalCode = getInt(4000000,4999999 , MSG_CATEGORY);
        verify_PostalCode(&(companies->companies[companies->counter].postalCode));
        
        return companies->counter++;
    }
    
    return -1;
}

void company_manage_menu() {

    Companies companies;
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
                createCompany(&companies);

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