
#pragma once
#include "Server.h"
#include <vector>

class NetworkApplication {
    Server* server;
    std::vector<NetworkService*> services;

public:
    NetworkApplication(Server* server);
    ~NetworkApplication();
    void addService(NetworkService* service);
    void displayServicesForSubscriber(const std::string& address) const;
    double calculateTotalCostForSubscriber(const std::string& address) const;
    void calculateNetworkBalance() const; // Using an iterator class for calculation
};
