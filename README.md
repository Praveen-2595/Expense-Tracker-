# Expense Tracker CLI (C++)

A simple, console-based Expense Tracker application written in C++. This program allows users to log their daily expenses, categorize them, and manage their financial records using persistent file storage.

## 🚀 Features

* **Add Expenses:** Log new expenses with an automatically generated ID, current date, and timestamp.
* **View Log:** Display a formatted table of all recorded expenses.
* **Automatic Totals:** Calculates and displays the sum of all expenses in the "View" mode.
* **Edit & Delete:** Modify existing records (Category, Remark, Amount) or delete them entirely by ID.
* **Search:** Filter expenses by specific categories.
* **Persistent Storage:** All data is saved in a CSV file (`saves.csv`), ensuring data isn't lost when the program closes.

## 🛠️ Built With

* **Language:** C++
* **Libraries:** `<iostream>`, `<fstream>`, `<sstream>`, `<ctime>`, `<iomanip>`
* **Storage:** CSV (Comma Separated Values) text file handling.

## 💻 How to Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
    ```
2.  **Compile the code:**
    You need a C++ compiler (like G++).
    ```bash
    g++ main.cpp -o expense_tracker
    ```
3.  **Run the executable:**
    * **Windows:**
        ```bash
        expense_tracker.exe
        ```
    * **Mac/Linux:**
        ```bash
        ./expense_tracker
        ```

## 📂 File Structure

* `main.cpp`: The source code containing all logic.
* `saves.csv`: The database file where expenses are stored (created automatically upon first entry).Format: `ID,Date,Time,Category,Remark,Amount`

## 📖 Usage Guide

When you run the program, you will see the following menu:

1.  **Add Expense:** Enter the category (e.g., Food, Travel), a short remark, and the amount.
2.  **View Expense:** Shows the history of all transactions.
3.  **Edit or Delete:** Enter the unique ID of the expense you wish to modify or remove.
4.  **Search/Filter:** Type a category name to see how much you have spent in that specific area.
5.  **Exit:** Closes the application.

## 🔮 Future Improvements

* Add input validation to prevent crashes if letters are entered instead of numbers.
* Add a function to generate monthly reports.
* Encrypt the data file for security.

## 🤝 Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## 📜 License

This project is open-source and available for educational purposes.
