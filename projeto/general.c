#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "admin.h"

#define MIN_VALUE_OPTION 0
#define MAX_VALUE_OPTION 5
#define OPTION_MESSAGE "Option > "

void main_menu() {
    int flag = 0, option = 0;

    do {

        printf("1 - Admin Panel\n"
                "2 - User Panel\n"
                "3 - Company Panel\n\n"
                "4 - Load Data\n"
                "5 - Save Data\n"
                "0 - Quit\n"
                "\n");

        option = getInt(MIN_VALUE_OPTION, MAX_VALUE_OPTION, OPTION_MESSAGE);

        switch (option) {

            case 1:
                //Admin Menu
                admin_menu();
                break;

            case 2:
                //User Menu
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
