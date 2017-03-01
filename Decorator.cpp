/* Decorator design pattern is useful when we need to add/remove functionalities at run time
   Decorator is like skin of an object that changes its behavior
   Tip: try to have a lean interface. We don't want to burnern our decorators with unnecessary storage	
*/

/* The example below talks about Desserts. Decorators are the dressings.
   Note that we can have multiple decorator covering the same Dessert.
*/

#include <iostream>
#include <memory>

class AbstractDessert
{
public:
	virtual void prepare() = 0;
	virtual float computeCost() = 0;
};   

class Waffle : public AbstractDessert
{
public:
	void prepare() { std::cout << " preparing fresh waffle " << std::endl; }
	float computeCost() { return 100.0f; }
};

class DomeOfChoc : public AbstractDessert
{
public:
	void prepare() { std::cout << " preparing Dome of Choc " << std::endl; }
	float computeCost() { return 150.0f; }
	
};

class Decorator : public AbstractDessert
{
public:
	Decorator(std::unique_ptr<AbstractDessert> dessert)
	{
		_dessert = std::move(dessert);
	}
	
	void prepare() { _dessert->prepare(); }
	float computeCost() { return _dessert->computeCost(); }
	
protected:
	std::unique_ptr<AbstractDessert> _dessert;
	
private:
	Decorator(); // locking down default construction
	
};

class ChocolateShavings : public Decorator
{
public:
	ChocolateShavings(std::unique_ptr<AbstractDessert> dessert) : Decorator(std::move(dessert)) {}
	void prepare() 
	{
		_dessert->prepare();
		//custom preparation. Decorator!!
		std::cout << " Adding ChocolateShavings " << std::endl;
	}	
	float computeCost()
	{
		return 50.0f + _dessert->computeCost();
			
	}	
};

class MoltenCaramel : public Decorator
{
public:
	MoltenCaramel(std::unique_ptr<AbstractDessert> dessert) : Decorator(std::move(dessert)) {}
	void prepare()
	{
		_dessert->prepare();
		std::cout << " Adding MoltenCaramel. Yumm " << std::endl;
	}
	float computeCost()
	{
		return 75.0f + _dessert->computeCost();
		
	}
};

int main()
{

	std::unique_ptr<AbstractDessert> myDomeWithMoltenCaramel = std::unique_ptr<AbstractDessert>
		(new MoltenCaramel(std::unique_ptr<AbstractDessert> (new DomeOfChoc()))); 
	//below should be possible with c++14
	//std::unique_ptr<AbstractDessert> myDomeWithMoltenCaramel = std::make_unique<MoltenCaramel>(std::make_unique<DomeOfChoc>());
	myDomeWithMoltenCaramel->prepare();
	std::cout << " Total cost = " << myDomeWithMoltenCaramel->computeCost() << std::endl;
	
	std::cout << std::endl;
	
	//Interesting case. You can add mulitple decorators too

	std::unique_ptr<AbstractDessert> myCustomDessert = std::unique_ptr<AbstractDessert>(new MoltenCaramel(std::unique_ptr<AbstractDessert> 
		(new ChocolateShavings(std::unique_ptr<AbstractDessert>(new Waffle())))));
	//below should be possible with c++14
	//std::unique_ptr<AbstractDessert> myCustomDessert = std::make_unique<MoltenCaramel>(std::make_unique<ChocolateShavings>(std::make_unique<Waffle>()));
	myCustomDessert->prepare();
	std::cout << " Total cost = " << myCustomDessert->computeCost() << std::endl;
}
