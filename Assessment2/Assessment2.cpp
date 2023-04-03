// Assessment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip> // for setprecision and setw functions
using namespace std;

// Function to display the menu and return the selected item's price
double displayMenu() {
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

// Main function to handle the ordering and payment process
int main() {
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
    cout << fixed << setprecision(2) << "Discount: $" << discount << endl;

    // Calculate the total price and display it
    double totalPrice = subtotal - discount;
    cout << fixed << setprecision(2) << "Total Price: $" << totalPrice << endl;

    // Ask for the payment type and handle the payment process
    int paymentType;
    cout << "Select a payment type:" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Credit Card" << endl;
    cin >> paymentType;

    if (paymentType == 1) {
        // Cash payment - ask for the amount and calculate the change
        double cash;
        cout << "Enter the amount of cash: $";
        cin >> cash;
        double change = cash - totalPrice;
        cout << fixed << setprecision(2) << "Change: $" << change << endl;
    }
    else if (paymentType == 2) {
        // Credit card payment - ask for the card number and confirm the payment
        string cardNumber;
        cout << "Enter the credit card number: ";
        cin >> cardNumber;
        // code for credit card payment confirmation here
    }

    return 0;
}
