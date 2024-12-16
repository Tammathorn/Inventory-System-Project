#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the path to save the coupon data
extern char *coupon_path;

int get_discount_data(int *discount_type, float *discount_price,int *discount_percent);
int get_product_data(char *product_name, char *product_type);
int save_coupon_data(char *coupon_code, char *product_name, char *product_type, float discount_price, int discount_percent,char *expiry_date);
int validate_date(const char *date);
int create_coupon();

// Function to get discount data
int get_discount_data(int *discount_type, float *discount_price,
                      int *discount_percent) {
  printf("Select discount type (1 for Price, 2 for Percentage): ");
  if (scanf("%d", discount_type) != 1) {
    printf("Invalid input. Please enter a number.\n");
    return -1;
  }

  if (*discount_type == 1) {
    printf("Enter discount price (e.g., 10.50): ");
    if (scanf("%f", discount_price) != 1 || *discount_price <= 0) {
      printf("Invalid discount price.\n");
      return -1;
    }
    *discount_percent = 0; // Set percent to 0 for price discount
  } else if (*discount_type == 2) {
    printf("Enter discount percentage (0-100): ");
    if (scanf("%d", discount_percent) != 1 || *discount_percent < 0 ||
        *discount_percent > 100) {
      printf("Invalid discount percentage.\n");
      return -1;
    }
    *discount_price = 0.0; // Set price to 0 for percentage discount
  } else {
    printf("Invalid discount type.\n");
    return -1;
  }

  return 0;
}

// Function to get product data
int get_product_data(char *product_name, char *product_type) {
  int choice;
  printf("Apply to\n1. Product Name\n2. Product Type\nEnter your choice:\n");
  if (scanf("%d", &choice) != 1) {
    printf("Invalid input. Please enter a number.\n");
    return -1;
  }

  if (choice == 1) {
    printf("Enter product name this coupon applies to: ");
    if (scanf("%19s", product_name) != 1 || strlen(product_name) == 0) {
      printf("Invalid product name.\n");
      return -1;
    }
    strcpy(product_type, "");
  } else if (choice == 2) {
    printf("Enter product type this coupon applies to: ");
    if (scanf("%19s", product_type) != 1 || strlen(product_type) == 0) {
      printf("Invalid product type.\n");
      return -1;
    }
    strcpy(product_name, "");
  } else {
    printf("Invalid choice.\n");
    return -1;
  }

  return 0;
}

// Function to save coupon data
int save_coupon_data(char *coupon_code, char *product_name, char *product_type,
                     float discount_price, int discount_percent,
                     char *expiry_date) {
  FILE *file = fopen(coupon_path, "a");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  // Write coupon data to the file
  if (fprintf(file, "%s,%s,%s,%.2f,%d,%s\n", coupon_code,
              strlen(product_name) > 0 ? product_name : "",
              strlen(product_type) > 0 ? product_type : "", discount_price,
              discount_percent, expiry_date) < 0) {
    perror("Error writing to file");
    fclose(file);
    return -1;
  }

  fclose(file);
  return 0;
}

// Function to validate date format (YYYY-MM-DD)
int validate_date(const char *date) {
  int year, month, day;
  if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
    return 0; // Invalid format
  }
  if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
    return 0; // Invalid date range
  }
  return 1; // Valid date
}

// Function to create a coupon
int create_coupon() {
  char coupon_code[20], product_name[20] = "", product_type[20] = "",
                        expiry_date[11];
  float discount_price = 0.0;
  int discount_percent = 0;
  int discount_type;

  // Get discount data
  if (get_discount_data(&discount_type, &discount_price, &discount_percent) ==
      -1) {
    return -1;
  }

  // Get product data
  if (get_product_data(product_name, product_type) == -1) {
    return -1;
  }

  // Get coupon code
  printf("Enter coupon code: ");
  if (scanf("%19s", coupon_code) != 1 || strlen(coupon_code) == 0) {
    printf("Invalid coupon code.\n");
    return -1;
  }

  // Get expiry date
  printf("Enter expiry date (YYYY-MM-DD): ");
  if (scanf("%10s", expiry_date) != 1 || !validate_date(expiry_date)) {
    printf("Invalid expiry date.\n");
    return -1;
  }

  // Save coupon data
  if (save_coupon_data(coupon_code, product_name, product_type, discount_price,
                       discount_percent, expiry_date) == 0) {
    printf("Successfully created coupon.\n");
  } else {
    printf("Failed to create coupon.\n");
    return -1;
  }

  return 0;
}
