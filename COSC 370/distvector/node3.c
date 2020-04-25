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

struct distance_table
{
  int costs[4][4];
} dt3;


struct rtpkt packet;
/* students to write the following two routines, and maybe some others */


/*rtinit3 is similar to rtinit0, 1 and 2.  That is, it's in charge of calculating the shortest distance vector from node 3 to nodes 0,1,2 */
void rtinit3()
{

  int infin = 9999;

	packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;

  printf("starting routine: rtinit3\n");
	printf("Clocktime in rtinit3: %f\n", clocktime);

  int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			dt3.costs[i][j] = infin;
		}
	}

  dt3.costs[0][0] = 7;
	dt3.costs[2][2] = 2;
	dt3.costs[3][3] = infin;

  for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(packet.mincost[i] > dt3.costs[i][j]){
				packet.mincost[i] = dt3.costs[i][j];
      }
		}
	}

	packet.sourceid = 3;
	packet.destid = 0;
	tolayer2(packet);

	packet.sourceid = 3;
	packet.destid = 2;
	tolayer2(packet);

	packet.sourceid = 3;
	printdt3(&dt3);
	printf("returning from routine: rtinit3\n");
}

/*This function updates the distance vector table after changes have been made to it */
void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("starting routine: rtupdate3\n");

  int infin = 9999;

  packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;
	printf("Clocktime in rtupdate3: %f, sender: %d\n", clocktime, rcvdpkt->sourceid);
	printdt3(&dt3);

  int temp[4], updated = 0;
	int i, j;
	for(i = 0; i < 4; ++i){
		if(dt3.costs[i][rcvdpkt->sourceid] > rcvdpkt->mincost[i]  + dt3.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]){
			dt3.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + dt3.costs[rcvdpkt->sourceid][rcvdpkt->sourceid];
			updated = 1;
		}
	}
	if(updated){
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				if(packet.mincost[i] > dt3.costs[i][j]){
					packet.mincost[i] = dt3.costs[i][j];
        }
			}
		}

		printf("updated distance table in rtupdate3\n");

		packet.sourceid = 3;
		packet.destid = 0;
		tolayer2(packet);

		packet.sourceid = 3;
		packet.destid = 2;
		tolayer2(packet);
	}

	printdt3(&dt3);
}


printdt3(dtptr)
  struct distance_table *dtptr;

{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}
