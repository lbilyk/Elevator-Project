<?php
require_once '..\server\index.php';
require_once '..\server\dbconfig.php';

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
    default:
        echo null;
        break;
}