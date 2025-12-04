#ifndef MAIN_H
#define MAIN_H
//headers
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE -1

//Linked list to store the file name
typedef struct List{
char*data;
struct List*link;
}Flist;

//create subnode
typedef struct Sub{
     int wordCount;
     char fileName[20];
     struct Sub*slink;
}Snode;


//create main node 
typedef struct Main{
     int fileCount;
     char word[20];
     Snode*Sublink;
     struct Main*Mlink;

}Mnode;


//create the hash table 
typedef struct Hash{
int index;
Mnode*mlink;
}Hasht;

//checking the arguments 
int checkArg(char*argv[],int );

//to check whether the file exist or not
int isFileExist(char*fileName);

//to check whether the file have data present
int isFileHaveData(char*fileName);

//to check whether the file have any copy 
int isFileDuplicate(char*fileName,Flist*head);


//add the file name to list 
 int addToFlist(char*fileName,Flist**head);

//print Flist 
void printFlist(Flist*head);


//search database
int searchDatabase(char str[],Hasht*arr);

//validate
int validate(void);

//update database
int updateDatabase(Hasht*arr);

//chech if it is text file or not
int isText(char fileName[]);

//save to file
void saveToFile(char fname[],Hasht*arr,int size);

#endif