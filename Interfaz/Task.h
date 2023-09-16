
#pragma once
#include <string>

class Task {
public:
    std::string filterType;
    std::string status; // New field for status

    Task() : filterType(""), status("Pending") {}
};
