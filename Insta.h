#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


typedef struct Cell{
	char *value=0;
	int version=0;
	Cell *next;
}Cell;

typedef struct Columns{
	char *name=0;
	Cell *cell;
	Columns *next;
}Columns;

typedef struct Rows{
	Columns *columns;
	int rowId=0;
	int commitVersion=0;
	Rows *next;
}Rows;

//Rows *rowHead = NULL;


struct tables
{
	char * tablename;
	struct Rows *rowHead;
	struct tables*next;
};

struct tables* table=NULL;
struct tables*currentTable = table;
//int nooftables = -1;

/*
void initializeTable()
{
	struct tables *newtable = (struct tables*)malloc(sizeof(struct tables));
	newtable->next = NULL;
	if (table == NULL)
	{
		table = newtable;
		currentTable = newtable;
	}
	else
	{
		currentTable->next =newtable;
	}
}
*/

 
void addTable()
{
	struct tables *newtable = (struct tables*)malloc(sizeof(struct tables));
	newtable->next = NULL;
	if (table == NULL)
	{
		table = newtable;
		currentTable = newtable;
	}
	else
	{
		currentTable->next = newtable;
		currentTable = newtable;
	}



	printf("enter table or schema name\n");
	char *c = (char *)malloc(100 * sizeof(char));
	scanf("%s", c);



	//++nooftables;
	
	currentTable->tablename = (char *)malloc(100 * sizeof(char));
	strcpy(currentTable->tablename, c);
	currentTable->rowHead = (struct Rows *)malloc(sizeof(struct Rows));
	currentTable->rowHead->rowId = 0;
	currentTable->rowHead->next = NULL;

}

struct tables* getTablePointer(char *tablename)
{
	int i=0;
	struct tables* temp=table;
	while (temp != NULL)
	{
		if (strcmp(temp->tablename, tablename) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	
	return NULL;
}

void saveToFile(struct tables *table)
{

}

void serialization()
{


}