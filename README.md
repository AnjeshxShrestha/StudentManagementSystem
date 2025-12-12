Student Management System (C Project)

This project is a simple console-based Student Management System written in C.
It allows users to add, search, update, delete, and display student records, with data stored in a binary file (students.dat) for persistence.

📌 Features

Add a new student

Search for a student by ID

Update existing student information

Delete a student record

Display all stored students

Auto-save and auto-load records using students.dat

Prevents duplicate student IDs

📁 File Storage

All records are saved in:

students.dat


The program saves automatically after:

Adding a student

Updating a student

Deleting a student

Records are loaded automatically when the program starts.

🧱 Data Structure
struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};


Records are stored in an array:

struct Student students[MAX];
int count = 0;

📌 Functions Overview
saveToFile()

Stores all current student records into students.dat using binary write.

loadFromFile()

Loads all saved records from students.dat into memory when the program starts.

searchStudent(int id)

Internal helper that returns:

index of the student if found

-1 if not found

Used by search, update, delete operations.

addStudent()

Adds a new student after checking:

Capacity limit

Duplicate ID

Automatically saves changes.

displayAll()

Prints every stored student record.

search()

User-facing search operation (wraps searchStudent()).

update()

Updates the name, age, and marks of a student identified by ID.

deleteStudent()

Deletes a student record and shifts the array to fill the gap.

main()

Runs the menu-driven interface:

1. Add Student
2. Search Student
3. Update Student
4. Delete Student
5. Display All Students
6. Exit

🔧 How to Compile

Use GCC:

gcc StudentManagementSystem.c -o student


Run:

./student

📌 Known Limitations

Maximum 100 students (because of the fixed array).

Names without spaces only (because scanf("%s") stops at spaces).

No input validation for malformed or out-of-range data.

Not using dynamic memory.

🚀 Possible Improvements

Use dynamic arrays or linked lists.

Accept names with spaces using fgets.

Add sorting options.

Add GPA calculation or additional fields.

Encrypt the data file.

Replace binary file with a text/JSON/SQLite database.
