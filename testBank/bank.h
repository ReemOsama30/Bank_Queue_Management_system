#pragma once
#include "teller.h" 
#include "customer.h" 
#include "comparecustomer.h" 
#include <queue>
#include "CustomerRecord.h"
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
        int waitingTime=0;
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
    void assignCustomers() {
        //in the rush hours 
        
        //customersize = customerQueue.size();
        //customerRecords.resize(customersize);
        if (customerQueue.size() > 20)
        {
            tellerList.push_back(teller());
        }

   
        tellerNum = tellerList.size();
    
        while (!customerQueue.empty()) {
            customer currentCustomer = customerQueue.top();
            customerQueue.pop();

            customerRecords.push_back(CustomerRecord());
           
            if (tellerList[currentTellerIndex].getisavailable())
                if (tellerList[currentTellerIndex].getServingTime() == 0)
                {
                    currentCustomer.setWaitingTime(0);
                    totalWaitingTime += currentCustomer.getWaitingTime();
                    tellerList[currentTellerIndex].serveCustomer(currentCustomer, currentTellerIndex);
                    tellerList[currentTellerIndex].setServingTime(currentCustomer.getLeavingTime());
                    totalServingTime += currentCustomer.getServiceTime();
                    // Update customer record
                    customerRecords[currentCustomer.getID() - 1].arrivalTime = currentCustomer.getArrivalTime();
                    customerRecords[currentCustomer.getID() - 1].ID = currentCustomer.getID();
                    customerRecords[currentCustomer.getID()-1].waitingTime = currentCustomer.getWaitingTime();
                    customerRecords[currentCustomer.getID()-1].leavingTime = currentCustomer.getLeavingTime();
                    customerRecords[currentCustomer.getID()-1].tellerID = currentTellerIndex+1;
                   

                }
                else
                {
               
                    int index = compareTeller(currentCustomer.getArrivalTime());  

                    currentCustomer.setWaitingTime(tellerList[index].getServingTime()- currentCustomer.getArrivalTime() );
                    totalWaitingTime += currentCustomer.getWaitingTime();
                    tellerList[index].serveCustomer(currentCustomer, index);
                    tellerList[index].setServingTime(currentCustomer.getLeavingTime());
                    totalServingTime += currentCustomer.getServiceTime();


                    //set customer record
                    customerRecords[currentCustomer.getID() - 1].arrivalTime = currentCustomer.getArrivalTime();
                    customerRecords[currentCustomer.getID() - 1].ID = currentCustomer.getID();
                    customerRecords[currentCustomer.getID()-1].waitingTime = currentCustomer.getWaitingTime();
                    customerRecords[currentCustomer.getID()-1].leavingTime = currentCustomer.getLeavingTime();
                    customerRecords[currentCustomer.getID()-1].tellerID = index+1;
                    
                }

            currentTellerIndex= (currentTellerIndex+1)%tellerNum;
        }

    }
 
    void print()
    {
        for (int i = 0; i < customerRecords.size(); i++)
        {
            cout << customerRecords[i].ID << "         " << endl;
        }
    }

    void printFinalReport(ofstream &outputFile){
       
    if (!outputFile) {
        std::cerr << "Error opening file: " <<endl;
        return;
    }
    outputFile << "Customer ID  : " << " Arrival Time : " << " Waiting Time: " << "Leaving Time: " << "Served by Teller: " << endl;
    for (size_t i = 0; i < customerRecords.size(); ++i) {
        outputFile << customerRecords[i].ID << "           :      ";
        outputFile << customerRecords[i].arrivalTime << "     :        ";
        outputFile << customerRecords[i].waitingTime << "     :        ";
        outputFile << customerRecords[i].leavingTime << "     :        ";
        outputFile  << customerRecords[i].tellerID <<endl;
    }

    outputFile << endl << endl;
    outputFile << "the average waiting time of the project is " <<double( totalWaitingTime)/customerRecords.size()<<endl;
    outputFile << "the average serving time of the project is " << double(totalServingTime) / customerRecords.size() << endl;
    for (int i = 0; i < tellerNum; i++)
    {
        outputFile << "the teller " << i + 1 << " served " << tellerList[i].getNumberOfServedCustomer() << endl;
        outputFile << "the utilization rate is of the teller  " << i + 1 << " is " << tellerList[i].getNumberOfServedCustomer()/ double(customerRecords.size()) * 100 <<"%"<< endl;
     }
    
    outputFile.close();
    }
};
