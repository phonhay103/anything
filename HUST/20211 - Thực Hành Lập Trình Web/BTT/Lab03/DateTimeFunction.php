<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data time process</title>
</head>
<body>
<form method="POST" action="DateTimeFunction.php">
        <label for="name">Your name </label><br>
        <input type="text" id="name1" name="name1"><br>
        
        <label for="start">birthday :</label>
        <input type="date" id="date1" name="date1" ><br>

        <label for="name">Your name </label><br>
        <input type="text" id="name2" name="name2"><br>

        <label for="appt">birthday </label>
        <input type="date" id="date2" name="date2"><br>

        <label for="submit">Submit</label><br>
        <input type="submit" name="submit" id="submit" value="Submit">
    </form>
</body>
</html>
<?php
    $date1 = strtotime($_POST['date1']);
    $date1 = date('Y-m-d', $date1);
    $date2 = strtotime($_POST['date2']);
    $date2 = date('Y-m-d', $date2);

    $today = date('Y-m-d');

    if($date1 > $today){
        echo("fail 1 !!!! <br>" );
    }
    elseif($date2 > $today){
        echo("fail 2 !!!! <br>" );
    }
    else {
        echo("Hi " . $_POST['name1'] . "<br>" );
        echo("your birthday was " . $date1 . "<br>");
        echo("Age : " . (int)$today - (int)$date1 . "<br>");
        echo("Hi " . $_POST['name2'] . "<br>" );
        echo("your birthday was " . $date2 . "<br>");
        echo("Age : " . (int)$today - (int)$date2 . "<br>");

        if($date1 > $date2) {
            echo("The difference is " . (int)$date1 - (int)$date2 . "<br>") ;
        }
        else {
            echo("The difference is " . (int)$date2 - (int)$date1 . "<br>") ;
        }


    }
?>