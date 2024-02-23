#pragma once

class customer {
    int ID;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
    int leavingTime;
public:

    customer(int id, int servicetime, int arrivaltime) {
        ID = id;
        serviceTime = servicetime;
        arrivalTime = arrivaltime;
        waitingTime = 0;
        leavingTime = arrivaltime + servicetime;
    }


    int getID() const {
        return ID;
    }

    int getArrivalTime() const {
        return arrivalTime;
    }

    int getServiceTime() const {
        return serviceTime;
    }

    int getWaitingTime() const {
        return waitingTime;
    }

    int getLeavingTime()
    {
        return leavingTime;
    }
    void setID(int id) {
        ID = id;
    }

    void setArrivalTime(int arrivaltime) {
        arrivalTime = arrivaltime;
    }

    void setServiceTime(int servicetime) {
        serviceTime = servicetime;
    }

    void setWaitingTime(int waitingtime) {
        waitingTime = waitingtime;

    }
    void setLeavingTime(int leavingtime)
    {
        leavingTime = leavingtime;
    }
};