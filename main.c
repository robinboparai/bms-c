#include "customer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;

    // Load existing data if available
    load_data("customers.dat");

    while (1) {
        // Main Menu
        printf("\n--- BANK MANAGEMENT SYSTEM ---\n");
        printf("1. Add Customer\n");
        printf("2. Display Customers\n");
        printf("3. Search Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Update Customer\n");
        printf("6. Sort Customers\n");
        printf("7. Save & Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: add_customer(); break;
            case 2: display_customers(); break;
            case 3: search_customer(); break;
            case 4: delete_customer(); break;
            case 5: update_customer(); break;
            case 6: sort_customers(); break;

            case 7:
                // Save data before exiting
                save_data("customers.dat");
                printf("Data saved. Exiting...\n");
                free(customers); // Free allocated memory
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}
