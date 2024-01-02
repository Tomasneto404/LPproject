#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "branchs.h"
#include "companys.h"

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


