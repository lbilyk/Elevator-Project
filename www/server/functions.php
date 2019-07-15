<?php
require_once '../server/server_requests.php';
require_once '../server/dbconfig.php';

function getCurrentDate() {

    return $date = date('Y-m-d H:i:s');
}

function getLogbookData(){

    global $mysqli;
    $query = "SELECT * FROM logbook";
    $entries = array();
    $statement = $mysqli->prepare($query);
    $statement->execute();
    $result = $statement->get_result();
    while($row = mysqli_fetch_assoc($result)) {
        $entries[] = $row;
    }
    return json_encode($entries);
}

function addLogbookEntry($entry, $user, $date) {

    global $mysqli;
    $query = "INSERT INTO logbook (username,date,entry) VALUES(?,?,?)";
    $statement = $mysqli->prepare($query);
    $statement->bind_param("sss",$user,$date, $entry);
    $result = $statement->execute();
    return $result;
}

function updateFloor($floor) {

    global $mysqli;
    $query = "UPDATE elevatorNetwork SET requestedFloor = ? WHERE nodeID = 1";
    $statement = $mysqli->prepare($query);
    $statement->bind_param("i",$floor);
    $result = $statement->execute();
    return $result;
}

function getLogData() {

    global $mysqli;
    $query = "SELECT * FROM Command_Log";
    $data = array();
    $statement = $mysqli->prepare($query);
    $statement->execute();
    $result = $statement->get_result();
    while($row = mysqli_fetch_assoc($result)) {
        $entries[] = $row;
    }
    return json_encode($data);
}