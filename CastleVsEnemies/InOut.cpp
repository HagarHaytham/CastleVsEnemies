#include"InOut.h"

//reading the data from input file
void file_loading (castle &c,float&c1,float&c2,float&c3)
{
	
	ifstream inputfile ("morethan50.txt",ios::in); //open the input file
	float HT; int enemeypershot; float FP;
	inputfile>>HT>>enemeypershot>>FP; //read the tower's data
	for(int i=0;i<4;i++)	//loop for assigning every tower with its data
	{
		c.Regions[i].T.Health=HT;
		c.Regions[i].T.numberofenemeies= enemeypershot;
		c.Regions[i].T.FirePower=FP;
	}
	inputfile>>c1>>c2>>c3; //read the constants
	int k;
	while (inputfile>>k && k!=-1) //read until reading -1
	{
		enemy temp;
		initenemy(temp); //initialize the enemy
		temp.ID=k; //k=enemy's id
		char region;
		int type;
		inputfile>>type>>temp.ArrivalTime>>temp.Health>>temp.FirePower>>temp.ReloadPeriod>>region>>temp.Speed; //reading enemy's data
		switch (region)
		{
			case'A':
				temp.Region=A_REG;
				break;
			case'B':
				temp.Region=B_REG;
				break;
			case'C':
				temp.Region=C_REG;
				break;
			case'D':
				temp.Region=D_REG;
				break;
		}
		switch(type)
		{
		case 0:
			temp.Type=PVR;
			break;
		case 1:
			temp.Type=FITR;
			break;
		case 2:
			temp.Type=SHLD_FITR;
			break;
		case 3:
			temp.Type=ZOM;
			break;
		case 4:
			temp.Type=PAR;
			break;
		}
		if (region=='A') //if the enemy's region is A 
		  Enque (c.Regions[0].inactiveEnemies,temp);	//Enqueue the enemy to inactive list for region A
		else if (region=='B') //if the enemy's region is B 
		  Enque (c.Regions[1].inactiveEnemies,temp);	//Enqueue the enemy to inactive list for region B
		else if (region=='C') //if the enemy's region is C 
		  Enque (c.Regions[2].inactiveEnemies,temp);	//Enqueue the enemy to inactive list for region C
		else if (region=='D') //if the enemy's region is D 
		  Enque (c.Regions[3].inactiveEnemies,temp);	//Enqueue the enemy to inactive list for region D	
	}
		inputfile.close(); //close the input file
}
//print the statistics for every time steps
void printTimeStep(castle c)
{
	for(int i=0;i<4;i++)
	{
		if(i==0)
		{
			cout<<"\n\nFor Region A :"<<endl;
			cout<<"              "<<"Total number of active enemies : "<<c.Regions[i].activeenemies.count<<"        Number of enemies killed at this time step : "<<c.Regions[i].Killed.current_killed;
			cout<<"        Total number of killed enemies from the first time step : "<<c.Regions[i].Killed.count<<"        Unpaved distance to castle : "<<c.Regions[i].unpaved<<endl;
		}
		else if(i==1)
		{
			cout<<"For Region B :"<<endl;
			cout<<"              "<<"Total number of active enemies : "<<c.Regions[i].activeenemies.count<<"        Number of enemies killed at this time step : "<<c.Regions[i].Killed.current_killed;
			cout<<"        Total number of killed enemies from the first time step : "<<c.Regions[i].Killed.count<<"        Unpaved distance to castle : "<<c.Regions[i].unpaved<<endl;
		}
		else if(i==2)
		{
			cout<<"For Region C :"<<endl;
			cout<<"              "<<"Total number of active enemies : "<<c.Regions[i].activeenemies.count<<"        Number of enemies killed at this time step : "<<c.Regions[i].Killed.current_killed;
			cout<<"        Total number of killed enemies from the first time step : "<<c.Regions[i].Killed.count<<"        Unpaved distance to castle : "<<c.Regions[i].unpaved<<endl;
		}
		else if(i==3)
		{
			cout<<"For Region D :"<<endl;
			cout<<"              "<<"Total number of active enemies : "<<c.Regions[i].activeenemies.count<<"        Number of enemies killed at this time step : "<<c.Regions[i].Killed.current_killed;
			cout<<"        Total number of killed enemies from the first time step : "<<c.Regions[i].Killed.count<<"        Unpaved distance to castle : "<<c.Regions[i].unpaved<<endl;
		}
	}

}
//print the final statistics in an output file
void outputfile (LinkedListE AllKilled,castle c,float &Fight_Delay,float& Kill_Delay)
{
	ofstream outfile ("outmorethan50.txt",ios::out);//create an output file
	NodeE* ptr=AllKilled.Head;
	for (int i=0;i<AllKilled.count;i++)//loop to print the statistics for every killed enemy
	{
		outfile<<ptr->e.Tenemy_killed<<"   "<<ptr->e.ID<<"   "<<ptr->e.FightDelay<<"   "<<ptr->e.KillDelay<<"   "<<ptr->e.Fighttime<<endl;
		ptr=ptr->next;
	}
	outfile<<endl<<"-------------------------------------------------------"<<endl;
	int ht;
	ifstream inputfile ("morethan50.txt",ios::in);
	inputfile>>ht;
	for (int i=0;i<4;i++)
	{
			outfile<<"T"<<i+1<<"_"<<ht-c.Regions[i].T.Health<<"   ";
	}
	outfile<<endl<<"-------------------------------------------------------"<<endl;
	for (int i=0;i<4;i++)
	{
		outfile<<"R"<<i+1<<"_"<<c.Regions[i].unpaved<<"   ";
	}
	outfile<<endl<<"-------------------------------------------------------"<<endl;
	int totalalive=0;
	for (int i=0;i<4;i++)
		totalalive+=c.Regions[i].activeenemies.count+c.Regions[i].inactiveEnemies.count;
	if (totalalive==0)
		{
			outfile<<"Game is WIN"<<endl;
			outfile<<"Total number of enemies = "<<AllKilled.count<<endl;
			outfile<<" Average Fight Delay = "<<Fight_Delay<<endl;
			outfile<<" Average Kill Delay = "<<Kill_Delay<<endl;
		}
	else 
		{
			outfile<<"Game is LOSS"<<endl;
			outfile<<"Total number of Killed enemies = "<<AllKilled.count<<endl;
			outfile<<"Number of alive enemies = "<<totalalive<<endl;
			outfile<<" Average Fight Delay = "<<Fight_Delay<<endl;
			outfile<<" Average Kill Delay = "<<Kill_Delay<<endl;
		}
	outfile.close ();
}