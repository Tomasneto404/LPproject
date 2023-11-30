/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

#define MIN_VALUE_OPTION 0
#define MAX_VALUE_OPTION 3
#define OPTION_MESSAGE "Option > "

void admin_menu() {

    int flag = 0, option = 0;

    do {

        printf("1 - Manage Companys\n"
                "2 - Manage Activity Things \n"
                "3 - Manage Users\n\n"

                "0 - Back\n"
                "\n");

        option = getInt(MIN_VALUE_OPTION, MAX_VALUE_OPTION, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Manage Companys menu
                break;

            case 2:
                //Manage Activity menu
                break;

            case 3:
                //Manage Users menu
                break;

            default:
                flag = 1;
                break;

        }


    } while (flag != 1);


}