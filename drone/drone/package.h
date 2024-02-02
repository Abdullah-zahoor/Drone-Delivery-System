#pragma once
#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

class Package {
private:
    std::string name;
    std::string dropOffPoint;
    std::string dropOffDeadline;

public:
    Package(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline);

    std::string getName() const;
    std::string getDropOffPoint() const;
    std::string getDropOffDeadline() const;
    void setName(const std::string& name);
    void setDropOffPoint(const std::string& dropOffPoint);
    void setDropOffDeadline(const std::string& dropOffDeadline);
};




#endif  
