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
  $table_name = 'Categories';
  $SQLcmd = "SELECT * FROM $table_name";
  $results = $mysqli->query($SQLcmd);
  $categoriesList = array();
  while ($row =  mysqli_fetch_array($results)) {
    $categoriesList[] = $row;
  }
?>

<html>
  <head>
    <title>Business Listing</title>
  </head>
  <body>
    <h1>Business Listing</h1>
    <hr>
    <table>
      <tr>
        <td valign="top">
          <?php
            print '<table border=1>';
            print '<th>Click on a category to find business listings:';
            foreach ($categoriesList as $row) {                
              print "<tr><td><a href='biz_listing.php?catID=$row[0]'>$row[1]</a></td></tr>";
            }
            print "</table>";
          ?>
        </td>
        <td valign="top">
          <?php
            if (isset($_GET['catID'])) {
              $catID = $_GET['catID'];
              if (strlen($catID) > 0) {
                $table_name = "Biz_Categories";
                $findBizQuery = "SELECT * FROM $table_name WHERE(Category_ID = '$catID')";
                $results = $mysqli->query($findBizQuery);
                if ($results) {
                  $table_name = "Businesses";
                  print '<table border=1>';
                  print '<th>ID<th>Name<th>Address<th>City<th>Telephone<th>URL';
                  while ($row = mysqli_fetch_row($results)) {
                    $bizQuery = "SELECT * FROM $table_name WHERE(Business_ID = $row[0])";
                    $bizs = $mysqli->query($bizQuery);
                    if ($bizs) {
                      while($row = mysqli_fetch_row($bizs)) {
                        print "<tr>";
                        foreach($row as $field) {
                          print "<td>$field</td>";
                        }
                        print "<tr/>";
                      }
                      
                    }
                  }
                  print "</table>";
                }
              }
            }
            $mysqli->close();
          ?>
        </td>
      </tr>
    </table>
  </body>
</html>