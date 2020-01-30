<?php
$servername = "localhost";
$username = "mmandulak1";
$password = "mmandulak1";
$db = "EndangeredAnimalsDB";

$query = "SELECT * FROM ";
$table1 = "";
$table2 = "";
$conn = mysqli_connect($servername, $username, $password, $db);
if(!$conn)
{
    die('<p> Could not connect to MySQL </p>');
}
else
{
    echo 'connected to DB<br>';
}
$q =$_GET["q"];
echo "<br> q: $q <br>";
$inputarr = explode(" ", $q);
echo "you selected $inputarr[0]";
echo "<br>";
echo "searchVal = $inputarr[1]";

switch($inputarr[0])
{
    case 'all':
        break;
    case 'animals':
        $table1 = "Animals_R1";
        $table2 = "Animals_R2";
    break;
    case 'plants':
        $table1 = "Plants_R1";
        $table2 = "Plants_R2";
    break;
    case 'region':
        $table1 = "Region";
    break;
    case 'dangers':
        $table1 = "Dangers";
    break;
    case 'population':
        $table1 = "Organisms_R1";
        $table2 = "Organisms_R2";
    break;
}
echo"<br>";
echo"tables: $table1 and $table2";
if($table2=="")
{
    $query = $query . $table1;
}
else
{
    $query = $query . $table1 . ", " . $table2;
}
echo "<br> $query";
$result = mysqli_query($conn, $query);


?>

