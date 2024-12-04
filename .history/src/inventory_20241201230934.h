#ifndef _INVENTORY_H_
#define _INVENTORY_H_

extern char *data_path;
extern char *basket_path;

int show_list_product();
int login_system();
int customer_system();
int basket_system(char *basket_path, char *name, char *type, int number, float price);
int basket_data_system();
int editFile();

// function from other script
int search();
int show_list_product();

#define max_char 10
#define max_product 100
#endif