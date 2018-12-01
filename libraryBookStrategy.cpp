#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;



class Book {
public:
    Book() {
    }
    int code;
    double price;
    int numOfBooks;
    int numOfClassEnroll;
    bool isMandatory;
    bool isNew; // -1 for optional, 0 for used, 1 for new
    int estimatedOrder;
    double totalCost;
    double profitRate = 0.2;
    void calculate() {
        if (isMandatory && isNew) estimatedOrder = 0.9* numOfClassEnroll-numOfBooks;
        else if (isMandatory && !isNew) estimatedOrder = 0.65* numOfClassEnroll-numOfBooks;
        else if (!isMandatory && isNew) estimatedOrder = 0.4* numOfClassEnroll-numOfBooks;
        else estimatedOrder = 0.2* numOfClassEnroll-numOfBooks;
        if (estimatedOrder < 0) estimatedOrder = 0;
        totalCost = price * estimatedOrder;
    }
    void print() {
        cout <<"***************************************************\n";
        cout << "Book: " << code << endl;
        cout << "Price: $" << price << endl;
        cout << "Inventory: " << numOfBooks << endl;
        cout << "Enrollment: " << numOfClassEnroll << endl;
        if (!isMandatory) cout << "The book is Optional" << endl;
        else if (isNew) cout << "The book is Required and New" << endl;
        else cout << "The book is Required and used" << endl;
        cout << "\nthe book " << code <<" has been added to the list.\n";
        cout <<"***************************************************\n";
        cout << "Need to order: " << estimatedOrder << endl;
        cout << "Total Cost: $" << totalCost << endl;
        
    }
    bool setBookInfo() {
        int temp = 0;
        cout << "Please enter the book code: ";
        cin >> code;
        cout << "single copy price: $";
        cin >> price;
        cout << "number on hand: ";
        cin >> numOfBooks;
        cout << "prospective enrollment: ";
        cin >> numOfClassEnroll;
        cout << "1 for reqd/0 for optional: ";
        cin >> temp;
        if (temp == 1) {
            isMandatory = true;
        } else {
            isMandatory = false;
        }
        cout << "1 for new/0 for used: ";
        cin >> temp;
        if (temp == 1) {
            isNew = true;
        } else {
            isNew = false;
        }
        calculate();
        print();
        return true;
    }
};

void printResult (double sumOfCost, double profitOfCost) {
    cout <<"***************************************************\n";
    cout <<"Total for all orders: $"<< sumOfCost << endl;
    cout <<"Profit: $" << profitOfCost << endl;
    cout <<"***************************************************\n";
}


int main() {
    vector <Book> booklist;
    double sumOfCost = 0;
    double profitOfCost = 0;
    string x = " ";
    cout << "Thank you for using the system! \n Press enter 'y/n' to continue or stop: ";
    cin >> x;
    while (x!= "n") {
        Book nextBook;
        if (nextBook.setBookInfo()) {
            booklist.push_back(nextBook);
            sumOfCost += nextBook.totalCost;
            profitOfCost += nextBook.totalCost * nextBook.profitRate;
        }
        cout << "Continue to add new books('y/n'): ";
        cin >> x;
    }
    printResult(sumOfCost, profitOfCost);
    return 0;
}
