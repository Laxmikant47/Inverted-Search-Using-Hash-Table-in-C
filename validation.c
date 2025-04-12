#include "head.h"

int validate(int argc, char *argv[], Slist **head)
{
    for (int i = 1; i < argc; i++)
    {
        char *ext = strrchr(argv[i], '.');      // it will return the add of string from .
        if (!ext || strcmp(ext, ".txt") != 0)   
        {
            printf("\nINFO: %s is not a .txt file\n", argv[i]);
            continue;
        }

        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("\nINFO: File %s not found\n", argv[i]);    
            continue;
        }

        fseek(fptr, 0, SEEK_END);    // check the contents of the file 
        if (ftell(fptr) == 0)
        {
            printf("\nINFO: %s is empty\n", argv[i]);
            fclose(fptr);
            continue;
        }
        fclose(fptr);

        // Check for duplicates
        Slist *temp = *head;
        int is_duplicate = 0; // for checking if the file is duplicate or not
        while (temp != NULL)
        {
            if (strcmp(argv[i], temp->file_name) == 0)
            {
                printf("\nINFO: Duplicate file %s not added.\n", argv[i]);
                is_duplicate = 1;
                break; // Stop checking once duplicate is found
            }
            temp = temp->link;
        }

        // If not a duplicate, add it to the list
        if (!is_duplicate)
        {
            if (insert_at_last(head, argv[i]) == SUCCESS) // file name adding to the list (insert at last)
            {
                printf("\nINFO: %s is added to the list successfully!\n", argv[i]);
            }
            else
            {
                printf("\nINFO: Error adding %s to the list!\n", argv[i]);
            }
        }
    }
    // print the list
    print_list(*head);
    return SUCCESS;
}
// validation for save database
int validation_for_save_DB(char * filename)
{
    char *str = strchr(filename, '.');
    if (str == NULL || strcmp(str, ".txt") != 0)
    {
        printf("\n\nINFO : The File %s is not in the formate of .txt\n\n", filename);
        return FAILURE;
    }
    return SUCCESS;
}


