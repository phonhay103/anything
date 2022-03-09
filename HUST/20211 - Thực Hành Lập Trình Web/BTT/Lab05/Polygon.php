<?php
    include 'Shape.php';
    abstract class Polygon extends Shape {
        abstract function getNumberOfSides();
    }
?>