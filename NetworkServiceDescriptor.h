#ifndef NETWORK_SERVICE_DESCRIPTOR_H
#define NETWORK_SERVICE_DESCRIPTOR_H

#include <string>
#include <chrono>

enum class ServiceType { Mail, File, Network };
enum class ConnectionType { Send, Receive };

class NetworkServiceDescriptor {
private:
    ServiceType serviceType;
    ConnectionType connectionType;
    std::string address;
    std::chrono::system_clock::time_point connectionTime;
    size_t dataSize;
    std::chrono::duration<double> connectionDuration;
    size_t incomingTraffic, outgoingTraffic;

public:
    NetworkServiceDescriptor(ServiceType st, ConnectionType ct, const std::string &addr,
                             std::chrono::system_clock::time_point time, size_t size,
                             std::chrono::duration<double> duration, size_t inTraffic, size_t outTraffic)
        : serviceType(st), connectionType(ct), address(addr), connectionTime(time),
          dataSize(size), connectionDuration(duration), incomingTraffic(inTraffic), outgoingTraffic(outTraffic) {}

    // Accessor functions
    ServiceType getServiceType() const { return serviceType; }
    ConnectionType getConnectionType() const { return connectionType; }
    std::string getAddress() const { return address; }
    std::chrono::system_clock::time_point getConnectionTime() const { return connectionTime; }
    size_t getDataSize() const { return dataSize; }
    std::chrono::duration<double> getConnectionDuration() const { return connectionDuration; }
    size_t getIncomingTraffic() const { return incomingTraffic; }
    size_t getOutgoingTraffic() const { return outgoingTraffic; }

    // Calculate service cost (dummy implementation)
   double NetworkServiceDescriptor::calculateServiceCost() {
    double cost = 0.0;

    // Пример расчета стоимости на основе длительности и объема данных
    double costPerMinute = 10tg; // Стоимость в минуту, установите подходящее значение
    double costPerMB = 5tg; // Стоимость за MB, установите подходящее значение

    cost += this->connectionDuration * costPerMinute; // Стоимость на основе длительности соединения
    cost += this->dataSize * costPerMB; // Стоимость на основе объема переданных данных

    // Дополнительные условия в зависимости от типа сервиса
    //if (this->serviceType == /* тип сервиса */) {
        // Дополнительные расчеты для конкретного типа сервиса
    //}

    // Другие расчеты по необходимости

    return cost;
}

};

#endif // NETWORK_SERVICE_DESCRIPTOR_H
