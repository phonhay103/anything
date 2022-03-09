<?php
    class MethodTest {
        public funtion __call($name, $args) {
            echo "Calling object method '$name' " . implode(", ", $args) . "<br>";
        }

        public static funtion __callStatic($name, $args) {
            echo "Calling static method '$name' " . implode(", ", $args) . "<br>";
        }
    }

    $obj = new MethodTest;
    $obj->runTest('In object context');
    MethodTest::runTest('In static context');
?>