#include <iostream>
#include "vehicle.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Car* c = new Car("BMW", 2022, 3.0, false, 5);
    c->info();
    c->toggleEngine();
    delete c;

    Truck* t = new Truck("Volvo", 2018, 12.0, false, 25.0);
    t->info();
    t->toggleEngine();
    delete t;

    ElectricCar* e = new ElectricCar("Tesla", 2023, 0.0, false, 4, 120.0);
    e->info();
    e->toggleEngine();
    delete e;

    Vehicle* fleet[3];
    fleet[0] = new Car("Kia", 2021, 1.6, false, 4);
    fleet[1] = new Truck("MAN", 2019, 15.0, false, 30.0);
    fleet[2] = new ElectricCar("Nissan Leaf", 2022, 0.0, false, 5, 40.0);

    for (int i = 0; i < 3; i++) {
        fleet[i]->info();
        fleet[i]->toggleEngine();
    }

    for (int i = 0; i < 3; i++) {
        delete fleet[i];
    }

    int choice;
    cout << "Выберите тип транспортного средства (2-Car, 3-Truck, 4-ElectricCar): ";
    cin >> choice;

    Vehicle* userObj = nullptr;
    try {
        if (choice == 2) userObj = new Car("UserCar", 2022, 3.0, false, 5);
        else if (choice == 3) userObj = new Truck("UserTruck", 2018, 12.0, false, 25.0);
        else if (choice == 4) userObj = new ElectricCar("UserElectric", 2023, 0.0, false, 4, 120.0);
        else throw ValueException("Неверный выбор типа ТС");

        userObj->info();
        userObj->toggleEngine();
    }
    catch (const ValueException& ex) {
        cout << "Ошибка (ValueException): " << ex.what() << endl;
        cout << "Создан Car по умолчанию." << endl;
    }
    catch (const BrandException& ex) {
        cout << "Ошибка (BrandException): " << ex.what() << endl;
    }
    catch (const InvalidVehicleException& ex) {
        cout << "Ошибка (InvalidVehicleException): " << ex.what() << endl;
    }
    delete userObj;
    userObj = nullptr;

    Car staticCar("StaticCar", 2020, 2.5, false, 4);
    Truck staticTruck("StaticTruck", 2015, 10.0, false, 20.0);
    ElectricCar staticElectric("StaticElectric", 2024, 0.0, false, 4, 100.0);

    staticCar.info();
    staticCar.toggleEngine();

    staticTruck.info();
    staticTruck.toggleEngine();

    staticElectric.info();
    staticElectric.toggleEngine();

    cout << endl;
    cout << "Демонстрация класса Fleet" << endl;

    Fleet fleet1;
    cout << "Название: " << fleet1.getFleetName() << endl;
    fleet1.showMainVehicle();
    fleet1.toggleMainVehicleEngine();

    cout << endl;

    Fleet fleet2("Городской парк", 3);
    cout << "Название: " << fleet2.getFleetName() << endl;
    fleet2.showMainVehicle();
    fleet2.toggleMainVehicleEngine();

    cout << endl;
    cout << "Изменение параметров (fleet1)" << endl;
    try {
        fleet1.changeBrand("Lada");
        fleet1.changeYear(2024);
        fleet1.changeEngineVolume(2.0);
        fleet1.changeIsRunning(true);
        fleet1.changeDoorsCount(3);
        fleet1.changePayload(10.0);
        fleet1.changeBatteryCapacity(50.0);
    }
    catch (const ValueException& ex) {
        cout << "Ошибка (ValueException): " << ex.what() << endl;
    }
    catch (const BrandException& ex) {
        cout << "Ошибка (BrandException): " << ex.what() << endl;
    }
    catch (const InvalidVehicleException& ex) {
        cout << "Ошибка (InvalidVehicleException): " << ex.what() << endl;
    }
    fleet1.showMainVehicle();

    cout << endl;
    cout << "Изменение параметров (fleet2)" << endl;
    try {
        fleet2.changeBrand("Scania");
        fleet2.changeYear(2020);
        fleet2.changeEngineVolume(16.0);
        fleet2.changeIsRunning(true);
        fleet2.changeDoorsCount(2);
        fleet2.changePayload(40.0);
        fleet2.changeBatteryCapacity(80.0);
    }
    catch (const ValueException& ex) {
        cout << "Ошибка (ValueException): " << ex.what() << endl;
    }
    catch (const BrandException& ex) {
        cout << "Ошибка (BrandException): " << ex.what() << endl;
    }
    catch (const InvalidVehicleException& ex) {
        cout << "Ошибка (InvalidVehicleException): " << ex.what() << endl;
    }
    fleet2.showMainVehicle();

    cout << endl;
    cout << "Статический метод Fleet::create" << endl;
    try {
        Fleet* fleet3 = Fleet::create("Новый парк", 4);
        cout << "Название: " << fleet3->getFleetName() << endl;
        fleet3->showMainVehicle();
        delete fleet3;
    }
    catch (const ValueException& ex) {
        cout << "Ошибка (ValueException): " << ex.what() << endl;
    }
    catch (const BrandException& ex) {
        cout << "Ошибка (BrandException): " << ex.what() << endl;
    }
    catch (const InvalidVehicleException& ex) {
        cout << "Ошибка (InvalidVehicleException): " << ex.what() << endl;
    }

    cout << endl;
    cout << "Демонстрация трёх типов исключений" << endl;

    try {
        Car demo("Demo", 2022, 2.0, false, 4);
        demo.setYear(1000);
    }
    catch (const ValueException& ex) {
        cout << "[ValueException] " << ex.what() << endl;
    }

    try {
        Car demo("Demo", 2022, 2.0, false, 4);
        demo.setBrand("");
    }
    catch (const BrandException& ex) {
        cout << "[BrandException] " << ex.what() << endl;
    }

    try {
        Car demo("Demo", 2022, 0.0, false, 4);
        demo.toggleEngine();
    }
    catch (const InvalidVehicleException& ex) {
        cout << "[InvalidVehicleException] " << ex.what() << endl;
    }

    cout << endl;
    cout << "Выход из main — деструкторы:" << endl;
    return 0;
}
