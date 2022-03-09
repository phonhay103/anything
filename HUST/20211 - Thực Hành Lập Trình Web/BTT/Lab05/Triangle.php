<?php
    require "Polygon.php";
    class Triangle extends Polygon {
        public $base;
        public $height;
        public function getArea() {
            return (($this->base * $this->height) / 2);
        }
        public function getNumberOfsides() {
            return 3;
        }
    }
?>
