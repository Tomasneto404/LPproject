#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "comments.h"

int searchComment(Comments comments, int code) {
    int i;
    for (i = 0; i < comments.counter; i++) {
        if (comments.comments[i].code == code) {
            return i;
        }
    }
    return -1;
}

void expandCommentsCapacity(Comments *comments) {
    int tam = (comments->size) == 0 ? MAX_COMMENT_SIZE : comments->size * 2;
    Comment *tmp = (Comment*) realloc(comments->comments, sizeof (Comment)*(tam));

    if (tmp != NULL) {
        comments->size = tam;
        comments->comments = tmp;
    }
}

int createComment(Comments *comments, Companies companies) {

    int companyCode = 0, code = getInt(MIN_COMMENT_CODE, MAX_COMMENT_CODE, CODE_MSG);


    if (searchComment(*comments, code) == -1) {

        companyCode = selectCompany(companies);

        if (companyCode != -1) {

            comments->comments[comments->counter].code = code;
            comments->comments[comments->counter].company_nif = companies.companies[companyCode].nif;

            readString(comments->comments[comments->counter].name, MAX_COMMENT_NAME, NAME_MSG);
            readString(comments->comments[comments->counter].email, MAX_COMMENT_EMAIL, COMMENT_EMAIL_MSG);
            readString(comments->comments[comments->counter].title, MAX_TITLE_SIZE, TITLE_MSG);
            readString(comments->comments[comments->counter].comment, MAX_COMMENT_SIZE, COMMENT_MSG);


            comments->comments[comments->counter].state = 1;

            return comments->counter++;

        } else {
            puts("ERROR: Company does not exist.");
        }

    } else {
        puts("ERROR: This code is already in use.");
    }


    return -1;
}

void createComments(Comments *comments, Companies companies) {

    if (companies.counter > 0) {
        if (comments->counter == comments->size) {
            expandCommentsCapacity(comments);
        }

        if (comments->counter < comments->size) {
            if (createComment(comments, companies) == -1) {
                puts("The comment already exists");
            }
        } else {
            puts("It's not possible to insert a new comment");
        }
    } else {
        puts("ERROR: Companies list is empty.");
    }

}

void loadComments(Comments *comments, char *file) {
    int i, sucesso = 0;

    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        comments->counter = 0;
        
        fread(&comments->counter, sizeof (int), 1, fp);

        if (comments->counter > 0) {
            comments->size = comments->counter;
            comments->comments = (Comment*) malloc(comments->counter * sizeof (Comment));
            for (i = 0; i < comments->counter; i++) {
                fread(&comments->comments[i], sizeof (Comment), 1, fp);
            }
            sucesso = 1;
        }

        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(file, "wb");
        if (fp != NULL) {

            comments->comments = (Comment*) malloc(MAX_COMMENTS * sizeof (comments));
            comments->counter = 0;
            comments->size = MAX_COMMENTS;

            fclose(fp);
        }
    }
}

void saveComments(Comments *comments, char *file) {
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&comments->counter, sizeof (int), 1, fp);

    for (i = 0; i < comments->counter; i++) {
        fwrite(&comments->comments[i], sizeof (Comment), 1, fp);
    }

    fclose(fp);
}

void freeComments(Comments *comments) {
    if (comments->comments) {
        free(comments->comments);
        comments->comments = NULL;
    }

    comments = NULL;
}

void printComment(Comment comment){
    
    printf("| ID - %-10d | State - %-10d\n", comment.code, comment.state);
    printf("| Author - %-20s\n", comment.name);
    printf("| Title - %-20s\n", comment.title);
    printf("| Text - %-20s\n", comment.comment);
    
}

void listComments(Comments *comments, Company company){
    int i;

    if (comments->counter > 0) {
        printf("|+++++++++++++++++++++++++++++++++++++++++|\n");
        for (i = 0; i < comments->counter; i++) {
            
            if (comments->comments[i].company_nif == company.nif) {
                printf("\n| -----------------------------------\n");
                printComment(comments->comments[i]);
                printf("| -----------------------------------\n");
            }
            
        }
        printf("\n|+++++++++++++++++++++++++++++++++++++++++|\n");
    } else {
        
        puts(EMPTY_LIST);
        
    }
}