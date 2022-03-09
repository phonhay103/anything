<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <?php
    $itemDes = $_POST["itemDes"];
    $weight = $_POST["weight"];
    $cost = $_POST["cost"];
    $numberAvai = $_POST["numberAvai"];
    $severname = "localhost";
    $username = "maiphong";
    $password = "maiphong";
    $table_name = "products";
    $mydb = "lab06";
    $connect = new mysqli($severname, $username, $password, $mydb);

    if ($connect->connect_error) {
        die("Error connecting to: " . $connect->connect_error);
    }
    else{
        $sql = "INSERT INTO $table_name VALUES('0', '$itemDes', '$weight', '$cost', '$numberAvai')";
        if($connect->query($sql)){
            
            echo $sql."<br> Insert into products table was successful! <br>";
        }
        else echo "Error to insert table " . $connect->error . $sql;
    }

    ?>
</body>

</html>