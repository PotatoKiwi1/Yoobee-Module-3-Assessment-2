// Yoobee College - Assessment 2 - Module 3 - Integrated Studio
// School Lunch Ordering System - Group Assessment BERENDS, Nikolos & LOWE, Sarah

#include <iostream>
#include <iomanip>
#include <vector>
// for setprecision and setw functions
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

// Function to calculate the discount based on the total price and user-defined percentage
double calculateDiscount(double totalPrice, double discountPercentage) {
    return discountPercentage * totalPrice;
}

// Function for payment process
void processPayment(double totalPrice, double subtotal, double discount) {
    // Ask for the payment type and handle the payment process
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

        // code for credit card payment confirmation here
        string cvcNumber;
        cout << "Enter the CVC Number" << endl;
        cin >> cvcNumber;

        // Expiry Date of the credit card
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
    // Display the menu and get the selected item's price
    double price = displayMenu();

    // Ask for the quantity of the selected item
    int quantity;
    cout << "Please enter the quantity: ";
    cin >> quantity;

    // Calculate the subtotal and display it
    double subtotal = price * quantity;
    cout << fixed << setprecision(2) << "Subtotal: $" << subtotal << endl;

    // Ask for the discount percentage and calculate the discount
    double discountPercentage;
    cout << "Enter the discount percentage (0-100): ";
    cin >> discountPercentage;
    double discount = calculateDiscount(subtotal, discountPercentage / 100.0);

    // Declare totalPrice here
    double totalPrice;

    // Calculate the total price and display it
    totalPrice = subtotal - discount;
    cout << fixed << setprecision(2) << "Total Price: $" << totalPrice << endl;

    // Call processPayment with the calculated values
    processPayment(totalPrice, subtotal, discount);

    return totalPrice;
}

// Main function to handle the ordering and payment process
int main() {
    // Sign-in menu
    string username, password;
    cout << "---------" << endl;
    cout << "Sign On" << endl;
    cout << "---------" << endl;
    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;
    if (username == "admin" && password == "adminpassword") {
        // Administrator menu
        cout << "Welcome, Admin!" << endl;
        cout << "Please select from the following options:" << endl;
        cout << "1. Create a new User" << endl;
        cout << "2. Open the Ordering system" << endl;
        int selection;
        cin >> selection;
        switch (selection) {
        case 1:
            // Code to create a new user
            break;
        case 2:
            // Code to open the ordering system
            openOrderingSystem();
            break;
        default:
            cout << "Invalid selection. Exiting program." << endl;
            return 0;
        }
    }
    else if (username == "user" && password == "userpassword") {
        // User menu
        cout << "Welcome to the Ordering System" << endl;
        cout << "Please select from the following options:" << endl;
        cout << "1. Open the Ordering System" << endl;
        int selection;
        cin >> selection;
        switch (selection) {
        case 1:
            // Code to open the ordering system
            openOrderingSystem();
            break;
        default:
            cout << "Invalid selection. Exiting program." << endl;
            return 0;
        }
    }
    else {
        cout << "Invalid username or password. Exiting program." << endl;
        return 0;
    }
}
