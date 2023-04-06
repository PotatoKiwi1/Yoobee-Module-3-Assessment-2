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

struct User {
    string username;
    string password;
};

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

void loadCredentials() {
    ifstream infile(credentials_file);
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

void saveCredentials() {
    ofstream file(credentials_file);
    for (User user : users) {
        file << user.username << " " << user.password << endl;
    }
    file.close();
}

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

void saveMenu() {
    ofstream file(menu_files, ios::app); // open the file in append mode
    for (Menu menu : menu) {
        file << menu.item << " " << menu.price << endl;
    }
    file.close();
}

void createMenuItem() {
    Menu MenuItem;
    cout << "Enter a new menu item: ";
    cin >> MenuItem.item;
    cout << "Enter a new price: ";
    cin >> MenuItem.price;
    MenuItem.index = menu.size(); // Set the index to the current size of the menu vector
    menu.push_back(MenuItem);
    saveMenu();
    cout << "New menu item created successfully." << endl;
}

void createUser() {
    User newUser;
    cout << "Enter a new username: ";
    cin >> newUser.username;
    cout << "Enter a new password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    saveCredentials();
    cout << "New user created successfully." << endl;
}

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

void signIn() {
    while (!is_authenticated) {
        cout << "------------" << endl;
        cout << "Sign In Menu" << endl;
        cout << "------------" << endl;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (authenticateUser(username, password)) {
            cout << "Login successful." << endl;
        }
        else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }
}

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
    cout << "Select a payment type:" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Credit Card" << endl;
    cin >> paymentType;

    if (paymentType == 1) {
        // Cash payment - ask for the amount and calculate the change if any.
        double cash;
        cout << "Enter the amount of cash: $";
        cin >> cash;
        double change = cash - totalPrice;
        cout << fixed << setprecision(2) << "Change: $" << change << endl;
        cout << "Invoice..." << endl;
        cout << "----------------" << endl;
        cout << "Total: $" << subtotal << endl;
        cout << "Discount: $" << discount << endl;
        cout << "Total after Discounts: $" << totalPrice << endl;

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
        cout << "Payment has been processed, Thank you" << endl;
    }
}


// Function for ordering system
double openOrderingSystem() {
    loadMenu();

    int selection;
    cout << "Select an option: ";
    cin >> selection;

    ifstream infile(menu_files);
    if (!infile.is_open()) {
        cerr << "Error: menu file could not be opened." << endl;
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

    cerr << "Error: invalid selection." << endl;
    exit(1);
}

void signOut() {
    is_authenticated = false;
    is_admin = false;
    current_user = "";
    cout << "Logout successful." << endl;
}

void adminMenu() {
    int selection;
    while (is_admin == true) {
        cout << "----------" << endl;
        cout << "Admin Menu" << endl;
        cout << "----------" << endl;
        cout << "1. Create new user" << endl;
        cout << "2. Create new menu item" << endl;
        cout << "3. Sign out" << endl;
        cout << "4. Exit" << endl;
        cout << "Please select an option (1-4): ";
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
            cout << "Invalid selection. Please try again." << endl;

            adminMenu();
        }
    }

}

void userMenu() {
    int selection;
    cout << "---------" << endl;
    cout << "User Menu" << endl;
    cout << "---------" << endl;
    cout << "1. Open ordering system" << endl;
    cout << "2. Sign out" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";
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
        cout << "Invalid selection. Please try again." << endl;
        userMenu();
    }
}

// main function to call the sign in ansign out functions and the ordering system

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