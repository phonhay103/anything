<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Shopping</title>
</head>
<body>

    <div class="">
        <form action="procductsDetail..php" method="post">
            <label for="product">Select the product you want to purchase</label>
            <br/>
            <select name="product" id="">
                <?php
                    include ('data.php');
                    global $products;
                    foreach($products as $product){
                       echo "<option value='$product'>$product</option>";
                    }
                ?>
            </select>
            <input type="submit" value="Submit">
        </form>
    </div>
</body>
</html>