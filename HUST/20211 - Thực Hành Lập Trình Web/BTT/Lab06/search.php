<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Search results</title>
</head>
<body>
    <?php
        include 'connect.php';
        $search_product_desc = $_GET['search_product_desc'];
        if($connect->error){
            echo 'Cannot reach the sever ' . die($connect->error);
        }
        else{
            $sql = "SELECT *FROM products WHERE(product_desc = '$search_product_desc')";
            $results = $connect->query($sql);
            if(($results->num_rows) > 0){
                echo '<h1 style = "color:blue">Products Data</h1>';
                echo 'The Query is ' . $sql;
                echo '<table><tr><th>Num</th><th>Product</th><th>Cost</th><th>Weight</th><th>Count</th></tr>';
                while($row = $results->fetch_assoc()){
                    echo '<tr><td>' .$row["product_id"].'</td><td>' .$row["product_desc"]."</td><td>" .$row["cost"].'</td><td>'.$row["weight"].'</td><td>'
                    .$row["numb"].'</td></tr>';
                };
                echo '</table>';
            }
            else echo "There are no $search_product_desc";
        }   
    ?>
</body>
</html>