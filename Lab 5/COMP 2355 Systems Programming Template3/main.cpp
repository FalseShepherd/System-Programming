#define _CRT_SECURE_NO_WARNINGS
#include  <iostream>
	struct Student {
		int studentId;
		int assignmentGrades[4];
	};
	
	int main(int argc, char* argv[])
	{
		const int NUM_VALUES = 5;
		std::FILE * f = fopen("Students", "wb+");
		Student a[NUM_VALUES];
		for (int i = 0; i < NUM_VALUES; i++)
		{
			a[i].studentId = i;
		}
		int x = 0;

		printf("\nEnter 4 grades for %d ...\n", NUM_VALUES);
		for (int i = 0; i < NUM_VALUES; ++i) {
			printf("%d: ", i);
			scanf("%d", &(a[i].assignmentGrades[0]));
			printf("%d: ", i);
			scanf("%d", &(a[i].assignmentGrades[1]));
			printf("%d: ", i);
			scanf("%d", &(a[i].assignmentGrades[2]));
			printf("%d: ", i);
			scanf("%d", &(a[i].assignmentGrades[3]));
		}
		fwrite(a, sizeof(Student), NUM_VALUES, f);
		int fileNum = 0;
		long numBytesRead = 0;
		
		numBytesRead = fread(&fileNum, sizeof(int), 1, f);

		while (numBytesRead != 0) {
			printf("num: %d\n", fileNum);
			numBytesRead = fread(&fileNum, sizeof(int), 1, f);
		}
		fclose(f);

	}