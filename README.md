# Inventory-System-Project
   CPE100 Inventory System Term Project
# 📦 Inventory System

## Project Overview
This project is a **C-based Inventory Management System** designed for the CPE100 course. The system enables efficient tracking, management, and optimization of inventory. It simulates real-world inventory operations, with features for both the **owner** and **customer** to manage stock levels, process purchases, and apply discount coupons.

## 🛠️ System Requirements
- **Language**: C
- **Data Storage**: File-based database (text or CSV files)
- **Interface**: Command-Line Interface (CLI)
- **Data Structures**: Using structs for products, customers, and transactions

---

## 📦 Features

### 👤 Owner Features
- **Inventory Reports**
  - Search and filter products by name or price range.
- **Product Management (CRUD)**
  - Add, view, edit, or delete products from the inventory.
- **Restocking**
  - Update stock levels and receive low-stock notifications.
- **Logging**
  - Track key actions such as stock updates, purchases, and reports.
- **Discount Coupons**
  - Create and manage unique discount codes with expiration dates.

### 🛒 Customer Features
- **View Products**
  - Browse available items with details (name, price, stock).
- **Shopping**
  - Add items to a cart, calculate totals, and apply discounts.
- **Inventory Updates**
  - Automatically update stock after purchase.

## 🛠️ System Requirements
- **Language**: C
- **Storage**: File-based database (text/CSV files)
- **Interface**: Command-Line Interface (CLI)
- **Data Structures**: Use `struct` for key elements like products, customers, and transactions.

## 📂 Project Structure
Below is the organized structure for the project's files and functions:

### 🗂️ **File Structure**
```plaintext
Inventory-System-Project/
├── src/
│   ├── main.c               # Entry point
│   ├── owner_functions.c    # Owner-specific operations
│   ├── customer_functions.c # Customer-specific operations
│   ├── utils.c              # Helper functions (e.g., input validation)
│   ├── file_io.c            # File handling (load/save database)
│   └── discount.c           # Discount coupon logic
├── include/
│   ├── owner_functions.h    # Header for owner functions
│   ├── customer_functions.h # Header for customer functions
│   ├── utils.h              # Header for utilities
│   ├── file_io.h            # Header for file I/O
│   └── discount.h           # Header for discounts
├── data/
│   ├── inventory.csv        # Product inventory database
│   ├── transactions.log     # Log file for actions
│   └── coupons.csv          # Discount coupons database
└── README.md                # Project documentation



