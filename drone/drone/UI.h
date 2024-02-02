#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "drone.h"
#include "package.h"
#include "vectorDrone.h"
#include "vectorPackage.h"


using namespace std;

class UI {
	
public:
    bool compareDronesByCapacity(const Drone& drone1, const Drone& drone2) {
        return drone1.getCapacity() < drone2.getCapacity();
    }

    bool comparePackagesByDeadline(const Package& package1, const Package& package2) {
        return package1.getDropOffDeadline() < package2.getDropOffDeadline();
    }

    void saveMatchingPlanToFile(const vector<pair<Drone, Package>>& matchingPlan, const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : matchingPlan) {
                file << "Drone: " << pair.first.getName() << " -> Package: " << pair.second.getName() << '\n';
            }
            file.close();
            cout << "Matching plan saved to file: " << filename << '\n';
        }
        else {
            cout << "Failed to open file: " << filename << '\n';
        }
    }

   
    bool computeGrace(const std::string& droneTime, const std::string& packageTime) {
        int droneMinutes = stoi(droneTime.substr(0, 2)) * 60 + stoi(droneTime.substr(3));
        int packageMinutes = stoi(packageTime.substr(0, 2)) * 60 + stoi(packageTime.substr(3));

        int deltaTime = packageMinutes - droneMinutes;

        if (deltaTime <= 20 || deltaTime >= 1440 - 20) {
            return true;
        }

        return false;
    }

    vector<pair<Drone, Package>> computeMatchingPlan(vector<Drone>& drones, vector<Package>& packages) {
        sort(drones.begin(), drones.end(), [this](const Drone& drone1, const Drone& drone2) {
            return compareDronesByCapacity(drone1, drone2);
            });

        sort(packages.begin(), packages.end(), [this](const Package& package1, const Package& package2) {
            return comparePackagesByDeadline(package1, package2);
            });

        vector<pair<Drone, Package>> matchingPlan;
        unordered_set<string> assignedDestinations;

        for (const auto& package : packages) {
            bool assigned = false;
            for (auto& drone : drones) {
                if (package.getDropOffDeadline() > drone.getRechargeDeadline()) {
                    continue;
                }
                if (package.getDropOffPoint() == drone.getDestination() && drone.getCapacity() > 0 &&
                    assignedDestinations.find(package.getDropOffPoint()) == assignedDestinations.end() &&
                    computeGrace(drone.getRechargeDeadline(), package.getDropOffDeadline())) {
                    matchingPlan.emplace_back(drone, package);
                    drone.setCapacity(drone.getCapacity() - 1);
                    assigned = true;
                    assignedDestinations.insert(package.getDropOffPoint());
                    break;
                }
            }
            if (!assigned) {
                cout << "No available drone to assign for package: " << package.getName() << '\n';
            }
        }

        return matchingPlan;
    }




    void displayMatchingPlan(const vector<pair<Drone, Package>>& matchingPlan) {
        cout << "Matching Plan:\n";
        for (const auto& pair : matchingPlan) {
            cout << "Drone: " << pair.first.getName() << " (Recharge Time: " << pair.first.getRechargeDeadline() << ")"
                << " -> Package: " << pair.second.getName()
                << " (Drop-off Deadline: " << pair.second.getDropOffDeadline() << ")"
                << '\n';
            
        }
    }

    void displayMatchingPlanByLoadCapacity(const vector<pair<Drone, Package>>& matchingPlan) {
        cout << "Matching Plan by Drone Load Capacity:\n";
        for (const auto& pair : matchingPlan) {
            cout << "Drone: " << pair.first.getName() << " (Load Capacity: " << pair.first.getCapacity() << "/" << pair.first.getMaxCapacity() << ")"
                << " -> Package: " << pair.second.getName() << '\n';
        }
    }


    void displayMatchingPlanByDeadline(const vector<pair<Drone, Package>>& matchingPlan) {
        cout << "Matching Plan by Package Deadline:\n";
        for (const auto& pair : matchingPlan) {
            cout << "Drone: " << pair.first.getName()
                << " -> Package: " << pair.second.getName() << " (Deadline: " << pair.second.getDropOffDeadline() << ")" << '\n';
        }
    }

    void displayDronesNotAtFullLoad(const vector<Drone>& drones) {
        cout << "Drones Not at Full Load Capacity:\n";
        for (const auto& drone : drones) {
            if (drone.getCapacity() < drone.getMaxCapacity()) {
                cout << "Drone: " << drone.getName() << " (Load Capacity: " << drone.getCapacity() << "/" << drone.getMaxCapacity() << ")\n";
            }
        }
    }

    void displayUnassignedPackages(const vector<Package>& packages, const vector<pair<Drone, Package>>& matchingPlan) {
        cout << "Unassigned Packages:\n";
        vector<string> assignedPackageNames;
        for (const auto& pair : matchingPlan) {
            assignedPackageNames.push_back(pair.second.getName());
        }
        for (const auto& package : packages) {
            if (find(assignedPackageNames.begin(), assignedPackageNames.end(), package.getName()) == assignedPackageNames.end()) {
                cout << "Package: " << package.getName() << '\n';
            }
        }
    }

    

    void saveDronesToFile(const vector<Drone>& drones, const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& drone : drones) {
                file << drone.getName() << " " << drone.getCapacity() << " " << drone.getMaxCapacity()
                    << " " << drone.getDestination() << " " << drone.getRechargeDeadline() << '\n';
            }
            file.close();
            cout << "Drones saved to file: " << filename << '\n';
        }
        else {
            cout << "Failed to open file: " << filename << '\n';
        }
    }

    void savePackagesToFile(const vector<Package>& packages, const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& package : packages) {
                file << package.getName() << " " << package.getDropOffPoint() << " " << package.getDropOffDeadline() << '\n';
            }
            file.close();
            cout << "Packages saved to file: " << filename << '\n';
        }
        else {
            cout << "Failed to open file: " << filename << '\n';
        }
    }


    void start() {
        vectorDrone vectorDroneInstance;
        vectorPackage vectorPackageInstance;
        vector<Drone> drones = vectorDroneInstance.readDronesFromFile("E:/DEMO1/customizedDrone/drone_data.txt");
        vector<Package> packages = vectorPackageInstance.readPackagesFromFile("E:/customizedDrone/package_data.txt");
        cout << "                                          ******************************************" << endl;
        cout << "                                          *                                        *" << endl;
        cout << "                                          *           Welcome to the               *" << endl;
        cout << "                                          *        Drone Delivery System           *" << endl;
        cout << "                                          *                                        *" << endl;
        cout << "                                          ******************************************" << endl;

        int choice;
        while (true) {

            cout << "\nSelect an option:\n";
            cout << "1. Add Drone\n";
            cout << "2. Edit Drone\n";
            cout << "3. Delete Drone\n";
            cout << "4. Add Package\n";
            cout << "5. Edit Package\n";
            cout << "6. Delete Package\n";
            cout << "7. Display Matching Plan\n";
            cout << "8. Save Drones and Packages to Files\n";
            cout << "9. Save Matching Plan to File\n";
            cout << "10. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                vectorDroneInstance.addDrone(drones);
                break;
            case 2:
                vectorDroneInstance.editDrone(drones);
                break;
            case 3:
                vectorDroneInstance.deleteDrone(drones);
                break;
            case 4:
                vectorPackageInstance.addPackage(packages);
                break;
            case 5:
                vectorPackageInstance.editPackage(packages);
                break;
            case 6:
                vectorPackageInstance.deletePackage(packages);
                break;
            case 7: {
                vector<pair<Drone, Package>> matchingPlan = computeMatchingPlan(drones, packages);
                displayMatchingPlan(matchingPlan);
                displayMatchingPlanByLoadCapacity(matchingPlan);
                displayMatchingPlanByDeadline(matchingPlan);
                displayDronesNotAtFullLoad(drones);
                displayUnassignedPackages(packages, matchingPlan);
                break;
            }
            case 8: {
                string newDronesFile, newPackagesFile;
                cout << "Enter the filename to save the drones: ";
                cin >> newDronesFile;
                cout << "Enter the filename to save the packages: ";
                cin >> newPackagesFile;
                saveDronesToFile(drones, newDronesFile);
                savePackagesToFile(packages, newPackagesFile);
                break;
            }
            case 9: {
                string newMatchingPlanFile;
                cout << "Enter the filename to save the Matching Plan: ";
                cin >> newMatchingPlanFile;
                vector<pair<Drone, Package>> matchingPlan = computeMatchingPlan(drones, packages);
                saveMatchingPlanToFile(matchingPlan, newMatchingPlanFile);

                break;
            }
            case 10:
                cout << "Thank you for using the Drone Delivery System. Goodbye!\n";
             
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    
};

#endif