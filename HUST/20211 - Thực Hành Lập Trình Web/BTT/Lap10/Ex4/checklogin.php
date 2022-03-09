<html>
    <?php session_start(); ?>
    <p>Welcome to checklogin page</p>
    <?php
        if(isset($_SESSION['UserName'])){
            print "You has already login";
        }else{
            header("Location: http://127.0.0.1:8080/Lab10/Ex4/login.php");
            exit();
        }
    ?>
    
</html>