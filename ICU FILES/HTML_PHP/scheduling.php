<!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
		<link rel="shortcut icon" type="image/ico" href="images/icon.ico"/>
		<link href="styles.css" rel="stylesheet" type="text/css" media="screen">
		<title>PLC | Scheduling</title>


		<script type="text/javascript"> 

			function stopRKey(evt) { 
			  var evt = (evt) ? evt : ((event) ? event : null); 
			  var node = (evt.target) ? evt.target : ((evt.srcElement) ? evt.srcElement : null); 
			  if ((evt.keyCode == 13) && (node.type=="text"))  {return false;} 
			} 

			document.onkeypress = stopRKey; 

		</script>

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
			<div class="heading">Scheduling</div>
			<br><br><br>

			<div class="content">
				<form action="scheduling.php" method="post">
					<label>RFID</label>
					<input type="text" name="RFID" size="40"> <br>
					<label>UPC</label>
					<input type ="text" name="UPC" size = "40"> 
					</div>
					<input id="button" type="submit" value="Join"> <br><br>
				</form>
			</div>
			<div class="content">
				<form action="scheduling.php" method="post">
					<label>New RFID</label>
					<input type="text" name="NEWRFID" size="40" placeholder="Insert a new RFID">
					</div>
					<input id="button" type="submit" value="Add"><br><br>
				</form>
			</div>
			<div class="content">
				<form action="scheduling.php" method="post">
					<label>Remove RFID</label>
					<input type="text" name="REMOVERFID" size="40" placeholder="Delete tracking before remove RFID">
					</div>
					<input id="button" type="submit" value="Delete"><br><br><br><br>
				</form>
			</div>
		</div>

		<?php
		$serverName = "JIMMY-PC\SQLEXPRESS"; //serverName\instanceName
		$connectionInfo = array( "Database"=>"testingdb", "UID"=>"xujianningkp", "PWD"=>"123456", "ReturnDatesAsStrings"=>"true");

		//"ReturnDatesAsStrings"=>"true"

		$conn = sqlsrv_connect( $serverName, $connectionInfo);

		$rfid = "";
		$upc = "";
		$newrfid = "";
		$removerfid = "";

		$rfid = $_POST["RFID"];
		$upc = $_POST["UPC"];
		$newrfid = $_POST["NEWRFID"];
		$removerfid = $_POST["REMOVERFID"];

		if (!empty($rfid) and !empty($upc)){
		$tsql = "update lab.marry set upc = '$upc' where rfid = '$rfid'; INSERT INTO lab.tracking (RFID, UPC, location) values ('$rfid','$upc','SCHEDULER')";

		$stmt = sqlsrv_query($conn, $tsql);
		}

		if (!empty($newrfid)){
		$tsql1 = "insert into lab.marry (RFID) values ('$newrfid')";

		$stmt1 = sqlsrv_query($conn, $tsql1);
		}

		if (!empty($removerfid)){
		$tsql1 = "delete from lab.marry where RFID = '$removerfid'";

		$stmt1 = sqlsrv_query($conn, $tsql1);
		}

		$tsql2 = "select * from lab.marry";

		$stmt2 = sqlsrv_query($conn, $tsql2);


		echo " <table class='gridtable'><tr><th>Index</th><th>RFID</th><th>UPC</th></tr>";

		$counter = 1;

		while($row = sqlsrv_fetch_array($stmt2))
		{
			echo "<tr><td>" . $counter . "</td><td>" . $row[RFID] . "</td><td>" . $row[UPC] . "</td></tr>";
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