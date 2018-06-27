#include "Sorting.h"

//sort the enemies by thier priority
void sortPriority(LinkedListE&list)
{
	if(list.count==0||list.count==1) //if the list have 1 node or free return it with no change
		return;
	else
	{
		for(int iteration=0;iteration<list.count-1;iteration++) //loop to sort the list
		{
			NodeE*p1=list.Head;
			NodeE*p2=p1->next;
			while(p2!=NULL)	//loop to find the greatest HP
			{
				if(p1->e.priority<p2->e.priority)	//if the first enemy's HP is smaller than the next enemy's
				{
					enemy temp;		//swap them
					temp=p1->e;
					p1->e=p2->e;
					p2->e=temp;
				}					//else take the next enemy
				p1=p1->next;
				p2=p2->next;
			}
		}
	}
}
//sort the enemies by the arrival time
void sortArrival(LinkedListE &list)
{
	NodeE * ptr=list.Head;
	while (ptr->e.Type==2)
		ptr=ptr->next;
	for (int i=0;i<list.count-list.Shielded-1;i++)
	{
		NodeE*p2=ptr->next;
		while(p2!=NULL)	//loop to find the greatest Arrival time
		{
			if(ptr->e.ArrivalTime >p2->e.ArrivalTime)	//if the first enemy's Arrival time is smaller than the next enemy's
			{
				enemy temp;		//swap them
				temp=ptr->e;
				ptr->e=p2->e;
				p2->e=temp;
			}
			
			ptr=ptr->next;
			p2=p2->next;
		}
	}
}
//sort the killed enemies by the killed time steps
void SortKTS(LinkedListE & list)
{
		if(list.count==0||list.count==1) //if the list have 1 node or free return it with no change
		return;
	else
	{
		for(int i=0;i<list.count-1;i++) //loop to sort the list
		{
			NodeE*p1=list.Head;
			NodeE*p2=p1->next;
			while(p2!=NULL)	//loop to find the greatest killed time step
			{
				if(p1->e.Tenemy_killed >p2->e.Tenemy_killed)	//if the first enemy's killed time step is smaller than the next enemy's
				{
					enemy temp;		//swap them
					temp=p1->e;
					p1->e=p2->e;
					p2->e=temp;
				}
				else if (p1->e.Tenemy_killed ==p2->e.Tenemy_killed)//sort the 2 enemies by thier fight delay
				{
					if(p1->e.FightDelay >p2->e.FightDelay)
					{
						enemy temp;		//swap them
						temp=p1->e;
						p1->e=p2->e;
						p2->e=temp;
					}
				}                   //else take the next enemy
				p1=p1->next;
				p2=p2->next;
			}
		}
	}
}