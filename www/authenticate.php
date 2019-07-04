<?php
require_once 'server/dbconfig.php';

session_start();
$authError = false;
$username = $_POST['username'];
$password = $_POST['password'];
if ($username && $password) {
    global $mysqli;
    $query = "SELECT * FROM users WHERE username = ?";
    $statement = $mysqli->prepare($query);
    $statement->bind_param('s', $username);
    $statement->execute();
    $result = $statement->get_result();
    $user = $result->fetch_assoc();
    if ($user["username"] == $username && $user["password"] == $password) {
        $authenticated = true;
        $_SESSION['user'] = $user["name"];
        header('Location: index.php');
        exit();
    } else {
        $authError = true;
        session_destroy();
        header('Location: login.php?authError='.$authError);
        exit();
    }
}
else {
    session_destroy();
    header('Location: login.php');

}
