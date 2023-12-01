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

struct ActivityBranch {
    int code, state;
    char name[50];
};

int autoIncrementCode();

/**
 * @brief This function writes in a file the data provided in the arguments
 * @param file The file where data will be writed.
 * @param branch The data that will be writed in the file.
 * @return This functions does not return a value. Writes the data in a file.
 */
void registerActivityBranch(FILE *file, struct ActivityBranch *branch);

/**
 * @brief This function allows the user to enter data associated with an Activity Branch and then calls another function that will register tha data provided y the usere in a file.
 * @return This functions does not return a value. Prompts the user  to introduce data associated with an Activity Branch.
 */
void createActivityBranch();

#endif /* ACTIVITYBRANCH_H */

