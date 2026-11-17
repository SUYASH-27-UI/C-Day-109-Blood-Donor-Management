
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Donor {
    int id;
    char name[50];
    char bloodGroup[10];
    char city[50];
    int age;
};

struct Donor donors[MAX];
int count = 0;

void loadDonors() {
    FILE *fp = fopen("donors.txt", "r");

    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d %49s %9s %49s %d",
                  &donors[count].id,
                  donors[count].name,
                  donors[count].bloodGroup,
                  donors[count].city,
                  &donors[count].age) == 5) {
        count++;
    }

    fclose(fp);
}

void addDonor() {
    if (count >= MAX) {
        printf("Donor limit reached!\n");
        return;
    }

    struct Donor d;
    d.id = count + 1;

    printf("Enter donor name (one word): ");
    scanf("%49s", d.name);

    printf("Enter blood group (e.g. O+): ");
    scanf("%9s", d.bloodGroup);

    printf("Enter city (one word): ");
    scanf("%49s", d.city);

    printf("Enter age: ");
    if (scanf("%d", &d.age) != 1 || d.age < 18 || d.age > 100) {
        printf("Invalid age. Donor must be 18 to 100.\n");
        return;
    }

    donors[count] = d;
    count++;

    FILE *fp = fopen("donors.txt", "a");

    if (fp == NULL) {
        printf("Unable to save donor!\n");
        count--;
        return;
    }

    fprintf(fp, "%d %s %s %s %d\n",
            d.id, d.name, d.bloodGroup, d.city, d.age);

    fclose(fp);

    printf("Donor added successfully! ID: %d\n", d.id);
}

void viewDonors() {
    if (count == 0) {
        printf("No donor records found.\n");
        return;
    }

    printf("\n===== DONOR LIST =====\n");

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", donors[i].id);
        printf("Name: %s\n", donors[i].name);
        printf("Blood Group: %s\n", donors[i].bloodGroup);
        printf("City: %s\n", donors[i].city);
        printf("Age: %d\n", donors[i].age);
    }
}

void searchByBloodGroup() {
    char group[10];
    int found = 0;

    printf("Enter blood group to search: ");
    scanf("%9s", group);

    printf("\nMatching donors:\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(donors[i].bloodGroup, group) == 0) {
            printf("ID: %d | Name: %s | City: %s\n",
                   donors[i].id,
                   donors[i].name,
                   donors[i].city);
            found = 1;
        }
    }

    if (!found)
        printf("No matching donors found.\n");
}

int main() {
    int choice;

    loadDonors();

    do {
        printf("\n===== BLOOD DONOR MANAGEMENT =====\n");
        printf("1. Add Donor\n");
        printf("2. View All Donors\n");
        printf("3. Search by Blood Group\n");
        printf("4. Total Donors\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addDonor();
                break;

            case 2:
                viewDonors();
                break;

            case 3:
                searchByBloodGroup();
                break;

            case 4:
                printf("Total Donors: %d\n", count);
                break;

            case 5:
                printf("Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
