#ifndef IS_H
#define IS_H
#define SUCCESS 0
#define FAILURE -1
#define INVALID_COMMAND -2
#define FILE_IS_EMPTY -3
#define MAX_FILENAME_LENGTH 50
#define EMPTYLIST -4
#define UPDATEFILECOUNT -5
#define FILEOPENERROR -6

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


typedef struct node
{
	char file_name[MAX_FILENAME_LENGTH];
	struct node *link;
}Slist;

typedef struct subnode
{
	int word_count;
	char f_name[MAX_FILENAME_LENGTH];
	struct subnode * sub_node_link;
}Sub_t;

typedef struct mainnode
{
	int file_count;
	char word[30];
	struct mainnode * main_node_link;
	struct subnode * sub_node_link;
}Main_t;

typedef struct hash
{
	int index;
	struct mainnode * link;
}Hash_t;


int validate(int argc,char *argv[],Slist **head);

int insert_at_last(Slist **head, char* file_name);

int read_datafile(Slist* file_head, char* file_name);

void print_list(Slist *head);

int create_DB(Slist *file_head);

int insert_at_last_main(Main_t ** head, char* word, char* file_name);

int update_sub_node(Sub_t** sub_head, char* file_name);

int update_word_count(Main_t **head, char *file_name); 

int display_DB();

void search(char *word);

int get_indexed_hash(const char *word);

int validation_for_save_DB(char * filename);

int save_database(char *s);

int update_DB(Slist** head);

#endif