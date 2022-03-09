<?php
    require "polygon.php";
    class Circle extends Polygon {
        public $radius;

        public function getArea() {
            return pi() * $this->radius * $this->radius;
        }
    }
?>