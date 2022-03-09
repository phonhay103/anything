<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sale table</title>
</head>
<style>
    table, th, td {
        border: solid 1px #000;
    }
</style>
<body>
    
    <?php
        include('connect.php'); 
        if($connect->connect_error){
            die("Error connecting to: ".$connect->connect_error);
       }
       else{
           $radio = $_POST["myradio"];
           $sql = "SELECT * FROM products";
           $sql2 = "UPDATE products SET numb = numb - 1 where product_desc = '$radio' ";
           $connect->query($sql2);
           $table = $connect->query($sql);
        if($table->num_rows > 0){
           echo '<h1 style = "color:blue">Update Results for Table</h1>';
                echo 'The Query is ' . $sql;
                echo '<table><tr><th>Num</th><th>Product</th><th>Cost</th><th>Weight</th><th>Count</th></tr>';
                while($row = $table->fetch_assoc()){
                    echo '<tr><td>' .$row["product_id"].'</td><td>' .$row["product_desc"]."</td><td>" .$row["cost"].'</td><td>'.$row["weight"].'</td><td>'
                    .$row["numb"].'</td></tr>';
                }
                echo '</table>';
        }
        else{
            echo 'Select table error' . $connect->error;
        }
       }
    ?>
</body>
</html>