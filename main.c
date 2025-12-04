//including headers required
#include<stdio.h>
#include<string.h>
#include "main.h"
#include "controller.h"
char go;
char newFile[20];
int validate()
{
    char go;
    printf("\n");
    printf("Do you want to continue ? press (y/n) : ");
    scanf(" %c", &go);

    go = tolower(go);  // convert user input

    if (go == 'y')
        return 1;

    if (go == 'n')
        return 0;

    // invalid input
    printf("Enter a valid choice ");
    return 2;
}

int main(int argc,char*argv[]){
     int choice;
     Hasht arr[27];

//check if the argumnets are .txt if not move to other 
int count=0;
char str[20];

printf("INFO: Validating of files started..\n");
printf("\n");
if(checkArg(argv,argc)==SUCCESS){
     printf("\nINFO: Sucessfully validated text files\n");
     while(1){
     printf("\n");
    printf("\033[1;32m--------------------------------------------------------\033[0m\n");
    printf("\t\t INVERTED SEARCH \t\t");
     printf("\n\033[1;32m--------------------------------------------------------\033[0m\n");
    printf("\033[1;37m 1.Create database \n\033[0m");
         printf("\033[1;37m 2.Display database \n\033[0m");
       printf("\033[1;37m 3.Search database \n\033[0m");
         printf("\033[1;37m 4.Update database \n\033[0m");
           printf("\033[1;37m 5.Save database \n\033[0m");
             printf("\033[1;37m 6.Exit  \n\033[0m");
           printf("\n\033[1;32m--------------------------------------------------------\033[0m\n");




          printf("\n");
          printf("Enter your choice: ");
          scanf("%d",&choice);

          // swicth case  validation
          switch(choice){
               case 1:
               printf("\n");
               printf("Sucessfully created  Database \n");
               if(createDatabase(arr,27)==FAILURE){
                    printf("ERROR: Creating database \n");
               }
               break;
               case 2:
               printf("\n");
               printf("Displaying database...\n");
               displayDatabase(arr,27);
               break;

               case 3:
               printf("\n");
               printf("Enter the word you want to search: ");
               scanf("%s",str);
               searchDatabase(str,arr);
               break;

               case 4:
               printf("\n");
               updateDatabase(arr);
               break;
               
               case 5:
               printf("\n");
               printf("Enter the new file name : ");
               scanf("%s",newFile);
               saveToFile(newFile,arr,27);
               break;
               default:
               printf("Wrong choice \n");
          }
          int res;
          do{
              res=validate();
          }while(res ==2);

         
          if (res == 0)
          return 0; 
         

          


     }


}
}