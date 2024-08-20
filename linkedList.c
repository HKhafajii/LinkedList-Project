
// Hassan Alkhafaji

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct LinkedList {

    int partNumber, quantity;
    float price;
    struct LinkedList* next;

} LinkedList;

void save(LinkedList *head) {

    FILE* file = fopen("Inventory.csv", "w");


    if (file == NULL) {
        printf("Error, couldn't open the file\n");
        exit(1);
    }

    fprintf(file, "Part Number, Quantity, Price\n");

    LinkedList *current = head;
    while (current != NULL) {
        fprintf(file, "%d, %d, %.2f\n", current->partNumber, current->quantity, current->price);
        current = current->next;
    }

    fclose(file);

}

void delete(LinkedList **head) {

    int partNumber;
    LinkedList *current = *head;
    LinkedList *previous = NULL;

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("Enter the part number of what you want to delete: ");
    scanf("%d", &partNumber);
    getchar();

    if ((*head)->partNumber == partNumber) {
        LinkedList *temp = *head;
        *head = temp->next;
        free(temp);
        return;
    } 

    while (current != NULL) {

        if (current->next == NULL) {
            previous->next = NULL;
            free(current);
            return;
        } else if (current->partNumber == partNumber) {
            LinkedList *temp = current->next;
            previous->next = current->next;
            free(temp);
            return;
        }
        previous = current;
        current = current->next;
    } // end of while loop
  
}

void insert(LinkedList **head) {
    LinkedList *newList = (LinkedList*)malloc(sizeof(LinkedList));
    LinkedList *current = *head;
    int partNumber, quantity;
    float price;

    if (newList == NULL) {
        printf("Error, couldn't allocate memory\n");
        exit(1);
    }

    printf("Enter part number: ");
    scanf("%d", &partNumber);
    getchar();
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    getchar();
    printf("Enter price: ");
    scanf("%f", &price);
    getchar();

    newList->partNumber = partNumber;
    newList->quantity = quantity;
    newList->price = price;

   if (*head == NULL) {
       *head = newList;
       return;
   } else if ((*head)->partNumber >= partNumber) {
        newList->next = *head;
        *head = newList;
        return;
   }
   
    while (current->next != NULL) {
        
         if (current->next->partNumber >= partNumber) {
            newList->next = current->next;
            current->next = newList;
            return;
        }
       current = current->next;

    }
    newList->partNumber = partNumber;
    newList->quantity = quantity;
    newList->price = price;
    newList->next = NULL;
    current->next = newList;
}

void select(LinkedList **head) {

    LinkedList *current = *head;
    int partNumber;

    printf("Enter a part number you'd like to select: ");
    scanf("%d", &partNumber);
    getchar();


    while (current != NULL) {
        if (current->partNumber == partNumber){
            printf("Part Number: %d\n", current->partNumber);
            printf("Quantity: %d\n", current->quantity);
            printf("Price: %.2f\n", current->price);
            break;
        } else {
            printf("Part number doesn't exist\n");
            break;
        }
        current = current->next;
    } // end of while loop

} // end of select function

void modify(LinkedList **head) {

    int partNumber;
    printf("Enter the part number of the structure you would like to modify: ");
    scanf("\n%d", &partNumber);

    LinkedList *current = *head;

    while (current != NULL) {
        if (current->partNumber == partNumber) {
            printf("Enter new quantity: ");
            scanf("\n%d", &current->quantity);
            printf("Enter new price: ");
            scanf("\n%f", &current->price);
            break;
        } 

        current = current->next;
    }

} // end of modify function

void help() {

printf("\nFunctions List:\ncreate\nprint\nselect\nmodify\ndelete\ninsert\nsave\nadd\nexit\nhelp\n");
} // end of help function

void printList(LinkedList *head) {

    LinkedList *current = head;

    while (current != NULL) {
        printf("Part Number: %d\n", current->partNumber);
        printf("Quantity: %d\n", current->quantity);
        printf("Price: %.2f\n", current->price);

        current = current->next;
    } // end of while loop
    printf("\n");

} // end of print function

void create(LinkedList **head) {

    int partNumber, quantity;
    float price;
    char cont = 'Y';

    while(cont != 'N') {
        LinkedList *newList = (LinkedList*)malloc(sizeof(LinkedList));
        if (newList == NULL) {
            printf("Error, couldn't allocate memory\n");
            exit(1);
        }
        printf("Enter part number: ");
            scanf("%d", &partNumber);
            getchar();
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            getchar();
            printf("Enter price: ");
            scanf("%f", &price);
            getchar();

        newList->partNumber = partNumber;
        newList->quantity = quantity;
        newList->price = price;
        newList->next = NULL;

        if (*head == NULL) {
            *head = newList;
        } else {
            LinkedList *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newList;
        }

        printf("Would you like to add another structure? (Y/N): ");
        scanf("%c", &cont);
        cont = toupper(cont);
    } // end of while loop

}

void add(LinkedList **head) {

    FILE *file = fopen("Inventory.csv", "r");
    float price;
    int partNumber, quantity;

    if (file == NULL) {
        printf("Error, couldn't open the file\n");
        exit(1);
    }

    char firstLine[100];

    fgets(firstLine, 100, file);

    LinkedList *current = NULL;
    LinkedList *previous = NULL;

    while (fscanf(file, "%d, %d, %f\n", &partNumber, &quantity, &price) != EOF) {
        current = (LinkedList*)malloc(sizeof(LinkedList));

        if (current == NULL) {
            printf("Error, couldn't allocate memory\n");
            exit(1);
        }

        current->partNumber = partNumber;
        current->quantity = quantity;
        current->price = price;
        current->next = NULL;

        if (*head == NULL) {
            *head = current;
        } else {
            previous->next = current;
        }

        previous = current;

    }

    if (previous != NULL) {
        previous->next = NULL;
    }

    fclose(file);
}

void clearList(LinkedList **head) {
    LinkedList *current = *head;
    LinkedList *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}

int main() {

    LinkedList *head = NULL;

    char command[10];
    
    int sentinel = 0;

    printf("\nWelcome, please get started with one of the commands below\n");
    help();
    printf("\nEnter a command: ");
    fgets(command, 10, stdin);
    command[strcspn(command, "\n")] = 0;

    while(sentinel != 1) {
    if (strcmp(command, "create") == 0) {   
        create(&head);
    } else if (strcmp(command, "print") == 0) {
        if (head != NULL) {
        printList(head);
        } else {
            printf("List is empty\n");
        }
    } else if (strcmp(command, "help") == 0) {
        help();
    } else if (strcmp(command, "select") == 0) {
        select(&head);
    } else if (strcmp(command, "insert") == 0) {
        insert(&head);
    } else if (strcmp(command, "modify") == 0) {
        modify(&head);
    } else if (strcmp(command, "delete") == 0) {
        delete(&head);
    } else if (strcmp(command, "save") == 0) {
        save(head);
        clearList(&head);
    } else if (strcmp(command, "add") == 0) {
        add(&head);
    } else if (strcmp(command, "exit") == 0) {
        printf("Have a good day\n");  
        exit(1);
    }  else {
        printf("Invalid command\n");
    }

    fflush(stdin);
    
    help();
    printf("\nEnter a command: ");
    fgets(command, 10, stdin);
    command[strcspn(command, "\n")] = 0;
    } // end of while loop

    return 0;
}