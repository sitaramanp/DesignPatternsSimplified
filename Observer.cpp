/* Also called Publisher-Subscriber. Various observer registers to the publisher. When the state of the publisher changes, it notifies all the registered
   subscribers. 
*/

/* Example shows a typical problem of embedded domain. Various applications like Fault Reporter, Performance Monitor, FDR logger needs to constantly 
   moniter various HW parameters. We will have these observers register to an HW reader which would poll the HW periodically and push the data read
   to these interested parties
*/

#include<iostream>
#include<chrono>
#include<memory>
#include<algorithm>
#include<vector>
#include<thread>

//Forward declaration, as we need to store the pointer of observers in publisher
class HwMonitorObserver;

/*In case of multiple publishers, we can have an abstract publisher class and pass *this in notify() to let the observer know from which publisher the notify()
  to let the observer know from which publisher notify() was called
*/

class HwMonitorPublisher 
{
public:
	void RegisterObserver(std::shared_ptr<HwMonitorObserver> observer)
	{
		if(std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
			_observers.push_back(observer);
	}
	
	void DeRegisterObserver(std::shared_ptr<HwMonitorObserver> observer)
	{
		_observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
			
	}
	
	void NotifyHwMonitorResults();
	
	void Tick()
	{
		while(1) // keep polling the HW continuosly 
		{
			NotifyHwMonitorResults();
			std::this_thread::sleep_for(std::chrono::seconds(1)); // poll every second
		}
	}
private:
	std::vector<std::shared_ptr<HwMonitorObserver>> _observers;
};

class HwMonitorObserver
{
public:
	virtual void HwMonitorUpdate() = 0;
    HwMonitorObserver(std::shared_ptr<HwMonitorPublisher> publisher) { _publisher = publisher;}

private:
	//locking default and copy constructor
	HwMonitorObserver();
	HwMonitorObserver(const HwMonitorObserver&);
	std::shared_ptr<HwMonitorPublisher> _publisher;
};

class FaultReporter: public HwMonitorObserver
{
public:
	FaultReporter(std::shared_ptr<HwMonitorPublisher> publisher) : HwMonitorObserver(publisher) {}
	void HwMonitorUpdate() { std::cout << " Fault Reporter got update from Publihser" << std::endl;}
};

class PerformanceMonitor: public HwMonitorObserver
{
public:
	PerformanceMonitor(std::shared_ptr<HwMonitorPublisher> publisher) : HwMonitorObserver(publisher) {}
	void HwMonitorUpdate() { std::cout << " Performance monitor got update from Publihser" << std::endl;}
};

class FdrLogger: public HwMonitorObserver
{
public:
	FdrLogger(std::shared_ptr<HwMonitorPublisher> publisher) : HwMonitorObserver(publisher) {}
	void HwMonitorUpdate() { std::cout << " Fdr logger got update from Publihser" << std::endl;}
};

void HwMonitorPublisher::NotifyHwMonitorResults()
{
	std::for_each(_observers.begin(), _observers.end(), [](std::shared_ptr<HwMonitorObserver> & obs) { obs->HwMonitorUpdate(); });
}

int main()
{
	auto publisher = std::make_shared<HwMonitorPublisher>() ;
	auto faultRep = std::make_shared<FaultReporter>(publisher);
	auto perfMon = std::make_shared<PerformanceMonitor>(publisher);
	auto fdrLog = std::make_shared<FdrLogger>(publisher);
	
	publisher->RegisterObserver(faultRep);
	publisher->RegisterObserver(perfMon);
	publisher->RegisterObserver(fdrLog);
	//Uncomment below line to see Deregistration in action.
	//publisher->DeRegisterObserver(faultRep);
			
	publisher->Tick();
	return 0;
}
	   