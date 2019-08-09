<?php
session_start();
?>
<script>
    localStorage.setItem('sessionUser','');
    let user = '<?php echo $_SESSION['user']; ?>';
    localStorage.setItem('sessionUser',user);
</script>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="mobile-web-app-capable" content="yes">
    <title>Elevator Project</title>
    <meta name="author" content="Lyubomyr Bilyk">
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css?family=Karla" rel="stylesheet">
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link href="css/index.css" rel="stylesheet">
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.min.js"></script>
    <link href="css/index.css" rel="stylesheet">
    <script type="text/javascript">
        $(document).on("click", ".navbar-right .dropdown-menu", function(e){
            e.stopPropagation();
        });
    </script>
</head>
<body id="page-top">
<nav class="navbar navbar-expand navbar-dark bg-dark static-top">
    <a class="navbar-brand mr-1" href="index.php">Elevator Project</a>
    <button class="btn btn-link btn-sm text-white order-1 order-sm-0" id="sidebarToggle" href="#">
        <i class="fas fa-bars"></i>
    </button>
    <ul class="nav navbar-nav navbar-right ml-auto">
        <li class="nav-item dropdown no-arrow mr-0">
            <a class=" nav-link dropdown-toggle d-inline-block px-3 mr-4" id="datetime"></a>
            <a class="nav-link dropdown-toggle d-inline" href="#" id="userDropdown" role="button" data-toggle="dropdown"
               aria-haspopup="true" aria-expanded="false">
                <div class="d-inline-block" id="loginSection"></div>
            </a>
        </li>

<!-- Based on code from tutorialrepublic.com-->

        <li class="nav-item login">
            <a data-toggle="dropdown" class="nav-link dropdown-toggle mr-3" href="#">Login</a>
            <ul class="dropdown-menu form-wrapper">
                <li>
                    <form action="authenticate.php" method="POST">
                        <p class="hint-text">Login to Elevator account.</p>
                        <div class="form-group">
                            <input type="text" class="form-control" placeholder="Username" name="username" required="required">
                        </div>
                        <div class="form-group">
                            <input type="password" class="form-control" placeholder="Password" name="password" required="required">
                        </div>
                        <input type="submit" class="btn btn-primary btn-block" value="Login">
                    </form>
                </li>
            </ul>
        </li>
        <li class="nav-item login">
            <a href="#" data-toggle="dropdown" class="btn btn-primary dropdown-toggle get-started-btn mt-1 mb-1">Sign up</a>
            <ul class="dropdown-menu form-wrapper">
                <li>
                    <form action="authenticate.php" method="post">
                        <p class="hint-text">Fill in this form to create your account!</p>
                        <div class="form-group">
                            <input type="text" class="form-control" placeholder="Username" required="required">
                        </div>
                        <div class="form-group">
                            <input type="password" class="form-control" placeholder="Password" required="required">
                        </div>
                        <div class="form-group">
                            <input type="password" class="form-control" placeholder="Confirm Password" required="required">
                        </div>
                        <input type="submit" class="btn btn-primary btn-block" value="Sign up">
                    </form>
                </li>
            </ul>
        </li>
    </ul>
</nav>
<!-- Modal HTML -->
</body>
</html>
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
        <li class="nav-item">
            <a class="nav-link" href="log.php">
                <i class="fas fa-fw fa-scroll"></i>
                <span>Log</span>
            </a>
        </li>
    </ul>
    <div class="elevator-container container my-2">
        <div class="elevator-building container">
            <div class="elevator-shaft container">
                <div class="container elevator-floor elevator-light">III</div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-floor elevator-light">II</div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-track elevator-light"></div>
                <div class="container elevator-floor elevator-light">I</div>
            </div>
        </div>
        <div class="elevator-controls container ">
            <div class="container elevator-button-box">
                <input type="button" class="elevator-call-btn btn btn-outline-secondary " value="III" onclick="moveElevator(this.value)">
                <input type="button" class="elevator-call-btn btn btn-outline-secondary " value="II" onclick="moveElevator(this.value)">
                <input type="button" class="elevator-call-btn btn btn-outline-secondary " value="I" onclick="moveElevator(this.value)">
            </div>
        </div>
    </div>
</div>
<script src="js/index.js"></script>
</body>
</html>