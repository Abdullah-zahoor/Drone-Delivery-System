#pragma once
#pragma once
#ifndef VECTORDRONE_H
#define VECTORDRONE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "drone.h"

class vectorDrone {
public:
    std::vector<Drone> readDronesFromFile(const std::string& filename) {
        std::vector<Drone> drones;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name, destination, rechargeDeadline;
            int capacity, maxCapacity;
            std::string droneTypeStr;
            DroneType type;
            while (file >> name >> capacity >> maxCapacity >> destination >> rechargeDeadline >> droneTypeStr) {
                if (droneTypeStr == "Mini") {
                    type = DroneType::Mini;
                }
                else if (droneTypeStr == "Maxi") {
                    type = DroneType::Maxi;
                }
                else if (droneTypeStr == "Heavy") {
                    type = DroneType::Heavy;
                }
                drones.emplace_back(name, type, capacity, maxCapacity, destination, rechargeDeadline);
            }
            file.close();
        }
        return drones;
    }

    void addDrone(std::vector<Drone>& drones) {
        std::string name, destination, rechargeDeadline;
        int capacity;
        std::string droneTypeStr;
        DroneType type;
        int maxCapacity;

        std::cout << "Enter drone name: ";
        std::cin >> name;
        std::cout << "Enter drone capacity: ";
        std::cin >> capacity;
        std::cout << "Enter drone destination: ";
        std::cin >> destination;
        std::cout << "Enter drone recharge deadline: ";
        std::cin >> rechargeDeadline;
        std::cout << "Enter drone type (Mini, Maxi, Heavy): ";
        std::cin >> droneTypeStr;

        if (droneTypeStr == "Mini") {
            type = DroneType::Mini;
            maxCapacity = 2;
        }
        else if (droneTypeStr == "Maxi") {
            type = DroneType::Maxi;
            maxCapacity = 5;
        }
        else if (droneTypeStr == "Heavy") {
            type = DroneType::Heavy;
            maxCapacity = 10;
        }
        else {
            std::cout << "Invalid drone type. Drone not added.\n";
            return;
        }

        drones.emplace_back(name, type, capacity, maxCapacity, destination, rechargeDeadline);
        std::cout << "Drone added successfully.\n";
    }

    void editDrone(std::vector<Drone>& drones) {
        std::string name;
        std::cout << "Enter the name of the drone to edit: ";
        std::cin >> name;

        bool found = false;
        for (auto& drone : drones) {
            if (drone.getName() == name) {
                std::string newName, newDestination, newRechargeDeadline;
                int newCapacity;
                std::cout << "Enter new drone name: ";
                std::cin >> newName;
                std::cout << "Enter new drone capacity: ";
                std::cin >> newCapacity;
                std::cout << "Enter new drone destination: ";
                std::cin >> newDestination;
                std::cout << "Enter new drone recharge deadline: ";
                std::cin >> newRechargeDeadline;

                drone.setName(newName);
                drone.setCapacity(newCapacity);
                drone.setDestination(newDestination);
                drone.setRechargeDeadline(newRechargeDeadline);

                std::cout << "Drone edited successfully.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Drone not found.\n";
        }
    }

    void deleteDrone(std::vector<Drone>& drones) {
        std::string name;
        std::cout << "Enter the name of the drone to delete: ";
        std::cin >> name;

        auto it = std::find_if(drones.begin(), drones.end(), [&](const Drone& drone) {
            return drone.getName() == name;
            });

        if (it != drones.end()) {
            drones.erase(it);
            std::cout << "Drone deleted successfully.\n";
        }
        else {
            std::cout << "Drone not found.\n";
        }
    }
};

#endif
