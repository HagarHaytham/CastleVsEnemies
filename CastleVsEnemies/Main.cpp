#include "Main.h"

void simulation (castle &c,float&c1,float&c2,float&c3)
{  
	for(int j=0;j<4;j++)	//initialize every region
	{
		initRegion(c.Regions[j]);
	}
	int mode;
	cin>>mode;
	initCastle(c);//initialize the castle
	file_loading(c,c1,c2,c3);	//read inputfile
	int countT=0;//counter for damaged towers
	int countR=0;//counter for destroyed regions
	int time=0;
	while(countT<4&&countR<4)	//start loop for time steps and end when no. damaged regions =4
	{
		NodeE*ptr;
		for(int i=0;i<4;i++)
		{
			c.Regions[i].Killed.current_killed=0;//initialize the current killed enemies counter by zero
		}
		for(int i=0;i<4;i++)//move enemies from inactive to active
		{
			if (!isEmpty(c.Regions[i].inactiveEnemies))
			{
				while (c.Regions[i].inactiveEnemies.front->e.ArrivalTime==time)
				{
					insert(c.Regions[i].inactiveEnemies,c.Regions[i].activeenemies,c.Regions[i].unpaved);//move the enemy from inactive to active
					if (c.Regions[i].inactiveEnemies.front==NULL) break;
				}
			}
		}
		for(int l=0;l<4;l++)//calculate the priority for all shielded enemies for each timestep
		{
			NodeE*p=c.Regions[l].activeenemies.Head;
			while(p!=NULL)
			{
				if(p->e.Type==2)
				{
					Calpriority(p->e,c1,c2,c3);
				}
				p=p->next;
			}
		}
		for(int k=0;k<4;k++)
		{
			sortPriority(c.Regions[k].activeenemies);//sort the active list by priority
		}
		for(int j=0;j<4;j++)//moving the enemies
		{
			ptr=c.Regions[j].activeenemies.Head;
			while(ptr!=NULL)
			{
				if(ptr->e.Distance==2)//if the enemy reach tha minimum between him and the tower(2)
				{
					ptr=ptr->next;
					continue;
				}
				if(ptr->e.Distance>c.Regions[j].unpaved)//if the unpaved area is smaller than the distance between the enemy and the tower->decrese the distance by one
				{
					ptr->e.Distance-=ptr->e.Speed; //move the enemy by its speed
				}
				ptr=ptr->next;
			}
		}
		for(int i =0;i<4;i++)///loop for damage the enemies
		{
			if(c.Regions[i].T.damage)
				continue;
			towerAttack(c.Regions[i].activeenemies,c.Regions[i].T,time,c.Regions[i].Killed);
		}
		for(int i=0;i<4;i++)///loop for damage the towers
		{
			if(c.Regions[i].T.damage)
				continue;
			enemyAttack(c.Regions[i].activeenemies,c.Regions[i].T);
			if(c.Regions[i].T.Health<0)
				c.Regions[i].T.Health=0.00;
		}
		for(int j=0;j<4;j++)//pave the area
		{
			ptr=c.Regions[j].activeenemies.Head;
			while(ptr!=NULL)
			{
				if(ptr->e.Type==0)
				{
					if(ptr->e.nextShoot>0)//if the paver is still reloading in this time step
					{
						ptr->e.nextShoot--;
					}
					if(ptr->e.Distance<=c.Regions[j].unpaved&&c.Regions[j].unpaved>2&&ptr->e.nextShoot==0)//if the unpaved area is smaller than the distance between the enemy and the tower->decrese the distance by one
					{
						c.Regions[j].unpaved-=int(ptr->e.FirePower);
						ptr->e.nextShoot=ptr->e.ReloadPeriod;
					}
					if (c.Regions[j].unpaved<2)//minimum distance which can be reached by enemies
						c.Regions[j].unpaved=2;
				}
				ptr=ptr->next;
			}
		}
		for(int z=0;z<4;z++)//loop to check the regions are damaged or not
		{  
			if(c.Regions[z].T.damage||c.Regions[z].destroyed)	//if current region is destroyed OR the tower is damaged skip this region
			continue;
		
				if (c.Regions[z].activeenemies.count==0&&c.Regions[z].inactiveEnemies.count==0)//if the region is destroyed
				{
					countR++;//increase the number of destroyed regions by one
					c.Regions[z].destroyed=true;
				}
				if (c.Regions[z].T.Health<=0)//if the tower is damaged
				{
					countT++;
					c.Regions[z].T.damage=true;	//damage this region
					int circle=0;
					int j=(z+1)%4;
					while(c.Regions[j].T.damage&&circle<4)//finding the next available region 
					{
						circle++;
						j=(j+1)%4;

					}
					if(countT==4)
						break;
					Region*rdamaged;//pointer to the damaged region
					Region*rfollowing;//pointer to next available region
					CircularRegions(c.Regions,z,j,rdamaged,rfollowing);//move the enemies in the next available region
					countR++;////increase the number of destroyed regions by one
				}
			
		}
		if(mode!=1&&mode!=2)//silent mode
		{
			time++;
			continue;
		}
		else if(mode==1)//interactive mode
		{
			cout<<"\n\n                                                                                  Press ENTER contiue";
			cin.get();
		}
		else if(mode==2)//sleep mode
		{
			Sleep(1000);
		}
		time++;
		int size=0;
		for(int i=0;i<4;i++)//finding the number of active enemies in this time step
			size+=c.Regions[i].activeenemies.count;
		enemy**en=new enemy*[size];//array of poiner to pointer to enemies For drawing function
		int u=0;
		for(int i=0;i<4;i++)//make every pointer in the array points to an active enemy
		{
			ptr=c.Regions[i].activeenemies.Head;
			while(ptr!=NULL)
			{
				en[u]=&ptr->e;
				u++;
				ptr=ptr->next;
			}
		}
		DrawCastle(c,time);//drawing castle
		DrawEnemies(en,size);//drawing enemies
		printTimeStep(c);//print statistics for this time step 
		delete[] en;
	}
	//end game
	cout<<"\n\n                                                                                  The Game is Over\n\nFor More Statistics Please go and check the output file which is located in project's folder\n\n";
}
void main()
{
	SetWindow();
	castle c;
	float c1,c2,c3;
	cout<<"For Interactive mode Enter 1             For Step-By-Step mode Enter 2             For Silent mode Enter any number\n";
	cout<<"Enter your wanted mode : ";
	simulation(c,c1,c2,c3); //calling simulation function
	LinkedListE AllKilled;
	initLinkedListE (AllKilled);
	for (int i=0;i<4;i++)
	{
		AllKilled.count+=c.Regions[i].Killed.count;
		Appendlists(AllKilled, c.Regions[i].Killed);
	}
	float fightdelay;
	float killdelay;
	calculateSkilled( AllKilled ,fightdelay,killdelay );//caculate statistics for killed enemies
	SortKTS(AllKilled);//sort the killed by thier killed time steps
	outputfile(AllKilled,c,fightdelay,killdelay);//calling outputfile to print final statistics of the game
}