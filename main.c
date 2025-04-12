/*
//  Name: Laxmikant
//  Title: Inverted (IS)
//  Date : 24/03/2025
//  Descrption : An Inverted Search system relies on an inverted index, a fundamental data structure used to enhance 
//               search efficiency in large text-based datasets, such as document retrieval systems and search engines.
//               This approach significantly optimizes search speed by mapping words or numbers to their respective locations
//               in a collection of documents, avoiding the need for exhaustive scanning.
*/
#include "head.h"

int main(int argc, char *argv[])
{
    int choice, crt_flag1=0, upd_flag2 =0;
    Slist* head = NULL;
    if(argc == 1)
    {
        printf("\nINFO: Unsufficient argument\nPlease pass the argument like a.out <txt\n");
        return -1;
    }    
    if(validate(argc, argv, &head) == SUCCESS) // validation for all files
    {
        printf("\nValidation succsessfull\n\n");
    }
    else
    {
        printf("\nValidation Failed\n\n");
    }
    
    do
    {
        printf("Menu:\n1. Create Database\n2. Display database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\nEnter Chaoice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            /* function for database */
                if(crt_flag1==0)
                {
                    if(create_DB(head)== EMPTYLIST)
                    {
                        printf("\nINFO : List is empty Database creation failed\n\n");
                    }
                    else
                    {
                        printf("\nINFO : Data Base Created Sccessfuly\n\n");
                        crt_flag1=1;
                        upd_flag2=1;
                    }
                }
                else
                    printf("\nINFO : Database Already created\n\n");
        break;
        case 2:
                // display the database
                display_DB();
        break;
        case 3:
            {
                // search the word
                char word[20];
                printf("\nINFO : Enter the word you want to search : ");
                scanf("%s",word);
                search(word);
            }
        break;
        case 4:
        {
            char file[50];
            printf("\nEnter the file name : ");
            scanf("%s", file);
            if(validation_for_save_DB(file)== SUCCESS) // validation for save database
            {
                if(save_database(file) == SUCCESS)
                {
                    printf("\nData base is saved to file successfully\n\n");
                }
                else
                {
                    printf("\nFile not saved\n\n");
                }
            }
            else
            {
                printf("\nValidation for save data base is failed\n\n");
            }
        }
        break;
        case 5:
        // update database
        if(crt_flag1==0 && upd_flag2==0)
        {
            if(update_DB(&head) ==SUCCESS)
            {
                printf("\nINFO : DataBase Updated Successfuly\n");
                upd_flag2=1;
            }
            else
            {
                printf("\nINFO : Update Database Failed\n");
            }
        }
        else
            printf("\nINFO : Already Updated\n\n");
        break;
        case 6:
                exit(1); // exit
        break;
        default:
            break;
        }
    } while (choice < 7);  // choice should be less than 7
    
    return 0;
}
