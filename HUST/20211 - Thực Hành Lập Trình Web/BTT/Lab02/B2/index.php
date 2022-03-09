<?php
    include('index.html');

    $string = $_POST["string"];
    $type = $_POST["type"];

    switch ($type)
    {
        case "strlen":
            $result = strlen($string);
            print("Result: $result");
            break;
        case "trim":
            $result = trim($string);
            print("Result: $result");
            break;
        case "strtolower":
            $result = strtolower($string);
            print("Result: $result");
            break;
        case "strtoupper":
            $result = strtoupper($string);
            print("Result: $result");
            break;
        default:
            break;
    }
?>