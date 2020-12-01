#include <iostream>

class Drone
{
    public:
	virtual void beep() = 0;
	virtual void spin_rotors() = 0;
	virtual void take_off() = 0;
};

class SuperDrone : public Drone
{
    public:
	void beep()
    {
		std::cout << "Beep beep beep" << std::endl;
	}
	void spin_rotors()
    {
		std::cout << "Rotors are spinning" << std::endl;
	}
	void take_off()
    {
		std::cout << "Taking off" << std::endl;
	}
};

class Duck
{
    public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class DroneAdapter : public Duck
{
    Drone *drone;
    
    public:
    DroneAdapter(Drone *drone) : drone(drone){}
    void quack()
    {
		drone->beep();
	}
	void fly()
    {
		drone->spin_rotors();
		drone->take_off();
	}
};

int main()
{
    DroneAdapter A(new SuperDrone);
    A.quack();
    A.fly();
    return 0;
}