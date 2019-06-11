<?php
session_start();

if($_SESSION['user'] == null || $_SESSION == '') {
    header('Location: login.php');
} else {
    ?>
    <script>
        let user = '<?php echo $_SESSION['user']; ?>'
        localStorage.setItem('sessionUser',user);
    </script>
    <?php
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Elevator Project</title>
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Karla" rel="stylesheet">
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link href="css/index.css" rel="stylesheet">
    <link href="css/logbook.css" rel="stylesheet">
</head>
<body id="page-top">
<nav class="navbar navbar-expand navbar-dark bg-dark static-top">
    <a class="navbar-brand mr-1" href="index.php">Elevator Project</a>
    <button class="btn btn-link btn-sm text-white order-1 order-sm-0" id="sidebarToggle" href="#">
        <i class="fas fa-bars"></i>
    </button>
    <ul class="navbar-nav ml-auto mr-0 mr-md-3 my-2 my-md-0">
        <li class="nav-item dropdown no-arrow">
            <a class="nav-link dropdown-toggle d-inline" href="#" id="userDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                <div class="d-inline-block px-3" id="datetime"></div>
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
        <li class="nav-item ">
            <a class="nav-link" href="index.php">
                <i class="fas fa-fw fa-home"></i>
                <span>Home</span>
            </a>
        </li>
        <li class="nav-item ">
            <a class="nav-link" href="project.html">
                <i class="fas fa-fw fa-project-diagram"></i>
                <span>Project</span>
            </a>
        </li>
        <li class="nav-item active">
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
    <!--<select class="browser-default custom-select">-->
    <!--<option selected>Select a user</option>-->
    <!--<option value="1">Ferencz Dominguez</option>-->
    <!--<option value="2">Lyubomyr Bilyk</option>-->
    <!--<option value="3">Nik Kershaw</option>-->
    <!--</select>-->

    <!--<footer class="sticky-footer">-->
    <!--<div class="container my-auto">-->
    <!--<div class="copyright text-center my-auto">-->
    <!--<span>Copyright © Lyubomyr Bilyk</span>-->
    <!--</div>-->
    <!--</div>-->
    <!--</footer>-->
    <div class="container-fluid px-5 py-2" id="logbookContainer">
        <div>
            <input id="minDate" type="date"> to <input id="maxDate" type="date">
            <div class="pl-5 d-inline">
                <select id="nameSelect" class="px-2"></select>
            </div>
            <div class="pl-5 d-inline">
                <input class="btn btn-primary" type="button" value="Apply Filters" class="px-2" onclick="filterLogbookEntries()">
            </div>
        </div>
        <hr>
        <div class="list-group container-fluid" id ="logbookEntries">
            <div class="form-group d-flex w-100 justify-content-between" id="entryBox">
                <textarea class="form-control z-depth-1" id="logbookEntry" rows="3" placeholder="Here's what I did..."></textarea>
                <hr/>
                <div class="container mx-5">
                    <input id="addEntryButton" type="button" class="btn btn-primary z-depth-1" value="Add" onclick="checkIfEntryExists()">
                </div>
            </div>
        </div>
    </div>
</div>
<script src="vendor/bootstrap/js/bootstrap.min.js"></script>
<script src="vendor/jquery/jquery.min.js"></script>
<script src="js/index.js"></script>
<script src="js/logbook.js"></script>
</body>
</html>