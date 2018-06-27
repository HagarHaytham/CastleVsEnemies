#include"Calculations.h"

	float damageEnemybyTower(int constant,int dist,int towerFP);
	float damageTowerbyEnemy(int constant,int dist,int enemyFP);
	void towerAttack(LinkedListE&active,tower t,int time,LinkedListE&killed);
	void enemyAttack(LinkedListE active,tower&t);
	void movekilled (NodeE*&pre,NodeE*&ptr,LinkedListE& active,LinkedListE & killed);
