#include <stdio.h>
#include <string.h>

//structure to store student info
struct student {
    char name[50];
    int roll;
    float marks;
};

//functions which will be used in the menu
void addStudent();
void viewStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
int rollCheck(int rollToCheck);

int main() {
    int choice;
    
    //menu 
    while(1) {
        printf("<------ Student Management System ------>\n");
        printf("1) Add Student Information\n");
        printf("2) View Student Information\n");
        printf("3) Search Student Information\n");
        printf("4) Update Student Information\n");
        printf("5) Delete Student Information\n");
        printf("6) Exit!\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');  
        printf("Invalid input: please try again!\n");
        continue;
}


        switch(choice) {
            case 1: addStudent();
			break;
            case 2: viewStudent();
			break;
            case 3: searchStudent();
			break;
            case 4: updateStudent();
			break;
            case 5: deleteStudent();
			break;
            case 6: printf("Successfully Exited the program!\n");
			return 0;
            default: printf("Invalid Input! Try again.\n");
        }
    }
    return 0;
}

//function to add student info
void addStudent() {
    struct student s;
    FILE *fptr;
	fptr = fopen("student.txt", "a");

    if(fptr == NULL) {
        printf("Error: File cannot be opened!\n");
        return;
    }

    printf("Enter Name: ");
    scanf("%49s", s.name);
    printf("Enter Roll number: ");
    scanf("%d", &s.roll);

    if (rollCheck(s.roll)) {
        printf("Error: Roll number already exists!\n");
        fclose(fptr);
        return;
    }

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fptr, "%s %d %.2f\n", s.name, s.roll, s.marks);
    printf("Record successfully saved!\n");
    printf("------------------------------------------------\n");
    fclose(fptr);
}

//function to view student info
void viewStudent() {
    FILE *fptr; 
	fptr = fopen("student.txt", "r");
    if (!fptr) {
        printf("No records found (student.txt not present).\n");
        return;
    }

    struct student s;
    int found = 0;
    printf("\n<------ All Student Records ------>\n");
    while (fscanf(fptr, "%49s %d %f", s.name, &s.roll, &s.marks) == 3) {
        printf("Name: %-12s | Roll: %-4d | Marks: %.2f\n", s.name, s.roll, s.marks);
        found = 1;
    }

    if (!found) printf("No valid records in file.\n");
    printf("----------------------------------\n");
    fclose(fptr);
}

//function to search student info
void searchStudent() {
    FILE *fptr;
	fptr = fopen("student.txt", "r");
    if(fptr == NULL) {
        printf("No records found!\n");
        return;
    }

    int a;
    printf("Enter a Roll number to search: ");
    scanf("%d", &a);

    struct student s;
    while (fscanf(fptr, "%49s %d %f", s.name, &s.roll, &s.marks) == 3) {
        if (s.roll == a) {
            printf("\nRecord Found!\n");
            printf("Name: %s | Roll: %d | Marks: %.2f\n", s.name, s.roll, s.marks);
            printf("----------------------------------\n");
            fclose(fptr);
            return;
        }
    }
    printf("No student with that roll number found!\n");
    printf("----------------------------------\n");
    fclose(fptr);
}

//function used in update student info to check if the roll number exists or not
int rollCheck(int rollToCheck) {
    FILE *fptr;
	fptr = fopen("student.txt", "r");
    if (fptr == NULL)
        return 0;

    struct student s;
    while (fscanf(fptr, "%49s %d %f", s.name, &s.roll, &s.marks) == 3) {
        if (s.roll == rollToCheck) {
            fclose(fptr);
            return 1; 
        }
    }

    fclose(fptr);
    return 0; 
}

//function to update student info
void updateStudent() {
    FILE *fptr;
	fptr = fopen("student.txt", "r");
    FILE *temp;
	temp = fopen("temp.txt", "w");
    struct student s;
    int updated = 0;

    if (fptr == NULL) {
        printf("No records found!\n");
        return;
    }

    int target;
    printf("Enter roll number to update: ");
    scanf("%d", &target);

    while (fscanf(fptr, "%49s %d %f", s.name, &s.roll, &s.marks) == 3) {
        if (s.roll == target) {
            printf("\nRecord Found!\n");
            printf("Enter new Name: ");
            scanf("%49s", s.name);
            printf("Enter new Roll number: ");
            int newRoll;
            scanf("%d", &newRoll);

            if (newRoll != target && rollCheck(newRoll)) {
                printf("This roll number already exists!\n");
                fclose(fptr);
                fclose(temp);
                remove("temp.txt");
                return;
            }

            s.roll = newRoll;
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            fprintf(temp, "%s %d %.2f\n", s.name, s.roll, s.marks);
            printf("Record updated successfully!\n");
            updated = 1;
        } else {
            fprintf(temp, "%s %d %.2f\n", s.name, s.roll, s.marks);
        }
    }

    fclose(fptr);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (!updated)
        printf("No student found with the given roll number!\n");
}

//function to delete student info
void deleteStudent() {
	FILE *fptr;
	fptr = fopen("student.txt", "r");
		if(fptr == NULL) {
		printf("No records found!\n");
		return;
	}
	FILE *temp;
	temp = fopen("temp.txt", "w");
	struct student s;
	
	int target;
	printf("Enter the roll number you want to delete: ");
	scanf("%d", &target);
	
	while (fscanf(fptr, "%49s %d %f", s.name, &s.roll, &s.marks) == 3) {
		if(s.roll == target) {
			printf("\nRecord found and deleted successfully\n");
		} else {
		    fprintf(temp, "%49s %d %f", s.name, s.roll, s.marks);
		}
}
	fclose(fptr);
    fclose(temp);
    remove("student.txt");
    rename("temp.txt", "student.txt");
}


