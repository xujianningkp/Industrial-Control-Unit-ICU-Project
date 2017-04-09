<!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
		<link rel="shortcut icon" type="image/ico" href="images/icon.ico"/>
		<link href="styles.css" rel="stylesheet" type="text/css" media="screen">
		<title>PLC | Location</title>
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
		<div class="heading">Location</div>
		<br><br><br>

		<div class="content">
			<form action="location.php" method="post">
				<label>New Location</label>
				<input type="text" name="NEWLOC" size="40">
				<input id="button" type="submit" value="Add"> <br><br>
			</form>
		</div>
		<div class="content">
			<form action="location.php" method="post">
				<label>Remove Location</label>
				<input type="text" name="REMOVELOC" size="40" placeholder="Delete tracking before remove location">
				<input id="button" type="submit" value="Delete"><br><br><br><br>
			</form>
		</div>

		<?php
		$serverName = "JIMMY-PC\SQLEXPRESS"; //serverName\instanceName
		$connectionInfo = array( "Database"=>"testingdb", "UID"=>"xujianningkp", "PWD"=>"123456", "ReturnDatesAsStrings"=>"true");

		//"ReturnDatesAsStrings"=>"true"

		$conn = sqlsrv_connect( $serverName, $connectionInfo);

		$newloc = "";
		$removeloc = "";

		$newloc = $_POST["NEWLOC"];
		$removeloc = $_POST["REMOVELOC"];

		if (!empty($newloc) and empty($removeloc)){
		$tsql = "INSERT INTO lab.location (Location) values ('$newloc')";

		$stmt = sqlsrv_query($conn, $tsql);
		}

		if (!empty($removeloc) and empty($newloc)){
		$tsql1 = "delete from lab.location where Location = '$removeloc'";

		$stmt1 = sqlsrv_query($conn, $tsql1);
		}


		$tsql2 = "select * from lab.location";

		$stmt2 = sqlsrv_query($conn, $tsql2);


		echo " <table class='gridtable'><tr><th>Index</th><th>Location</th><th>Status/RFID</th></tr>";

		$counter = 1;

		while($row = sqlsrv_fetch_array($stmt2))
		{
			echo "<tr><td>" . $counter . "</td><td>" . $row[Location] . "</td><td>" . $row[Status] . "</td></tr>";
			$counter = $counter+1;
		}

		sqlsrv_free_stmt($stmt2);

		echo "</table>";


		?>

		<br><br>
		<div id="footer">
			<p class="foottext">Copyright &copy; 2014 | All Rights Reserved</p>
		</div>

	</body>
</html>