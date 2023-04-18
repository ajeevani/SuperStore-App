# SuperStore-App

This is a C++ OOP-based application that lists all products in inventory, allows users to add or remove items, stock items, and use a point of sale system that prints a bill at the end of the transaction. The application takes input from a CSV file and saves data in a CSV file at the end to mimic a database.

## Installation

1. Clone the repository to your local machine.
2. Open the terminal and navigate to the project directory.
3. Compile the program using a C++ compiler.
4. Run the executable file.

## Usage

### Listing Products

To list all products in the inventory, simply run the program and select the appropriate option from the main menu.

### Adding an Item

To add an item to the inventory, select the "Add Item" option from the main menu and follow the prompts.

### Removing an Item

To remove an item from the inventory, select the "Remove Item" option from the main menu and follow the prompts.

### Stocking an Item

To add stock to an existing item in the inventory, select the "Stock Item" option from the main menu and follow the prompts.

### Point of Sale System

To use the point of sale system, select the "POS" option from the main menu and follow the prompts. The program will display all the items in the inventory and prompt you to enter the SKU of the item. Once all items have been entered, the program will print a bill and save all the data in the app to a csv file for next launch.

## CSV File Format

The CSV file used by the application should be formatted as follows:

```
(Non)Perishable,SKU,Item Name,Price,Taxed,Quantity,Expiry date
P,1001,Apple,0.50,10,2023/05/01
P,1002,Banana,0.25,20,2023/04/25
P,1003,Orange,0.75,5,2023/04/25
```

The program will save transaction data in a separate CSV file with same layout as above for next launch.


## Conclusion

This superstore application provides a simple and efficient way to manage inventory and sales. The use of C++ OOP ensures that the program is easy to maintain and expand upon in the future.
