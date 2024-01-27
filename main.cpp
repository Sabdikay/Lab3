#include <iostream>
#include <vector>
#include <string>
#include <ctime>

enum class ServiceType { Mail, File, Network };
enum class ConnectionType { Input, Output };

std::string formatDateTime(std::time_t dateTime) {
    std::tm *ptm = std::localtime(&dateTime);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", ptm);
    return std::string(buffer);
}

class NetworkService {
public:
    virtual ServiceType getType() const = 0;
    virtual ConnectionType getConnectionType() const = 0;
    virtual std::string getAddress() const = 0;
    virtual void setAddress(const std::string& addr) = 0;
    virtual double calculateCost() const = 0;
    virtual std::string getDateTime() const = 0;
    virtual double getVolume() const = 0;
    virtual void setVolume(double newVolume) = 0;
    virtual ~NetworkService() {}
};

class MailDescriptor : public NetworkService {
protected:
    ConnectionType connectionType;
    std::string address;
    std::time_t dateTime;
    double volume;

public:
    MailDescriptor(ConnectionType type, std::string addr, std::time_t dt, double vol)
        : connectionType(type), address(addr), dateTime(dt), volume(vol) {}

    ServiceType getType() const override { return ServiceType::Mail; }
    ConnectionType getConnectionType() const override { return connectionType; }
    std::string getAddress() const override { return address; }
    void setAddress(const std::string& addr) override { address = addr; }
    double calculateCost() const override { return volume * 0.05; }
    std::string getDateTime() const override { return formatDateTime(dateTime); }
    double getVolume() const override { return volume; }
    void setVolume(double newVolume) override { volume = newVolume; }
};

class FileDescriptor : public NetworkService {
protected:
    ConnectionType connectionType;
    std::string address;
    std::time_t dateTime;
    double volume;

public:
    FileDescriptor(ConnectionType type, std::string addr, std::time_t dt, double vol)
        : connectionType(type), address(addr), dateTime(dt), volume(vol) {}

    ServiceType getType() const override { return ServiceType::File; }
    ConnectionType getConnectionType() const override { return connectionType; }
    std::string getAddress() const override { return address; }
    void setAddress(const std::string& addr) override { address = addr; }
    double calculateCost() const override { return volume * 0.05; }
    std::string getDateTime() const override { return formatDateTime(dateTime); }
    double getVolume() const override { return volume; }
    void setVolume(double newVolume) override { volume = newVolume; }
};

class NetworkDescriptor : public NetworkService {
protected:
    std::string senderAddress;
    std::time_t dateTime;
    int duration;
    double volume;

public:
    NetworkDescriptor(std::string senderAddr, std::time_t dt, int dur, double vol)
        : senderAddress(senderAddr), dateTime(dt), duration(dur), volume(vol) {}

    ServiceType getType() const override { return ServiceType::Network; }
    ConnectionType getConnectionType() const override { return ConnectionType::Output; }
    std::string getAddress() const override { return senderAddress; }
    void setAddress(const std::string& addr) override { senderAddress = addr; }
    double calculateCost() const override { return volume * 0.05 + duration * 0.1; }
    std::string getDateTime() const override { return formatDateTime(dateTime); }
    double getVolume() const override { return volume; }
    void setVolume(double newVolume) override { volume = newVolume; }
};

class Subscriber {
private:
    std::string networkAddress;

public:
    Subscriber(std::string addr) : networkAddress(addr) {}
    std::string getAddress() const { return networkAddress; }
};

class Table {
private:
    std::vector<NetworkService*> services;

public:
    void addService(NetworkService* service) {
        services.push_back(service);
    }

    std::vector<NetworkService*> getAllServices() const {
        return services;
    }

    void display() const {
        for (const auto* service : services) {
            std::cout << "Адрес: " << service->getAddress() << "\n"
                      << "Тип сервиса: " << static_cast<int>(service->getType()) << "\n"
                      << "Время: " << service->getDateTime() << "\n"
                      << "Стоимость: " << service->calculateCost() << std::endl;
        }
    }
};

class ServerDescriptor {
private:
    std::string networkAddress;
    std::string networkName;
    Table connectionTable;

public:
    ServerDescriptor(std::string addr, std::string name)
        : networkAddress(addr), networkName(name) {}

    std::string getNetworkAddress() const { return networkAddress; }

    void addSubscriber(NetworkService* service) {
        connectionTable.addService(service);
    }

    NetworkService* findServiceByAddress(const std::string& address) const {
        auto services = connectionTable.getAllServices();
        for (auto* service : services) {
            if (service->getAddress() == address) {
                return service;
            }
        }
        return nullptr;
    }

    void displayConnectionTable() const {
        connectionTable.display();
    }
};

class Application {
private:
    Table connectionTable;

public:
    void addService(NetworkService* service) {
        connectionTable.addService(service);
    }

    void displayServicesForSubscriber(const std::string& subscriberAddress) const {
    auto services = connectionTable.getAllServices();
    bool serviceFound = false;

    for (const auto* service : services) {
        if (service->getAddress() == subscriberAddress) {
            std::cout << "Адрес: " << service->getAddress() << "\n"
                      << "Тип сервиса: " << static_cast<int>(service->getType()) << "\n"
                      << "Время: " << service->getDateTime() << "\n"
                      << "Стоимость: " << service->calculateCost() << std::endl;
            serviceFound = true;
        }
    }

    if (!serviceFound) {
        std::cout << "Услуги для абонента с адресом " << subscriberAddress << " не найдены." << std::endl;
    }
}

};

int main() {
    setlocale(LC_ALL, "Russian");

    ServerDescriptor server("192.168.1.1", "MainServer");
    Application app;

    // Демонстрация создания различных сервисов
    MailDescriptor mailService(ConnectionType::Output, "192.168.1.2", std::time(nullptr), 10);
    FileDescriptor fileService(ConnectionType::Input, "192.168.1.3", std::time(nullptr), 15);
    NetworkDescriptor networkService("192.168.1.4", std::time(nullptr), 30, 20);

    // Добавление сервисов в таблицу сервера
    server.addSubscriber(&mailService);
    server.addSubscriber(&fileService);
    server.addSubscriber(&networkService);

    // Добавление сервисов в приложение
    app.addService(&mailService);
    app.addService(&fileService);
    app.addService(&networkService);

    bool running = true;
    while (running) {
        int choice;
        std::cout << "1. Показать таблицу соединений сервера\n";
        std::cout << "2. Показать услуги для конкретного абонента\n";
        std::cout << "3. Выйти\n";
        std::cout << "Выберите операцию: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                server.displayConnectionTable();
                break;
            }
            case 2: {
                std::string address;
                std::cout << "Введите сетевой адрес абонента: ";
                std::cin >> address;
                app.displayServicesForSubscriber(address);
                break;
            }
            case 3:
                running = false;
                break;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}

