/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   general.h
 * Author: Tania, Gonçalo, Tomas
 *
 * Created on 20 de dezembro de 2023, 17:49
 */

#ifndef GENERAL_H
#define GENERAL_H

/**
 * Função para escrever dados no programa
 * @param companies
 * @param branchs
 */
void martelaDados(Companies *companies, ActivityBranchs *branchs);

/**
 * Falta documentar - Guardar dados de memoria para ficheiro
 * @param companies
 * @param file
 */
void saveCompanies(Companies *companies, char *file);

/**
 * Falta documentar
 * @param branchs
 * @param file
 */
void saveBranchs(ActivityBranchs *branchs, char *file);

/**
 * Falta documentar
 * @param companies
 */
void freeCompanies(Companies *companies);

/**
 * Falta documentar
 * @param branchs
 */
void freeBranchs(ActivityBranchs *branchs);

/**
 * 
 * @param companies
 * @param file
 */
void loadCompanies(Companies *companies, char *file);
#endif /* GENERAL_H */

