<?php
$dbhost = "localhost";
$dbuser = "ese";
$dbpass = "ese";
$dbname = "elevator";

try {
    $conn = new PDO("mysql:host=$dbhost;dbname=$dbname", $dbuser, $dbpass);
    $mysqli = new mysqli($dbhost, $dbuser, $dbpass, $dbname);
} catch (PDOException $pe) {
    die("Could not connect to the database $dbname :" . $pe->getMessage());
}