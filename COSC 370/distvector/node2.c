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
} dt2;


struct rtpkt packet;
/* students to write the following two routines, and maybe some others */

void rtinit2()
{
  int infin = 9999; //largest value (not really, but it will work for our application as these numbers will be quite small)

  //init all min costs to infinite (or our version of infinite)
	packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;

  printf("starting routine: rtinit2\n");
	printf("Clocktime in rtinit2: %f\n", clocktime);
	int i,j;

  for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			dt2.costs[i][j] = infin;
		}
	}

  dt2.costs[0][0] = 3;
	dt2.costs[1][1] = 1;
	dt2.costs[2][2] = infin;
	dt2.costs[3][3] = 2;

  for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(packet.mincost[i] > dt2.costs[i][j]){
				packet.mincost[i] = dt2.costs[i][j];
      }
		}
	}

	packet.sourceid = 2;
	packet.destid = 0;
	tolayer2(packet);

	packet.sourceid = 2;
	packet.destid = 1;
	tolayer2(packet);

	packet.sourceid = 2;
	packet.destid = 3;
	tolayer2(packet);

	printdt2(&dt2);
	printf("returning from routine: rtinit2\n");
}

/*updates data in distance table in case of changes*/
void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
{

  printf("starting routine: rtupdate2\n");

  int infin = 9999;

  packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	extern float clocktime;
	printf("Clocktime in rtupdate2: %f, sender: %d\n", clocktime, rcvdpkt->sourceid);
	printdt2(&dt2);

  int temp[4], updated = 0;
	int i, j;
  for(i = 0; i < 4; ++i){
		if(dt2.costs[i][rcvdpkt->sourceid] > rcvdpkt->mincost[i]  + dt2.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]){
			dt2.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + dt2.costs[rcvdpkt->sourceid][rcvdpkt->sourceid];
			updated = 1;
		}
	}
	if(updated){
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				if(packet.mincost[i] > dt2.costs[i][j]){
					packet.mincost[i] = dt2.costs[i][j];
        }
			}
		}

		printf("finished updating distance table\n");

		packet.sourceid = 2;
		packet.destid = 0;
		tolayer2(packet);

		packet.sourceid = 2;
		packet.destid = 1;
		tolayer2(packet);

		packet.sourceid = 2;
		packet.destid = 3;
		tolayer2(packet);
	}
  
	printdt2(&dt2);
}


printdt2(dtptr)
  struct distance_table *dtptr;

{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}
