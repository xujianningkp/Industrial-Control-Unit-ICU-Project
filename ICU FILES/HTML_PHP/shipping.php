<!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
		<link rel="shortcut icon" type="image/ico" href="images/icon.ico"/>
		<link href="styles.css" rel="stylesheet" type="text/css" media="screen">
		<title>PLC | Shipping</title>

		<style>
			body {
				background-image:url(images/background.png);
				background-repeat:repeat-x;
			}
		</style>

	</head>

	<body>
		<div id="container">
			<div class="header">
				<div class="nav">
					<ul>
						<li><a href="iisstart.htm">Home</a></li>
						<li><a href="scheduling.php">Scheduling</a></li>
						<li><a href="search.php">Tracking</a></li>
						<li><a href="shipping.php">Shipping</a></li>
						<li><a href="location.php">Location</a></li>
					</ul>
						
				</div>
				<img class="logo" src="images/home.PNG" width="220" height="60">
			</div>
				
			<br><br><br><br><br><br><br>
			<div class="heading">Shipping</div>
			<br><br><br>

			<div class="content">
				<form action="shipping.php" method="post">
					<label>RFID</label>
					<input type="text" name="RFID" size="40">
					<input id="button" type="submit" value="Ship"><br><br><br><br>
				</form>
			</div>

			<?php
			$serverName = "JIMMY-PC\SQLEXPRESS"; //serverName\instanceName
			$connectionInfo = array( "Database"=>"testingdb", "UID"=>"xujianningkp", "PWD"=>"123456", "ReturnDatesAsStrings"=>"true");

			//"ReturnDatesAsStrings"=>"true"

			$conn = sqlsrv_connect( $serverName, $connectionInfo);

			$rfid = $_POST["RFID"];

			if(!empty($rfid))
			{
			$tsql2 = "select UPC from lab.marry where rfid = '$rfid'";
			$stmt2 = sqlsrv_query($conn, $tsql2);
			while($row = sqlsrv_fetch_array($stmt2)){
			$marryupc = $row[UPC];
			}
			$tsql = "update lab.marry set upc = '' where rfid = '$rfid'; INSERT INTO lab.tracking (RFID, UPC, location) values ('$rfid','$marryupc','SHIPPER')";
			$stmt = sqlsrv_query($conn, $tsql);
			}


			$tsql1 = "select * from lab.marry";

			$stmt1 = sqlsrv_query($conn, $tsql1);


			echo " <table class='gridtable'><tr><th>Index</th><th>RFID</th><th>UPC</th></tr>";

			$counter = 1;

			while($row = sqlsrv_fetch_array($stmt1))
			{
				echo "<tr><td>" . $counter . "</td><td>" . $row[RFID] . "</td><td>" . $row[UPC] . "</td></tr>";
				$counter = $counter+1;
			}

			sqlsrv_free_stmt($stmt1);

			echo "</table>";

			?>

			<br><br>
			<div id="footer">
				<p class="foottext">Copyright &copy; 2014 | All Rights Reserved</p>
			</div>
		</div>
	</body>
</html>