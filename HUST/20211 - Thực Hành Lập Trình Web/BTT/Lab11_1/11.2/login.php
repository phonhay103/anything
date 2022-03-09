<?
$linkTo = $_REQUEST["LinkTo"];
$userName = $_POST["UserName"];
$password = $_POST["Password"];

if (isset($userName)){
    $host= "localhost";
    $user = "nhay";
    $passwd = "123456";
    $database = "Lab12";
    $table_name = "Users";

    $query = "SELECT * FROM $table_name WERE UserName='$userName' AND Password='$password'";
    $connect = mysqli_connect($host, $user, $passwd);

    if($connect){
        mysqli_select_db($database);
        $result = mysqli_query($query, $connect);

        $row = mysqli_fetch_row($result);
        if ($result && $row){
            if($linkTo != ""){
                header("Location: ".$linkTo);
            }else{
                header("Location: http://google.com/");
                exit();
            }
        }
    }
}
?>

<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {font-family: Arial, Helvetica, sans-serif;}
        form {border: 3px solid #f1f1f1;}

        input[type=text], input[type=password] {
            width: 100%;
            padding: 12px 20px;
            margin: 8px 0;
            display: inline-block;
            border: 1px solid #ccc;
            box-sizing: border-box;
        }

        button {
            background-color: #4CAF50;
            color: white;
            padding: 14px 20px;
            margin: 8px 0;
            border: none;
            cursor: pointer;
            width: 100%;
        }

        button:hover {
            opacity: 0.8;
        }

        .imgcontainer {
            text-align: center;
            width: 150px;
            margin: 20px auto;
        }

        img.avatar {
            width: 100%;
            border-radius: 50%;
        }

        .container {
            padding: 16px;
            width: 40%;
            margin: 10px auto;
        }

        span.psw {
            float: right;
            padding-top: 16px;
        }

    </style>

    <script language="javascript">
        function fCommit(){
            if (document.frmLogin.UserName.value == ""){
                alert("UseName mus be enter !");
                document.frmLogin.UserName.focus();
                return false
            }
            return true;
        }

        function fReset(){
            document.frmLogin.UserName.value = "";
            document.frmLogin.Password.value = "";
            document.frmLogin.UserName.focus();
        }
    </script>
</head>
<body>

<h2 style="text-align: center">Login Form</h2>

<form action="<?php echo $_SERVER["PHP_SELF"] ?>" method="post" name="frmLogin" onsubmit="return fCommit();">
    <div class="imgcontainer">
        <img src="avatar.jpg" alt="Avatar" class="avatar">
    </div>

    <div class="container">
        <b>Username</b>
        <input type="text" placeholder="Enter Username" name="UserName" value="<?php echo $userName ?>">
        <input type="hidden" name="LinkTo" value="<?php echo $linkTo ?>">
        <br />
        <b>Password</b>
        <input type="password" placeholder="Enter Password" name="Password">

        <button type="submit" name="submit">Login</button>
        <button type="reset" name="reset" onclick="fReset();">Reset</button>
        <input type="hidden" name="LinkTo" value="<?php echo $linkTo ?>">
    </div>

    <?php
    if(isset($user) && !$row){
        echo "<p>Invalid name and/or password</p>";
    }
    mysqli_free_result($result);

    mysqli_close($connect);
    ?>
</form>

</body>
</html>