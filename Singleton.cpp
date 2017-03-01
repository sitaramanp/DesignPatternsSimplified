/* Singleton is a pattern through which we make sure only one instance of a class is available.
   Many people have strong arguments against the use of this pattern, if the design is good enough.
   Another argument is Singleton would waste lot of time re-writing the code, if in an agile environment, 
   with the change in requirements, we need multiple instances of a class
*/

/* Typically in embedded systems, we would have only one instance of a HW controller. All access/control of that HW would be through
   this controller only.
*/

#include<iostream>
#include<memory>
#include<thread>
#include<vector>
#include<algorithm>

class PowerMonitorController
{
	protected: // Open for inheritance
	// locking the default constructor, copy constructor and assignment operator
	PowerMonitorController() { }
	PowerMonitorController( PowerMonitorController const& ) { }
	PowerMonitorController& operator = ( PowerMonitorController const& );
public:
	static std::shared_ptr<PowerMonitorController> GetInstance();
	void MonitorPower() { std::cout << " Power Monitored " << std::endl; }
	void ManageFault()  { std::cout << " Manage Fault " << std::endl; }
	void AdjustPower()  { std::cout << " Adjust Power " << std::endl; }
private:
	static std::shared_ptr<PowerMonitorController> _pmcInstance;
	
};

std::shared_ptr<PowerMonitorController> PowerMonitorController::_pmcInstance = nullptr;
// Crux of Singleton pattern. In instance is not created yet, create one. 
std::shared_ptr<PowerMonitorController> PowerMonitorController::GetInstance()
{
	if(PowerMonitorController::_pmcInstance == nullptr)
	{
		_pmcInstance = std::make_shared<PowerMonitorController>();
		std::cout << " Created a PowerMonitorController " << std::endl;
	}
	return _pmcInstance;
}

//The following singleton would be thread safe in c++11
class ThreadSafePowerMonitorController
{
protected:
	ThreadSafePowerMonitorController() { std::cout << " Created a ThreadSafePowerMonitorController " << std::endl;}
	ThreadSafePowerMonitorController(ThreadSafePowerMonitorController const&);
	ThreadSafePowerMonitorController(ThreadSafePowerMonitorController &&); //move constructor
	ThreadSafePowerMonitorController& operator =(ThreadSafePowerMonitorController const&);
	ThreadSafePowerMonitorController& operator =(ThreadSafePowerMonitorController &&); // move assignment
public:
	static ThreadSafePowerMonitorController& GetInstance();
	void MonitorPower() { std::cout << " Power Monitored " << std::endl; }
	void ManageFault()  { std::cout << " Manage Fault " << std::endl; }
	void AdjustPower()  { std::cout << " Adjust Power " << std::endl; }
};

ThreadSafePowerMonitorController& ThreadSafePowerMonitorController::GetInstance()
{
	// concurrent execution shall wait for completion of initialization, since below is a static vaiable
	static ThreadSafePowerMonitorController _staticInstance;
	return _staticInstance;
}

int main()
{
	// Sample output of Thread unsafe singleton when following code is executed
	// CCrreeaatteedd  aa  PPoowweerrMMoonniittoorrCCoonnttrroolllleerr
	std::vector<std::thread> th;
	for(int i=0; i<10; ++i)
	{
		auto t = std::thread( [] () {PowerMonitorController::GetInstance(); });
		th.push_back(std::move(t));
	}
	
	std::for_each(th.begin(), th.end(), [] (std::thread& t) { t.join(); });
	
	th.clear();
	for(int i=0; i<10; ++i)
	{
		auto t = std::thread([]() {ThreadSafePowerMonitorController::GetInstance(); });
		th.push_back(std::move(t));
	}
	
	std::for_each(th.begin(), th.end(), [](std::thread& t) {t.join(); });
	
	PowerMonitorController::GetInstance()->MonitorPower();
	PowerMonitorController::GetInstance()->ManageFault();
	PowerMonitorController::GetInstance()->AdjustPower();
	
}