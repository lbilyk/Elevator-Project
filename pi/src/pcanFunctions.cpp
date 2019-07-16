#include "../include/pcanFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>  
#include <errno.h>
#include <unistd.h> 
#include <signal.h>
#include <string.h>
#include <fcntl.h>    					// O_RDWR
#include <unistd.h>
#include <ctype.h>
#include <libpcan.h>   					// PCAN library


// Globals
// ***********************************************************************************************************
HANDLE h;
static HANDLE h2;
TPCANMsg Txmsg;
TPCANMsg Rxmsg;
DWORD status;

// Code
// ***********************************************************************************************************

// Functions
// *****************************************************************
int pcanTx(int id, int data){
	// Clear the channel - new - Must clear the channel before Tx/Rx
	status = CAN_Status(h2);

	// Set up message
	Txmsg.ID = id; 	
	Txmsg.MSGTYPE = MSGTYPE_STANDARD; 
	Txmsg.LEN = 1; 
	Txmsg.DATA[0] = data; 

	//sleep(0.1);  
	status = CAN_Write(h2, &Txmsg);

	printf(" ");
}

int pcanRx(int num_msgs){
	int i = 0;

	// Clear the channel - new - Must clear the channel before Tx/Rx
	status = CAN_Status(h2);

	// Clear screen to show received messages
	system("@cls||clear");

	// receive CAN message  - CODE adapted from PCAN BASIC C++ examples pcanread.cpp
	printf("\nReady to receive message(s) over CAN bus\n");
	
	// Read 'num' messages on the CAN bus
	while(i < num_msgs) {
		while((status = CAN_Read(h2, &Rxmsg)) == PCAN_RECEIVE_QUEUE_EMPTY){
			//sleep(0.1);
		}
		if(status != PCAN_NO_ERROR) {						// If there is an error, display the code
			printf("Error 0x%x\n", (int)status);
			//break;
		}
										
		if(Rxmsg.ID != 0x01 && Rxmsg.LEN != 0x04) {		// Ignore status message on bus	
			printf("  - R ID:%4x LEN:%1x DATA:%02x \n",	// Display the CAN message
				(int)Rxmsg.ID, 
				(int)Rxmsg.LEN,
				(int)Rxmsg.DATA[0]);
		i++;
		}
	}
	
	// Close CAN 2.0 channel and exit	
	return ((int)Rxmsg.DATA[0]);						// Return the last value received
}

int pcanCheck(int prevMsg)
{
    //variables
    int newMsg = 4;

    // Clear the channel - new - Must clear the channel before Tx/Rx
    status = CAN_Status(h2);

    status = CAN_Read(h2, &Rxmsg);

    if(status != PCAN_NO_ERROR) {						// If there is an error, display the code
        printf("Error 0x%x\n", (int)status);
        //break;
    }

    //printf("\n__Dataframe__prev_msg:%d\n",prevMsg);
    if(Rxmsg.ID != 0x01 && Rxmsg.LEN != 0x04 && Rxmsg.DATA[0] != 4 && Rxmsg.ID >= 0x200) {		// Ignore status message on bus
        //printf("  - R ID:%4x LEN:%1x DATA:%d \n",	// Display the CAN message
        //       (int)Rxmsg.ID,
        //       (int)Rxmsg.LEN,
        //       (int)Rxmsg.DATA[0]);
        newMsg = (Rxmsg.DATA[0] - 4);

        return(newMsg);
    }
    else
    {
		return(newMsg);
    }

}

int pcanStatus()
{
    //variables
    int newMsg = 4;

    // Clear the channel - new - Must clear the channel before Tx/Rx
    status = CAN_Status(h2);

    status = CAN_Read(h2, &Rxmsg);

    if(status != PCAN_NO_ERROR) {						// If there is an error, display the code
        printf("Error 0x%x\n", (int)status);
        //break;
    }

    if(Rxmsg.ID != 0x01 && Rxmsg.LEN != 0x04 && Rxmsg.DATA[0] != 4 && Rxmsg.ID == 0x101) {		// Ignore status message on bus
        //printf("  - R ID:%4x LEN:%1x DATA:%d \n",	// Display the CAN message
        //       (int)Rxmsg.ID,
        //       (int)Rxmsg.LEN,
        //       (int)Rxmsg.DATA[0]);
        newMsg = (Rxmsg.DATA[0] - 4);
        printf("current floor is: %d\n",newMsg);
        return(newMsg);
    }
    else
    {
        return(newMsg);
    }
}

void initPcan() {
	// Open a CAN channel
	h2 = LINUX_CAN_Open("/dev/pcanusb32", O_RDWR);

	// Initialize an opened CAN 2.0 channel with a 125kbps bitrate, accepting standard frames
	status = CAN_Init(h2, CAN_BAUD_125K, CAN_INIT_TYPE_ST);

	status = CAN_Status(h2);

	printf("PCAN initialized\n");
}

