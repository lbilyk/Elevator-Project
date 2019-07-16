#ifndef DB_FUNCTIONS
#define DB_FUNCTIONS

int db_logFloor(int floorNum);
int db_getFloorNum();
int db_getReqNum();
int db_setReqNum(int floorNum);
int db_logUpdate(int reqNum, int reqType);
int db_setFloorNum(int floorNum);
void eraseReqFloor();
#endif
