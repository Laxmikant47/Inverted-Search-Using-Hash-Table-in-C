#include "head.h"

int insert_at_last(Slist **head, char* file_name)
{
	int i=0;
    Slist *new = malloc(sizeof(Slist));
        if(new == NULL)
        {
            return FAILURE;
        }
        // create a node
        strcpy(new->file_name, file_name);
        new->link = NULL;

        if(*head == NULL)
        {
            *head = new;
            return SUCCESS;
        }

        Slist *temp = *head; 
        while(temp->link !=NULL)
        {
            temp = temp->link;
        }

        temp->link = new;
        return SUCCESS;

}