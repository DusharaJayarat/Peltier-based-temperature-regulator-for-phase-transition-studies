<?php
$hostname = "localhost";
$username = "root";
$password = "";
$database = "final";

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

echo "Database connection is OK <br>";

if(isset($_POST["RoomTemperature"]) && isset($_POST["RoomPressure"]) && isset($_POST["temperature"])) {

	$temperature = $_POST["temperature"];
    $RoomTemperature = $_POST["RoomTemperature"];
    $RoomPressure = $_POST["RoomPressure"];
    

    $sql = "INSERT INTO cooling1 (temperature, RoomTemperature, RoomPressure) VALUES ('$temperature','$RoomTemperature', '$RoomPressure')";

    if (mysqli_query($conn, $sql)) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
}

mysqli_close($conn);
?>

