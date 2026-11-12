#include "vehicle.h"

Vehicle::Vehicle(string b, int y, double v, bool r) {
    cout << "[Vehicle Constructor]" << endl;
    brand = new string(b);
    year = new int(y);
    engineVolume = new double(v);
    isRunning = new bool(r);
}

Vehicle::~Vehicle() {
    cout << "[Vehicle Destructor]" << endl;
    delete brand;
    delete year;
    delete engineVolume;
    delete isRunning;
}

void Vehicle::setBrand(string b) {
    if (b.empty()) throw BrandException("Бренд не может быть пустым");
    if (b.length() > 50) throw BrandException("Бренд слишком длинный (макс. 50 символов)");
    *brand = b;
}

void Vehicle::setYear(int y) {
    if (y < 1886 || y > 2100) throw ValueException("Год должен быть в диапазоне 1886..2100");
    *year = y;
}

void Vehicle::setEngineVolume(double v) {
    if (v < 0.0 || v > 50.0) throw ValueException("Объём двигателя должен быть 0..50 л");
    *engineVolume = v;
}

void Vehicle::setIsRunning(bool r) { *isRunning = r; }
string Vehicle::getBrand() { return *brand; }
int Vehicle::getYear() { return *year; }
double Vehicle::getEngineVolume() { return *engineVolume; }
bool Vehicle::getIsRunning() { return *isRunning; }

Car::Car(string b, int y, double v, bool r, int d) : Vehicle(b, y, v, r) {
    cout << "[Car Constructor]" << endl;
    doorsCount = new int(d);
}

Car::~Car() {
    cout << "[Car Destructor]" << endl;
    delete doorsCount;
}

void Car::setDoorsCount(int d) {
    if (d < 2 || d > 6) throw ValueException("Количество дверей должно быть 2..6");
    *doorsCount = d;
}

int Car::getDoorsCount() { return *doorsCount; }

void Car::toggleEngine() {
    if (!*isRunning && *engineVolume <= 0.0) throw InvalidVehicleException("Нельзя завести автомобиль с нулевым объёмом двигателя");
    *isRunning = !*isRunning;
    cout << "Двигатель автомобиля " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
}

void Car::info() {
    cout << "Автомобиль " << *brand << ", год: " << *year
        << ", объём: " << *engineVolume << " л"
        << ", дверей: " << *doorsCount
        << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
}

Truck::Truck(string b, int y, double v, bool r, double p) : Vehicle(b, y, v, r) {
    cout << "[Truck Constructor]" << endl;
    payload = new double(p);
}

Truck::~Truck() {
    cout << "[Truck Destructor]" << endl;
    delete payload;
}

void Truck::setPayload(double p) {
    if (p <= 0.0 || p > 100.0) throw ValueException("Грузоподъёмность должна быть 0..100 т");
    *payload = p;
}

double Truck::getPayload() { return *payload; }

void Truck::toggleEngine() {
    if (!*isRunning && *engineVolume <= 0.0) throw InvalidVehicleException("Нельзя завести грузовик с нулевым объёмом двигателя");
    *isRunning = !*isRunning;
    cout << "Двигатель грузовика " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
}

void Truck::info() {
    cout << "Грузовик " << *brand << ", год: " << *year
        << ", объём: " << *engineVolume << " л"
        << ", грузоподъёмность: " << *payload << " т"
        << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
}

ElectricCar::ElectricCar(string b, int y, double v, bool r, int d, double c) : Car(b, y, v, r, d) {
    cout << "[ElectricCar Constructor]" << endl;
    batteryCapacity = new double(c);
}

ElectricCar::~ElectricCar() {
    cout << "[ElectricCar Destructor]" << endl;
    delete batteryCapacity;
}

void ElectricCar::setBatteryCapacity(double c) {
    if (c <= 0.0 || c > 1000.0) throw ValueException("Ёмкость батареи должна быть 0..1000 кВт·ч");
    *batteryCapacity = c;
}

double ElectricCar::getBatteryCapacity() { return *batteryCapacity; }

void ElectricCar::toggleEngine() {
    *isRunning = !*isRunning;
    cout << "Электродвигатель " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
}

void ElectricCar::info() {
    cout << "Электромобиль " << *brand << ", год: " << *year
        << ", дверей: " << *doorsCount
        << ", батарея: " << *batteryCapacity << " кВт·ч"
        << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
}

Fleet::Fleet() {
    cout << "[Fleet Constructor]" << endl;
    mainVehicle = nullptr;
    fleetName = nullptr;
    try {
        mainVehicle = new Car();
        fleetName = new string("Без названия");
    }
    catch (...) {
        delete mainVehicle;
        delete fleetName;
        throw;
    }
}

Fleet::Fleet(string name, int type) {
    cout << "[Fleet Constructor]" << endl;
    mainVehicle = nullptr;
    fleetName = nullptr;
    try {
        if (type != 2 && type != 3 && type != 4) throw ValueException("Неверный тип ТС (ожидается 2, 3 или 4)");
        if (type == 2) mainVehicle = new Car("Kia", 2021, 1.6, false, 4);
        else if (type == 3) mainVehicle = new Truck("MAN", 2019, 15.0, false, 30.0);
        else mainVehicle = new ElectricCar("Nissan Leaf", 2022, 0.0, false, 5, 40.0);
        fleetName = new string(name);
    }
    catch (...) {
        delete mainVehicle;
        delete fleetName;
        throw;
    }
}

Fleet::~Fleet() {
    cout << "[Fleet Destructor]" << endl;
    delete mainVehicle;
    delete fleetName;
}

string Fleet::getFleetName() { return *fleetName; }

void Fleet::showMainVehicle() {
    cout << "Главное ТС автопарка: ";
    mainVehicle->info();
}

void Fleet::toggleMainVehicleEngine() { mainVehicle->toggleEngine(); }

void Fleet::changeBrand(string b) { mainVehicle->setBrand(b); }
void Fleet::changeYear(int y) { mainVehicle->setYear(y); }
void Fleet::changeEngineVolume(double v) { mainVehicle->setEngineVolume(v); }
void Fleet::changeIsRunning(bool r) { mainVehicle->setIsRunning(r); }

bool Fleet::changeDoorsCount(int d) {
    Car* car = dynamic_cast<Car*>(mainVehicle);
    if (car == nullptr) throw InvalidVehicleException("Главное ТС не Car — двери не изменить.");
    car->setDoorsCount(d);
    return true;
}

bool Fleet::changePayload(double p) {
    Truck* truck = dynamic_cast<Truck*>(mainVehicle);
    if (truck == nullptr) throw InvalidVehicleException("Главное ТС не Truck — грузоподъёмность не изменить.");
    truck->setPayload(p);
    return true;
}

bool Fleet::changeBatteryCapacity(double c) {
    ElectricCar* ec = dynamic_cast<ElectricCar*>(mainVehicle);
    if (ec == nullptr) throw InvalidVehicleException("Главное ТС не ElectricCar — батарею не изменить.");
    ec->setBatteryCapacity(c);
    return true;
}

Fleet* Fleet::create(string name, int type) {
    return new Fleet(name, type);
}
