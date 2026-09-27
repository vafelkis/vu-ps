#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
	char name[30];
	char surname[30];
	int course;
	double average;

	int load;
	char courses[10][30];
	int grades[10];

	char languages[100];

} Student;

int main(int argc, char *argv[])
{
	FILE *db = NULL;
	if (argc > 1)
		db = fopen(argv[1], "rb");
	else
		db = fopen("db.bin", "rb");

	if (db)
	{
		Student students[1000];
		int size = 0;

		fread(&size, sizeof(int), 1, db);

		for (int i = 0; i < size; i++)
		{
			fread(&students[i], sizeof(Student), 1, db);
		}
		printf("%d records loaded succesfully\n", size);

		int counterDemo = 0;

		for (int i = 0; i < size; ++i)
		{
			Student s = students[i];

			if (strstr(s.languages, "Lithuanian") != NULL)
			{
				++counterDemo;
				printf("%s\n%s\n%d\n%f\n%d\n", s.name, s.surname, s.course, s.average, s.load);
				for (int j = 0; j < s.load; ++j)
				{
					printf("%s\n%d\n", s.courses[j], s.grades[j]);
				}
				printf("%s\n\n", s.languages);
			}
		}
		printf("Filter applied, %d students found\n", counterDemo);
		fclose(db);
	}
	else
	{
		printf("File db.bin not found, check current folder\n");
	}

	return 0;
}