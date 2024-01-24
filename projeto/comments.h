/**
 * @file comments.h
 * @author Tania, Gonçalo, Tomas
 * @date 11-01-2024
 * @version 1
 *
 * @copyright Copyright (C) Tania, Gonçalo, Tomas 2023. All Rights MIT Licensed.
 *
 * @brief A header file that provides comments functions such as create, read, update and delete.
 * 
 */

#ifndef COMMENTS_H
#define COMMENTS_H

#include "companys.h"

#define LINES1 "|+++++++++++++++++++++++++++++++++++++++++|\n"
#define LINES2 "\n| -----------------------------------\n"

#define MAX_COMMENTS 10
#define CODE_ALREADY_EXISTS "ERROR: This code is alredy in use!\n"

#define MIN_COMMENT_CODE 1
#define MAX_COMMENT_CODE 1000

#define MAX_COMMENT_NAME 100
#define COMMENT_NAME_MSG "Name > "

#define MAX_COMMENT_EMAIL 100
#define COMMENT_EMAIL_MSG "Email > "

#define MAX_TITLE_SIZE 100
#define TITLE_MSG "Title > "

#define MAX_COMMENT_SIZE 256
#define COMMENT_MSG "Comment > "

#define ERROR_CODE_COMMENTS "ERROR: Code is already in use"
#define ERROR_NOT_EXIST_COMMENTS "ERROR: Company does not exist."
#define ERROR_EMPTY_COMMENTS "ERROR: Companies list is empty."

#define SUCCESS_CREATE_COMMENTS "SUCCESS: Comment created."
#define ERROR_INSERT_COMMENTS  "ERROR: It's not possible to insert a new comment"

#define ERROR_WITHOUT_COMMENTS "ERROR: Company doesn´t have comments."

#define SUCCESS_STATE_COMMENTS "SUCCESS: Comment state was changed to Inactive."
#define ERROR_STATE_COMMENTS "ERROR: Comment is already Inactive."
#define ERROR_BELONG_COMMENT "ERROR: This comment doesn´t belong to this company."
#define ERROR_COMMENT "ERROR: Comment not found."

#define SUCCESS_DELETE_COMMENT "SUCCESS: Comment deleted."

#define COMMENTS_FILE "comments.bin"


typedef struct{
    int state, company_nif, code;
    char name[256];
    char email[256];
    char title[256];
    char comment[256];
}Comment;

typedef struct{
    int counter, size;
    Comment *comments;
}Comments;


/**
 * @brief This function verifies if it's possible to create a new comment. Verifies if it has enough memory allocated (if it doesn´t it allocs more memory) and calls the function to insert the new comment after the validations. 
 * @param comments 
 * @param companies
 */
void createComments(Comments *comments, Companies companies);


/**
 * @brief This function reads the data from the file that is given in the second argument and allocs memmory with the size of the Comments struct and allocs memmory for the data data was read. 
 * If the file does not exist it allocs a default size of memory for the future data.
 * @param comments The pointer where the memmory will be allocated
 * @param file The file that the function will read
 */
void loadComments(Comments *comments, char *file);

/**
 * @brief This function writes the data of Comments that is in memory pointed by the first argument to the specified file.
 * @param comments The pointer of the data memory.
 * @param file The file where the data will be stored.
 */
void saveComments(Comments *comments, char *file);

/**
 * @brief This function frees the memory that was allocated for the Comments pointer given in the argument that was being used to store the data. After freeing the memory in puts all the values to NULL.
 * @param comments The pointer where data was being stored.
 */
void freeComments(Comments *comments);

/**
 * @brief This function lists all the active comments of a specific company.
 * @param comments The comments search and list.
 * @param company The specific company.
 */
void listComments(Comments *comments, Company company);

/**
 * @brief This function prompts the user to change the state of a specific comment at a specific company.
 * @param company The company where it will "hide" the comment.
 * @param comments The list of comments to find the specific one.
 */
void hideComment(Company company, Comments *comments);

/**
 * @brief This function prompts the user to select a comment to hide a comment and then executes the function to change its state.
 * @param companies The pointer to the companies variable
 * @param comments The pointer to the comments variable
 */
void hideComments(Companies *companies, Comments *comments);

/**
 * @brief This function prompts the user to select a comment from the comments list and then shifts the comments since the selected onde to the beginning.
 * @param comments The pointer to the comments variable
 */
void deleteComments(Comments *comments);

/**
 * @brief This function lists all the comments of a specific company.
 * @param comments The pointer to the comments variable
 * @param companies The pointer to the companies variable
 */
void listCommentsAdmin(Comments *comments, Companies *companies);

#endif /* COMMENTS_H */

