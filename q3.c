#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book {
    int bookID;
    char title[50];
    char author[50];
    int copies;
};

// Function to read strings
void readString(char str[], int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

// Add a book
void addBook() {

    FILE *fp;
    struct Book b;
    int n;

    fp = fopen("books.dat", "ab");

    if (fp == NULL) {
        printf("File opening error!\n");
        return;
    }

    printf("How many books do you want to add? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {

        printf("\nEnter Book ID: ");
        scanf("%d", &b.bookID);
        getchar();

        printf("Enter Book Title: ");
        readString(b.title, 50);

        printf("Enter Author Name: ");
        readString(b.author, 50);

        printf("Enter Available Copies: ");
        scanf("%d", &b.copies);
        getchar();

        fwrite(&b, sizeof(struct Book), 1, fp);

        printf("Book added successfully!\n");
    }

    fclose(fp);
}

// Display all books
void displayBooks() {

    FILE *fp;
    struct Book b;

    fp = fopen("books.dat", "rb");

    if (fp == NULL) {
        printf("No book records available!\n");
        return;
    }

    printf("\n--- ALL BOOK RECORDS ---\n");

    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {

        printf("\nBook ID: %d\n", b.bookID);
        printf("Title: %s\n", b.title);
        printf("Author: %s\n", b.author);
        printf("Available Copies: %d\n", b.copies);
    }

    fclose(fp);
}

// Search book using ID
void searchBook() {

    FILE *fp;
    struct Book b;
    int id;
    int found = 0;

    fp = fopen("books.dat", "rb");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {

        if (b.bookID == id) {

            printf("\nBook Found!\n");
            printf("Book ID: %d\n", b.bookID);
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);
            printf("Available Copies: %d\n", b.copies);

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Book not found!\n");
    }

    fclose(fp);
}

// Update available copies
void updateBook() {

    FILE *fp;
    struct Book b;
    int id;
    int found = 0;

    fp = fopen("books.dat", "rb+");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to update: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {

        if (b.bookID == id) {

            printf("Current Copies: %d\n", b.copies);

            printf("Enter new number of copies: ");
            scanf("%d", &b.copies);

            // Move file pointer back to current record
            fseek(fp, -(long)sizeof(struct Book), SEEK_CUR);

            // Overwrite the existing record
            fwrite(&b, sizeof(struct Book), 1, fp);

            printf("Book updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Book not found!\n");
    }

    fclose(fp);
}

// Delete a book
void deleteBook() {

    FILE *fp, *temp;

    struct Book b;
    int id;
    int found = 0;

    fp = fopen("books.dat", "rb");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL) {
        printf("Temporary file error!\n");
        fclose(fp);
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp) == 1) {

        if (b.bookID == id) {

            found = 1;
            continue;
        }

        fwrite(&b, sizeof(struct Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (found == 1) {

        remove("books.dat");
        rename("temp.dat", "books.dat");

        printf("Book deleted successfully!\n");
    }
    else {

        remove("temp.dat");

        printf("Book not found!\n");
    }
}

// Main function
int main() {

    int choice;

    do {

        printf("\n===== LIBRARY BOOK RECORD SYSTEM =====\n");

        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                updateBook();
                break;

            case 5:
                deleteBook();
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}