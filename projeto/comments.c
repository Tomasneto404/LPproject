#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "comments.h"


/**
 * @brief 
 * @param email
 * @return 
 */
int verifyEmail(char *email) {
    int i, tam, x;
    char *atSign = NULL, *point = NULL;

    tam = strlen(email);

    for (i = 0; i < tam; i++) {
        if (email[i] == '@') {
            atSign = email + i;
            x = i;
            break;
        }
    }

    if (atSign == NULL) {
        return 0;
    }

    for (i = x; i < tam; i++) {
        if (email[i] == '.') {
            point = email + i;
            break;
        }
    }

    if (point == NULL) {
        return 0;
    }
    if (point == atSign + 1) {
        return 0;
    }

    if (point + 1 == email + tam) {
        return 0;
    }

    return 1;
}


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

    int companyCode = -1, code = 0;


    if (companies.counter > 0) {

        companyCode = selectCompany(companies);

        if (companyCode != -1) {

            code = getInt(MIN_COMMENT_CODE, MAX_COMMENT_CODE, CODE_MSG);

            if (searchComment(*comments, code) == -1) {

                comments->comments[comments->counter].code = code;
                comments->comments[comments->counter].company_nif = companies.companies[companyCode].nif;

                readString(comments->comments[comments->counter].name, MAX_COMMENT_NAME, NAME_MSG);
                do{
                readString(comments->comments[comments->counter].email, MAX_COMMENT_EMAIL, COMMENT_EMAIL_MSG);
                }while((verifyEmail(comments->comments[comments->counter].email))!=1);
                
                readString(comments->comments[comments->counter].title, MAX_TITLE_SIZE, TITLE_MSG);
                readString(comments->comments[comments->counter].comment, MAX_COMMENT_SIZE, COMMENT_MSG);


                comments->comments[comments->counter].state = 1;

                return comments->counter++;

            } else {
                puts(ERROR_CODE_COMMENTS);
            }

        } else {
            puts(ERROR_NOT_EXIST_COMMENTS);
        }

    } else {
        puts(ERROR_EMPTY_COMMENTS);
    }

    return -1;
}

void createComments(Comments *comments, Companies companies) {

    if (companies.counter > 0) {
        if (comments->counter == comments->size) {
            expandCommentsCapacity(comments);
        }

        if (comments->counter < comments->size) {
            if (createComment(comments, companies) != -1) {
                puts(SUCCESS_CREATE_COMMENTS);
            }
        } else {
            puts(ERROR_INSERT_COMMENTS);
        }
    } else {
        puts(ERROR_EMPTY_COMMENTS);
    }

}

void loadComments(Comments *comments, char *file) {
    int i, sucesso = 0;

    FILE *fp = fopen(file, "rb");
    if (fp != NULL) {
        comments->counter = 0;

        fread(&(comments->counter), sizeof (int), 1, fp);

        if (comments->counter > 0) {
            comments->size = comments->counter;
            comments->comments = (Comment*) malloc(comments->counter * sizeof (Comment));
            for (i = 0; i < comments->counter; i++) {
                fread(&(comments->comments[i]), sizeof (Comment), 1, fp);
            }
            sucesso = 1;
        }

        fclose(fp);
    }

    if (!sucesso) {
        comments->comments = (Comment*) malloc(MAX_COMMENTS * sizeof (comments));
        comments->counter = 0;
        comments->size = MAX_COMMENTS;
    }
}

void saveComments(Comments *comments, char *file) {
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&(comments->counter), sizeof (int), 1, fp);

    for (i = 0; i < comments->counter; i++) {
        fwrite(&(comments->comments[i]), sizeof (Comment), 1, fp);
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

/**
 * Falta documentar
 * @param comment
 * @return 
 */
int isStateActive(Comment comment) {

    if (comment.state != 0) {
        return 0;
    }
    return -1;
}

void printComment(Comment comment) {

    printf("| ID - %-10d \n", comment.code);
    printf("| Author - %-20s\n", comment.name);
    printf("| Title - %-20s\n", comment.title);
    printf("| Text - %-20s\n", comment.comment);

}

void listComments(Comments *comments, Company company) {
    int i;

    if (hasComments(company, *comments) == 1) {

        if (comments->counter > 0) {
            printf(LINES1);
            for (i = 0; i < comments->counter; i++) {

                if (comments->comments[i].company_nif == company.nif) {

                    if (isStateActive(comments->comments[i]) == 0) {
                        printf(LINES2);
                        printComment(comments->comments[i]);
                        printf(LINES2);
                    }

                }

            }
            printf(LINES1);
        } else {

            puts(EMPTY_LIST);

        }
    } else {
        puts(ERROR_WITHOUT_COMMENTS);
    }


}

void hideComment(Company company, Comments *comments) {

    int commentPosition = -1, code = 0;

    if (hasComments(company, *comments) == 1) {

        code = getInt(MIN_COMMENT_CODE, MAX_COMMENT_CODE, CODE_MSG);
        commentPosition = searchComment(*comments, code);

        if (commentPosition != -1) {
            if (comments->comments[commentPosition].company_nif == company.nif) {
                if (isStateActive(comments->comments[commentPosition]) == 0) {
                    comments->comments[commentPosition].state = 0;
                    puts(SUCCESS_STATE_COMMENTS);
                } else {
                    puts(ERROR_STATE_COMMENTS);
                }
            } else {
                puts(ERROR_BELONG_COMMENT);
            }
        } else {
            puts(ERROR_COMMENT);
        }
    } else {
        puts(ERROR_WITHOUT_COMMENTS);
    }


}