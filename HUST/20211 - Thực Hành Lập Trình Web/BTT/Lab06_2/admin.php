<html>
  <head>
    <title>
    <?php
      // print the window title and the topmost body heading
      $doc_title = 'Category Administration';
      echo "$doc_title\n";
    ?>
    </title>
  </head>
  <body>
    <h1>Category Adminstration</h1>
    <hr>
    <form action="admin.php" method="POST">
      <?php
        $server = 'localhost';
        $user = 'root';
        $pass = '';
        $mydb = 'business_service';
        $table_name = 'categories';
        $mysqli = new mysqli($server, $user, $pass, $mydb);       
        if ($mysqli->connect_errno) {
          die ("Cannot connect to $server using $user");
          exit();
        } else {
          if (isset($_POST['catID'])) {
            $catID = $_POST['catID'];
            if (strlen($catID) > 0) {
              $description = $_POST['description'];
              $title = $_POST['title'];
              $updateQuery = "INSERT INTO $table_name VALUES('$catID', '$title', '$description')";
              if (!$mysqli->query($updateQuery)) {
                echo "Add new category failed";
              }
            }
          }

          $SQLcmd = "SELECT * FROM $table_name";
          $mysqli->select_db($mydb);
          $results = $mysqli->query($SQLcmd);
          if ($results){
            print '<table>';
            print '<th>Cat ID<th>Title<th>Description';
            while($row = mysqli_fetch_row($results)) {
              print "<tr>";
              foreach($row as $field) {
                print "<td>$field</td>";
              }
              print "<tr/>";
            }
          } else {
            die ("Query Failed, SQLcmd=$SQLcmd");
          } 
        }
      ?>
      <tr>
        <td><input type="text" name="catID" size="10"></td>
        <td><input type="text" name="title" size="20"></td>
        <td><input type="text" name="description" size="40"></td>
      </tr>
      <tr>
        <td><input type="submit" value="Add Category"></td>
      </tr>
      <?php
        $mysqli->close();
      ?>
    </form>
  </body>
</html>