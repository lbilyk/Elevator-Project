    <?php
    session_start();


    session_destroy();
    session_write_close();
    unset($_SESSION);
    header('Location: index.php');
    exit;
