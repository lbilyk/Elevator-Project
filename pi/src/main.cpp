#include "../include/pcanFunctions.h"
#include "../include/databaseFunctions.h"
#include "../include/mainFunctions.h"
#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include<list>  /*Linked list */

using namespace std;

/* Globals */
list<int> floorQueue;
int nextFloor = 0;

// ******************************************************************

int main() {

    int choice;
    int ID;
    int data;
    int numRx;
    int floorNumber = 1, floorNumberPhys = 4, req_floor = 1;

	bool requested = false;

    system("@cls||clear");

	/* Init queue */
	initQueue();

	/* Init PCAN */
	initPcan();

    printf("\nNow listening to commands from the website or physical buttons - press ctrl-z to cancel\n");
    // Synchronize elevator db and CAN (start at 1st floor)
    pcanTx(ID_SC_TO_EC, GO_TO_FLOOR1);
    db_setFloorNum(1);
    db_setReqNum(1);

    while (1) {

        // Physical hardware checking
        floorNumberPhys = pcanCheck(floorNumber);

        if (floorNumberPhys != 4)
        {                                                                     // check for floor num change
            printf("Physical button (%d) was pressed...\n",floorNumberPhys);
            db_setReqNum(floorNumberPhys);
			db_logUpdate(0, 1);

        }

		/* Check if there is requested floor on DB */
		req_floor = db_getReqNum();

		if (!floorQueue.empty()) {
			if (pcanStatus() == nextFloor) {
				requested = false;

				nextFloor = 0;

				if (!floorQueue.empty()) {
					floorQueue.pop_front();
				}
			}
		}

		if (req_floor != 4) {

			queueNextFloor(req_floor);

			if (requested == false) {
				/* Call next floor */
				nextFloor = getNextFloor();

				printf("moving now to floor %d\n", nextFloor);
				pcanTx(ID_SC_TO_EC, HexFromFloor(nextFloor));                    // change floor number in elevator - send command over CAN

				db_logUpdate(nextFloor, 0);

				requested = true;
			}
		}

		sleep(0.1);
		
    }

	return (0);
}

int getNextFloor() {

	if (!floorQueue.empty()) {
		nextFloor = floorQueue.front();

		return nextFloor;
	}
	
	/* Keep same floor as before if queue is empty else will trigger error */
	return nextFloor;
}

void queueNextFloor(int req_floor) {

	bool requested = false;

	if (req_floor == 4) {
		// Do nothing
	}
	else {

		/* Check if value is already queued */
		for (auto it = floorQueue.begin(); it != floorQueue.end(); ++it) {

			/* Floor is already in queue */
			if (req_floor == *it) {
				requested = true;
			}
		}

		if (requested == false) {
			floorQueue.push_back(req_floor);
			printf("Queued floor %d\n", req_floor);
		}
	}
}

void initQueue() {
	floorQueue.assign(1, 0);
	floorQueue.pop_front();

	printf("Queue initialized\n");
}



	
