#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "API.h"

void insertRow(struct tables*ourtable){

	char choice, index = 0;

	char **columnNames = (char **)malloc(sizeof(char*)* MIN_SIZE);
	char **values = (char **)malloc(sizeof(char*)* MIN_SIZE);

	do{
		columnNames[index] = (char *)malloc(sizeof(char)* STRING_SIZE);
		values[index] = (char *)malloc(sizeof(char)* STRING_SIZE);


		printf("\nEnter column name: ");
		fflush(stdin);
		gets(columnNames[index]);

		printf("\nEnter value: ");
		fflush(stdin);
		gets(values[index]);

		index++;

		printf("\nDo you want to insert another column? [Y/N]");
		scanf("%c", &choice);

	} while (choice == 'y' || choice == 'Y');

	putData(ourtable,columnNames, values, index, -1);
}

void getRow(struct tables*ourtable){
	int id;

	printf("\nEnter the id: ");
	scanf("%d", &id);

	getData(ourtable,id);
}

void putRow(struct tables* ourtable){

	int id;
	printf("\nEnter id: ");
	scanf("%d", &id);

	char choice, index = 0;

	char **columnNames = (char **)malloc(sizeof(char*)* MIN_SIZE);
	char **values = (char **)malloc(sizeof(char*)* MIN_SIZE);

	do{
		columnNames[index] = (char *)malloc(sizeof(char)* STRING_SIZE);
		values[index] = (char *)malloc(sizeof(char)* STRING_SIZE);


		printf("\nEnter column name: ");
		fflush(stdin);
		gets(columnNames[index]);

		printf("\nEnter value: ");
		fflush(stdin);
		gets(values[index]);

		index++;

		printf("\nDo you want to insert another column? [Y/N]");
		scanf("%c", &choice);

	} while (choice == 'y' || choice == 'Y');

	putData(ourtable,columnNames, values, index, id);
}

void deleteRow(struct tables*ourtable){
	int id;

	printf("\nEnter id: ");
	scanf("%d", &id);

	deleteData(ourtable,id);
}

int main(){

	int choice;
	char ch;
	char * tablename;
	struct tables*ourtable=NULL;

	
	while (1){

		
			printf("1:add table\n");
			printf("2:login to table\n");
			printf("3:drop table\n");
			printf("4: Exit\n");
			

			printf("\n\nEnter your choice: ");
			fflush(stdin);
			scanf("%c", &ch);

			switch (ch)
			{
			case '1':
				addTable();
				printf("successfully added\n");
				break;
			case '2':
				
				printf("enter table schema name\n");

				tablename = (char *)malloc(100 * sizeof(char));
				scanf("%s", tablename);

				ourtable = getTablePointer(tablename);
				if (ourtable == NULL)
				{
					printf("no such table\n try after sometime\n");
					break;
				}


				printf("\n1. Insert Row");
				printf("\n2. Get Row Data");
				printf("\n3. Put Row Data");
				printf("\n4. Delete Row Data");
				printf("\n5. post\n");
				printf("\n6. getLatest posts\n");
				printf("\n7. Exit");
				printf("\n\nEnter your choice to handle table: ");
				fflush(stdin);
				scanf("%d", &choice);

				switch (choice){
				case 1: insertRow(ourtable);
					break;
				case 2: getRow(ourtable);
					break;
				case 3: putRow(ourtable);
					break;
				case 4: deleteRow(ourtable);
					break;
				case 5:
					addPost(tablename);
					break;
				case 6:
					getLatestPosts(tablename);
				case 7:
					saveToFile(ourtable);
					break;
				case 8: exit(1);
					break;
				default: printf("\nInvalid Option");
				}
				break;
			case '3':
				printf("failed droped\n");
				break;
			case '4':
				return 0;

			}
		
	}

	system("pause");
	return 0;
}