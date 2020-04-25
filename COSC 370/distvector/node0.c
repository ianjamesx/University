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

struct distance_table {
  int costs[4][4];
} dt0;


struct rtpkt packet;
/* students to write the following two routines, and maybe some others */

void rtinit0(){

  /*
  NOTE:
  all these routines are pretty cookie-cutter
  routines in node0.c are the best commented as the other routines are very similar
  (with the exception of some value changes)
  this file will be the best reference of comments
  */

  int infin = 9999; //largest value (not really, but it will work for our application as these numbers will be quite small)

  //init all min costs to infinite (or our version of infinite)
	packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

  printf("starting routine: rtinit0\n");

	int i, j;
	//sets all distances to node i from node j to infinity
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			dt0.costs[i][j]= infin;
		}
	}

  /*
  from program description:
  "reflect the direct costs of 1, 3, and 7 to nodes 1, 2, and 3, respectively"
  */

	dt0.costs[1][1] = 1;
	dt0.costs[2][2] = 3;
	dt0.costs[3][3] = 7;

	//for each distance through node i from node j, check if min cost is smaller than infinity, if so set it to the minimum cost
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(packet.mincost[i] > dt0.costs[i][j]){
				packet.mincost[i] = dt0.costs[i][j];
      }
		}
	}

  packet.sourceid = 0; //set packet's sourceid to 0, since this code is for node 0 (this applies to all)
	packet.destid = 1;
	tolayer2(packet); //calling function tolayer2 in order for data to be transferred to layer2

	packet.sourceid = 0;
	packet.destid = 2;
	tolayer2(packet);

	packet.sourceid = 0;
	packet.destid = 3;
	tolayer2(packet);

	printdt0(&dt0);
	printf("returning from routine: rtinit0\n");
}

/*updates the distance vector table in case of changes*/
void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{

  printf("starting routine: rtupdate0\n");

  int infin = 9999;

  //setting all minimum costs to nodes 0,1,2,3 to infinity
  packet.mincost[0] = infin;
	packet.mincost[1] = infin;
	packet.mincost[2] = infin;
	packet.mincost[3] = infin;

	//prints out updates of packets sent to sourceid = node 0
	extern float clocktime; //from prog3.c
	printf("Clocktime in rtupdate0: %f, sender: %d\n", clocktime, rcvdpkt->sourceid);
	printdt0(&dt0);

	int temp[4], updated = 0;
	int i, j;
	for(i = 0; i < 4; ++i){
		//checks for updates to see if any cost should be changed
		if(dt0.costs[i][rcvdpkt->sourceid] > rcvdpkt->mincost[i] +  dt0.costs[rcvdpkt->sourceid][rcvdpkt->sourceid]){
			dt0.costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i]  + dt0.costs[rcvdpkt->sourceid][rcvdpkt->sourceid];
			updated = 1;
		}
	}

	//if change occurred, update the table in accordance with the change (change minimum cost from
  //infinity to the distance vector cost according to the diagram)
	if(updated == 1){
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++){
				if(packet.mincost[i]  > dt0.costs[i][j]){
					packet.mincost[i] = dt0.costs[i][j];
        }
			}
		}

		printf("updated distance table in rtupdate0\n");

		//calls function tolayer2 to simulate data link layer after table has been updated
		packet.sourceid = 0;
		packet.destid = 1;
		tolayer2(packet);

		packet.sourceid = 0;
		packet.destid = 2;
		tolayer2(packet);

		packet.sourceid = 0;
		packet.destid = 3;
		tolayer2(packet);
	}

	//prints the distance vector diagram after update
	printdt0(&dt0);

}

printdt0(dtptr)
  struct distance_table *dtptr;
{
  //code provided by program description
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

//I think Me, Keith, and Justin are undergrads
//so we're just going to leave this blank

{
}
