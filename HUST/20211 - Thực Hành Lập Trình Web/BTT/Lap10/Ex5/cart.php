<!doctype html>
<?php
    $product = $_POST['product'];
    session_start();
    if( $_SESSION['products'] != null){
        $products = $_SESSION['products'];
    }
    else{
        $products = [];
    }
    array_push($products, $product);
    $_SESSION['products'] = $products;
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
<h1>View shopping cart</h1>
<table>
    <tr>
        <td>Software Title</td>
        <td>Deliverable</td>
        <td>Price</td>
    </tr>
    <?php
        foreach($products as $product){
            echo '<tr>';
            echo "<td>$product</td>";
            echo "<td>Download</td>";
            echo '<td>Free!</td>';
            echo '</tr>';
        }
    ?>



</table>
<a href="home.php">Continue to shopping</a>
<a href="removeSession.php">Checkout</a>
</body>
</html>