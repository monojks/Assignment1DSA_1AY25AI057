#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
 {
    int roll_no;
    char name[20];
    float marks;
};

void readStudent(struct Student *s)
 {
    printf("Enter roll number: ");
    scanf("%d", &s->roll_no);
    printf("Enter name (maximum 19 characters): ");
    scanf("%19s", s->name);
    printf("Enter marks: ");
    scanf("%f", &s->marks);
}

void printStudent(const struct Student *s) 
{
    printf("\nHighest-scoring student:\n");
    printf("Roll No : %d\n", s->roll_no);
    printf("Name    : %s\n", s->name);
    printf("Marks   : %.2f\n", s->marks);
}

int main(void)
{
    struct Student *ptr = NULL;
    struct Student *temp = NULL;
    struct Student *topper = NULL;
    int n = 0, i;
    float total = 0.0f, average = 0.0f;
    char choice;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0)
	{
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = (struct Student *)malloc(n * sizeof(struct Student));
    if (ptr == NULL) 
	{
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) 
	{
        printf("\nEnter details for student %d:\n", i + 1);
        readStudent(ptr + i);
    }

    topper = ptr;

    for (i = 0; i < n; i++) 
	{
        struct Student *current = ptr + i;

        total += current->marks;

        if (current->marks > topper->marks) 
		{
            topper = current;
        }
    }

    average = total / n;

    printf("\nAverage marks: %.2f\n", average);
    printStudent(topper);

    printf("\nDo you want to add 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') 
	{
        temp = (struct Student *)realloc(ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL) 
		{
            printf("Memory reallocation failed. Existing data is still valid.\n");
        } else 
		{
            ptr = temp;
            n = n + 2;

            for (i = n - 2; i < n; i++) 
			{
                printf("\nEnter details for student %d:\n", i + 1);
                readStudent(ptr + i);
            }

            total = 0.0f;
            topper = ptr;
            for (i = 0; i < n; i++) 
			{
                struct Student *current = ptr + i;

                total += current->marks;

                if (current->marks > topper->marks) 
				{
                    topper = current;
                }
            }

            average = total / n;

            printf("\nUpdated average marks: %.2f\n", average);
            printStudent(topper);
        }
    }
    free(ptr);
    ptr = NULL;

    return 0;
}
