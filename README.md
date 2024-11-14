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

## 📋 Features

### 👤 Owner Features
1. **View Reports and Analysis**
   - Display inventory reports with options to search and filter by product name or price range.

2. **Product Management (CRUD Operations)**
   - **Create**: Add a new product to the inventory.
   - **View**: Check product details including name, price, and stock.
   - **Edit**: Update details for existing products.
   - **Delete**: Remove a product from the inventory.

3. **Restocking**
   - Add stock to any product when required.
   - Trigger a notification if a product’s stock falls below the minimum threshold, indicating the need for restocking.

4. **Logging**
   - Maintain a log file to track key actions such as product restocks, customer purchases, and report generation.

5. **Discount Coupons**
   - Create and manage discount coupons with a unique code, discount percentage, and expiration date.
   - Allow coupons to be applied at checkout for applicable products.

### 🛒 Customer Features
1. **View Products**
   - Browse available products with details (name, description, price, and stock).
   - Filter products by category or price range.

2. **Purchase Products**
   - Add products to a shopping cart with desired quantities.
   - Calculate the total cost at checkout, factoring in discounts if applicable.
   - Update inventory levels automatically after purchase.

3. **Discount Coupon Application**
   - Apply valid discount coupons at checkout to reduce total cost.
   - Ensure coupons are not expired before allowing application.

---

## 🗂️ Project Structure

