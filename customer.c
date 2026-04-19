#include "customer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
Customer *customers = NULL;
int count = 0;
int capacity = 0;

// Clears the input buffer to prevent issues with fgets after scanf
void clear_input_buffer() {
    while (getchar() != '\n');
}

// Loads customer data from a binary file
void load_data(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;

    fread(&count, sizeof(int), 1, fp);
    capacity = count;

    customers = (Customer*)malloc(capacity * sizeof(Customer));
    fread(customers, sizeof(Customer), count, fp);

    fclose(fp);
}

// Saves customer data to a binary file
void save_data(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error saving file!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(customers, sizeof(Customer), count, fp);

    fclose(fp);
}

int find_customer_by_id(int id) {
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id)
            return i;
    }
    return -1;
}

// Adds a new customer
void add_customer() {
    Customer c;

    printf("Enter ID: ");
    scanf("%d", &c.id);
    clear_input_buffer();

    if (find_customer_by_id(c.id) != -1) {
        printf("ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    printf("Enter Address: ");
    fgets(c.address, sizeof(c.address), stdin);
    c.address[strcspn(c.address, "\n")] = 0;

    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    printf("Enter Balance: ");
    scanf("%lf", &c.balance);
    clear_input_buffer();

    if (count >= capacity) {
        capacity = (capacity == 0) ? 10 : capacity * 2;
        customers = realloc(customers, capacity * sizeof(Customer));
    }

    customers[count++] = c;

    printf("Customer added successfully!\n");
}

// Displays all customers
void display_customers() {
    if (count == 0) {
        printf("No customers available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nPhone: %s\nAddress: %s\nEmail: %s\nBalance: %.2lf\n",
               customers[i].id,
               customers[i].name,
               customers[i].phone,
               customers[i].address,
               customers[i].email,
               customers[i].balance);
    }
}

//Updates a customer
void update_customer() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();

    int index = find_customer_by_id(id);

    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    Customer *c = &customers[index];
    char buffer[100];

    printf("\nPress Enter to keep existing value.\n");

    //Update fields, if only below inputs are provided//

    // Name
    printf("Enter new Name (%s): ", c->name);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(c->name, buffer);
    }

    // Phone
    printf("Enter new Phone (%s): ", c->phone);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(c->phone, buffer);
    }

    // Address
    printf("Enter new Address (%s): ", c->address);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(c->address, buffer);
    }

    // Email
    printf("Enter new Email (%s): ", c->email);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(c->email, buffer);
    }

    // Balance
    printf("Enter new Balance (%.2lf): ", c->balance);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        double newBalance;
        if (sscanf(buffer, "%lf", &newBalance) == 1 && newBalance >= 0) {
            c->balance = newBalance;
        } else {
            printf("Invalid balance input. Keeping old value.\n");
        }
    }

    printf("Customer updated successfully!\n");
}

//Searches and displays a customer by ID
void search_customer() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    int index = find_customer_by_id(id);

    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }

    printf("\nID: %d\nName: %s\nPhone: %s\nAddress: %s\nEmail: %s\nBalance: %.2lf\n",
           customers[index].id,
           customers[index].name,
           customers[index].phone,
           customers[index].address,
           customers[index].email,
           customers[index].balance);
}

// Deletes a customer and shifts array
void delete_customer() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    int index = find_customer_by_id(id);

    if (index == -1) {
        printf("Customer not found!\n");
        return;
    }
        // Shift elements left to fill the gap
    for (int i = index; i < count - 1; i++) {
        customers[i] = customers[i + 1];
    }

    count--;

    printf("Customer deleted successfully!\n");
}

// sorting helpers
int compare_asc(const void *a, const void *b) {
    Customer *c1 = (Customer*)a;
    Customer *c2 = (Customer*)b;

    if (c1->id < c2->id) return -1;
    if (c1->id > c2->id) return 1;
    return 0;
}

int compare_desc(const void *a, const void *b) {
    Customer *c1 = (Customer*)a;
    Customer *c2 = (Customer*)b;

    if (c1->id > c2->id) return -1;
    if (c1->id < c2->id) return 1;
    return 0;
}

// sorting (qsort) by ID
void sort_customers() {
    if (count == 0) {
        printf("No customers to sort.\n");
        return;
    }

    int choice;
    printf("\nSort by ID:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_input_buffer();

    if (choice == 1) {
        qsort(customers, count, sizeof(Customer), compare_asc);
        printf("Sorted in ascending order.\n");
    } 
    else if (choice == 2) {
        qsort(customers, count, sizeof(Customer), compare_desc);
        printf("Sorted in descending order.\n");
    } 
    else {
        printf("Invalid choice!\n");
        return;
    }

    display_customers(); // show result immediately
}
