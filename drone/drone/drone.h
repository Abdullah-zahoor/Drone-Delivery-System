#pragma once
#pragma once
#ifndef DRONE_H
#define DRONE_H

#include <string>

enum class DroneType {
    Mini,
    Maxi,
    Heavy
};


class Drone {
private:
    std::string name;
    DroneType droneType;
    int capacity;
    int maxCapacity; 
    std::string destination;
    std::string rechargeDeadline;

public:
    
    Drone(const std::string& name, DroneType type, int capacity, int maxCapacity, const std::string& destination, const std::string& rechargeDeadline);
    std::string getName() const;
    int getCapacity() const;
    int getMaxCapacity() const; 
    std::string getDestination() const;
    std::string getRechargeDeadline() const;
    void setName(const std::string& name);
    void setCapacity(int capacity);
    void setDestination(const std::string& destination);
    void setRechargeDeadline(const std::string& rechargeDeadline);
    

};

#endif  