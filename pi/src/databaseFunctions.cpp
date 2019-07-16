// Includes required (headers located in /usr/include) 
#include "../include/databaseFunctions.h"
#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

 
using namespace std; 
 
int db_getFloorNum() {
	sql::Driver *driver; 			// Create a pointer to a MySQL driver object
	sql::Connection *con; 			// Create a pointer to a database connection object
	sql::Statement *stmt;			// Create a pointer to a Statement object to hold statements
	sql::ResultSet *res;			// Create a pointer to a ResultSet object to hold results 
	int floorNum;					// Floor number 
	
	// Create a connection 
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");	
	con->setSchema("elevator");		
	
	// Query database
	// ***************************** 
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT currentFloor FROM elevatorNetwork WHERE nodeID = 1");	// message query
	while(res->next()){
		floorNum = res->getInt("currentFloor");
	}
	
	// Clean up pointers 
	delete res;
	delete stmt;
	delete con;
	
	return floorNum;
}

int db_getReqNum() {
    sql::Driver *driver; 			// Create a pointer to a MySQL driver object
    sql::Connection *con; 			// Create a pointer to a database connection object
    sql::Statement *stmt;			// Create a pointer to a Statement object to hold statements
    sql::ResultSet *res;			// Create a pointer to a ResultSet object to hold results
    int floorNum;					// Floor number

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
    con->setSchema("elevator");

    // Query database
    // *****************************
    stmt = con->createStatement();


    res = stmt->executeQuery("SELECT requestedFloor FROM elevatorNetwork WHERE nodeID = 1");	// message query

    while(res->next()){
        floorNum = res->getInt("requestedFloor");
    }
    
    // Clean up pointers
    delete res;
    delete stmt;
    delete con;

    return floorNum;
}

int db_setFloorNum(int floorNum) {
    sql::Driver *driver; 				// Create a pointer to a MySQL driver object
    sql::Connection *con; 				// Create a pointer to a database connection object
    sql::PreparedStatement *pstmt; 		// Create a pointer to a prepared statement
    sql::ResultSet *res;				// Create a pointer to a ResultSet object to hold results

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
    con->setSchema("elevator");

    // Update database
    // *****************************
    pstmt = con->prepareStatement("UPDATE elevatorNetwork SET currentFloor = ? WHERE nodeID = 1");
    pstmt->setInt(1, floorNum);
    pstmt->executeUpdate();

    // Clean up pointers
    delete res;
    delete pstmt;
    delete con;
}

 int db_setReqNum(int floorNum) {
     sql::Driver *driver; 				// Create a pointer to a MySQL driver object
     sql::Connection *con; 				// Create a pointer to a database connection object
     sql::PreparedStatement *pstmt; 		// Create a pointer to a prepared statement
     sql::ResultSet *res;				// Create a pointer to a ResultSet object to hold results

     // Create a connection
     driver = get_driver_instance();
     con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
     con->setSchema("elevator");

     // Update database
     // *****************************
     pstmt = con->prepareStatement("UPDATE elevatorNetwork SET requestedFloor = ? WHERE nodeID = 1");
     pstmt->setInt(1, floorNum);
     pstmt->executeUpdate();

     // Clean up pointers
     delete pstmt;
     delete con;
 }

int db_logFloor(int floorNum) {
    sql::Driver *driver; 				// Create a pointer to a MySQL driver object
    sql::Connection *con; 				// Create a pointer to a database connection object
    sql::PreparedStatement *pstmt; 		// Create a pointer to a prepared statement
    sql::ResultSet *res;				// Create a pointer to a ResultSet object to hold results

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
    con->setSchema("elevator");

    // Update database
    // *****************************
    pstmt = con->prepareStatement("UPDATE log SET call_count = call_count + 1 WHERE floor_num = ?");
    pstmt->setInt(1, floorNum);
    pstmt->executeUpdate();

    // Clean up pointers
    delete res;
    delete pstmt;
    delete con;
}

int db_logUpdate(int reqNum, int reqType) {
    sql::Driver *driver; 				// Create a pointer to a MySQL driver object
    sql::Connection *con; 				// Create a pointer to a database connection object
    sql::PreparedStatement *pstmt; 		// Create a pointer to a prepared statement
    sql::ResultSet *res;				// Create a pointer to a ResultSet object to hold results

    // Create a connection
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
    con->setSchema("elevator");

    // Update database
    // *****************************
	if (reqType == 0)
	{
		pstmt = con->prepareStatement("INSERT INTO `Command_Log` (`Timestamp`, `Command`, `Floor`) VALUES (CURRENT_TIMESTAMP, 'updated from server to go to floor',?)");
		pstmt->setInt(1, reqNum);
		pstmt->executeUpdate();
	}
	else {
		pstmt = con->prepareStatement("INSERT INTO `Command_Log` (`Timestamp`, `Command`, `Floor`) VALUES (CURRENT_TIMESTAMP, 'updated queue','')");
		pstmt->executeUpdate();
	}
    // Clean up pointers
    delete pstmt;
    delete con;
}

void eraseReqFloor() {
	sql::Driver* driver; 				// Create a pointer to a MySQL driver object
	sql::Connection* con; 				// Create a pointer to a database connection object
	sql::PreparedStatement* pstmt; 		// Create a pointer to a prepared statement
	sql::ResultSet* res;				// Create a pointer to a ResultSet object to hold results

	// Create a connection
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "ese", "ese");
	con->setSchema("elevator");

	// Update database
	// *****************************
	pstmt = con->prepareStatement("UPDATE elevatorNetwork SET requestedFloor = ?");
	pstmt->setInt(1, 4);
	pstmt->executeUpdate();

	// Clean up pointers
	delete pstmt;
	delete con;
}
