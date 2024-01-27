#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include <unordered_map>
#include <memory>
#include<map>
#include <string>
#include "NetworkServiceDescriptor.h"

class NetworkServer {
private:
    std::string networkAddress;
    std::string networkName;
    double costPerMinute;
    double costPerMB;
    std::map<std::string, NetworkServiceDescriptor*> connectionTable;

public:
    NetworkServer(const std::string &address, const std::string &name, double costMinute, double costMB)
        : networkAddress(address), networkName(name), costPerMinute(costMinute), costPerMB(costMB) {}

    // Getters
    std::string getNetworkAddress() const { return networkAddress; }
    double getCostPerMinute() const { return costPerMinute; }
    double getCostPerMB() const { return costPerMB; }

    // Add/Delete/Find connection


void addConnection(const std::string& address, NetworkServiceDescriptor* descriptor) {
        if (connectionTable.find(address) != connectionTable.end()) {
            std::cerr << "Ошибка: Соединение с адресом " << address << " уже существует." << std::endl;
        } else {
            connectionTable[address] = descriptor;
        }
    }

    void deleteConnection(const std::string& address) {
        auto it = connectionTable.find(address);
        if (it == connectionTable.end()) {
            std::cerr << "Ошибка: Соединение с адресом " << address << " не найдено." << std::endl;
        } else {
            connectionTable.erase(it);
        }
    }

    NetworkServiceDescriptor* findConnection(const std::string& address) {
        auto it = connectionTable.find(address);
        if (it == connectionTable.end()) {
            std::cerr << "Ошибка: Соединение с адресом " << address << " не найдено." << std::endl;
            return nullptr;
        } else {
            return it->second;
        }
    }

    void displayAllConnections() {
        if (connectionTable.empty()) {
            std::cout << "Нет активных соединений." << std::endl;
            return;
        }

        std::cout << "Активные соединения:" << std::endl;
        for (const auto& pair : connectionTable) {
            std::cout << "Адрес: " << pair.first
                      << ", Сервис: " << pair.second->getServiceType()
                      // Дополнительные детали соединения
                      << std::endl;
        }
    }
};



#endif // NETWORK_SERVER_H
