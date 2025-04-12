
#include "head.h"

Hash_t h_table[28];

int create_DB(Slist *file_head)    //Function controls the create list operation
{
	if(file_head==NULL)     // check the list is empty or not
	{
		return EMPTYLIST;
	}
	while(file_head)     // if not empty read the contents of each file 
	{
		read_datafile(file_head,file_head->file_name);  // we have to pass head and file name 
        
		file_head=file_head->link;    // after reading move to the next node
	}
    return SUCCESS;
}

int read_datafile(Slist* file_head, char* file_name)
{
    char str[20]; //to fetch the words from the file
    int ind=0;  // to check the index
    int i=0;
    FILE* fptr = fopen(file_head->file_name, "r");  // open the file
    if(fptr == NULL)
    {
        perror("\nError opening file\n");
        return FILEOPENERROR;
    }
    while (fscanf(fptr, "%s", str) != EOF)  // it will get each word
    {
        i=0;
        while (str[i])
        {
            if(str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] += 32;   // convert into lower case 
            }
            i++;
        }
        // calculate index
        ind = str[0] - 97;   // we have to check for first later (0th index)
        if(ind > 25 || ind < 0)
        {
            if(isdigit(str[0]))  // for digit
            {
                ind = 26;
            }
            else            // for special char
            {
                ind = 27;
            }
        }
        if(ind >= 0 && ind <= 25)  // we have to add char (if char add to the main_node)
        {
            insert_at_last_main(&h_table[ind].link, str, file_head->file_name);   // we have to pass head, word and file name
        }
        else if (ind == 26)  // for digits
        {
            insert_at_last_main(&h_table[ind].link, str, file_head->file_name);   // we have to pass head, word and file name
        }
        else if (ind ==27)  // for special characters
        {
            insert_at_last_main(&h_table[ind].link, str, file_head->file_name);   // we have to pass head, word and file name
        }

    }
    fclose(fptr); // after completing we have to close the file
}

int insert_at_last_main(Main_t ** head, char* word, char* file_name)
{
    if(*head == NULL)  // if head is null we have to add the newnode
    {
        Main_t* newnode = malloc(sizeof(Main_t));
        if(newnode == NULL)
        {
            return FAILURE;
        }
        strcpy(newnode->word, word); // copy word 
        newnode->main_node_link = NULL;  // make main_node_link to NULL
        newnode->file_count = 1; // make file count to 1
        newnode->sub_node_link = NULL;   // make sub_node_link to NULL
        // create a sub node and update to main node
        update_sub_node(&newnode->sub_node_link, file_name);   // we have to pass sub_node_link, word and file_name
        update_word_count(&newnode, file_name);
        *head = newnode;  // update head with newnode
        return SUCCESS;
    }
    else   
    {
        Main_t* temp = *head;
        Main_t* prev = NULL;
        int flag = 0;
        while (temp)    // traverse the list to check if word is already exist
        {
            if(!strcmp(temp->word, word)) // if found
            {
                flag =1;
                // update file count if it is new file
                if(update_sub_node(&temp->sub_node_link, file_name) == UPDATEFILECOUNT)
                {
                    temp->file_count++;
                }
                update_word_count(&temp, file_name);
            }
            prev = temp;
            temp = temp->main_node_link;
        }
        if(!flag)
        {
            // If the Word is Not Found, Insert a New Node at the End
            Main_t* newnode = malloc(sizeof(Main_t));
            strcpy(newnode->word, word);
            newnode->main_node_link = NULL;
            newnode->file_count++;   
            newnode->sub_node_link = NULL;
            update_sub_node(&newnode->sub_node_link, file_name);
            update_word_count(&newnode, file_name);
            prev->main_node_link = newnode;  
        }
        return SUCCESS;
    }
}

int update_sub_node(Sub_t** sub_head, char* file_name)  // function to add file names and data into main hash tables
{
    if(*sub_head == NULL)
    {
        Sub_t* newnode = malloc(sizeof(Sub_t)); // create a new node 
        strcpy(newnode->f_name, file_name); // update file name to the new node file name member
        // newnode->word_count = 1;
        newnode->sub_node_link = NULL; // update sub node link to null
        *sub_head = newnode;
    }
    else
    {
        Sub_t* temp = *sub_head;
        Sub_t* prev = NULL;
        while(temp)
        {
            if(!strcmp(temp->f_name, file_name))
            {
                return SUCCESS;
            }
            prev = temp;
            temp = temp->sub_node_link;
        }
        Sub_t* newnode = malloc(sizeof(Sub_t));
        strcpy(newnode->f_name, file_name);
        newnode->sub_node_link = NULL;
        prev->sub_node_link = newnode;
        return UPDATEFILECOUNT;
    }
}

int update_word_count(Main_t **head, char *file_name)  //to update word count
{
	Sub_t *temp=(*head)->sub_node_link; // update link to temp
	while(temp)
	{
		if(!strcmp(temp->f_name, file_name))   // if file names are same 
		{
			temp->word_count++;  // inc the word count
			return SUCCESS;
		}
		temp=temp->sub_node_link;
	}
}

// display the database
#include "head.h"
int display_DB() {
    printf("....................................................................\n");
    printf("INDEX      WORD        FILE COUNT        file name        word count\n");
    printf("....................................................................\n");
    for (int i = 0; i < 28; i++) 
    {
        Main_t *temp = h_table[i].link;
        while (temp != NULL) 
        {
            printf("%-10d %-14s %-17d", i, temp->word, temp->file_count);// for main node
            Sub_t *temp2 = temp->sub_node_link;
            printf("%-17s %d\n", temp2->f_name, temp2->word_count);
            temp2 = temp2->sub_node_link;
            while (temp2 != NULL) 
            {
                printf("%49s %12d\n", temp2->f_name, temp2->word_count); // for sub node
                temp2 = temp2->sub_node_link;
            }
            temp = temp->main_node_link;
            printf("\n");
            }
    }
    return SUCCESS;
}
// functoin for seach word from the data base
void search(char *word)
{
    int flag=0;
    int index = get_indexed_hash(word); // get the index
    Main_t* temp = h_table[index].link; // table link to the temp 
    while(temp!=NULL)
    {
        if(strcmp(temp-> word,word)==0) // compare the words
        {
            flag = 1;
            Sub_t *temp_sub = temp->sub_node_link;
            while(temp_sub!=NULL)
            {
                printf("\nThe word %s exist in %s %d times\n",word,temp_sub->f_name,temp_sub->word_count);
                temp_sub = temp_sub->sub_node_link;
            }
            break;
        }
        temp = temp->main_node_link;
    }

    if(flag==0)
    {
        printf("\nThe Word %s does not exist in Database Files\n",word);  // if file is not present
    }
    printf("\n\n");
}

//save database function
int save_database(char *s)
{
    FILE *fptr = fopen(s,"w"); // open the file 
    if(fptr==NULL)
    {
        return FAILURE; // if null return failure
    }
    for(int i=0;i<28;i++)
    {
        Main_t *main_temp = h_table[i].link; // temp struct variable
        while(main_temp!=NULL)
        {
            fprintf(fptr,"#%d;%s;%d;",i,main_temp->word,main_temp->file_count); // for main node 
            Sub_t *sub_temp = main_temp->sub_node_link;
            while(sub_temp!=NULL)
            {
                fprintf(fptr,"%s;%d;",sub_temp->f_name,sub_temp->word_count);  // for sub node
                sub_temp = sub_temp->sub_node_link;
            }
            fprintf(fptr,"#\n");
            main_temp = main_temp->main_node_link;
        }
    }
    fclose(fptr); // close the file
    return SUCCESS;
}

int update_DB(Slist **head)   //Function to update data base from reading backup file
{
    char fname[20];
    printf("\nINFO : Enter the database file name in "".txt"" extension : ");
    scanf(" %s",fname);
    char *check;
	if((check= strstr(fname,".txt")) && !strcmp(check,".txt"))
    {
        FILE *fptr=fopen(fname,"r");
        if(fptr!=NULL)
        {
           char ch;
           fscanf(fptr," %c",&ch);
           if(ch=='#')
           {
			ch=0;
             fseek(fptr,-2,SEEK_END);
             fscanf(fptr," %c",&ch);
             if(ch=='#')
             {
                rewind(fptr);
                int ind;
                char str[250];
                while(fscanf(fptr,"%[^\n]",str)!=EOF)
                {
					ind=0;
                    char *res;
                    res=strtok(&str[1],";");
					int i=0;
					while(res[i])
					{
						ind =ind*10+res[i]-48;
						i++;
					}
                    char *word;
					word=strtok(NULL,";");
					char *count=strtok(NULL,"#;");
					int filecount=count[0]-48;
					char *fname;
					for(int i=0;i<filecount;i++)
					{
						fname=strtok(NULL,"#;");
						char *times=strtok(NULL,"#;");
						int time=times[0]-48;
						for(int j=0;j<time;j++)
						{
							insert_at_last_main(&h_table[ind].link,word,fname);
						}
						Slist *temp=*head;
						Slist *prev=NULL;
						while(temp)
						{
							if(!strcmp(temp->file_name,fname))
							{
								if(prev==NULL)
								{
									*head=(*head)->link;
									free(temp);
									break;
								}
								else
								{
									prev->link=temp->link;
									free(temp);
									break;
								}
							}
							prev=temp;
							temp=temp->link;
						}
						

					}
					char ch;
					fgetc(fptr);

                    
                }
				return SUCCESS;
                

             }
             else
              printf("\nINFO : Invalid Backup File\n");
           }
           else
           {
            printf("\nINFO : Invalid Backup File\n");
           }
        }
        else
        {
            printf("\nINFO : File Dosent Exists\n");
            return FAILURE;
        }
    }
    else
    return FAILURE;

	return FAILURE;

}



