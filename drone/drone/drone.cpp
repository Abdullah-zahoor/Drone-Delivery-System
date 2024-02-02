#include "drone.h"
using namespace std;


Drone::Drone(const string& name, DroneType type, int capacity, int maxCapacity, const string& destination, const string& rechargeDeadline)
    : name(name), droneType(type), capacity(capacity), maxCapacity(maxCapacity), destination(destination), rechargeDeadline(rechargeDeadline) {}


string Drone::getName() const {
    return name;
}

int Drone::getCapacity() const {
    return capacity;
}

int Drone::getMaxCapacity() const {
    return maxCapacity;
}

string Drone::getDestination() const {
    return destination;
}

string Drone::getRechargeDeadline() const {
    return rechargeDeadline;
}

void Drone::setName(const std::string& name) {
    this->name = name;
}

void Drone::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Drone::setDestination(const std::string& destination) {
    this->destination = destination;
}

void Drone::setRechargeDeadline(const std::string& rechargeDeadline) {
    this->rechargeDeadline = rechargeDeadline;
}