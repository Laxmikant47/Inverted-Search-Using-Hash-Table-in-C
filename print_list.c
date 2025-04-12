#include "head.h"

void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("\nINFO : List is empty\n");
	}
    else
    {
		printf("\nINFO: Linked List Is: \n");
	    while (head)		
	    {
		    printf("%s -> ", head->file_name);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}