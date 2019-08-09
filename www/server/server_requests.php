<?php
require_once '../server/functions.php';
require_once '../server/dbconfig.php';

$action = filter_input(INPUT_POST, 'action');

switch ($action) {
    case 'getLogbookData':
        echo getLogbookData();
        break;
    case 'addLogbookEntry':
        $entry = filter_input(INPUT_POST,'entry');
        $user = filter_input(INPUT_POST,'user');
        $date = getCurrentDate();
        echo addLogbookEntry($entry, $user, $date);
        break;
    case 'updateFloor':
        $floor = filter_input(INPUT_POST,'floor');
        echo updateFloor($floor);
        break;
    case 'getLogData':
        echo getLogData();
        break;
    case 'getCurrentFloor':
        echo getCurrentFloor();
        break;
    case 'getStatData':
        echo getStatData();
        break;
    default:
        echo null;
        break;
}