void manage_coupons() {
  int running = 1; // ใช้เป็นสถานะควบคุมลูป
  while (running) {
    printf("\n===== Coupon Management System =====\n");
    printf("1. Create a Coupon\n");
    printf("2. View All Coupons\n");
    printf("3. Delete a Coupon\n");
    printf("4. Go Back to Previous Menu\n"); // เปลี่ยนข้อความ
    printf("Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Returning to the previous menu...\n");
      return; // กลับไปยังฟังก์ชันที่เรียก manage_coupons()
    }

    switch (choice) {
    case 1: {
      if (create_coupon() == 0) {
        printf("Coupon created successfully.\n");
      } else {
        printf("Failed to create coupon.\n");
      }
      break;
    }
    case 2: {
      coupon_t coupons[100];
      int coupon_count = 0;
      if (load_coupons(coupons, &coupon_count, coupon_path) == 0) {
        display_coupons(coupons, coupon_count);
      } else {
        printf("Failed to load coupons.\n");
      }
      break;
    }
    case 3: {
      coupon_t coupons[100];
      int coupon_count = 0;
      if (load_coupons(coupons, &coupon_count, coupon_path) == 0) {
        display_coupons(coupons, coupon_count);

        char coupon_code[20];
        printf("Enter the coupon code to delete: ");
        if (scanf("%19s", coupon_code) == 1) {
          if (delete_coupon(coupon_code) == 0) {
            printf("Coupon deleted successfully.\n");
          } else {
            printf("Coupon not found.\n");
          }
        } else {
          printf("Invalid input.\n");
        }
      } else {
        printf("Failed to load coupons.\n");
      }
      break;
    }
    case 4: {
      printf("Returning to the previous menu...\n");
      running = 0; // จบการทำงานของลูป
      break;
    }
    default: {
      printf("Invalid choice. Please enter a number between 1 and 4.\n");
      break;
    }
    }
  }
}
