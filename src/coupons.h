#ifndef COUPON_H
#define COUPON_H

extern char *coupon_path;

// Create and Save
int get_discount_data(int *discount_type, float *discount_price, int *discount_percent);
int get_product_data(char *product_name, char *product_type);
int save_coupon_data(char *coupon_code, char *product_name, char *product_type, float discount_price, int discount_percent, char *expiry_date);
int create_coupon();
int validate_date();//Checking if expiry info have a date range not out of real valid date

//Display and Manage
void display_coupons();
int delete_coupon(const char *coupon_code);

//Auto clean up expired
int clean_expired_coupons();

#endif
