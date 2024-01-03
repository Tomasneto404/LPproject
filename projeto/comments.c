#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "companys.h"
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

}

void loadComments(Comments *comments, char *file) {
    int i;

    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        fread(&comments->counter, sizeof (int), 1, fp);

        comments->counter = 0;

        for (i = 0; i < comments->counter; i++) {
            fread(&comments->comments[i], sizeof (Comment), 1, fp);

        }

        fclose(fp);
    } else {
        perror("Error opening file");
        exit(EXIT_FAILURE);
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
        free(comments);
    }

    comments = NULL;
}