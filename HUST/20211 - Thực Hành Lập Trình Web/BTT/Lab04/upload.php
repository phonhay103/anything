<?php
    $target_dir    = "posts/";
    
    $files = scandir($target_dir);
    for ($i = 2; $i < count($files); $i++) {
        if (explode(".", $files[$i])[1] == "txt") {
            print(explode("_", explode(".", $files[$i])[0])[0] . " says: ");
            print(file_get_contents($target_dir . $files[$i]));
            print("<br>");
        }
        else {
            print("<img src=\"" . $target_dir . $files[$i] . "\" width=\"80\" height=\"80\">");
        }
    }

    print("<br><br>");
    include("upload.html");

    $upload_file = $_FILES["fileupload"]['error'];
    $allowUpload   = false;

    if ($upload_file == 0) {
        $allowUpload   = true;
        $imageFileType = pathinfo($target_dir . basename($_FILES["fileupload"]["name"]), PATHINFO_EXTENSION);
        $target_file   = $target_dir . basename($_FILES["fileupload"]["name"]);
        $maxfilesize   = 8000000;
        $allowtypes    = array('jpg', 'png', 'jpeg', 'gif');

        $check = getimagesize($_FILES["fileupload"]["tmp_name"]);
        if($check !== false)
            $allowUpload = true;
        else
        {
            echo "Không phải file ảnh. ";
            $allowUpload = false;
        }

        if ($_FILES["fileupload"]["size"] > $maxfilesize)
        {
            echo "Không được upload ảnh lớn hơn $maxfilesize (bytes).";
            $allowUpload = false;
        }

        if (!in_array($imageFileType,$allowtypes ))
        {
            echo "Chỉ được upload các định dạng JPG, PNG, JPEG, GIF";
            $allowUpload = false;
        }
    }

    if (isset($_POST['anonymous']) || $_POST['username'] == "")
        $fileName = $target_dir . "anonymous_" . date("d-m-Y h-i-s");
    else
        $fileName = $target_dir . $_POST['username'] . "_" . date("d-m-Y h-i-s");

    if ($_POST['comment']) {
        if ($allowUpload) {
            move_uploaded_file($_FILES["fileupload"]["tmp_name"], $fileName . "." . $imageFileType);
        }

        $fp = fopen($fileName . ".txt", 'w');
        fwrite($fp, $_POST['comment']);
        fclose($fp);
    }
?>