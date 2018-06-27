#include"Sorting.h"

	void CircularRegions(Region*regions,int damaged,int following,Region*&rdamaged,Region*&rfollowing);
	void Appendlists (LinkedListE & Allkilled,LinkedListE& killedR);
	void MergeQueue(queue & q1, queue & q2);
	void RegionTransfer(REGION newregion,NodeE*&oldregion);
	void movetorightspot(LinkedListE & list,int unpaved );