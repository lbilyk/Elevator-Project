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
    <link href="css/index.css" rel="stylesheet">
</head>
<body id="page-top">
<nav class="navbar navbar-expand navbar-dark bg-dark static-top">
    <a class="navbar-brand mr-1" href="index.php">Elevator Project</a>
    <button class="btn btn-link btn-sm text-white order-1 order-sm-0" id="sidebarToggle" href="#">
        <i class="fas fa-bars"></i>
    </button>
    <ul class="navbar-nav ml-auto mr-0 mr-md-3 my-2 my-md-0">
        <li class="nav-item dropdown no-arrow">
            <a class=" nav-link dropdown-toggle d-inline-block px-3" id="datetime"></a>
            <a class="nav-link dropdown-toggle d-inline" href="#" id="userDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                <div class="d-inline-block" id="loginSection"></div>
                <i class="fas fa-user-circle fa-fw"></i>
            </a>
            <a href="logout.php" class="nav-link d-inline">Logout</a>

            <!--            <div class="dropdown-menu dropdown-menu-right" aria-labelledby="userDropdown">-->
<!--                <a class="dropdown-item" href="#">Settings</a>-->
<!--                <div class="dropdown-divider"></div>-->
<!--                <a class="dropdown-item" href="#" data-toggle="modal" data-target="#logoutModal">Logout</a>-->
<!--            </div>-->
        </li>
    </ul>
</nav>
<div id="wrapper">
    <ul class="sidebar navbar-nav">
        <li class="nav-item active">
            <a class="nav-link" href="index.php">
                <i class="fas fa-fw fa-home"></i>
                <span>Home</span>
            </a>
        </li>
        <li class="nav-item">
            <a class="nav-link" href="project.html">
                <i class="fas fa-fw fa-project-diagram"></i>
                <span>Project</span>
            </a>
        </li>
        <li class="nav-item">
            <a class="nav-link" href="logbook.php">
                <i class="fas fa-fw fa-book"></i>
                <span>Log Book</span>
            </a>
        </li>
        <li class="nav-item">
            <a class="nav-link" href="about.html">
                <i class="fas fa-fw fa-info-circle"></i>
                <span>About</span>
            </a>
        </li>
    </ul>
    <div class="container pt-5">
                <div id="elevatorBuilding">
                    <div id="elevatorShaft">
                        <div id="elevatorContainer">
                            <div id="elevator">
                                <div class="door open-left" id="doorLeft"></div>
                                <div class="door open-right" id="doorRight"></div>
                            </div>
                        </div>
                    </div>
                    </div>
                </div>

    <div class="card bg-dark" id="elevatorControls">
        <div class="card-text text-white text-center">Go To Floor</div>
        <div class="card-body">
            <div class="form-group text-center" >
                <input type="button" class="btn btn-outline-warning rounded-circle d-block my-2 " value='3' onclick="moveElevator(this.value)">
                <input type="button" class="btn btn-outline-warning rounded-circle d-block my-2" value='2' onclick="moveElevator(this.value)">
                <input type="button" class="btn btn-outline-warning rounded-circle d-block my-2" value='1' onclick="moveElevator(this.value)">
            </div>
        </div>
    </div>

    </div>
    <div class="fixed-bottom">
        <div class="text-center pt-5">
        <div class="text-center pt-5">
            <hr/>
            <span>Copyright © Lyubomyr Bilyk</span>
        </div>
    </div>
</div>

<script src="vendor/bootstrap/js/bootstrap.min.js"></script>
<script src="vendor/jquery/jquery.min.js"></script>
<script src="js/index.js"></script>
</body>
</html>
