<html>

<form action="<?php echo $_SERVER["PHP_SELF"] ?>" method="POST">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Submit">
    <input type="reset" value="Reset">
</form>
<?php session_start(); ?>

<?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $mydb = "Lab12";
    $table_name = "Users";
    // Create connection
    $connect = mysqli_connect($servername, $username, $password);

    // Check connection
    if (!$connect) {
        die("Connection failed: <br>" . mysqli_connect_error());
    }
    
    $connect->select_db($mydb);
    
    if(array_key_exists('username',$_POST) && array_key_exists('password',$_POST)){
        
        $username = $_POST['username'];
        $password = $_POST['password'];

        $query = "SELECT * FROM $table_name WHERE UserName = '$username'";

        
        $result = $connect->query($query);
        
        if ($result) {
            while($row = $result->fetch_assoc()){
                if($password == $row['Password']){
                    print('Welcome you to my page');
                    $_SESSION['UserName'] = $username;
                }else{
                    print('<p style="color:red;">Password not valid</p>');
                }
            }
        }else{
            print "Username not correct";
        }
    }else{
        print "Please login"; 
    }
?>


</html>
