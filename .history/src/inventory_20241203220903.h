#ifndef _INVENTORY_H_
#define _INVENTORY_H_

extern char *data_path;
extern char *basket_path;

int customer_system();
int show_list_product();
int login_system();
int editFile();
int login_system();

// function from other script
int search();
int show_list_product();
int show_list_product_struct();

#define max_char 10
#define max_product 100
#endif