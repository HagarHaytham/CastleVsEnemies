#include"Attack.h"


float damageEnemybyTower(int constant,int dist,float towerFP)
{
	float damage=float(towerFP)/(dist*constant);
	return damage;
}
float damageTowerbyEnemy(int constant,int dist,float enemyFP)
{
	float damage=float(constant*enemyFP)/dist;
	return damage;
}
void towerAttack(LinkedListE&active,tower t,int time,LinkedListE&Killed)
{
	NodeE*pre=NULL;
	NodeE*ptr=active.Head;
	int counter=0;
	//loop for the tower to attack its enemies and will end when the tower find its enemies OR attack all active
	while(ptr!=NULL&&counter<t.numberofenemeies)
	{
		if(ptr->e.Type==2)//the enemy is shielded
		{
			if (ptr->e.Tfirst_shot==-1)//if it was the first time to be shoot
				ptr->e.Tfirst_shot=time;//make its first shot equal this time step
			//the constant for the shielded enmey is 2
			ptr->e.Health-=damageEnemybyTower(2,ptr->e.Distance,t.FirePower);//the enemy's health will decrease by the damaged which the tower cause to enemy
		}
		else//any type (PVR_FTR_ZOM_PAR)
		{
			if (ptr->e.Tfirst_shot==-1)//if it was the first time to be shoot
				ptr->e.Tfirst_shot=time;//make its first shot equal this time step
			//the constant for any enemy is 1
			ptr->e.Health-=damageEnemybyTower(1,ptr->e.Distance,t.FirePower);//the enemy's health will decrease by the damaged which the tower cause to enemy
		}
		if(ptr->e.Type==3)//Zombie
		{
			if(ptr->e.Health<=-25)//will be killed when its HP is less than or equal -25
			{
				ptr->e.Tenemy_killed=time;//set its killed time equal this time step
				movekilled(pre,ptr,active,Killed);//move it to killed list
				counter++;//the counter for attacked enemies increases by one
				Killed.current_killed++;//the number of killed enemies in this time step increases by one
				continue;
			}
		}
		else if(ptr->e.Health<=0)//for any enemy expect the zombie
		{
			ptr->e.Tenemy_killed=time;//set its killed time equal this time step
			movekilled(pre,ptr,active,Killed);//move it to killed list
			counter++;//the counter for attacked enemies increases by one
			Killed.current_killed++;//the number of killed enemies in this time step increases by one
			continue;
		}
		pre=ptr;
		ptr=ptr->next;
		counter++;//the counter for attacked enemies increases by one
	}
}
void enemyAttack(LinkedListE active,tower&t)
{
	NodeE*ptr=active.Head;
	while(ptr!=NULL)
	{
		if(ptr->e.Type==0)//if the enemy is paver->it cannot attack
		{
			ptr=ptr->next;
			continue;
		}
		else if (ptr->e.Type==2)//if the enemy is shielded->constant is 2
		{
			t.Health-=damageTowerbyEnemy(2,ptr->e.Distance,ptr->e.FirePower);//the tower's HP decreases by the damage which is caused by the enemy
			ptr=ptr->next;
		}
		else//if the enemy isn't shielded->constant is 1
		{
			t.Health-=damageTowerbyEnemy(1,ptr->e.Distance,ptr->e.FirePower);//the tower's HP decreases by the damage which is caused by the enemy
			ptr=ptr->next;
		}
	}
}
void movekilled (NodeE*&pre,NodeE*&ptr,LinkedListE& active,LinkedListE & killed)
{
	if(ptr->e.Type==4)//the killed enemy is parachut
		active.Parachut--;//decrease the number of parachut enemies by one in the active list
	else if(ptr->e.Type==3)//the killed enemy is zombie
		active.Zombie--;//decrease the number of zombie enemies by one in the active list
	else if(ptr->e.Type==2)//the killed enemy is shielded
		active.Shielded--;//decrease the number of shielded enemies by one in the active list
	else if(ptr->e.Type==1)//the killed enemy is normal
		active.normal--;//decrease the number of normal enemies by one in the active list
	else//the killed enemy is paver
		active.paver--;//decrease the number of paverenemies by one in the active list

	if (pre==NULL )//if the killed enemy is the first ont in the active list
	  {
		  active.Head = ptr ->next;
	      ptr -> next = killed.Head;
	      killed.Head = ptr;
	      ptr = active.Head;
	  }
	else
	  {
	     pre -> next = ptr -> next;
	     ptr -> next = killed.Head;
	     killed.Head = ptr;
	     ptr = pre-> next;
	  }
	killed.count ++;//increase the count of killed list by one
	active.count --;//decrease the count of active list by one
	return;
}