#include <stdio.h>


extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

int connectcosts[4] = {1,0,1,999};

struct distance_table
{
  int costs[4][4];
} dt1;

struct rtpkt packet;
/* students to write the following two routines, and maybe some others */

void rtinit1(){

  int infin = 9999; //largest value (not really, but it will work for our application as these numbers will be quite small)

  //init all min costs to infinite (or our version of infinite)
	packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;

	printf("starting routine: rtinit1\n");
	printf("Clocktime in rtinit1: %f\n", clocktime);

  int i, j;
	//sets all distances to node i from node j to infinity
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			dt1.costs[i][j] = infin;
		}
	}

  dt1.costs[0][0] = 1;
	dt1.costs[2][2] = 1;

  for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(packet.mincost[i] > dt1.costs[i][j]){
				packet.mincost[i] = dt1.costs[i][j];
      }
		}
	}

	packet.sourceid = 1;
	packet.destid = 0;
	tolayer2(packet);

	packet.sourceid = 1;
	packet.destid = 2;
	tolayer2(packet);

	packet.sourceid = 1;
	printdt1(&dt1);
	printf("returning from routine: rtinit1\n");
}


void rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
{

  printf("starting routine: rtupdate1\n");

  int infin = 9999;

  packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;
	printf("Clocktime in rtupdate1: %f, sender: %d\n", clocktime, rcvdpkt->sourceid);
	printdt1(&dt1);

	int temp[4], updated = 0;
	int i, j;
	for(i = 0; i < 4; ++i){
		if(dt1.costs[i][rcvdpkt->sourceid] > rcvdpkt->mincost[i]  + dt1.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]){
			dt1.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + dt1.costs[rcvdpkt->sourceid][rcvdpkt->sourceid];
			updated = 1;
		}
	}
	if(updated){
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				if(packet.mincost[i] > dt1.costs[i][j]){
					packet.mincost[i] = dt1.costs[i][j];
        }
			}
		}

		printf("updated distance table in rtupdate1\n");

		packet.sourceid = 1;
		packet.destid = 0;
		tolayer2(packet);

		packet.sourceid = 1;
		packet.destid = 2;
		tolayer2(packet);
	}

	printdt1(&dt1);
}


printdt1(dtptr)
  struct distance_table *dtptr;

{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}

linkhandler1(linkid, newcost)
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
