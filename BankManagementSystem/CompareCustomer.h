#pragma once
#include "customer.h"
struct CompareCustomer {
    bool operator()(const customer& c1, const customer& c2) {
        return c1.getArrivalTime() > c2.getArrivalTime();
    }
};