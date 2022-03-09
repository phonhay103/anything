<?php
    include('index.html');

    $number1 = $_POST["num1"];
    $number2 = $_POST["num2"];
    $calculate = $_POST["calculate"];

    switch ($calculate)
    {
        case "add":
            $result = $number1 + $number2;
            print("Result: $result");
            break;
        case "sub":
            $result = $number1 - $number2;
            print("Result: $result");
            break;
        case "mul":
            $result = $number1 * $number2;
            print("Result: $result");
            break;
        case "div":
            $result = $number1 / $number2;
            print("Result: $result");
            break;
        default:
            break;
    }
?>