/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   activityBranch.h
 * Author: tomas
 *
 * Created on 1 de dezembro de 2023, 16:48
 */

#ifndef ACTIVITYBRANCH_H
#define ACTIVITYBRANCH_H

#define MAX_ACTIVITY_BRANCHS 30

typedef struct ActivityBranch {
    int code, state;
    char name[50];
} ActivityBranch;

typedef struct ActivityBranchs {
    int contador;
    ActivityBranch branchs[MAX_ACTIVITY_BRANCHS];
}ActivityBranchs;

int autoIncrementCode();

/**
 * @brief This function allows the user to enter data associated with an Activity Branch and then writes the data in a file.
 * @param
 * @return This functions does not return a value. Prompts the user  to introduce data associated with an Activity Branch and writes the data in a file.
 */
int createActivityBranch(ActivityBranchs *branchs);

/**
 * @brief This function allows the user to see what´s inside the file that stores Activity Branchs in the terminal.
 * @return This functions does not return a value. Shows the data inside of a specified file.
 */
void listActivityBranch();

void updateActivityBranch();

#endif /* ACTIVITYBRANCH_H */

