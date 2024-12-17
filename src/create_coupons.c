#include "coupons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_discount_data(int *discount_type, float *discount_price,
                      int *discount_percent);
int get_product_data(char *product_name, char *category);
int save_coupon_data(char *coupon_code, char *product_name, char *category,
                     float discount_price, int discount_percent,
                     char *expiry_date);
int validate_date(const char *date);
int create_coupon();

// Function to get discount data
int get_discount_data(int *discount_type, float *discount_price,
                      int *discount_percent)
{
  printf("Select discount category (1 for Price, 2 for Percentage): ");
  if (scanf("%d", discount_type) != 1)
  {
    printf("Invalid input. Please enter a number.\n");
    return -1;
  }

  if (*discount_type == 1)
  {
    printf("Enter discount price (e.g., 10.50): ");
    if (scanf("%f", discount_price) != 1 || *discount_price <= 0)
    {
      printf("Invalid discount price.\n");
      return -1;
    }
    *discount_percent = 0;
  }
  else if (*discount_type == 2)
  {
    printf("Enter discount percentage (0-100): ");
    if (scanf("%d", discount_percent) != 1 || *discount_percent < 0 ||
        *discount_percent > 100)
    {
      printf("Invalid discount percentage.\n");
      return -1;
    }
    *discount_price = 0.0;
  }
  else
  {
    printf("Invalid discount category.\n");
    return -1;
  }

  return 0;
}

// Function to get product data
int get_product_data(char *product_name, char *category)
{
  int choice;
  printf("Apply to\n1. Product Name\n2. Product Category\nEnter your choice: ");
  if (scanf("%d", &choice) != 1)
  {
    printf("Invalid input.\n");
    return -1;
  }

  if (choice == 1)
  {
    printf("Enter product name: ");
    scanf("%49s", product_name);
    strcpy(category, "");
  }
  else if (choice == 2)
  {
    printf("Enter category: ");
    scanf("%29s", category);
    strcpy(product_name, "");
  }
  else
  {
    printf("Invalid choice.\n");
    return -1;
  }

  return 0;
}

// Function to validate date
int validate_date(const char *date)
{
  int year, month, day;
  if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3)
  {
    return 0; // Invalid format
  }
  if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31)
  {
    return 0; // Invalid date range
  }
  return 1;
}

// Function to save coupon data
int save_coupon_data(char *coupon_code, char *product_name, char *category,
                     float discount_price, int discount_percent,
                     char *expiry_date)
{
  FILE *file = fopen(coupon_path, "a");
  if (file == NULL)
  {
    perror("Error opening file");
    return -1;
  }

  fprintf(file, "%s,%s,%s,%.2f,%d,%s\n", coupon_code, product_name, category,
          discount_price, discount_percent, expiry_date);
  fclose(file);
  return 0;
}

// Function to create a coupon
int create_coupon()
{
  char coupon_code[20], product_name[50] = "", category[30] = "",
                        expiry_date[11];
  float discount_price = 0.0;
  int discount_percent = 0;

  // รับข้อมูล discount
  int discount_type;
  printf("Select discount category (1 for Price, 2 for Percentage): ");
  if (scanf("%d", &discount_type) != 1)
  {
    printf("Invalid input. Please enter a number.\n");
    return -1;
  }

  if (discount_type == 1)
  {
    printf("Enter discount price (e.g., 10.50): ");
    if (scanf("%f", &discount_price) != 1 || discount_price <= 0)
    {
      printf("Invalid discount price.\n");
      return -1;
    }
    discount_percent = 0; // ตั้งเป็น 0 เพราะเลือกใช้ราคาลดราคา
  }
  else if (discount_type == 2)
  {
    printf("Enter discount percentage (0-100): ");
    if (scanf("%d", &discount_percent) != 1 || discount_percent < 0 ||
        discount_percent > 100)
    {
      printf("Invalid discount percentage.\n");
      return -1;
    }
    discount_price = 0.0; // ตั้งเป็น 0 เพราะเลือกใช้เปอร์เซ็นต์
  }
  else
  {
    printf("Invalid discount category.\n");
    return -1;
  }

  // รับข้อมูล product_name หรือ category
  int choice;
  printf("Apply to\n1. Product Name\n2. Product Type (Category)\nEnter your "
         "choice: ");
  if (scanf("%d", &choice) != 1)
  {
    printf("Invalid input. Please enter a number.\n");
    return -1;
  }

  if (choice == 1)
  {
    printf("Enter product name this coupon applies to: ");
    scanf(" %[^\n]", product_name);
    if (strlen(product_name) == 0)
    { // กรณีผู้ใช้ไม่ใส่ค่า
      strcpy(product_name, "N/A");
    }
    strcpy(category, "N/A"); // ตั้ง category เป็น N/A
  }
  else if (choice == 2)
  {
    printf("Enter product type (category) this coupon applies to: ");
    scanf(" %[^\n]", category);
    if (strlen(category) == 0)
    { // กรณีผู้ใช้ไม่ใส่ค่า
      strcpy(category, "N/A");
    }
    strcpy(product_name, "N/A"); // ตั้ง product_name เป็น N/A
  }
  else
  {
    printf("Invalid choice.\n");
    return -1;
  }

  // รับข้อมูล coupon code
  printf("Enter coupon code: ");
  if (scanf("%19s", coupon_code) != 1 || strlen(coupon_code) == 0)
  {
    printf("Invalid coupon code.\n");
    return -1;
  }

  // รับข้อมูล expiry date
  printf("Enter expiry date (YYYY-MM-DD): ");
  if (scanf("%10s", expiry_date) != 1 || !validate_date(expiry_date))
  {
    printf("Invalid expiry date.\n");
    return -1;
  }

  // บันทึกข้อมูล coupon
  if (save_coupon_data(coupon_code, product_name, category, discount_price,
                       discount_percent, expiry_date) == 0)
  {
    printf("Successfully created coupon.\n");
  }
  else
  {
    printf("Failed to create coupon.\n");
    return -1;
  }

  return 0;
}
