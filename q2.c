#include <stdio.h>
#include <string.h>

int main() {

    FILE *fp;

    char item[50];
    char location[50];
    char contact[20];

    char search[50];

    int n;
    int found = 0;

    // Open file in append mode
    fp = fopen("lostfound.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!");
        return 1;
    }

    printf("How many records do you want to add? ");
    scanf("%d", &n);
    getchar();

    // Add records
    for (int i = 0; i < n; i++) {

        printf("\nEnter item name: ");
        fgets(item, sizeof(item), stdin);
        item[strcspn(item, "\n")] = '\0';

        printf("Enter location: ");
        fgets(location, sizeof(location), stdin);
        location[strcspn(location, "\n")] = '\0';

        printf("Enter contact ID: ");
        fgets(contact, sizeof(contact), stdin);
        contact[strcspn(contact, "\n")] = '\0';

        fprintf(fp, "%s|%s|%s\n", item, location, contact);
    }

    fclose(fp);

    printf("\nRecords added successfully!\n");

    // Display all records
    fp = fopen("lostfound.txt", "r");

    if (fp == NULL) {
        printf("Error reading file!");
        return 1;
    }

    printf("\n--- ALL LOST AND FOUND RECORDS ---\n");

    while (fscanf(fp, " %49[^|]|%49[^|]|%19[^\n]",
                  item, location, contact) == 3) {

        printf("\nItem: %s\n", item);
        printf("Location: %s\n", location);
        printf("Contact ID: %s\n", contact);
    }

    fclose(fp);

    // Search for an item
    printf("\nEnter item name to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    fp = fopen("lostfound.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!");
        return 1;
    }

    while (fscanf(fp, " %49[^|]|%49[^|]|%19[^\n]",
                  item, location, contact) == 3) {

        if (strcmp(search, item) == 0) {

            printf("\n--- RECORD FOUND ---\n");
            printf("Item: %s\n", item);
            printf("Location: %s\n", location);
            printf("Contact ID: %s\n", contact);

            found = 1;
        }
    }

    if (found == 0) {
        printf("\nNo matching record found!\n");
    }

    fclose(fp);

    return 0;
}