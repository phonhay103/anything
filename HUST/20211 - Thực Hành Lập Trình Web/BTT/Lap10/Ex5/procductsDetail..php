<!doctype html>
<?php
    $product = $_POST['product'];

?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title><?php  print "$product" ?></title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">

</head>
<body>
<form action="cart.php" method="post">
    <div class="father d-flex align-self-center w-50">
        <div class="left w-75">
            <ul>
                <li>Product name: <?php print "$product" ?></li>
                <li>Publisher: <a href="#">Microsoft  Corp</a></li>
                <li>SKU: 0000</li>
                <li>Platform: windows</li>
            </ul>
        </div>
        <div class="right w-25">
            <a href="#">View Product Description</a>
        </div>
    </div>

    <table>
        <tr>
            <td>・</td>
            <td>Deliverable</td>
            <td>Description</td>
            <td>Price</td>
        </tr>
        <tr>
            <td><input type="radio"></td>
            <td>Download</td>
            <td>Choose this option if you wish to download the software over the internet</td>
            <td>Free!</td>
        </tr>
    </table>
    <input type="hidden" value="<?php print "$product";?>" name="product">
    <input type="submit" value="Add to cart">
</form>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>

</body>
</html>


