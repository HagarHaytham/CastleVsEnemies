#include"InitImple.h"

//initialize the castle
void initCastle(castle&c)
{
	c.W=CastleWidth;
	c.L=CastleLength;
	c.Xstrt=CastleXStrt;
	c.Ystrt=CastleYStrt;
}
//initialize the region
void initRegion (Region &R)
{
	R.unpaved=30;	//unpaved distnace
	initQueue (R.inactiveEnemies);	//initialize the inactive list for the region
	initLinkedListE (R.activeenemies);		//initialize the active list for the region
	initLinkedListE (R.Killed);		//initialize the killed list for the region
	R.T.TL=TowerLength;
	R.T.TW=TowerWidth;
	R.T.damage=false;	//damage for tower
	R.destroyed=false;	//destroyed for enemies
}
//initialize the linked list
void initLinkedListE (LinkedListE &l)
{
	//initialize the list
	l.count=0;	//its size
	l.Head=NULL;	//its head
	l.paver= l.normal= l.Shielded =l.Zombie =l.Parachut= 0;	//counter for every type
	l.current_killed=0;	//counter for killed for every timestep
}
//initialize the queue
void initQueue (queue &q)
{
	q.front = q.rear = NULL ;
	q.count=0;
}
//initialize the enemy
void initenemy(enemy &e)
{
	e.Distance=60;	//initial distance
	e.priority=0;	//initial priority
	e.nextShoot=0;	//time to next shoot
	e.pave=false;	//for pavers
	e.Tfirst_shot=-1; //counter to the first time step in which the tower attacks the enemy
}
//check the queue is empty or not
bool isEmpty (queue q)
{
	if (q.count==0)
		return true ;
	else 
		return false;
}
//enque Fn. added the enmey from the input file to the inactive queue
void Enque ( queue &q,enemy e)
{
	NodeE *n_ptr=new NodeE;
	if (n_ptr==NULL)
		return;
	n_ptr->e=e;
	n_ptr->next=NULL;
	if (isEmpty(q))
		{
			q.front=q.rear=n_ptr;
			q.count++;
			return ;
		}
	else
	{
		q.rear->next=n_ptr;
		q.rear=n_ptr;
		q.count++;
		return;}
}
//deque Fn. remove the enemy from inactive to active list 
void Deque (queue &q,enemy &e)
{
	if (isEmpty(q))
		return;
	NodeE*temp=q.front;
	q.front=q.front->next;
	e= temp->e;
	if (q.count ==1)
	{
		q.front=q.rear=NULL;
	}
	q.count--;
	delete temp;
	return;
}
//insert the enemy 
void insert(queue&q,LinkedListE&list,int unpaved)
{
	NodeE *en=new NodeE;
	Deque(q,en->e);
	if(list.Head==NULL)//empty list
	{
		list.Head=en;
		if(en->e.Type==4)//if the inserted enemy is Parachut
		{
			en->e.Distance=unpaved+5;
			list.count++;//increase the counter of total enemies
			list.Parachut++;//increase the counter of parachut enemies
			en->next=NULL;
		}
		else if(en->e.Type==3)//if the inserted enemy is zombie
		{
			list.count++;//increase the counter of total enemies
			list.Zombie++;//increase the counter of zombie enemies
			en->next=NULL;
		}
		else if(en->e.Type==2)//if the inserted enemy is shielded
		{
			list.count++;//increase the counter of total enemies
			list.Shielded++;//increase the counter of shielded enemies
			en->next=NULL;
		}
		else if(en->e.Type==1)//if the inserted enemy is normal
		{
			list.count++;//increase the counter of total enemies
			list.normal++;//increase the counter of normal enemies
			en->next=NULL;
		}
		else if(en->e.Type==0)//if the inserted enemy is paver
		{
			list.count++;//increase the counter of total enemies
			list.paver++;//increase the counter of paver enemies
			en->next=NULL;
		}
		return;
	}
	else
	{
		NodeE*ptr=list.Head;
		while(ptr->next!=NULL)//append the new enemy to the list
		{
			ptr=ptr->next;
		}
		ptr->next=en;
		if(en->e.Type==4)//if the inserted enemy is Parachut
		{
			en->e.Distance=unpaved+5;
			list.count++;//increase the counter of total enemies
			list.Parachut++;//increase the counter of parachut enemies
			en->next=NULL;
		}
		else if(en->e.Type==3)//if the inserted enemy is zombie
		{
			list.count++;//increase the counter of total enemies
			list.Zombie++;//increase the counter of zombie enemies
			en->next=NULL;
		}
		else if(en->e.Type==2)//if the inserted enemy is shielded
		{
			list.count++;//increase the counter of total enemies
			list.Shielded++;//increase the counter of shielded enemies
			en->next=NULL;
		}
		else if(en->e.Type==1)//if the inserted enemy is normal
		{
			list.count++;//increase the counter of total enemies
			list.normal++;//increase the counter of normal enemies
			en->next=NULL;
		}
		else if(en->e.Type==0)//if the inserted enemy is paver
		{
			list.count++;//increase the counter of total enemies
			list.paver++;//increase the counter of paver enemies
			en->next=NULL;
		}
		return;
	}
}