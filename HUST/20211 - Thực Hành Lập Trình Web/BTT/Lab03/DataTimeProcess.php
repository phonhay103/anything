<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data time process</title>
</head>
<body>
<form method="POST" action="datatimeprocess.php">
        <label for="name">Your name </label><br>
        <input type="text" id="name" name="name"><br>
        
        <label for="start">Date time :</label>
        <input type="date" id="date" name="date" min="2000-01-01" max="2023-12-31"><br>

        <label for="appt">Time </label>
        <input type="time" id="time" name="time"><br>

        <label for="submit">Submit</label><br>
        <input type="submit" name="submit" id="submit" value="Submit">
    </form>
</body>
</html>
<?php
    $time = strtotime($_POST['date']);
    $month= date("m",$time);
    echo($month);
    $year= date("Y",$time);
    $today = date('Y-m-d');
    $dayleft = (int)$today - (int)$_POST['date'];

    echo("Hi " . $_POST['name'] . "<br>" );
    echo("You have choose to have an appointment on " . $_POST['time'] . " " . $_POST['date'] . "<br>");
    echo("More information <br>");
    echo("In 12 hours, the time and date is " . $_POST['time'] . " " . $_POST['date'] . "<br>");

    $days = [31, 28, 31, 30, 31, 30, 31 ,31 ,30, 31, 30 ,31];
    if ($month != 2 ){
        echo("this month has " . $days[$month - 1 ] . "days <br>");
    }
    else {
        if($year % 100 == 0 && $year % 4 == 0){
            echo("this month has " . $days[$month - 1 ] + 1 . "days <br>");
        }
        elseif($year % 100 != 0 && $year % 4 == 0) {
            echo("this month has " . $days[$month - 1 ] + 1 . "days <br>");
        }
        else{
            echo("this month has " . $days[$month - 1 ] . "days <br>");
        }
    }
?>