// AbstractFactory pattern is closely related to the Factory pattern. Here we have the Factory to be abstract by itself. 

// This example talks about making cars! We have 2 cars, Holden and Honda. We will build these cars in our yard

#include<iostream>
#include<memory>

class AbstractCarDoor
{
public:
	virtual void open() = 0;
	virtual void close() = 0;
};

class HoldenDoor : public AbstractCarDoor
{
public:
	void open() { std::cout << " Open door of Holden " << std::endl; }
	void close() { std::cout << " Close door of Holden " << std::endl;}
};

class HondaDoor : public AbstractCarDoor
{
public:
	void open() { std::cout << " Open door of Honda " << std::endl; }
	void close() { std::cout << " Close door of Honda " << std::endl;}
};

class AbstractCarSteering
{
public:
	virtual void steer() = 0;
};

class HoldenSteering : public AbstractCarSteering
{
public:
	void steer() { std::cout << " Steering Holden " << std::endl; }
	
};

class HondaSteering : public AbstractCarSteering
{
public:
	void steer() { std::cout << " Steering Honda " << std::endl; }
};

class AbstractCarFactory
{
public:
	virtual std::shared_ptr<AbstractCarDoor> createDoor() = 0;
	virtual std::shared_ptr<AbstractCarSteering> createSteering() = 0;
};

class HoldenCar : public AbstractCarFactory
{
public:
	std::shared_ptr<AbstractCarDoor> createDoor()
	{
		return std::make_shared<HoldenDoor>();
	}
	
	std::shared_ptr<AbstractCarSteering> createSteering()
	{
		return std::make_shared<HoldenSteering>();
	}
};

class HondaCar : public AbstractCarFactory
{
public:
	std::shared_ptr<AbstractCarDoor> createDoor()
	{
		return std::make_shared<HondaDoor>();
	}
	
	std::shared_ptr<AbstractCarSteering> createSteering()
	{
		return std::make_shared<HondaSteering>();
	}
};

int main()
{
	std::unique_ptr<AbstractCarFactory> myHoldenCar (new HoldenCar());
	
	std::cout << "Creating My Holden Car" << std::endl;
	myHoldenCar->createDoor()->open();
	myHoldenCar->createSteering()->steer();
	
	std::unique_ptr<AbstractCarFactory> myHondaCar (new HondaCar());
	
	std::cout << "Creating My Honda Car" << std::endl;
	myHondaCar->createDoor()->open();
	myHondaCar->createSteering()->steer();
	
}