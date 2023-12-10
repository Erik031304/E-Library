#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char name[50];
    char author[50];
    int pages;
    float price;
};

void displayBookInfo(struct Book book) {
    printf("Book Name: %s\n", book.name);
    printf("Author Name: %s\n", book.author);
    printf("Pages: %d\n", book.pages);
    printf("Price: %.2f\n", book.price);
}

void addBook(struct Book library[], int* bookCount) {
    if (*bookCount == MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    printf("Enter Book Name: ");
    scanf(" %49[^\n]", library[*bookCount].name);

    printf("Enter Author Name: ");
    scanf(" %49[^\n]", library[*bookCount].author);

    do {
        printf("Enter Pages (must be a positive number): ");
        scanf("%d", &library[*bookCount].pages);
        if (library[*bookCount].pages <= 0) {
            printf("Invalid input. Please enter a positive number of pages.\n");
        }
    } while (library[*bookCount].pages <= 0);

    do {
        printf("Enter Price (must be a positive number): ");
        scanf("%f", &library[*bookCount].price);
        if (library[*bookCount].price <= 0) {
            printf("Invalid input. Please enter a positive price.\n");
        }
    } while (library[*bookCount].price <= 0);

    printf("Book added successfully!\n");
    displayBookInfo(library[*bookCount]);

    (*bookCount)++;
}

void displayBooks(struct Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("Library is empty. Add books first.\n");
        return;
    }

    printf("\nBook Information:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Book %d:\n", i + 1);
        displayBookInfo(library[i]);
        printf("\n");
    }
}

void listBooksByAuthor(struct Book library[], int bookCount) {
    char author[50];
    printf("Enter the author name: ");
    scanf(" %49[^\n]", author);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].author, author) == 0) {
            printf("Book %d:\n", i + 1);
            displayBookInfo(library[i]);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found for author %s\n", author);
    }
}

void countBooks(int bookCount) {
    printf("Total number of books in the library: %d\n", bookCount);
}

void editBook(struct Book library[], int bookCount) {
    char bookName[50];
    printf("Enter the name of the book to edit: ");
    scanf(" %49[^\n]", bookName);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].name, bookName) == 0) {
            printf("Enter new information for the book:\n");

            printf("Enter Author Name: ");
            scanf(" %49[^\n]", library[i].author);

            do {
                printf("Enter Pages (must be a positive number): ");
                scanf("%d", &library[i].pages);
                if (library[i].pages <= 0) {
                    printf("Invalid input. Please enter a positive number of pages.\n");
                }
            } while (library[i].pages <= 0);

            do {
                printf("Enter Price (must be a positive number): ");
                scanf("%f", &library[i].price);
                if (library[i].price <= 0) {
                    printf("Invalid input. Please enter a positive price.\n");
                }
            } while (library[i].price <= 0);

            printf("Book information updated successfully!\n");
            displayBookInfo(library[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book with name %s not found.\n", bookName);
    }
}

void deleteBook(struct Book library[], int* bookCount) {
    char bookName[50];
    printf("Enter the name of the book to delete: ");
    scanf(" %49[^\n]", bookName);

    int found = 0;
    for (int i = 0; i < *bookCount; i++) {
        if (strcmp(library[i].name, bookName) == 0) {
            // Shift elements to remove the book
            for (int j = i; j < *bookCount - 1; j++) {
                library[j] = library[j + 1];
            }

            (*bookCount)--;
            printf("Book '%s' deleted successfully!\n", bookName);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book with name %s not found.\n", bookName);
    }
}

// Function to calculate the average number of pages in the library
float calculateAveragePages(struct Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("Library is empty. Add books first.\n");
        return 0.0;
    }

    int totalPages = 0;

    // Calculate the total number of pages
    for (int i = 0; i < bookCount; i++) {
        totalPages += library[i].pages;
    }

    // Calculate the average number of pages
    float averagePages = (float)totalPages / bookCount;

    return averagePages;
}

// Function to save library data to a file
void saveLibraryToFile(struct Book library[], int bookCount) {
    FILE* file = fopen("library.txt", "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s;%s;%d;%.2f\n", library[i].name, library[i].author, library[i].pages, library[i].price);
    }

    fclose(file);
    printf("Library data saved to library.txt\n");
}

int main() {
    struct Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice;

    do {
        printf("\nE-Library Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. List Books by Author\n");
        printf("4. Count Books\n");
        printf("5. Edit Book\n");
        printf("6. Delete Book\n");
        printf("7. Calculate Average Pages\n"); // Added option for average pages
        printf("8. Save Library to File\n");     // Added option for saving to a file
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBook(library, &bookCount);
            break;
        case 2:
            displayBooks(library, bookCount);
            break;
        case 3:
            listBooksByAuthor(library, bookCount);
            break;
        case 4:
            countBooks(bookCount);
            break;
        case 5:
            editBook(library, bookCount);
            break;
        case 6:
            deleteBook(library, &bookCount);
            break;
        case 7:
            printf("Average number of pages in the library: %.2f\n", calculateAveragePages(library, bookCount));
            break;
        case 8:
            saveLibraryToFile(library, bookCount);
            break;
        case 0:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

