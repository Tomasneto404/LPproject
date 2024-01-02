/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   comments.h
 * Author: tomas
 *
 * Created on 2 de janeiro de 2024, 15:25
 */

#ifndef COMMENTS_H
#define COMMENTS_H

typedef struct{
    char name[256];
    char email[256];
    char comment[256];
    int state;
}Comment;

typedef struct{
    int counter,size;
    Comment *comments;
}Comments;

#endif /* COMMENTS_H */

