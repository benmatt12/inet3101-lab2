// Ben Matthews (5788625)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nameLength 50       // Max length of part name
#define metricLength 10     // Max length of part size metric

// Record structure definition
typedef struct {
    int partNum;
    char partName[nameLength];
    float partSize;
    char partSizeMetric[metricLength];
    float partCost;
} Record;

// Global variables to store records and changes
Record* records = NULL; // Pointer to dynamically allocated array of records
int recordCount = 0;    // Track the number of records in the database
int changeCount = 0;    // Track the number of changes made in the database

// Print all records function
void printAllRecords() {
    if (recordCount == 0) {
        printf("\nNo records found.\n");
    } else {
        printf("\nPrinting all records...\n");
        for (int i = 0; i < recordCount; i++) {
            printf("\nRecord %d:\n", i + 1);
            printf("    Part Number: %d:\n", records[i].partNum);
            printf("    Part Name: %s\n", records[i].partName);
            printf("    Part Size: %.2f %s\n", records[i].partSize, records[i].partSizeMetric);
            printf("    Part Cost: $%.2f\n", records[i].partCost);
            printf("\n");
        }
    }
}

// Add record function
void addRecord() {
    // Resize records array to allow new record
    Record* temp = (Record*)realloc(records, (recordCount + 1) * sizeof(Record));
    if (temp == NULL) {
        printf("\nError: Unable to resize memory.\n");
        return;
    }
    records = temp;

    // Get part number
    printf("\nEnter part numnber: ");
    scanf("%d", &records[recordCount].partNum);

    // Get part name
    printf("\nEnter part name: ");
    getchar();
    fgets(records[recordCount].partName, nameLength, stdin);   // Get user part name input
    records[recordCount].partName[strcspn(records[recordCount].partName, "\n")] = '\0';   // Remove newline

    // Get part size
    printf("\nEnter part size: ");
    scanf("%f", &records[recordCount].partSize);

    // Get part size metric
    printf("\nEnter part size metric: ");
    getchar();
    fgets(records[recordCount].partSizeMetric, metricLength, stdin);   // Get user part size metric input
    records[recordCount].partSizeMetric[strcspn(records[recordCount].partSizeMetric, "\n")] = '\0';  // Remove newline

    // Get part cost
    printf("\nEnter part cost: ");
    scanf("%f", &records[recordCount].partCost);

    // Incrememnt record and change count
    recordCount++;
    changeCount++;
    printf("\nAdding record...\n");
}

// Delete last record function
void deleteLast() {
    if (recordCount > 0) {
        // Resize records array to delete last record
        Record* temp = (Record*)realloc(records, (recordCount - 1) * sizeof(Record));
        if (temp == NULL && recordCount > 1) {
            printf("\nError: Unable to resize memory\n");
            return;
        }
        records = temp;
        recordCount--;  // Decrement record count when deleting last record
        changeCount++;  // Increment change count
        printf("\nDeleting last record.\n");
    } else {
        printf("\nNo records to delete.\n");
    }
}

// Print size of the database function
void sizeOfDatabase() {
    size_t databaseSize = recordCount * sizeof(Record); // Calculate total memory used by records
    printf("\nSize of database: %zu bytes\n", databaseSize);
}

int main() {

    int userNum;    // Declare the int that will be used as the user input

    do {
        // Print out the record database menu
        printf("\n[ Parts Record Database ]\n");
        printf("\n1. Print all records\n");
        printf("2. Add record\n");
        printf("3. Delete the last record\n");
        printf("4. Print number of records\n");
        printf("5. Print database size\n");
        printf("6. Print number of changes\n");
        printf("7. Exit\n");

        // Allow the user to select one of seven options on the menu
        printf("\nEnter your selection (1-7): ");
        scanf("%d", &userNum);

        // Case statements that allow the user to interact with the menu
        switch (userNum) {
            default:
                // Allow the user to try again if an incorrect input was made
                printf("\nIncorrect input. Try again.\n");
                break;
            case 1:
                // Print all records in the database
                printAllRecords();
                break;
            case 2:
                // Add a record to the database
                addRecord();
                break;
            case 3:
                // Delete the last added record
                deleteLast();
                break;
            case 4:
                // Print the number of records in the database
                printf("\nNumber of records: %d\n", recordCount);
                break;
            case 5:
                // Print the size of the database
                sizeOfDatabase();
                break;
            case 6:
                // Print the number of changes made to the database
                printf("\nNumber of changes made: %d\n", changeCount);
                break;
            case 7:
                // Exit the menu
                printf("\nExitting...\n");
                break;
        }
    } while (userNum != 7); // Keep showing the user the menu after each selection except 7

    // Free dynamically allocated memory before exiting
    free(records);
    records = NULL;

    return 0;
}
