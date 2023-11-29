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

#define ADMIN_USERNAME "admin"
#define ADMIN_USERNAME_SIZE 10
#define ADMIN_PASSWORD "admin"
#define ADMIN_PASSWORD_SIZE 10

int authenticate_admin(){
    
    char username[ADMIN_USERNAME_SIZE], password[ADMIN_PASSWORD_SIZE];
    
    readString(username, ADMIN_USERNAME_SIZE, "Username > ");
    readString(password, ADMIN_PASSWORD_SIZE, "Password > ");
    
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
    
}
