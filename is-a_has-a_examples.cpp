/**
 * @file    vehicles.cpp
 * @brief   CISP-1010: is-a and has-a relationships, live build.
 *
 * Build this in class one STEP at a time, compiling after each step.
 *
 * Relationships modeled:
 *  - Car   is-a  Vehicle   (inheritance)
 *  - Truck is-a  Vehicle   (inheritance)
 *  - Vehicle has-a Engine  (composition: the Vehicle owns it)
 *  - Vehicle has-a Driver  (aggregation: the Vehicle only points to one)
 *
 * The constructors and destructors print a line each, so the output
 * shows the order in which objects are built and destroyed.
 */

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
// STEP 1: Engine, a small class that will be a PART of a Vehicle.
// ---------------------------------------------------------------------------

/**
 * @brief An engine that is part of a Vehicle.
 *
 * Used for composition: each Vehicle contains its own Engine as a
 * member object, so the Engine is created and destroyed with it.
 */
class Engine
{
private:
    int horsepower;   ///< The engine's power output, in horsepower.

public:
    /**
     * @brief Constructs an Engine.
     * @param hp The engine's horsepower.
     */
    Engine(int hp) : horsepower(hp)
    {
        cout << "  Engine constructed\n";
    }

    /**
     * @brief Destroys the Engine and reports it.
     */
    ~Engine()
    {
        cout << "  Engine destroyed\n";
    }

    /**
     * @brief Gets the engine's horsepower.
     * @return The horsepower.
     */
    int getHorsepower() const
    {
        return horsepower;
    }
};

// ---------------------------------------------------------------------------
// STEP 2: Driver exists on its own. Vehicles point to one but don't own it.
// ---------------------------------------------------------------------------

/**
 * @brief A person who can be assigned to drive a Vehicle.
 *
 * Used for aggregation: a Driver exists independently of any Vehicle,
 * can be shared by several vehicles, and outlives them.
 */
class Driver
{
private:
    string name;   ///< The driver's name.

public:
    /**
     * @brief Constructs a Driver.
     * @param n The driver's name.
     */
    Driver(string n) : name(n)
    {}

    /**
     * @brief Gets the driver's name.
     * @return The name.
     */
    string getName() const
    {
        return name;
    }
};

// ---------------------------------------------------------------------------
// STEP 3: Vehicle, the base class.
// ---------------------------------------------------------------------------

/**
 * @brief Base class for all vehicles.
 *
 * - Has-a Engine by composition: a member object that the Vehicle owns.
 * - Has-a Driver by aggregation: a pointer to a Driver the Vehicle does
 *   not own and never deletes.
 *
 * @see Car
 * @see Truck
 */
class Vehicle
{
protected:
    string make;     ///< Manufacturer. Protected, so derived classes can use it directly.

private:
    int year;        ///< Model year.
    Engine engine;   ///< Composition: built and destroyed with the Vehicle.
    Driver* driver;  ///< Aggregation: the current driver, or nullptr. Not owned.

public:
    /**
     * @brief Constructs a Vehicle with no driver assigned.
     *
     * Engine has no default constructor, so @c engine must be
     * initialized in the member initialization list.
     *
     * @param m  The manufacturer.
     * @param y  The model year.
     * @param hp The engine's horsepower.
     */
    Vehicle(string m, int y, int hp)
        : make(m), year(y), engine(hp), driver(nullptr)
    {
        cout << "  Vehicle constructed\n";
    }

    /**
     * @brief Destroys the Vehicle and reports it.
     *
     * Does not delete @c driver: the Vehicle does not own it.
     */
    ~Vehicle()
    {
        cout << "  Vehicle destroyed\n";
    }

    /**
     * @brief Assigns a driver to this Vehicle, replacing any current one.
     * @param d Pointer to a Driver that must outlive this Vehicle,
     *          or nullptr for no driver.
     */
    void assignDriver(Driver* d)
    {
        driver = d;
    }

    /**
     * @brief Prints the year, make, horsepower and driver, with no newline.
     *
     * Derived classes redefine this function and call it to print
     * the Vehicle part of their information.
     */
    void print() const
    {
        cout << year << " " << make << ", "
            << engine.getHorsepower() << " hp, driver: "
            << (driver ? driver->getName() : "none");
    }
};

// ---------------------------------------------------------------------------
// STEP 4: Car IS-A Vehicle.
// ---------------------------------------------------------------------------

/**
 * @brief A passenger car. A Car is-a Vehicle.
 *
 * Shows passing arguments to the base class constructor, redefining
 * a base class function, and using a protected base member.
 */
class Car : public Vehicle
{
private:
    int doors;   ///< Number of doors.

public:
    /**
     * @brief Constructs a Car.
     *
     * The Vehicle part, including its Engine, is built before
     * this constructor's body runs.
     *
     * @param m  The manufacturer.
     * @param y  The model year.
     * @param hp The engine's horsepower.
     * @param d  The number of doors.
     */
    Car(string m, int y, int hp, int d)
        : Vehicle(m, y, hp), doors(d)
    {
        cout << "  Car constructed\n";
    }

    /**
     * @brief Destroys the Car and reports it.
     *
     * Runs before the Vehicle destructor.
     */
    ~Car()
    {
        cout << "  Car destroyed\n";
    }

    /**
     * @brief Prints the Car's information, followed by a newline.
     *
     * Redefines Vehicle::print() and calls it for the shared fields.
     */
    void print() const
    {
        cout << "Car:   ";
        Vehicle::print();                    // reuse the base version
        cout << ", " << doors << " doors\n";
    }

    /**
     * @brief Prints a horn message using the car's make.
     *
     * Reads @c make directly, which is allowed because it is protected
     * in Vehicle.
     */
    void honk() const
    {
        cout << "The " << make << " goes beep beep!\n";
    }
};

// ---------------------------------------------------------------------------
// STEP 5: Truck IS-A Vehicle. (Good one for students to write first.)
// ---------------------------------------------------------------------------

/**
 * @brief A cargo truck. A Truck is-a Vehicle.
 */
class Truck : public Vehicle
{
private:
    double payloadTons;   ///< Maximum cargo weight, in tons.

public:
    /**
     * @brief Constructs a Truck.
     * @param m    The manufacturer.
     * @param y    The model year.
     * @param hp   The engine's horsepower.
     * @param tons The maximum payload, in tons.
     */
    Truck(string m, int y, int hp, double tons)
        : Vehicle(m, y, hp), payloadTons(tons)
    {
        cout << "  Truck constructed\n";
    }

    /**
     * @brief Destroys the Truck and reports it.
     *
     * Runs before the Vehicle destructor.
     */
    ~Truck()
    {
        cout << "  Truck destroyed\n";
    }

    /**
     * @brief Prints the Truck's information, followed by a newline.
     *
     * Redefines Vehicle::print() and calls it for the shared fields.
     */
    void print() const
    {
        cout << "Truck: ";
        Vehicle::print();
        cout << ", hauls " << payloadTons << " tons\n";
    }
};

// ---------------------------------------------------------------------------
// STEP 8: is-a means a Car or Truck can be passed where a Vehicle is expected.
// ---------------------------------------------------------------------------

/**
 * @brief Prints any Vehicle, followed by a newline.
 *
 * Accepts a Car or a Truck because each is-a Vehicle. Because
 * Vehicle::print() is not virtual, the Vehicle version always runs here.
 *
 * @param v The vehicle to describe.
 */
void describe(const Vehicle& v)
{
    cout << "Some vehicle: ";
    v.print();      // which print() runs? (Vehicle's: preview of virtual)
    cout << "\n";
}

/**
 * @brief Builds a Car and a Truck, assigns drivers, and prints them.
 * @return 0 on success.
 */
int main()
{
    // STEP 6: Drivers are created first and live on their own.
    Driver ana("Ana");
    Driver ben("Ben");

    // Watch the order: Engine, then Vehicle, then Car.
    cout << "Building a Car:\n";
    Car car("Honda", 2022, 180, 4);

    cout << "\nBuilding a Truck:\n";
    Truck truck("Ford", 2019, 400, 2.5);

    // STEP 7: Aggregation. One Driver can be shared, and reassigned.
    cout << "\n";
    car.assignDriver(&ana);
    truck.assignDriver(&ana);
    car.print();
    truck.print();

    cout << "\nAna hands the truck to Ben:\n";
    truck.assignDriver(&ben);
    truck.print();

    cout << "\n";
    car.honk();

    // STEP 8: Substitution (is-a).
    cout << "\n";
    describe(car);
    describe(truck);

    // STEP 9: Uncomment one at a time. Each should FAIL to compile. Why?
    // car.make = "Kia";              // make is protected
    // car.engine.getHorsepower();    // engine is private to Vehicle
    // Vehicle v("Kia", 2020, 150);
    // v.honk();                      // a Vehicle is not a Car

    // Watch the order: Truck, Vehicle, Engine (reverse of construction).
    // Ana and Ben are destroyed last: they outlive the vehicles.
    cout << "\nEnd of main:\n";
    return 0;
}

// ---------------------------------------------------------------------------
// Extensions to try:
//  1. Add Motorcycle IS-A Vehicle with a bool hasSidecar.
//  2. Give Engine a second member (cylinders). What has to change in Car?
//  3. Add a Garage that HAS-A list of Vehicle* it does not own.
//  4. Make print() virtual in Vehicle and run describe() again.
// ---------------------------------------------------------------------------
