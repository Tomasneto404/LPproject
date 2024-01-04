/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   comments.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 2 de janeiro de 2024, 15:25
 */

#ifndef COMMENTS_H
#define COMMENTS_H

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
 * Falta documentar
 * @param comments
 * @param code
 * @return 
 */
int searchComment(Comments comments, int code);

/**
 * Falta documentar
 * @param comments
 * @param companies
 */
void createComments(Comments *comments, Companies companies);

/**
 * Falta documentar
 * @param comments
 * @param companies
 * @return 
 */
int createComment(Comments *comments, Companies companies);

/**
 * Falta documentar
 * @param comments
 * @param file
 */
void loadComments(Comments *comments, char *file);

/**
 * Falta documentar
 * @param comments
 * @param file
 */
void saveComments(Comments *comments, char *file);

/**
 * Falta documentar
 * @param comments
 */
void freeComments(Comments *comments);

/**
 * Falta documentar
 * @param comments
 * @param company
 */
void listComments(Comments *comments, Company company);

#endif /* COMMENTS_H */

