#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

struct Student students[MAX];
int count = 0;

// ---- FUNCTION PROTOTYPES ----
void saveToFile();
void loadFromFile();
void addStudent();
void displayAll();
int searchStudent(int id);
void search();
void update();
void deleteStudent();


// ---- SAVE DATA TO FILE ----
void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }
    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
}


// ---- LOAD DATA FROM FILE ----
void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp != NULL) {
        count = fread(students, sizeof(struct Student), MAX, fp);
        fclose(fp);
    }
}


// ---- SEARCH STUDENT BY ID (USED INTERNALLY) ----
int searchStudent(int id) {
    for (int i = 0; i < count; i++)
        if (students[i].id == id)
            return i;
    return -1;
}


// ---- ADD STUDENT ----
void addStudent() {
    if (count >= MAX) {
        printf("Limit reached.\n");
        return;
    }

    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    if (searchStudent(s.id) != -1) {
        printf("ID %d is already taken.\n", s.id);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[count++] = s;
    saveToFile();
    printf("Student added successfully.\n");
}


// ---- DISPLAY ALL STUDENTS ----
void displayAll() {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nAge: %d\nMarks: %.2f\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].marks);
    }
}


// ---- SEARCH STUDENT (USER OPTION) ----
void search() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    int index = searchStudent(id);
    if (index == -1) {
        printf("Student not found.\n");
    } else {
        printf("ID: %d\nName: %s\nAge: %d\nMarks: %.2f\n",
               students[index].id,
               students[index].name,
               students[index].age,
               students[index].marks);
    }
}


// ---- UPDATE STUDENT ----
void update() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    int index = searchStudent(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new Name: ");
    scanf("%s", students[index].name);
    printf("Enter new Age: ");
    scanf("%d", &students[index].age);
    printf("Enter new Marks: ");
    scanf("%f", &students[index].marks);

    saveToFile();
    printf("Student updated.\n");
}


// ---- DELETE STUDENT ----
void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    int index = searchStudent(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < count - 1; i++)
        students[i] = students[i + 1];

    count--;
    saveToFile();
    printf("Student deleted.\n");
}


// ---- MAIN PROGRAM ----
int main() {
    loadFromFile();
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Display All Students\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: search(); break;
            case 3: update(); break;
            case 4: deleteStudent(); break;
            case 5: displayAll(); break;
            case 6: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
