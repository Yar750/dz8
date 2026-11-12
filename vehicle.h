#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

using namespace std;

class InvalidVehicleException {
private:
    string message;
public:
    InvalidVehicleException(string msg) : message(msg) {}
    string what() const { return message; }
};

class BrandException : public InvalidVehicleException {
public:
    BrandException(string msg) : InvalidVehicleException(msg) {}
};

class ValueException : public InvalidVehicleException {
public:
    ValueException(string msg) : InvalidVehicleException(msg) {}
};

class Vehicle {
protected:
    string* brand;
    int* year;
    double* engineVolume;
    bool* isRunning;

public:
    Vehicle(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false);
    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;
    virtual ~Vehicle();

    void setBrand(string b);
    void setYear(int y);
    void setEngineVolume(double v);
    void setIsRunning(bool r);

    string getBrand();
    int getYear();
    double getEngineVolume();
    bool getIsRunning();

    virtual void toggleEngine() = 0;
    virtual void info() = 0;
};

class Car : public Vehicle {
protected:
    int* doorsCount;

public:
    Car(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false, int d = 4);
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;
    ~Car() override;

    void setDoorsCount(int d);
    int getDoorsCount();

    void toggleEngine() override;
    void info() override;
};

class Truck : public Vehicle {
protected:
    double* payload;

public:
    Truck(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false, double p = 5.0);
    Truck(const Truck&) = delete;
    Truck& operator=(const Truck&) = delete;
    ~Truck() override;

    void setPayload(double p);
    double getPayload();

    void toggleEngine() override;
    void info() override;
};

class ElectricCar : public Car {
protected:
    double* batteryCapacity;

public:
    ElectricCar(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false, int d = 4, double c = 60.0);
    ElectricCar(const ElectricCar&) = delete;
    ElectricCar& operator=(const ElectricCar&) = delete;
    ~ElectricCar() override;

    void setBatteryCapacity(double c);
    double getBatteryCapacity();

    void toggleEngine() override;
    void info() override;
};

class Fleet {
private:
    string* fleetName;
    Vehicle* mainVehicle;

public:
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;
    Fleet();
    Fleet(string name, int type);
    ~Fleet();

    string getFleetName();
    void showMainVehicle();
    void toggleMainVehicleEngine();

    void changeBrand(string b);
    void changeYear(int y);
    void changeEngineVolume(double v);
    void changeIsRunning(bool r);

    bool changeDoorsCount(int d);
    bool changePayload(double p);
    bool changeBatteryCapacity(double c);

    static Fleet* create(string name, int type);
};

#endif
