#include"Const.h"

	struct enemy {

	int ID;
	int ArrivalTime;
	int nextShoot;
	int Distance;
	float Health;
	float priority;
	float FirePower;
	int ReloadPeriod;
	bool pave;
	Etype Type;		//PVR, FITR, SHLD_FITR, ZOM, PAR
	REGION Region;	//Region of this enemy
	int Tfirst_shot; 
	int Tenemy_killed;
	int FightDelay;//Tfirst_shot -ArrivalTime
	int KillDelay;//Tenemy_killed - Tfirst_shot
	int Fighttime;//=FD+KD
	int Speed;
};
	struct NodeE
{
	enemy e;
	NodeE* next;
};
	struct queue 
{
	NodeE* front;
	NodeE* rear;
	int count;
};
	struct LinkedListE
{
	NodeE*Head;
	int count;
	int Shielded;
	int normal;
	int paver;
	int Zombie;
	int Parachut;
	int current_killed;
};
	struct tower
{
	int TW; //Tower width
	int TL; //Tower Height
	float Health;
	float FirePower;
	char region;
	int numberofenemeies;
	bool damage;
};
	struct Region
{
	queue inactiveEnemies;
	LinkedListE activeenemies;
	LinkedListE Killed;
	tower T;
	int unpaved;
	bool destroyed;
};
	struct castle
{
	int Xstrt;
	int Ystrt; 
	int W;
	int L;
    Region Regions[4]; //array of regions
};