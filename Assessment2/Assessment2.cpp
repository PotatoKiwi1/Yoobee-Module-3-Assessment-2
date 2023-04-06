// Yoobee College - Assessment 2 - Module 3 - Integrated Studio
// School Lunch Ordering System - Group Assessment BERENDS, Nikolos & LOWE, Sarah

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

// Function to display the menu and return the selected item's price
double displayMenu() {
    cout << "School Lunch Ordering System" << endl;
    cout << "---------------------------" << endl;
    cout << "Menu:" << endl;
    cout << "1. Chicken Sandwich - $3.50" << endl;
    cout << "2. Cheeseburger - $4.00" << endl;
    cout << "3. Veggie Wrap - $3.00" << endl;
    cout << "4. Garden Salad - $2.50" << endl;
    cout << "Please select an item (1-4): ";
    int selection;
    cin >> selection;
    double price = 0.0;
    switch (selection) {
    case 1:
        price = 3.50;
        break;
    case 2:
        price = 4.00;
        break;
    case 3:
        price = 3.00;
        break;
    case 4:
        price = 2.50;
        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
        price = displayMenu();
    }
    return price;
}

struct User {
    string username;
    string password;
};

vector<User> users;
bool is_authenticated = false;
bool is_admin = false;
bool is_running = true;
string current_user = "";
string credentials_file = "users.txt";

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

    double price = displayMenu();

    int quantity;
    cout << "Please enter the quantity: ";
    cin >> quantity;

    double subtotal = price * quantity;
    cout << fixed << setprecision(2) << "Subtotal: $" << subtotal << endl;

    double discountPercentage;
    cout << "Enter the discount percentage (0-100): ";
    cin >> discountPercentage;
    double discount = calculateDiscount(subtotal, discountPercentage / 100.0);

    double totalPrice;

    totalPrice = subtotal - discount;
    cout << fixed << setprecision(2) << "Total Price: $" << totalPrice << endl;

    processPayment(totalPrice, subtotal, discount);

    return totalPrice;
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
        cout << "Admin Menu" << endl;
        cout << "----------" << endl;
        cout << "1. Create new user" << endl;
        cout << "2. Sign out" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option (1-2): ";
        cin >> selection;
        switch (selection) {
        case 1:
            createUser();
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
            adminMenu();
        }
    }

}

void userMenu() {
    int selection;
    cout << "User Menu" << endl;
    cout << "---------" << endl;
    cout << "1. Open ordering system" << endl;
    cout << "2. Sign out" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-2): ";
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