#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "user.h"

void martelaDados(Companies *companies, ActivityBranchs *branchs){
    /*SÓ DADOS DE TESTE*/
    /*COMPANIES*/
    companies->counter = 2;
    companies->companies[0].nif = 147147147;
    strcpy(companies->companies[0].name, "worten");
    companies->companies[0].postalCode = 4000000;
    companies->companies[0].category = 0;
    companies->companies[0].state = 1;
    strcpy(companies->companies[0].locality, "Lamoso");
    strcpy(companies->companies[0].street, "Rua das flores");
    companies->companies[0].branch = 1;

    companies->companies[1].nif = 258258258;
    strcpy(companies->companies[1].name, "Fnac");
    companies->companies[1].postalCode = 4000001;
    companies->companies[1].category = 0;
    companies->companies[1].state = 1;
    strcpy(companies->companies[1].locality, "Lamoso");
    strcpy(companies->companies[1].street, "Rua Alf. Neto");
    companies->companies[1].branch = 2;

    /*BRANCHS*/
    branchs->counter = 2;
    branchs->branchs[0].code = 1;
    branchs->branchs[0].state = 1;
    strcpy(branchs->branchs[0].name, "Agricultura");

    branchs->branchs[1].code = 2;
    branchs->branchs[1].state = 0;
    strcpy(branchs->branchs[1].name, "Eletricidade");
    /*SÓ DADOS DE TESTE*/
}

void saveCompanies(Companies *companies, char *file){
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    
    fwrite(&companies->counter, sizeof (int), 1, fp);
    
    for (i = 0; i < companies->counter; i++) {
        fwrite(&companies->companies[i], sizeof (Company), 1, fp);
    }
    
    fclose(fp);
}

void saveBranchs(ActivityBranchs *branchs, char *file){
    int i;

    FILE *fp = fopen(file, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&branchs->counter, sizeof (int), 1, fp);

    for (i = 0; i < branchs->counter; i++) {
        fwrite(&branchs->branchs[i], sizeof (ActivityBranch), 1, fp);
    }

    fclose(fp);
}

void freeCompanies(Companies *companies) {
    if (companies->companies) {
        free(companies);
    }

    companies = NULL;
}

void freeBranchs(ActivityBranchs *branchs) {
    if (branchs->branchs) {
        free(branchs);
    }

    branchs = NULL;
}

void loadCompanies(Companies *companies, char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fread(&companies->counter, sizeof(int), 1, fp);

    int i;
    for (i = 0; i < companies->counter; i++) {
        fread(&companies->companies[i], sizeof(Company), 1, fp);
    }

    fclose(fp);
}

void loadBranchs(ActivityBranchs *branchs, char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fread(&branchs->counter, sizeof(int), 1, fp);

    int i;
    for (i = 0; i < branchs->counter; i++) {
        fread(&branchs->branchs[i], sizeof(ActivityBranch), 1, fp);
    }

    fclose(fp);
}

