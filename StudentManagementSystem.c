#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

struct Student students[MAX];
int count = 0;

/* -------- FUNCTION PROTOTYPES -------- */
void saveToFile();
void loadFromFile();
void addStudent();
void displayAll();
int searchStudent(int id);
void search();
void update();
void deleteStudent();
int isValidName(const char *name);

/* -------- SAVE DATA -------- */
void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");
    if (!fp) {
        printf("Error saving file.\n");
        return;
    }
    fwrite(students, sizeof(struct Student), count, fp);
    fclose(fp);
}

/* -------- LOAD DATA -------- */
void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp) {
        count = fread(students, sizeof(struct Student), MAX, fp);
        fclose(fp);
    }
}

/* -------- VALIDATE NAME -------- */
int isValidName(const char *name) {
    int hasAlpha = 0;

    for (int i = 0; name[i]; i++) {
        if (isalpha(name[i])) {
            hasAlpha = 1;
        } else if (name[i] == ' ') {
            continue;
        } else {
            return 0; // invalid character
        }
    }
    return hasAlpha;
}

/* -------- SEARCH BY ID -------- */
int searchStudent(int id) {
    for (int i = 0; i < count; i++)
        if (students[i].id == id)
            return i;
    return -1;
}

/* -------- ADD STUDENT -------- */
void addStudent() {
    if (count >= MAX) {
        printf("Limit reached.\n");
        return;
    }

    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    if (searchStudent(s.id) != -1) {
        printf("ID already exists.\n");
        return;
    }

    getchar(); // clear newline

    while (1) {
        printf("Enter Name: ");
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0';

        if (isValidName(s.name))
            break;

        printf("Invalid name. Use alphabets and spaces only.\n");
    }

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[count++] = s;
    saveToFile();

    printf("Student added successfully.\n");
}

/* -------- DISPLAY ALL -------- */
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

/* -------- SEARCH -------- */
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

/* -------- UPDATE -------- */
void update() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    int index = searchStudent(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    getchar(); // clear newline

    while (1) {
        printf("Enter new Name: ");
        fgets(students[index].name, sizeof(students[index].name), stdin);
        students[index].name[strcspn(students[index].name, "\n")] = '\0';

        if (isValidName(students[index].name))
            break;

        printf("Invalid name. Use alphabets and spaces only.\n");
    }

    printf("Enter new Age: ");
    scanf("%d", &students[index].age);

    printf("Enter new Marks: ");
    scanf("%f", &students[index].marks);

    saveToFile();
    printf("Student updated.\n");
}

/* -------- DELETE -------- */
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

/* -------- MAIN -------- */
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

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 0;
        }

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
