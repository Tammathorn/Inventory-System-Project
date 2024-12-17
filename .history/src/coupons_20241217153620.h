#ifndef COUPONS_H
#define COUPONS_H

// Define a structure for coupon
struct coupon_t {
    char code[20];
    char product_name[50];
    char category[30];
    float discount_price;
    int discount_percent;
    char expiry_date[11];
};

// Global variable for coupon file path
extern char *coupon_path;

// Function declarations

// Create and Save
int get_discount_data(int *discount_type, float *discount_price, int *discount_percent);
int get_product_data(char *product_name, char *category);
int save_coupon_data(char *coupon_code, char *product_name, char *category, float discount_price, int discount_percent, char *expiry_date);
int create_coupon();
int validate_date(const char *date);

// Display and Manage
int load_coupons(struct coupon_t coupons, int *coupon_count, const char *file_path);
void display_coupons();
int delete_coupon(const char *coupon_code);


// Auto clean up expired
int clean_expired_coupons();
void auto_cleanup_expired_coupon();
void delete_used_coupon(const char *used_coupon_code) 


// Run manage coupons
void manage_coupons();
void apply_coupon();

#endif // COUPONS_H
