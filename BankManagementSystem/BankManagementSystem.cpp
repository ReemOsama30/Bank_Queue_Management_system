#include "Bank.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outputFile("file.txt", ios::app);
    ifstream inputFile("rush.txt");

    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    cout << "___________________________Bank Management system__________________________\n";
    bank b(3);
    int num;
    inputFile >> num;
    inputFile.ignore(); // Ignore the newline character after num
    for (int i = 0; i < num; i++) {
        int id, arrivaltime, servicetime;
        inputFile >> id >> arrivaltime >> servicetime; // Read customer details from the file
        b.addCustomers(id, servicetime, arrivaltime);
    }
    inputFile.close();
    b.assignCustomers();

    // Print the final report 
    b.printFinalReport(outputFile);
    b.printFinalReportToConsole();

    return 0;
}