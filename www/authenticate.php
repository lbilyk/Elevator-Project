<?php

session_start();
$authError = false;
$username = $_POST['username'];
$password = $_POST['password'];
if ($username && $password) {
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
