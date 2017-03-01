/* Chain of responsibility pattern lets more than one object handle an event. Basically a list of objects is maintained and the request is 
   passed along the chain. Either all the objects can handle this event or we can bail out when an appropriate object in the chain has handled 
   the event. Exception handling in c++ is a beautiful example of this pattern. 
*/

/* Inspired by a recent cricket match, this example assumes a team is made up of 3 batsmen. An opener, middle order and tail ender. Their
   batting capabilities decrease in that order. Given a target score the program checks whether the team would chases it down 
*/

#include<iostream>
#include<memory>
#include<stdlib.h>
#include<time.h>

class Batsman
{
public:
	Batsman(std::shared_ptr<Batsman> batsman = nullptr) {_batsman = std::move(batsman); }
	void SetNext(std::shared_ptr<Batsman> batsman) {_batsman = std::move(batsman); }
	std::shared_ptr<Batsman> GetNext() { return _batsman?_batsman:nullptr ;}
	virtual bool Chase(int target) = 0;
protected:
	std::shared_ptr<Batsman> _batsman;	
};

class Opener: public Batsman
{
public:
	Opener(std::shared_ptr<Batsman> batsman = nullptr):Batsman(batsman) { }
	bool Chase (int target) 
	{	
		if(target > 0)
		{
			//std::srand(std::time(NULL));
			int score = std::rand()%100; // random number between 0 - 99
			
			if(target - score > 0)
			{
				std::cout << " Opener scored " << score << std::endl;
				return _batsman->Chase(target-score);  
			}
			else
			{
				std::cout << " Opener scored " << target << std::endl;
			}
		}
		return true;
	}
};

class MiddleOrder: public Batsman
{
public:
	MiddleOrder(std::shared_ptr<Batsman> batsman = nullptr):Batsman(batsman) { }
	bool Chase (int target) 
	{	
		if(target > 0)
		{
			//std::srand(std::time(NULL));
			int score = rand()%50; // random number between 0 -49
			
			if(target - score > 0)
			{
				std::cout << " Middle Order batsman scored " << score << std::endl;
				return _batsman->Chase(target-score);  
			}
			else
			{
				std::cout << " Middle order batsman scored the remaining " << target << std::endl;
			}
		}
		return true;
	}
};

class TailEnder: public Batsman
{
public:
	TailEnder(std::shared_ptr<Batsman> batsman = nullptr):Batsman(batsman) { }
	bool Chase (int target) 
	{	
		if(target > 0)
		{
			//std::srand(std::time(NULL));
			int score = rand()%20; // random number between 0-19
			
			if(target - score > 0)
			{
				std::cout << " Tail ender batsman scored " << score << std::endl;
				return false;
			}
			else
			{
				std::cout << " Tail ender batsman scored the remaining " << target << std::endl;
			}
		}
		return true;
	}
};

class Team // Little Facade!
{
public:
	Team()
	{
		//_teamBatsman = std::shared_ptr<Batsman>(new Opener(std::shared_ptr<Batsman>(new MiddleOrder(std::shared_ptr<Batsman>(new TailEnder()))))); 
		//std::make_shared apart from better efficiency makes it easy on the eye.
		_teamBatsman = std::make_shared<Opener>(std::make_shared<MiddleOrder>(std::make_shared<TailEnder>()));
	}
	
	void ChaseTarget(int target)
	{
		if(_teamBatsman->Chase(target))
		{
			std::cout << " We won! Better luck next time! " << std::endl;
		}
		else
			std::cout << " You won! Well played! " << std::endl;
	}
private:
	std::shared_ptr<Batsman> _teamBatsman;
};

int main()
{
	Team team;
	std::srand(std::time(NULL));
	int target = rand()%200 + 1; // random number between 1-200
	std::cout << " Match 1. Target " << target << std::endl;
	team.ChaseTarget(target);
	
	target = rand()%200 + 1; // random number between 1-200
	std::cout << std::endl << " Match 2. Target = " << target << std::endl;
	team.ChaseTarget(target);
	
	target = rand()%200 + 1; // random number between 1-200
	std::cout << std::endl << " Match 3. Target = " << target << std:: endl;
	team.ChaseTarget(target);
}