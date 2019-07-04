<?php
session_start();
unset($_SESSION);
session_destroy();
session_write_close();
?>
<script>localStorage.removeItem('sessionUser')</script>
<?php
header('Location: login.php');
exit;