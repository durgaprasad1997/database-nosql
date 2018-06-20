#define STRING_SIZE 255
#define _CRT_SECURE_NO_WARNINGS
#define MIN_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "StructureFile.h"

void getData(struct tables * t, int id){
	Rows *tempNode = t->rowHead;
	int flag = 1;
	while (tempNode != NULL){
		if (tempNode->rowId == id){
			printDetails(tempNode);
			flag = 0;
			break;
		}
		tempNode = tempNode->next;
	}
	if (flag)
		printf("\n%d id not found", id);
}

void putData(struct tables * t,char **columnNames, char **values, int index, int id){

	Rows *tempRowNode = t->rowHead;
	while (tempRowNode != NULL){
		printf("%d", tempRowNode->rowId);

		if (tempRowNode->rowId == id){
			for (int i = 0; i < index; ++i)
				tempRowNode->columns = getColumnHead(tempRowNode->columns, columnNames[i], values[i]);
		}
		tempRowNode = tempRowNode->next;
	}



	tempRowNode = t->rowHead;
	Rows *newRowNode = createRowNode();
	for (int i = 0; i < index; ++i){
		newRowNode->columns = getColumnHead(newRowNode->columns, columnNames[i], values[i]);
	}
	if (t->rowHead == NULL){
		newRowNode->rowId = 1;
		newRowNode->commitVersion = 1;
		t->rowHead = newRowNode;
	}
	else{
		while (tempRowNode->next != NULL){
			tempRowNode = tempRowNode->next;
		}
		newRowNode->rowId = tempRowNode->rowId + 1;
		newRowNode->commitVersion = getCommitVersion(newRowNode);
		tempRowNode->next = newRowNode;
	}
}

void deleteData(struct tables * t,int id){

	Rows **tempNode1 = &t->rowHead, *prevNode = t->rowHead;
	Rows *tempNode = *tempNode1;

	if (tempNode->rowId == id)
	{
		t->rowHead = tempNode->next;
	}

	while (tempNode != NULL){
		if (tempNode->rowId != id){
				prevNode->next = tempNode->next;
			free(tempNode);
			break;
		}
		prevNode = tempNode;
		tempNode = tempNode->next;
	}
}


void addPost(char *tablename)
{
	int id;
	printf("enter your id\n");
	scanf("%d", &id);

	struct tables*t1=table;
	struct tables*t2 = t1->next;
	struct tables*t3 = t2->next;

	printf("%s  %s  %s\n", t1->tablename, t2->tablename, t3->tablename);

	while (t3 != NULL)
	{
		if (strcmp(t3->rowHead->next->rowId+"", id+"") == 0)
		{
			printf("enter your post\n");
			char * c = (char *)malloc(100 * sizeof(char *));
			scanf("%s", c);

			Cell *newcell = createCellNode();
			strcpy(newcell->value, c);

			//struct tables *t = (struct tables *)malloc(sizeof(struct tables));
		//	strcpy(t->tablename, t3->tablename);
			
			char **colsname = (char **)malloc(3*sizeof(char *));
			colsname[0] = (char *)malloc(100 * sizeof(char));
			strcpy(colsname[0], "id");
			colsname[1] = (char *)malloc(100 * sizeof(char));
			strcpy(colsname[1], "post");


			char **name = (char **)malloc(3 * sizeof(char *));
			name[0] = (char *)malloc(100 * sizeof(char));
			strcpy(name[0], id+"");
			name[1] = (char *)malloc(100 * sizeof(char));
			strcpy(name[1], c);


			putData(t3, colsname, name,3, id);
			
		}
	}

}


char* seperator(char** stringp, const char* delim)
{
	char* start = *stringp;
	char* p;

	p = (start != NULL) ? strpbrk(start, delim) : NULL;

	if (p == NULL)
	{
		*stringp = NULL;
	}
	else
	{
		*p = '\0';
		*stringp = p + 1;
	}

	return start;
}

void getLatestPosts(char *tablename)
{
	char * id=(char *)malloc(5*sizeof(char));
	printf("enter your id\n");
	scanf("%s", id);

	struct tables*t1 = table;
	struct tables*t2 = t1->next;
	struct tables*t3 = t2->next;

	//printf("%s  %s  %s\n", t1->tablename, t2->tablename, t3->tablename);

	char * followinglist = (char *)malloc(100 * sizeof(char));
	//scanf("%s", followinglist);
	char *token = (char *)malloc(100 * sizeof(char));

	while (t2 != NULL)
	{
		printf("%s ", t2->rowHead->next->columns->cell->value);


		if (strcmp(t2->rowHead->next->columns->cell->value, id)==0)
		{
			strcpy(followinglist, t2->rowHead->next->next->columns->cell->value);

			int id1=getIdByName(t1,followinglist);
			char*stringid = (char *)malloc(10 * sizeof(char));

			_itoa(id1, stringid, 10);
			while (t3 != NULL)
			{
				printf("\n%d  %d\n", t3->rowHead->next->columns->cell->value, stringid);
				if (strcmp(t3->rowHead->next->columns->cell->value ,stringid)==0)
				{
					Cell *c = (Cell *)malloc(sizeof(Cell));
					c = t3->rowHead->next->next->columns->cell;
					while (c != NULL)
					{
						printf("%s\n", c->value);

						c = c->next;
					}
				}

				t3 = t3->next;
			}
		}
		t2 = t2->next;
	}


}