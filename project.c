#include <stdio.h>
#include <string.h>

int total=0;
int balance;

typedef struct {
    int id;
    char name[50];
    float age;
    int price; 
} Bird;

void addBird(Bird birds[], int *count) {
    printf("\n--- Add Bird ---\n");
    Bird newBird;
    
    if(balance>0){
    printf("Enter Bird ID: ");
    scanf("%d", &newBird.id);
    printf("Enter Bird name: ");
    scanf(" %s", newBird.name);
    printf("Enter Bird's age: ");
    scanf("%f", &newBird.age);
    printf("Enter Bird's Price: ");
    scanf("%d", &newBird.price);
    total++;
    balance=balance-newBird.price;
    birds[(*count)++] = newBird;
    printf("New Bird added successfully.\n");
    printf("total bird = %d\n",total);
    printf("Your balace = %d",balance);
    }
    else{
        printf("Your don't have money\n");
        printf("Your balace = %d",balance);
    }
    
}

void searchBird(const Bird birds[], int count) {
    printf("\n--- Search Bird ---\n");
    int id;
    char name[50];
    int found = 0;

    printf("Enter Bird ID or variety name to find the bird: ");
    scanf(" %s", name);

    if (sscanf(name, "%d", &id)==1) {
        for (int i = 0; i < count; i++) {
            if (birds[i].id == id) {
                printf("Bird Found: ID: %d, Name: %s, Age: %f, Price: %d\n",
                       birds[i].id, birds[i].name, birds[i].age, birds[i].price);
                found = 1;
                break;
            }
        }
    } else {
        for (int i = 0; i < count; i++) {
            if (strcmp(birds[i].name, name) == 0) {
                printf("Bird Found: ID: %d, Name: %s, Age: %f, Price: %d\n",
                       birds[i].id, birds[i].name, birds[i].age, birds[i].price);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Bird not available.\n");
    }
}

void displayAllbirds(const Bird birds[], int count) {
    printf("\n--- All ---\n");

    if (count == 0) {
        printf("No bird available.\n");
        return;
    }
    for (int i=0; i < total; i++)
    {
        printf("All birds : %d. ID: %d, Name: %s, Age: %.f, Price: %d\n",i+1, birds[i].id, birds[i].name, birds[i].age, birds[i].price);
    }
    printf("total bird = %d",total);
    }

void manageFile(Bird birds[], int *count, int save) {
    FILE *file;
    if (save) {
        file = fopen("project.txt", "w");
        if (!file) {
            printf("Could not open file for writing.\n");
            return;
        }

        fprintf(file, "%d\n", *count);
        for (int i = 0; i < *count; i++) {
            fprintf(file, "%d %s %f %d\n", 
                    birds[i].id, birds[i].name,
                    birds[i].age, birds[i].price
                    );
        }

        fclose(file);
    } else {
        file = fopen("project.txt", "r");
        if (!file) {
            printf("Could not open file for reading.\n");
            return;
        }

        fscanf(file, "%d", count);
        for (int i = 0; i < *count; i++) {
            fscanf(file, "%d %s %f %d", 
                   birds[i].id, birds[i].name,
                    birds[i].age, birds[i].price);
        }

        fclose(file);
    }
}

int main() {
    Bird birds[100]; 
    int count = 0;         
    int Enter;

    manageFile(birds, &count, 0); 
    printf("Enter Your Budget: ");
    scanf("%d",&balance);
    do {
        printf("\n--- Aviary Management Menu ---\n");
        printf("1. Buy Bird\n");
        printf("2. Search Bird\n");
        printf("3. Display All Bird\n");
        printf("4. Exit\n");
        printf("What do you want to do: ");
        scanf("%d", &Enter);

        if (Enter == 1) {
            addBird(birds, &count); 
        } else if (Enter == 2) {
            searchBird(birds, Enter); 
        } else if (Enter == 3) {
            displayAllbirds(birds, Enter); 
        } else if (Enter == 4) {
            printf("Exiting app. Goodbye!\n");
            manageFile(birds, &Enter, 1);
        } else {
            printf("Not found. Try again.\n");
        }

    } while (Enter != 4);

    return 0;
}