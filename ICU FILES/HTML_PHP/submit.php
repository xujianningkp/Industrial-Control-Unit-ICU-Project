<?php
$serverName = "JIMMY-PC\SQLEXPRESS"; //serverName\instanceName
$connectionInfo = array( "Database"=>"testingdb", "UID"=>"xujianningkp", "PWD"=>"123456");

$conn = sqlsrv_connect( $serverName, $connectionInfo);

$rfid = "";
$status = "";
$location = "";

$rfid = $_POST["RFID"];
$status = $_POST["STATUS"];
$location = $_POST["LOCATION"];

$tsql1 = "select UPC from lab.marry where rfid = '$rfid'";
$stmt1 = sqlsrv_query($conn, $tsql1);
while($row = sqlsrv_fetch_array($stmt1)){
$marryupc = $row[UPC];
}

if (!empty($rfid) and empty($status)){
$tsql = "INSERT INTO lab.tracking (RFID, UPC, location) values ('$rfid','$marryupc','$location')";
$stmt = sqlsrv_query($conn, $tsql);
$tsql2 = "update lab.location set Status = '$rfid' where Location = '$location'";
$stmt2 = sqlsrv_query($conn, $tsql2);
}
elseif (!empty($rfid) and !empty($status)){
$tsql = "INSERT INTO lab.tracking (RFID, UPC, location) values ('$rfid','$marryupc','$location')";
$stmt = sqlsrv_query($conn, $tsql);
$tsql2 = "update lab.location set Status = '$status' where Location = '$location'";
$stmt2 = sqlsrv_query($conn, $tsql2);
}





if ($stmt or $stmt1 or $stmt2)
{
	echo "<h1>Submission Successful.<h1><br />";
	echo "<h2>The data = $txdata<h2>";
}
else
{
	echo "submission unsuccessful. <br />";
	die ( print_r(sqlsrv_errors(), true));
}

?>

