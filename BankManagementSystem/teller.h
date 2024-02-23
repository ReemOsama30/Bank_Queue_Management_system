#pragma once
#include "customer.h"
#include <fstream>
#include <iostream>
using namespace std;
class teller
{
    bool isavailable;
    int servingTime;
    int numberOfServedCustomer;

public:
    teller()
    {
        isavailable = true;
        servingTime = 0;
        numberOfServedCustomer = 0;
    }

    int getNumberOfServedCustomer()
    {
        return numberOfServedCustomer;
    }
    void  setNumberOfServedCustomer(int num)
    {
        numberOfServedCustomer = num;
    }


    void Setisavailable(bool value) {
        isavailable = value;
    }
    void setServingTime(int servingtime)
    {
        servingTime = servingtime;
    }
    int getServingTime()
    {
        return servingTime;
    }
    bool getisavailable() {
        return isavailable;
    }
    void serveCustomer(customer& customer, int tellerID) {
        isavailable = false;
        customer.setLeavingTime(customer.getArrivalTime() + customer.getServiceTime() + customer.getWaitingTime());

        numberOfServedCustomer += 1;

        isavailable = true;

    }




};