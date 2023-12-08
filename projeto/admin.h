/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   admin.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 29 de novembro de 2023, 18:13
 */

#ifndef ADMIN_H
#define ADMIN_H

#define MSG_NIF "Please, insert your nif!\n"
#define MSG_NAME "Please, insert company's name\n"
#define MSG_CATEGORY "Choose the category:\n0.MICRO\n1.SME\n2.BIG_COMPANY\n"
#define MSG_BRANCH "Choose\n"
#define MSG_STREET "Put the name's street\n"
#define MSG_LOCALITY "Put the locality's name\n"
#define MSG_POSTALCODE "Insert postal code\n"



#define MIN_NIF 100000000
#define MAX_NIF 999999999
#define MIN_POSTALCODE 4000000
#define MAX_POSTALCODE 9999999
#define MAX_COMPANIES 300
#define MAX_ACTIVITY_BRANCHS 30

/**********************************COMPANY********************************************/
typedef enum {
    MICRO, SME, BIG_COMPANY
} Category;

typedef struct {
    int nif;
    char name[50];
    Category category;
    int branch;
    char street[50];
    char locality[50];
    int postalCode;
    int views;
} Company;

typedef struct {
    int counter;
    Company companies[MAX_COMPANIES];
} Companies;

/**
 * @brief This function is used to analyze whether there is already a company with the same NIF
 * @param receives an integer pointer called nif
 * @param receives a pointer to a file
 * @return 1 if it already exists and 0 if it does not exist 
 */
int verifyNif(int *nif, char *filename);

/**
 * @brief checks if there is a '-' character between the code and the postal code, if not, add it
 * @param receives a pointer to characters called postal code that is found inside the struct
 * @return 
 */
int verify_PostalCode(int *PostalCode);

/**
 * @brief serves to obtain the necessary data for the creation of a company
 * @param receives as a parameter a pointer of type Companies
 * @return counter if successful, returns -1 if not
 */
int createCompany(Companies *companies);

/**********************************ACTIVITY BRANCH**************************************/

typedef struct ActivityBranch {
    int code, state;
    char name[50];
} ActivityBranch;

typedef struct ActivityBranchs {
    int contador;
    ActivityBranch branchs[MAX_ACTIVITY_BRANCHS];
} ActivityBranchs;

/**
 * @brief This function is used to convert the entire string to lowercase
 * @param receives a pointer of type ActivityBranchs called name
 * @return zero in the end of function
 */
char convertLowercase(ActivityBranchs *name);
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

/**
 * Falta Documentar
 */
void updateActivityBranch();

/**
 * Falta Documentar
 */
void deleteActivityBranch();



#endif /* ADMIN_H */

