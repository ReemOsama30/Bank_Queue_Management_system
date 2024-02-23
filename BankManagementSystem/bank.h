#pragma once
#include "teller.h" 
#include "customer.h" 
#include "comparecustomer.h" 
#include <queue>
#include "CustomerRecord.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <windows.h>
#include <iomanip>
using namespace std;

class bank {

    priority_queue<customer, vector<customer>, CompareCustomer> customerQueue; // Combined customer queue
    vector<CustomerRecord> customerRecords;
    vector<teller> tellerList;
    int tellerNum;
    int currentTellerIndex;
    int totalWaitingTime;
    int totalServingTime;
public:
    bank(int tellernum) {
        tellerNum = tellernum;
        for (int i = 0; i < tellerNum; ++i) {
            tellerList.push_back(teller());
        }

        currentTellerIndex = 0;
        totalWaitingTime = 0;
        totalServingTime = 0;
    }

    void addCustomers(int id, int servicetime, int arrivaltime) {
        customer cust(id, servicetime, arrivaltime);
        customerQueue.push(cust);



    }

    int compareTeller(int arrivaltime)
    {
        int minindex = 0;
        int waitingTime = 0;
        int minwaitingTime = INT_MAX;

        for (int i = 0; i < tellerNum; i++)
        {
            waitingTime = tellerList[i].getServingTime() - arrivaltime;
            if (minwaitingTime > waitingTime)  //leaving 
            {
                minwaitingTime = waitingTime;
                minindex = i;
            }
        }
        return minindex;
    }


    void SetColor(int ForgC)
    {
        WORD wColor;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
    }
    void assignCustomers() {

        ////in the rush hours 
        if (customerQueue.size() > 10)
        {
            tellerList.push_back(teller());
            tellerNum++;
        }

        int customerIndexCounter = 0; // Counter for customer index

        while (!customerQueue.empty()) {
            customer currentCustomer = customerQueue.top();
            customerQueue.pop();

            if (tellerList[currentTellerIndex].getisavailable() && tellerList[currentTellerIndex].getServingTime() == 0)
            {
                customerRecords.push_back(CustomerRecord());
                currentCustomer.setWaitingTime(0);
                totalWaitingTime += currentCustomer.getWaitingTime();
                tellerList[currentTellerIndex].serveCustomer(currentCustomer, currentTellerIndex);
                tellerList[currentTellerIndex].setServingTime(currentCustomer.getLeavingTime());
                totalServingTime += currentCustomer.getServiceTime();

                // Update customer record
                if (customerIndexCounter < customerRecords.size()) {
                    customerRecords[customerIndexCounter].arrivalTime = currentCustomer.getArrivalTime();
                    customerRecords[customerIndexCounter].ID = currentCustomer.getID();
                    customerRecords[customerIndexCounter].waitingTime = currentCustomer.getWaitingTime();
                    customerRecords[customerIndexCounter].leavingTime = currentCustomer.getLeavingTime();
                    customerRecords[customerIndexCounter].tellerID = currentTellerIndex + 1;
                    customerIndexCounter++; // Increment the counter
                }
                else {
                    cerr << "Error: Customer index counter out of bounds." << endl;
                }
            }
            else
            {
                customerRecords.push_back(CustomerRecord());
                int index = compareTeller(currentCustomer.getArrivalTime());
                currentCustomer.setWaitingTime(tellerList[index].getServingTime() - currentCustomer.getArrivalTime());
                totalWaitingTime += currentCustomer.getWaitingTime();
                tellerList[index].serveCustomer(currentCustomer, index);
                tellerList[index].setServingTime(currentCustomer.getLeavingTime());
                totalServingTime += currentCustomer.getServiceTime();

                // Set customer record
                if (customerIndexCounter < customerRecords.size()) {
                    customerRecords[customerIndexCounter].arrivalTime = currentCustomer.getArrivalTime();
                    customerRecords[customerIndexCounter].ID = currentCustomer.getID();
                    customerRecords[customerIndexCounter].waitingTime = currentCustomer.getWaitingTime();
                    customerRecords[customerIndexCounter].leavingTime = currentCustomer.getLeavingTime();
                    customerRecords[customerIndexCounter].tellerID = index + 1;
                    customerIndexCounter++; // Increment the counter
                }
                else {
                    cerr << "Error: Customer index counter out of bounds." << endl;
                }
            }

            currentTellerIndex = (currentTellerIndex + 1) % tellerNum;
        }
    }


    void printFinalReport(ofstream& outputFile) {

        if (!outputFile) {
            std::cerr << "Error opening file: " << endl;
            return;
        }

        outputFile << std::left << std::setw(12) << "Customer ID"
            << std::setw(15) << "Arrival Time"
            << std::setw(15) << "Waiting Time"
            << std::setw(15) << "Leaving Time"
            << "Served by Teller:" << endl;

        for (size_t i = 0; i < customerRecords.size(); ++i) {
            outputFile << std::setw(15) << customerRecords[i].ID
                << std::setw(20) << customerRecords[i].arrivalTime
                << std::setw(15) << customerRecords[i].waitingTime
                << std::setw(20) << customerRecords[i].leavingTime
                << customerRecords[i].tellerID << endl;
        }

        outputFile << endl << endl;
        outputFile << "The average waiting time of the project is " << std::fixed << std::setprecision(2)
            << double(totalWaitingTime) / customerRecords.size() << endl;
        outputFile << "The average serving time of the project is " << std::fixed << std::setprecision(2)
            << double(totalServingTime) / customerRecords.size() << endl;

        for (int i = 0; i < tellerNum; i++) {
            outputFile << "The teller " << i + 1 << " served " << tellerList[i].getNumberOfServedCustomer() << endl;
            outputFile << "The utilization rate of teller " << i + 1 << " is "
                << std::fixed << std::setprecision(2)
                << tellerList[i].getNumberOfServedCustomer() / static_cast<double>(customerRecords.size()) * 100
                << "%" << endl;
        }

        outputFile.close();
    }


    void printFinalReportToConsole() {
        SetColor(22);
        std::cout << std::left << std::setw(12) << "Customer ID"
            << std::setw(15) << "Arrival Time"
            << std::setw(15) << "Waiting Time"
            << std::setw(15) << "Leaving Time"
            << "Served by Teller:" << std::endl;

        for (size_t i = 0; i < customerRecords.size(); ++i) {
            std::cout << std::setw(15) << customerRecords[i].ID
                << std::setw(20) << customerRecords[i].arrivalTime
                << std::setw(15) << customerRecords[i].waitingTime
                << std::setw(20) << customerRecords[i].leavingTime
                << customerRecords[i].tellerID << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Delay of 100 milliseconds
        }
        SetColor(11);
        std::cout << std::endl << std::endl;
        std::cout << "The average waiting time of the project is " << std::fixed << std::setprecision(2)
            << double(totalWaitingTime) / customerRecords.size() << std::endl;
        std::cout << "The average serving time of the project is " << std::fixed << std::setprecision(2)
            << double(totalServingTime) / customerRecords.size() << std::endl;

        for (int i = 0; i < tellerNum; i++) {
            std::cout << "The teller " << i + 1 << " served " << tellerList[i].getNumberOfServedCustomer() << std::endl;
            std::cout << "The utilization rate of teller " << i + 1 << " is "
                << std::fixed << std::setprecision(2)
                << tellerList[i].getNumberOfServedCustomer() / static_cast<double>(customerRecords.size()) * 100
                << "%" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Delay of 100 milliseconds
        }



    }
};