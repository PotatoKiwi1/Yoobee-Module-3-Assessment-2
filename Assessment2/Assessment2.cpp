// Yoobee College - Assessment 2 - Module 3 - Integrated Studio
// School Lunch Ordering System - Group Assessment BERENDS, Nikolos & LOWE, Sarah

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Function to display the menu and return the selected item's price

const int NUM_MENU_ITEMS = 999;

// Defines a structure named User which represents the users of the application. It then stores the username and password. 
struct User {
    string username;
    string password;
};

// Much the same as the Struct User, this does the same but with them Menu Items and their price. 
struct Menu {
    string item;
    string price;
    string index;
};

vector<User> users;
vector<Menu> menu;
bool is_authenticated = false;
bool is_admin = false;
bool is_running = true;
string current_user = "";
string credentials_file = "users.txt";
string menu_files = "menu.txt";

// Reads the user credentials from the “users.txt” file and stores them in a sector of User Structs
void loadCredentials() {
    ifstream infile(credentials_file, ios::app); // open the file in append mode so as not to overwrite any already existing menu items. 
    if (!infile.is_open()) {
        cerr << "Error: credentials file could not be opened." << endl;
        exit(1);
    }
    string username, password;
    while (infile >> username >> password) {
        User user = { username, password };
        users.push_back(user);
    }
    infile.close();
}

// Writes the user credentials to the “users.txt” file. 
void saveCredentials() {
    ofstream file(credentials_file);
    for (User user : users) {
        file << user.username << " " << user.password << endl;
    }
    file.close();
}

// Reads the menu items and their prices from the “menu.txt” file and displays them on the console. 
void loadMenu() {
    ifstream infile(menu_files);
    if (!infile.is_open()) {
        cerr << "Error: menu file could not be opened." << endl;
        exit(1);
    }
    int itemNumber = 1;
    string menuItem;
    double itemPrice;
    while (infile >> menuItem >> itemPrice) {
        cout << itemNumber << ". " << menuItem << " - $" << itemPrice << endl;
        itemNumber++;
    }
    infile.close();
}

// Appends new menu items and their prices to the “menu.txt” file.
void saveMenu() {
    ofstream file(menu_files, ios::app); // open the file in append mode so as not to overwrite any already existing menu items. 
    for (Menu menu : menu) {
        file << menu.item << " " << menu.price << endl;
    }
    file.close();
}

// Allows an admin user to create a new menu item and its price, which then call saveMenu to write the newly created menu item to the “menu.txt” file.  
void createMenuItem() {
    Menu MenuItem;
    cout << "Enter a new menu item: ";
    cin >> MenuItem.item;
    cout << "Enter a new price: ";
    cin >> MenuItem.price;
    MenuItem.index = menu.size(); // Set the index to the current size of the menu vector
    menu.push_back(MenuItem);
    saveMenu();
    cout << "New menu item created successfully.\n" << endl;
}

// Allows the admin user to create a new user and their password, which then calls saveCredentials to write the newly created credentials to the “users.txt” file. 
void createUser() {
    User newUser;
    cout << "Enter a new username: ";
    cin >> newUser.username;
    cout << "Enter a new password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    saveCredentials();
    cout << "New user created successfully.\n" << endl;
}

// Takes a username and password as arguments and checks if the user is authenticated by comparing the input to the credentials store in the users vector. This will return true if the user is authenticated or false otherwise. 
bool authenticateUser(string username, string password) {
    for (User user : users) {
        if (user.username == username && user.password == password) {

            is_authenticated = true;
            current_user = username;
            is_admin = (username == "admin");

            return true;
        }
    }
    return false;
}

// Prompts the user to sign in by entering their username and password. If the input is valid, the user is authenticated, and their name is stored in the current user variable. 
void signIn() {
    while (!is_authenticated) {
        cout << "\t------------" << endl;
        cout << "\tSign In Menu" << endl;
        cout << "\t------------\n" << endl;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (authenticateUser(username, password)) {
            cout << "Login successful.\n" << endl;
        }
        else {
            cout << "Invalid username or password. Please try again.\n" << endl;
        }
    }
}

// Displays the menu items and their prices on the console and returns the total price of the items.  
double displayMenuItems() {
    double price = 0.0;
    for (Menu menuItem : menu) {
        cout << menuItem.item << " " << menuItem.price << endl;
        price += stod(menuItem.price);
    }
    return price;
}

// Function to calculate the discount based on the total price and user-defined percentage
double calculateDiscount(double totalPrice, double discountPercentage) {
    return discountPercentage * totalPrice;
}

// Function for payment processing - cash or credit card
void processPayment(double totalPrice, double subtotal, double discount) {

    int paymentType;
    cout << "\nSelect a payment type:" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Credit Card" << endl;
    cin >> paymentType;

    if (paymentType == 1) {
        // Cash payment - ask for the amount and calculate the change if any.
        double cash;
        cout << "Enter the amount of cash: $";
        cin >> cash;
        double change = cash - totalPrice;
        if (change < 0) {
            cout << "Insufficient amount. Please try ordering again.\n" << endl;
        }
        else {
            cout << fixed << setprecision(2) << "Change: $" << change << endl;
            cout << "Invoice..." << endl;
            cout << "----------------" << endl;
            cout << "Total: $" << subtotal << endl;
            cout << "Discount: $" << discount << endl;
            cout << "Total after Discounts: $" << totalPrice << "\n" << endl;
        }

    }
    else if (paymentType == 2) {
        // Credit card payment - ask for the card number and confirm the payment
        string cardNumber;
        cout << "Enter the credit card number: " << endl;
        cin >> cardNumber;

        string cvcNumber;
        cout << "Enter the CVC Number" << endl;
        cin >> cvcNumber;

        string cardDate;
        cout << "Enter the expiry date:" << endl;
        cin >> cardDate;

        cout << "Invoice..." << endl;
        cout << "----------------" << endl;
        cout << "Total: $" << subtotal << endl;
        cout << "Discount: $" << discount << endl;
        cout << "Total after Discounts: $" << totalPrice << endl;
        cout << "Payment has been processed. Thank you.\n" << endl;
    }
}


// Initializes the database, sets up the initial menu, and then enters a loop that repeatedly displays the menu and prompts the user for input until the user chooses to exit the program.
double openOrderingSystem() {
    cout << "\n\t----------" << endl;
    cout << "\tLunch Menu" << endl;
    cout << "\t---------\n" << endl;
    loadMenu();

    int selection;
    cout << "\nPurchases over $50 automatically receive discount of 10%" << endl;
    cout << "Select an option: ";
    cin >> selection;

    ifstream infile(menu_files);
    if (!infile.is_open()) {
        cerr << "Error: menu file could not be opened.\n" << endl;
        exit(1);
    }
    int itemNumber = 1;
    string menuItem;
    double itemPrice;
    while (infile >> menuItem >> itemPrice) {
        if (itemNumber == selection) {
            infile.close();
            int quantity;
            cout << "Please enter the quantity: ";
            cin >> quantity;
            double subtotal = itemPrice * quantity;
            double discountPercentage = 0.0;
            if (subtotal >= 50.0) {
                discountPercentage = 0.1;
            }
            double discount = calculateDiscount(subtotal, discountPercentage);
            double totalPrice = subtotal - discount;
            processPayment(totalPrice, subtotal, discount);
            return totalPrice;
        }
        itemNumber++;
    }
    infile.close();

    cerr << "Error: invalid selection.\n" << endl;
    exit(1);
}

// Removes the is_authenticated and is_admin tags from the currently signed in user. It then pushes back to the sign in screen. 
void signOut() {
    is_authenticated = false;
    is_admin = false;
    current_user = "";
    cout << "Logout successful.\n" << endl;
}

// When the user logs in as an administrator. It displays a menu of options that the admin can choose from, such as adding or removing items from the menu, viewing orders, and updating the status of orders.
void adminMenu() {
    int selection;
    while (is_admin == true) {
        cout << "\t----------" << endl;
        cout << "\tAdmin Menu" << endl;
        cout << "\t----------\n" << endl;
        cout << "1. Create new user" << endl;
        cout << "2. Create new menu item" << endl;
        cout << "3. Sign out" << endl;
        cout << "4. Exit" << endl;
        cout << "\nPlease select an option (1-4): ";
        cin >> selection;
        switch (selection) {
        case 1:
            createUser();
            break;
        case 2:
            createMenuItem();
            break;
        case 3:
            signOut();
            break;
        case 4:
            is_running = false;
            signOut();
            break;
        default:
            cout << "Invalid selection. Please try again.\n" << endl;

            adminMenu();
        }
    }

}

// This is called when the user logs in as a regular user. It displays a menu of options that the user can choose from, such as placing a new order, viewing their previous orders, and updating their account information.
void userMenu() {
    int selection;
    cout << "\t---------" << endl;
    cout << "\tUser Menu" << endl;
    cout << "\t---------\n" << endl;
    cout << "1. Open ordering system" << endl;
    cout << "2. Sign out" << endl;
    cout << "3. Exit" << endl;
    cout << "\nPlease select an option (1-3): ";
    cin >> selection;
    switch (selection) {
    case 1:
        openOrderingSystem();
        break;
    case 2:
        signOut();
        break;
    case 3:
        is_running = false;
        signOut();
        break;
    default:
        cout << "Invalid selection. Please try again.\n" << endl;
        userMenu();
    }
}

// This is the entry point of the program. It initializes the database, sets up the initial menu, and then enters a loop that repeatedly displays the menu and prompts the user for input until the user chooses to exit the program.

int main() {

    loadCredentials();

    while (is_running) {
        signIn();
        if (is_admin) {
            adminMenu();
        }
        else {
            userMenu();
        }
    }

}
