#include "Circular.h"

void CircularRegions (Region*regions,int damaged,int following,Region*&rdamaged,Region*&rfollowing)
{
	rfollowing=&regions[following];//a pointer to the next available region
	rdamaged=&regions[damaged];//a pointer to the damaged region
	rfollowing->destroyed=false;
	MergeQueue(rfollowing->inactiveEnemies,rdamaged->inactiveEnemies);//merge inactive queues 
	movetorightspot(rdamaged->activeenemies,rfollowing->unpaved);//move the enemies to its' distance in the new region
	NodeE*ptr=rdamaged->activeenemies.Head;
	while(ptr!=NULL)
	{
		RegionTransfer(rfollowing->Killed.Head->e.Region,ptr);//transfer the region of the enemies to the new region(name)
		ptr=ptr->next;
	}
	Appendlists(rfollowing->activeenemies,rdamaged->activeenemies);//append the active lists
	rfollowing->activeenemies.count+=rdamaged->activeenemies.count;//the counter of the active list of the new region increases by the counter of the active list for old region
	rfollowing->activeenemies.paver+=rdamaged->activeenemies.paver;//the counter of the pavers of the new region increases by the counter of the pavers for old region
	rfollowing->activeenemies.normal+=rdamaged->activeenemies.normal;//the counter of the fighter of the new region increases by the counter of the fighter for old region
	rfollowing->activeenemies.Shielded+=rdamaged->activeenemies.Shielded;//the counter of shielded of the new region increases by the counter of the shielded for old region
	rfollowing->activeenemies.Zombie+=rdamaged->activeenemies.Zombie;//the counter of the zombie of the new region increases by the counter of the zombie for old region
	rfollowing->activeenemies.Parachut+=rdamaged->activeenemies.Parachut;//the counter of the parachut of the new region increases by the counter of the parachut for old region
	initLinkedListE(rdamaged->activeenemies);//to make the counters in the old active list equal 0
	sortPriority(rfollowing->activeenemies);//sort the new active list by priorty(FOR SHIELDED)
	sortArrival(rfollowing->activeenemies);//sort the new active list by arrival time
}
////For moving the enemies to thier old distance in the new region
void movetorightspot(LinkedListE & list,int unpaved)
{
	NodeE *ptr =list.Head;
	while (ptr !=NULL)
	{
		if (ptr->e.Distance<=unpaved)//move the enemy in the paved area if its distance in the new region is unpaved
			ptr->e.Distance=unpaved+1;
		ptr=ptr->next;
	}
}
//Append the lists
void Appendlists (LinkedListE & Allkilled,LinkedListE& killedR)///new///
{
	NodeE* ptr1=Allkilled.Head;
	NodeE* ptr2 = killedR.Head;
	if (ptr1==NULL) 
	{
		Allkilled.Head = ptr2; 
		ptr1=ptr2;
		return;
	}
	while (ptr1->next!=NULL) 
		ptr1 = ptr1->next;
	ptr1->next = ptr2;
	killedR.Head=NULL;
}
//Merge inactive queues
void MergeQueue(queue & q1, queue & q2)
{
	queue temp;
	initQueue (temp);
	while (q1.front !=NULL && q2.front !=NULL)
	{
		if(q1.front->e.ArrivalTime>q2.front->e.ArrivalTime)
		{
			enemy x;
			Deque(q2,x);
			x.Region=q1.front->e.Region;
			Enque (temp,x);
		}
		else 
		{
			enemy x;
			Deque(q1,x);
			Enque (temp,x);
		}
	}
	if (q1.front==NULL&&temp.front!=NULL)
	{
		temp.rear->next=q2.front;
	}
	else if (q2.front==NULL&&temp.front!=NULL)
		temp.rear->next=q1.front;
	q1=temp;
}
//transfer the enemy's old region to the new region
void RegionTransfer(REGION newregion,NodeE*&oldregion)
{
	oldregion->e.Region=newregion;
}