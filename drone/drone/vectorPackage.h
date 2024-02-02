#pragma once

#ifndef VECTORPACKAGE_H
#define VECTORPACKAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "package.h"

class vectorPackage {
public:
    std::vector<Package> readPackagesFromFile(const std::string& filename) {
        std::vector<Package> packages;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name, dropOffPoint, dropOffDeadline;
            while (file >> name >> dropOffPoint >> dropOffDeadline) {
                packages.emplace_back(name, dropOffPoint, dropOffDeadline);
            }
            file.close();
        }
        return packages;
    }

    void addPackage(std::vector<Package>& packages) {
        std::string name, dropOffPoint, dropOffDeadline;
        std::cout << "Enter package name: ";
        std::cin >> name;
        std::cout << "Enter package drop-off point: ";
        std::cin >> dropOffPoint;
        std::cout << "Enter package drop-off deadline: ";
        std::cin >> dropOffDeadline;

        packages.emplace_back(name, dropOffPoint, dropOffDeadline);
        std::cout << "Package added successfully.\n";
    }

    void editPackage(std::vector<Package>& packages) {
        std::string name;
        std::cout << "Enter the name of the package to edit: ";
        std::cin >> name;

        bool found = false;
        for (auto& package : packages) {
            if (package.getName() == name) {
                std::string newName, newDropOffPoint, newDropOffDeadline;
                std::cout << "Enter new package name: ";
                std::cin >> newName;
                std::cout << "Enter new package drop-off point: ";
                std::cin >> newDropOffPoint;
                std::cout << "Enter new package drop-off deadline: ";
                std::cin >> newDropOffDeadline;

                package.setName(newName);
                package.setDropOffPoint(newDropOffPoint);
                package.setDropOffDeadline(newDropOffDeadline);

                std::cout << "Package edited successfully.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Package not found.\n";
        }
    }

    void deletePackage(std::vector<Package>& packages) {
        std::string name;
        std::cout << "Enter the name of the package to delete: ";
        std::cin >> name;

        auto it = std::find_if(packages.begin(), packages.end(), [&](const Package& package) {
            return package.getName() == name;
            });

        if (it != packages.end()) {
            packages.erase(it);
            std::cout << "Package deleted successfully.\n";
        }
        else {
            std::cout << "Package not found.\n";
        }
    }

    void savePackagesToFile(const std::vector<Package>& packages, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& package : packages) {
                file << package.getName() << " " << package.getDropOffPoint() << " " << package.getDropOffDeadline() << '\n';
            }
            file.close();
            std::cout << "Packages saved to file: " << filename << '\n';
        }
        else {
            std::cout << "Failed to open file: " << filename << '\n';
        }
    }
};

#endif
