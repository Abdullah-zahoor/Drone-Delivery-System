#include "package.h"
using namespace std;
Package::Package(const std::string& name, const std::string& dropOffPoint, const std::string& dropOffDeadline)
    : name(name), dropOffPoint(dropOffPoint), dropOffDeadline(dropOffDeadline) {}

string Package::getName() const {
    return name;
}

string Package::getDropOffPoint() const {
    return dropOffPoint;
}

string Package::getDropOffDeadline() const {
    return dropOffDeadline;
}

void Package::setName(const std::string& name) {
    this->name = name;
}

void Package::setDropOffPoint(const std::string& dropOffPoint) {
    this->dropOffPoint = dropOffPoint;
}

void Package::setDropOffDeadline(const std::string& dropOffDeadline) {
    this->dropOffDeadline = dropOffDeadline;
}

