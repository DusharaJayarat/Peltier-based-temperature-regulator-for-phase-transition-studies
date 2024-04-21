<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "final";


$conn = new mysqli($servername, $username, $password, $dbname);

$min_temperature = 0;
$max_temperature = 150;

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


$sql = "SELECT  time, ROUND(temperature, 1) AS temperature FROM cooling1 WHERE temperature >= $min_temperature AND temperature <= $max_temperature ORDER BY time ASC";

$result = $conn->query ($sql);


$data = array();
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}


$conn->close();


header('Content-Type: application/json');
echo json_encode($data);
?>

