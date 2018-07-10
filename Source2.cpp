#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct column{
	char * data;
	struct column * next_col;
}; struct column * start = NULL;

struct row{
	char * userid;
	struct row * next_row;
	struct column * next_col;
}; struct row *start_row = NULL;

struct table_type{
	struct row *tabletorow;
	char * name;
	int max_cols;
	char ** column_names;
	struct table_type * next_table;
	int rowStart = 0;
}; struct table_type * start_table = NULL;


struct row* create_row( struct table_type * table)
{
	
	printf("\nEnter user id:\n");
	struct row * rows = (struct row *)malloc(sizeof(struct row));
	rows->userid = (char *)malloc(sizeof(char)*15);
	scanf("%s", rows->userid);
	rows->next_row = NULL;
	rows->next_col = NULL;
	printf("\nEnter data for following columns:\n");

	for (int i = 0; i < table->max_cols; i++)
	{
		printf("\nEnter data for column %s:\n", table->column_names[i]);
		struct column * col = (struct column *)malloc(sizeof(struct column));
		col->data = (char *)malloc(sizeof(char) * 30);
		col->next_col = NULL;
		char * str = (char*)malloc(sizeof(char) * 30);
		scanf("%s", str);
		strcpy(col->data, str);
		
		if (start == NULL)
		{
			start = col;
			rows->next_col = col;	
		}
		else
		{
			struct column * temp = start;
			while (temp->next_col != NULL)
				temp = temp->next_col;
			temp->next_col = col;
		}
	}
	start = NULL;
	//rows = start_row;


	return rows;
};

void print_all(struct table_type * table)
{
	struct row * rows = table->tabletorow;
	while (rows != NULL)
	{
		int i = 0;
		struct column * col = rows->next_col;
		while (col != NULL)
		{
			printf("%s -> %s	", table->column_names[i++], col->data);
			col = col->next_col;
		}
		printf("\n");
		rows = rows->next_row;
	}
}

void print_by_id(struct table_type * table, struct row * rows)
{
//	struct row * rows = table->tabletorow;
	while (rows != NULL)
	{
		int i = 0;
		struct column * col = rows->next_col;
		while (col != NULL)
		{
			printf("%s -> %s	", table->column_names[i++], col->data);
			col = col->next_col;
		}
		printf("\n");
		break;
		rows = rows->next_row;
	}
}

struct row * get_by_id(struct row* rows, char * id)
{
	while (rows != NULL)
	{
		int i = 0;
		if (strcmp(rows->userid, id) == 0)
			return rows;
		rows = rows->next_row;
	}
	return NULL;
}

struct table_type * createTable(char * name)
{
	struct table_type * newtable = (struct  table_type *)malloc(sizeof(struct table_type));
	newtable->name = (char *)malloc(sizeof(char) * 20);
	newtable->column_names = (char **)malloc(sizeof(char *)*25);
	newtable->max_cols = 0;
	newtable->tabletorow = NULL;
	newtable->next_table = NULL;
	strcpy(newtable->name, name);
	if (start_table == NULL)
	{
		start_table = newtable;
	}
	else
	{
		struct table_type * temp = start_table;
		while (temp->next_table != NULL)
			temp = temp->next_table;
		temp->next_table = newtable;
	}

	printf("Enter number of columns\n");
	int num;
	scanf("%d", &num);
	printf("Enter column names:");
	for (int i = 0; i < num; i++)
	{
		newtable->column_names[i] = (char *)malloc(sizeof(char) * 20);
		printf("Enter column %d:\n", i + 1);
		scanf("%s", newtable->column_names[i]);
	}
	newtable->max_cols = num;

	return newtable;
}
void insert_rows(struct table_type* table)
{
		//table->tabletorow = rows;
		while (1)
		{
			struct row * temp = create_row(table);
			if (table->tabletorow == NULL)
				table->tabletorow = temp;
			else
			{
				struct row * temp1 = table->tabletorow;
				while (temp1->next_row != NULL)
					temp1 = temp1->next_row;
				temp1->next_row = temp;
			}
			printf("\nPress 1 to create another user or 0 to exit.\n");
			int q;
			scanf("%d", &q);
			if (q == 0)
				break;
		}
	
}
struct table_type * selectTable()
{
	system("cls");

	printf("Enter the table 'name' you want to select:\n");
	struct table_type * tables = start_table;

	int i = 0;
	while (tables != NULL)
	{
		printf("%d.	%s\n", i + 1, tables->name);
		tables = tables->next_table;
		i++;
	}
	char tablename[20];
	scanf("%s", tablename);
	tables = start_table;
	while (tables != NULL)
	{
		if (strcmp(tables->name, tablename) == 0)
			break;
		tables = tables->next_table;
	}
	if (tables == NULL)
	{
		printf("\nTable not found, select Table which is available or create a new Table\n");
		printf("press any key to continue..");
		system("pause");
	}
	return tables;
}

char* concat(const char *s1, const char *s2)
{
	char *result = (char *)malloc(sizeof(char)*(strlen(s1) + strlen(s2) + 1));
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}
void dump_tables()
{
	struct table_type * temp = start_table;
	if (temp == NULL)
	{
		printf("No table found\n");
		system("pause");
		return;
	}
	char * filename = concat("tables", "_info.txt");
	FILE * fp = fopen(filename, "w");
	while (temp != NULL)
	{
		fprintf(fp, "%s\n", temp->name);
		temp = temp->next_table;
	}
	fclose(fp);
	temp = start_table;
	while (temp != NULL)
	{
		char * filename = concat(temp->name, "_info.txt");
		FILE * fp = fopen(filename, "w");
		fprintf(fp, "%d\n", temp->max_cols);
		for (int i = 0; i < temp->max_cols; i++)
			fprintf(fp,"%s\n", temp->column_names[i]);
		fclose(fp);
		temp = temp->next_table;
	}
	temp = start_table;
	while (temp != NULL)
	{
		for (int i = 0; i < temp->max_cols; i++)
		{
			char * filename = concat(temp->name, "_");
			filename = concat(filename, temp->column_names[i]);
			filename = concat(filename, ".txt");
			FILE * fp = fopen(filename, "w");
			struct row * temp_row = temp->tabletorow;
			while (temp_row != NULL){
				struct column * temp_col = temp_row->next_col;
				int k = 0;
				while (k != i && temp_col != NULL)
				{
					temp_col = temp_col->next_col;
					k++;
				}
				fprintf(fp, "%s\n", temp_col->data);
				temp_row = temp_row->next_row;
			}
			fclose(fp);
		}
		temp = temp->next_table;
	}
	system("cls");
	printf("Files dumped successfully.\n");
	system("pause");
}

//void retrieve_tables()
//{
//	FILE * fp = fopen("tables_info.txt", "r");
//	char * str = (char *)malloc(sizeof(char));
//
//	struct table_type * newtable = (struct  table_type *)malloc(sizeof(struct table_type));
//	newtable->name = (char *)malloc(sizeof(char) * 20);
//	newtable->column_names = (char **)malloc(sizeof(char *) * 25);
//	newtable->max_cols = 0;
//	newtable->tabletorow = NULL;
//	newtable->next_table = NULL;
//	strcpy(newtable->name, str);
//	if (start_table == NULL)
//	{
//		start_table = newtable;
//	}
//	else
//	{
//		struct table_type * temp = start_table;
//		while (temp->next_table != NULL)
//			temp = temp->next_table;
//		temp->next_table = newtable;
//	}
//
//	char * filename = (char *)malloc(sizeof(char) * 20);
//	filename = concat(str, "_info.txt");
//	FILE * fp2 = fopen(filename, "r");
//	fgets(str, 1000, fp);
//}
int main()
{
	struct table_type * tables = (struct table_type *)malloc(sizeof(struct table_type));
	//start_table = NULL;
	while (1)
	{	
		init:
		system("cls");

		printf("1.	Create a Table\n");
		printf("2.	Insert into the table\n");
		printf("3.	Query to insert into table\n");
		printf("4.	Get row by id\n");
		printf("5.	Delete a row by id\n");
		printf("6.	Print table\n");
		printf("7.	Dump tables into files\n");
		printf("8.	Exit\n");

		printf("\nEnter your choice:\n\n");
		int q;
		scanf("%d", &q);
		switch (q)
		{
		case 1:	
			system("cls");
			printf("Enter Table name:\n");
			char tableName[20];
			scanf("%s", tableName);
			tables= start_table;
			while (tables != NULL)
			{
				if (strcmp(tables->name, tableName) == 0)
				{
					printf("\nTable already exists! Please take another name.\n");
					system("pause");
					goto init;
				}
				tables = tables->next_table;
			}
	
			tables = createTable(tableName);
			printf("Table created successfully\n");
			//printf("Enter any key to continue...\n");
			system("pause");
			break;
		case 2: 
		    tables = selectTable();
			if (tables == NULL)
				goto init;
			if (tables == NULL)
				break;
			insert_rows(tables);
			break;
		case 3:	
			break;
		case 4:
			system("cls");
			tables = selectTable();
			if (tables == NULL)
				goto init;
			char id[20];
			printf("\nName id to get the row by id\n");
			scanf("%s", id);
			struct row * temprow;
			temprow = get_by_id(tables->tabletorow, id);
			if (temprow == NULL)
			{
				printf("ID not found.\n");
				printf("Press any key to continue...\n");
				system("pause");
				break;
			}
			else
				print_by_id(tables, temprow);
			system("pause");
			break;
		case 5: //delete_by_id();
			break;
		case 6:
			tables = selectTable();
			if (tables == NULL)
				goto init;
			print_all(tables);
			system("pause");
			break;
		case 7:	dump_tables();
			break;
		case 8: exit(0);
		default: printf("enter valid input\n");
			break;
		}
	}

	fflush(stdin);
	//cin.get();
	return 0;
}