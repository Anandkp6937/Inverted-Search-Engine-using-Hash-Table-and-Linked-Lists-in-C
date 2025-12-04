#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "main.h"

//to create database 
int createDatabase(Hasht*arr,int size);
//insert to hash table
int insertToHash(Hasht*arr,int index,char word[],char*fileName);

int  generateHash(Flist*head);

//to display hash table
int displayDatabase(Hasht*arr,int size);

#endif