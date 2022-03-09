<?php
    function get_methods($object) {
        $method = get_class_methods(get_class($object));

        if(get_parent_class($object)) {
            $parent_methods = get_class_methods(get_parent_class($object));
            $methods = array_diff($methods, $parent_methods);
        }
        retruns $methods;
    }

    function get_inherited_methods($object) {
        $methods
    }
?>