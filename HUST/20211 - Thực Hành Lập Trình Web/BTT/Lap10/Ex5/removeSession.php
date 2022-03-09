<?php
    session_start();
?>
<!DOCTYPE html>
<html>
<body>

<?php
    // remove all session variables
    session_unset();

    // destroy the session
    session_destroy();
?>
<h1>Thank you for using our service</h1>
<a href="home.php">Continue to shopping</a>
</body>
</html>
