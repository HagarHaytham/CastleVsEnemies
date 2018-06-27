#include"Calculations.h"


void calculateSkilled(LinkedListE & AllKilled,float &Fight_Delay,float& Kill_Delay )//calculate the statistics of killed enemies
{
	NodeE *ptr=AllKilled.Head;
	float sumFightDelay=0;
	float sumKillDelay=0;
	while (ptr !=NULL)
	{
		ptr->e.FightDelay=ptr->e.Tfirst_shot+ptr->e.ArrivalTime;
		ptr->e.KillDelay=ptr->e.Tenemy_killed-ptr->e.Tfirst_shot;
		ptr->e.Fighttime=ptr->e.FightDelay+ptr->e.KillDelay;
		sumFightDelay+=ptr->e.FightDelay;
		sumKillDelay+=ptr->e.KillDelay;
		ptr=ptr->next;
	}
	Fight_Delay=sumFightDelay/AllKilled.count;
	Kill_Delay=sumKillDelay/AllKilled.count;
}
void Calpriority(enemy &e,float c1,float c2,float c3)//calculate the priority of shielded enemies
{
	e.priority=(e.FirePower/e.Distance)*c1+c2/(e.nextShoot+1)+e.Health*c3;
}