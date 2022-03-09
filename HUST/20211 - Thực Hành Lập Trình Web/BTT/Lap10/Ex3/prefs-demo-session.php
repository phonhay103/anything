<html>

<head>
    <title>Front Door</title>
</head>
<?php session_start(); 
    $bg = $_SESSION["bg"];
    $fg = $_SESSION["fg"];
?>

<body bgcolor="<?= $bg ?>" text="<?= $fg ?>">
    <h1>Welcome to the Store</h1>
    <p>We have many fine products for you to view. Please feel free to browse the aisles and stop an assitant at any time. But remember, you break it you bought it!</p>
    Would you like to <a href="prefselection.html">change your preferences?</a>

</body>

</html>