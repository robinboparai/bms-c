#ifndef CUSTOMER_H
#define CUSTOMER_H

// Customer structure
typedef struct {
    int id;
    char name[50];
    char phone[15];
    char address[100];
    char email[50];
    double balance;
} Customer;

// Global variables
extern Customer *customers;
extern int count;
extern int capacity;

// Functions
void clear_input_buffer();

void load_data(const char *filename);
void save_data(const char *filename);
void add_customer();
void display_customers();
void search_customer();
void delete_customer();
void update_customer();
void sort_customers();

int find_customer_by_id(int id);

#endif