#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char description[100];
    float amount;
    int n;

    // Create and open file in write mode
    fp = fopen("expenses.txt", "w");

    if (fp == NULL) {
        printf("Error opening file!");
        return 1;
    }

    printf("How many expenses do you want to enter? ");
    scanf("%d", &n);

    getchar(); // Remove newline from input buffer

    // Enter and save expenses
    for (int i = 0; i < n; i++) {

        printf("\nEnter expense description: ");
        fgets(description, sizeof(description), stdin);

        // Remove newline
        description[strcspn(description, "\n")] = '\0';

        printf("Enter amount: ");
        scanf("%f", &amount);
        getchar();

        // Write record into file
        fprintf(fp, "%s|%.2f\n", description, amount);
    }

    fclose(fp);

    printf("\nExpenses saved successfully!\n");

    // Open file in read mode
    fp = fopen("expenses.txt", "r");

    if (fp == NULL) {
        printf("Error reading file!");
        return 1;
    }

    printf("\n--- EXPENSE RECORDS ---\n");

    // Read and display records
    while (fscanf(fp, " %99[^|]|%f", description, &amount) == 2) {

        printf("Description: %s\n", description);
        printf("Amount: %.2f\n\n", amount);
    }

    fclose(fp);

    return 0;
}