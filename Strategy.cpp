/* Strategy pattern, also known as policy pattern lets users choose one algorithm from a family of interchangable algorithms. It can provide
   different implementations of same behaviour. Downside is the proliferation of objects
*/

/* Exmaple shows an application that uses different means to control memory allocation. Assume we have 3 types of memory management used by the
   application. 1)Memory Pool 2)Controlled via locks 3)Unmanaged. Different modules of the application can choose which theme of memory management
   it needs. It can also be changed at run time.
*/

#include<iostream>
#include<memory>


class MemoryManagementTheme
{
public:
	virtual void AllocateMemory(uint) = 0;
	virtual ~MemoryManagementTheme() { std::cout << " Clean up " << std::endl; }
}; 

class MemoryPoolAllocator : public MemoryManagementTheme
{
public:
	void AllocateMemory(uint _size)
	{
		std::cout << " Memory Pool allocated of size " << _size << std::endl;
	}
};

class ControlledMemoryAllocator : public MemoryManagementTheme
{
public:
	void AllocateMemory(uint _size)
	{
		std::cout << " Controlled Memory allocated of size " << _size << std::endl;
	}
};

class UnmanagedMemoryAllocator : public MemoryManagementTheme
{
public:
	void AllocateMemory(uint _size)
	{
		std::cout << " Unmanaged memory allocated of size " << _size << std::endl;
	}
};
	
class Module
{
public:
	void SetMemoryManagementTheme(std::unique_ptr<MemoryManagementTheme> mmTheme) { _memoryTheme = std::move(mmTheme); }
	void AllocateMemory(uint _size) { _memoryTheme->AllocateMemory(_size); }
	void DeAllocateMemory() { _memoryTheme.reset();}
private:
	std::unique_ptr<MemoryManagementTheme> _memoryTheme; 
};	

int main()
{
	
	Module m1, m2;
	// Setting a new theme
	m1.SetMemoryManagementTheme(std::unique_ptr<MemoryPoolAllocator>(new MemoryPoolAllocator()));
	m1.AllocateMemory(5);
	m2.SetMemoryManagementTheme(std::unique_ptr<ControlledMemoryAllocator>(new ControlledMemoryAllocator()));
	m2.AllocateMemory(10);
	
	// Changing the theme at run time
	m1.SetMemoryManagementTheme(std::unique_ptr<UnmanagedMemoryAllocator>(new UnmanagedMemoryAllocator()));
	m1.AllocateMemory(15);
	
	// Explicit de-allocation
	m2.DeAllocateMemory();
	m2.SetMemoryManagementTheme(std::unique_ptr<MemoryPoolAllocator>(new MemoryPoolAllocator()));
	m2.AllocateMemory(20);
	
	return 0;
}
		
		 