#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    ofstream outputFile("myfile.txt", ios::app);
    ifstream inputFile("input.txt");
  
    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    cout << "Bank Management system!\n";
    bank b(3);
    int num;
    inputFile >> num; 
    for (int i = 0; i < num; i++)
    {
        int id, arrivaltime, servicetime;
        inputFile >> id >> arrivaltime >> servicetime; // Read customer details from the file
        b.addCustomers(id, servicetime, arrivaltime);
    }
    inputFile.close();
    b.assignCustomers();
    cout << "_______________________________________" << endl;
    b.printFinalReport(outputFile);

   

}

