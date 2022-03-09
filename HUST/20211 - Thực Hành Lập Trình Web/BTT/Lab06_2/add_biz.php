<?php
$server = 'localhost';
$user = 'root';
$pass = '';
$mydb = 'business_service';
  $mysqli = new mysqli($server, $user, $pass, $mydb);
  $mysqli->select_db($mydb);
  if ($mysqli->connect_errno) {
    die ("Cannot connect to $server using $user");
    exit();
  }
  $isRegistered = false;
  if (isset($_POST['bizName'])) {
    $bizName = $_POST['bizName'];
    $address = $_POST['address'];
    $city = $_POST['city'];
    $telephone = $_POST['telephone'];
    $categories = $_POST['categories'];
    $url = $_POST['url'];
    if ((strlen($bizName) > 0)
      && (strlen($address) > 0)
      && (strlen($city) > 0)
      && (count($categories) > 0)) {
      $isRegistered = true;
    }
  }
?>
<html>
  <head>
    <title>Business Registration</title>
  </head>
  <body>
    <h1>Business Registration</h1>
    <hr>
    <form action="add_biz.php" method="POST">
      <table>
        <tr>
          <td>
            <p>
              <?php
                $table_name = 'Categories';
                $SQLcmd = "SELECT * FROM $table_name";
                $results = $mysqli->query($SQLcmd);
                $categoriesList = array();
                while ($row =  mysqli_fetch_array($results)) {
                  $categoriesList[] = $row;
                }
                if(!$isRegistered) {
                  echo "Click on one, or control-click on multiple categories:";
                } else {
                  $isRegisterSuccess = true;
                  $table_name = 'Businesses';
                  $mysqli->select_db($mydb);
                  $addQuery = "INSERT INTO $table_name(name, address, city, telephone, url) VALUES('$bizName', '$address', '$city', '$telephone', '$url')";
                  $result = $mysqli->query($addQuery);
                  if ($result) {
                    $bizID = $mysqli->insert_id;
                    $table_name = "Biz_Categories";
                    foreach ($categoriesList as $row) {
                      if (in_array($row[1], $categories)) {
                        $catBizUpdateQuery = "INSERT INTO $table_name(business_id, category_id) VALUES($bizID, '$row[0]')";
                        if (!$mysqli->query($catBizUpdateQuery)) {
                          $mysqli->rollback();
                          echo "Insert failed! query = $catBizUpdateQuery";
                          $isRegisterSuccess = false;
                          break;
                        }
                      }
                    }
                  } else {
                    $isRegisterSuccess = false;
                  }
                  if ($isRegisterSuccess) {
                    echo "Record inserted as shown below.";
                  } else {
                    echo "Insert failed!";
                  }
                }
              ?>
            </p>
            <p>Select category values are highlighted: </p>
            <?php
              
              if ($categoriesList){
                print '<select name="categories[]" size=5 multiple>';
                foreach ($categoriesList as $row) {                
                  if ($isRegistered) {
                    if (in_array($row[1], $categories)) {
                      print "<option selected>$row[1]</option>";
                    } else {
                      print "<option>$row[1]</option>";
                    }
                  } else {
                    print "<option>$row[1]</option>";
                  }
                }
                print "</select>";
              } else {
                die ("Query Failed, SQLcmd=$SQLcmd");
              } 
            ?>
          </td>
          <td>
            <table>
              <tr>
                <td>Business Name: </td>
                <td><input type="text" name="bizName" size="40" value=""></td>
              </tr>
              <tr>
                <td>Address: </td>
                <td><input type="text" name="address" size="40" value=""></td>
              </tr>
              <tr>
                <td>City: </td>
                <td><input type="text" name="city" size="40" value=""></td>
              </tr>
              <tr>
                <td>Telephone: </td>
                <td><input type="text" name="telephone" size="40" value=""></td>
              </tr>
              <tr>
                <td>URL: </td>
                <td><input type="text" name="url" size="40" value=""></td>
              </tr>
            </table>
          </td>
        </tr>
        <tr>
          <td>
            <?php
              if(!$isRegistered) {
                echo '<input type="submit" value="Add Business">';
              } else {
                echo '<a href="add_biz.php">Add Another Business</a>';
              }
              $mysqli->close();
            ?>
          </td>
        </tr>
      </table>  
    </form>
  </body>
</html>