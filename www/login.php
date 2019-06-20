<?php
error_reporting(0);
ini_set('display_errors', 0);
session_start();
$authError = filter_input(INPUT_GET, 'authError');
?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <title>Elevator Project</title>
        <meta name="author" content="Lyubomyr Bilyk">
        <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css?family=Karla" rel="stylesheet">
        <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
        <link href="css/login.css" rel="stylesheet">
    </head>
    <body id="page-top" class="bg-dark">
        <div class="container">
            <div class="card card-login mx-auto mt-5">
                <div class="card-header mb-1">Elevator Project Login</div>
                <div class="card-body">
                    <form action="authenticate.php" method="POST">
                        <div class="form-group my-2">
                            <input type="text" id="username" name="username" class="form-control" placeholder="Username"
                                   required="required" autofocus="autofocus">
                        </div>
                        <div class="form-group">
                            <input type="password" id="userPassword" name="password" class="form-control" placeholder="Password"
                                   required="required" autofocus="autofocus">
                        </div>
                        <input type="submit" value="Login" class="btn btn-primary btn-block">
                    </form>
                    <?php if($authError) { ?>
                        <script>alert("Username or password is incorrect");</script>
                    <?php } ?>
                </div>
                <hr/>
                <div class="text-center font-weight-bold">
                    or...
                </div>
                <div class="text-center">
                    <div class="pt-1 pb-3 px-5 text-center">
                        <input type="submit" value="Request Access" class="btn btn-primary btn-block" onclick="window.location.href ='request.html'">
                    </div>
                </div>

            </div>
        </div>
    </body>
</html>
