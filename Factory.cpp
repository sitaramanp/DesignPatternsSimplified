// Also called virtual constructor, it helps in defering instantiation of a class. This creation would be done at run time. 
// Example talks about a console vehicle driving game in the streets. User has the option to choose among a bike, car , truck.

#include<iostream>
#include<memory>

namespace factory
{
	enum vehicle { BIKE, CAR, TRUCK};
};

class AbstractVehicle
{
public:
	virtual void drive() = 0;
};

class Bike:public AbstractVehicle
{
public:
	void drive() { std::cout << " Driving Bike " << std::endl;}
};

class Car:public AbstractVehicle
{
public:
	void drive() { std::cout << " Driving Car " << std::endl;}
};

class Truck:public AbstractVehicle
{
public:
	void drive() { std::cout << " Driving Truck " << std::endl;}
};

class VehicleFactory
{
public:
	static std::shared_ptr<AbstractVehicle> createVehicle(factory::vehicle vehicleType)
	{
		switch(vehicleType)
		{
			case factory::BIKE:
				return std::make_shared<Bike>();
			case factory::CAR:
				return std::make_shared<Car>();
			case factory::TRUCK:
				return std::make_shared<Truck>();
			default:
				return nullptr;
		}
	}
};

int main()
{
	
	std::shared_ptr<AbstractVehicle> bike = VehicleFactory::createVehicle(factory::BIKE);
	bike->drive();
	
	std::shared_ptr<AbstractVehicle> car = VehicleFactory::createVehicle(factory::CAR);
	car->drive();
	
	std::shared_ptr<AbstractVehicle> truck = VehicleFactory::createVehicle(factory::TRUCK);
	truck->drive();
}