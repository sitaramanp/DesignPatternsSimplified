/* To solve a complex problem, often we break down it to smaller pieces. In the process we might have a bunch of components represented
   as vairous classes. For a client who does not want to get involved in the nitty gritty of the inter-dependancy of these components,
   an easier interface can be provided. This interface is Facade
*/

/* In the example below, an user instructs an autonomus car to drive to destination, D.
*/

#include <iostream>
#include <string>

namespace constCommands {
	enum commands {
		eDRIVE,
		eSTOP
		 
	};
};	

class Doors
{
public:
	bool AreDoorsClosed() { std::cout << " Checking whether doors are closed " << std::endl; return true; }
	bool CloseDoors() { std::cout << " Closing the doors " << std::endl; return true; }
	bool OpenDoors() { std::cout << " Opening the doors " << std::endl; return true; }
};

class SeatBeltSensors
{
public:
	bool AreSeatBeltsFastened() { std::cout << " Checking Passenger occupancy" << std::endl << " Checking SeatBelt Fasten sensor " << std::endl; return true;}
};

class Safety
{
public:
	bool IsSafeForDrive() {return _doors.AreDoorsClosed() && _seatBeltSensor.AreSeatBeltsFastened() ;}
private:
	Doors _doors;
	SeatBeltSensors _seatBeltSensor;
};	

class Map
{
public:
	bool FindRoute(std::string destination = "Mars") { std::cout << " Find route to destination " << std::endl; return true;} 
	void GetCurrentLocation() { std::cout << " Contacting GPS and getting current location " << std::endl; }
	
};

class Drive
{
public:
	bool GetDataFromSensors() { std::cout << " Getting data from sensors " << std::endl; return true;}
	bool StartDriving() { GetDataFromSensors(); std::cout << " Enjoy the drive " << std::endl; return true;}
};

class RobotFacade
{
public:
	bool TakeMeToMars()
	{
		if(_safety.IsSafeForDrive())
		{
			_map.FindRoute();
			_drive.StartDriving();	
		}
		return true;
	}
private:
	Map _map;
	Drive _drive;
	Safety _safety;
};

int main()
{
	RobotFacade rf;
	rf.TakeMeToMars();
	return 0;
}