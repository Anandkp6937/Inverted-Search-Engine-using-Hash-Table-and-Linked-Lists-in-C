#include "main.h"

Flist*head=NULL; //header pointer of file LL

int flag=0;
char fname[20];

// function to print the file list linked list
void printFlist(Flist*head){
     
     if(head==NULL){
        printf("nothing here! \n");
     }

     Flist*temp=head;
     printf("INFO: ");
     while(temp!=NULL){
          printf("%s",temp->data);
          printf(" ->");
          temp=temp->link;
     }

     printf(" NULL");



}

//function to add file name to LL
int  addToFlist(char* fileName,Flist**head){

     Flist*new=(Flist*)malloc(sizeof(Flist));//create new  list element
     
     if(new==NULL){
          return FAILURE;
     }

     new->data=fileName;
     new->link=NULL;

     if(*head==NULL){
          *head=new;
          return SUCCESS;
     }

    else{
     Flist*temp=*head;
     while(temp->link!=NULL){
          
          temp=temp->link;
     }
     temp->link=new;
     return SUCCESS;
    }
return FAILURE;
}

//function to check  file is duplicate 
int isFileDuplicate(char*fileName,Flist*head){
     if(head==NULL){
          return FAILURE;
     }

     Flist*temp=head;
     while(temp!=NULL){
          if(strcmp(temp->data,fileName)==0){
               return SUCCESS;
          }
          temp=temp->link;
     }
     return FAILURE;

}

//function to check  whether file exsist
int isFileExist(char*fileName){
     FILE*fptr=fopen(fileName,"r");
     if(fptr==NULL){
          return FAILURE;
     }
     return SUCCESS;

}


//function to check whether file have data or not
int isFileHaveData(char*fileName){
     FILE*fptr=fopen(fileName,"r");

     fseek(fptr,0,SEEK_END);
     long size=ftell(fptr);

     if(size>0){
     return SUCCESS;
     }
     else
     return FAILURE;



}

//function to check arguments given from console
int  checkArg(char*argv[],int argc){

     for(int i=1;i<argc;i++){
          char*fileName=argv[i];
          isText(fileName);
     }
          return SUCCESS;
}

//insert to hash table
int insertToHash(Hasht *arr, int index, char word[], char *fileName) {

    Mnode *temp = arr[index].mlink;

    
    if (temp == NULL) {

        Mnode *newM = malloc(sizeof(Mnode));
        Snode *newS = malloc(sizeof(Snode));

        strcpy(newM->word, word);
        newM->fileCount = 1;
        newM->Mlink = NULL;
        newM->Sublink = newS;

        strcpy(newS->fileName, fileName);
        newS->wordCount = 1;
        newS->slink = NULL;

        arr[index].mlink = newM;
        return SUCCESS;
    }

    //Search if the word already exists
    Mnode *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {

           
            Snode *tempsub = temp->Sublink;

          
            while (tempsub != NULL) {
                if (strcmp(tempsub->fileName, fileName) == 0) {
                    tempsub->wordCount += 1;      
                    return SUCCESS;
                }
                if (tempsub->slink == NULL) break;
                tempsub = tempsub->slink;
            }

            // File not found 
            Snode *newS = malloc(sizeof(Snode));
            strcpy(newS->fileName, fileName);
            newS->wordCount = 1;
            newS->slink = NULL;

            tempsub->slink = newS;

            temp->fileCount += 1;
            return SUCCESS;
        }

        prev = temp;
        temp = temp->Mlink;
    }

//     Word NOT found 
    Mnode *newM = malloc(sizeof(Mnode));
    Snode *newS = malloc(sizeof(Snode));

    strcpy(newM->word, word);
    newM->fileCount = 1;
    newM->Mlink = NULL;
    newM->Sublink = newS;

    strcpy(newS->fileName, fileName);
    newS->wordCount = 1;
    newS->slink = NULL;

    prev->Mlink = newM;

    return SUCCESS;
}

//create hash map
int  generateHash(Flist*head,Hasht*arr){
     int index;
     Flist*temp=head;
     char word[20];

   while(temp!=NULL){  
   
     FILE*fptr=fopen(temp->data,"r"); 

     while(fscanf(fptr,"%s",word)!=EOF){

       if(isalpha(word[0])){
          index=tolower(word[0])-'a';
       }   
       else{
          index=26;
       }
     insertToHash(arr,index,word,temp->data);
          
     }
     temp=temp->link;

   }

     return SUCCESS;
}


//create database 
int createDatabase(Hasht*arr,int size){
     for(int i=0;i<size;i++){
          arr[i].index=i;
          arr[i].mlink=NULL;
     }

     generateHash(head,arr);
}



//display database
int displayDatabase(Hasht*arr,int size){
        printf("\033[1;32m-----------------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
        printf("[ index_no] \t\t < Word > \t\t < file_count >  < file_name > \t\t < word_count >\t\n");
          printf("\033[1;32m-----------------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
          for (int i = 0; i < size; i++) {

    Mnode *tempM = arr[i].mlink;
     if(tempM!=NULL){
              printf("\033[32m[ %d ]\033[0m",arr[i].index);
    
     }
    while (tempM != NULL) {
        printf("\t\t%15s \t\t\t %d \t  file(s) :",tempM->word, tempM->fileCount);

        Snode *tempN = tempM->Sublink;
          printf(" file :");
        while (tempN != NULL) {
         
           printf(" \033[32m%s\033[0m : \033[32m%d\033[0m time(s) :",tempN->fileName,tempN->wordCount);

            tempN = tempN->slink;
        }

        printf("\n");
        tempM = tempM->Mlink;
        flag=0;
    }
}

          return SUCCESS;
}


//serach database
int searchDatabase(char str[], Hasht *arr)
{
    // convert first char to lowercase
    char ch = tolower(str[0]);

    int index;
    if (ch >= 'a' && ch <= 'z')
        index = ch - 'a';
    else
        index = 26;

    Mnode *temp = arr[index].mlink;

    while (temp != NULL)  
    {
        if (strcmp(temp->word, str) == 0)  
        {
            printf("\nWord \033[32m\" %s \"\033[0m found in \033[32m%d\033[0m files\n",
                str, temp->fileCount);

            Snode *tempS = temp->Sublink;

            while (tempS != NULL)
            {
                printf("In file \033[32m\" %s \"\033[0m %d time(s)\n",
                       tempS->fileName, tempS->wordCount);

                tempS = tempS->slink;
            }

            return SUCCESS;
        }

        temp = temp->Mlink;  
    }

    printf("\n\033[1;31mEntered word \" %s \" is not present in database \033[0m\n", str);
    return FAILURE;
}


//update database
int updateDatabase(Hasht*arr){
printf("Enter the file new name : ");
scanf("%s",fname);

if(isText(fname)==SUCCESS){
     
     Flist*temp=head;
     while(temp->link!=NULL){
          temp=temp->link;
     }
     generateHash(temp,arr);
}

}
int isText(char fileName[]){

     int count=0;
     int length=strlen(fileName);

     if(length>=4 && strcmp(fileName+(length-4),".txt")==0){
             
               // printf("INFO: Validated the file %s as .txt\n",file);

               //check if the .txt file exist or not
               if(isFileExist(fileName)==SUCCESS){
                    // printf("INFO:Validated %s is present \n",fileName);
                    
                    //check if the .txt file contain any data 
                    if(isFileHaveData(fileName)==SUCCESS){
                         // printf("INFO:Validated %s is not empty  \n",fileName);
                         //check if is it a duplicate ;if then ignore
                         if(isFileDuplicate(fileName,head)==FAILURE){
                              // printf("INFO: Validated  file dosen't have any copy \n");
                              if(addToFlist(fileName,&head)==SUCCESS){
                                   printf("\n\033[1;32mSucessfully added to list : %s\n\033[0m",fileName);
                                   printf("\n");
                                    count++;
                              }
                               
                         }
                         else{
                              printf("\033[1;31mERROR:The file %s is repeated \n\033[0m",fileName);
                              printf("so we are not adding to list\n");
                              printf("\n");
                         }
                          
                     }else{
                         printf("\033[1;31mERROR:The file %s dosen't have data\n\033[0m",fileName);
                          printf("so we are not adding to list\n");
                          printf("\n");
                     }}else{
                        printf("\033[1;31mERROR:The file %s is not present \n\033[0m",fileName);
                         printf("so we are not adding to list\n");
                         printf("\n");
                     }}else{
                       printf("\033[1;31mERROR:The file %s is not a text file\n\033[0m",fileName);
                              printf("so we are not adding to list\n");
                              printf("\n");
                     }

                     if(count==0){
                         return FAILURE;
                     }
                     
                     return SUCCESS;
}

//save to file
void saveToFile(char fname[],Hasht*arr,int size){
 int length=strlen(fname);
     if(length>=4 && strcmp(fname+(length-4),".txt")==0){
          FILE*fptr=fopen(fname,"w");
          for(int i=0;i<size;i++){
              Mnode *tempM = arr[i].mlink;

          if(tempM!=NULL){
               fprintf(fptr,"[ %d ]",arr[i].index);
          }
     while (tempM != NULL) {
        fprintf(fptr,"\t\t%15s \t\t\t %d \t  file(s) :",tempM->word, tempM->fileCount);
        Snode *tempN = tempM->Sublink;
          fprintf(fptr," file :");
        while (tempN != NULL) {
         
           fprintf(fptr,"%s %d  time(s) :",tempN->fileName,tempN->wordCount);

            tempN = tempN->slink;
        }

        fprintf(fptr,"\n");
        tempM = tempM->Mlink;
        flag=0;
    }
}
          fclose(fptr);
             printf("\n\033[1;32mINFO: file %s  created and updated sucessfully \n\033[0m \n",fname);
             printf("\n");
             printf("\033[1;32mINFO: Sucessfully created  backup  %s\n\033[0m \n",fname);
             
          }
         

     else{
          printf("Please enter a .txt file");
     }
             


}