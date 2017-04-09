<!DOCTYPE html>
<html>
	<head>
		<script src="jquery-1.6.2.min.js"></script>
		<script src="jquery-ui-1.8.15.custom.min.js"></script>
		<link rel="stylesheet" href="jqueryCalendar.css">
		<script>
			jQuery(function() {
							jQuery( "#datepicker" ).datepicker();
			});
		</script>

		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
		<link rel="shortcut icon" type="image/ico" href="images/icon.ico"/>
		<link href="styles.css" rel="stylesheet" type="text/css" media="screen">
		<title>PLC | Search</title>

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
			<div class="heading">Search the Database</div>
			<br><br><br>

			<div class="content">
				<form action="search.php" method="post">
					<label>RFID</label>
					<input type="text" name="searchRFID" size="40" placeholder="Search / Enter [delete] to clear table"> <br>
					<label>UPC</label>
					<input type ="text" name="searchUPC" size = "40"> <br>
					<label>Location</label>
					<input type ="text" name="searchLOC" size = "40"><br>
					<label>Date</label>
					<input id="datepicker" type="text" name="searchDATE1" size = "40" placeholder="Date / From"><br> 
					<input id="datepicker" type="text" name="searchDATE2" size="40" placeholder="To"><br>
					<label>Time</label>
					<input type="text" name="searchTIME1" size = "40" placeholder="Time / From"><br>
					<input type="text" name="searchTIME2" size="40" placeholder="To">
					<input id="button" type="submit" value="Search"><br><br><br>
				</form>
			</div>


			<?php
			$serverName = "JIMMY-PC\SQLEXPRESS"; //serverName\instanceName
			$connectionInfo = array( "Database"=>"testingdb", "UID"=>"xujianningkp", "PWD"=>"123456", "ReturnDatesAsStrings"=>"true");

			$conn = sqlsrv_connect( $serverName, $connectionInfo);

			$RFID = '';
			$UPC = '';
			$LOC = '';
			$DATE1 = '';
			$DATE2 = '';
			$TIME1 = '';
			$TIME2 = '';

			$RFID = $_POST["searchRFID"];
			$UPC = $_POST["searchUPC"];
			$LOC = $_POST["searchLOC"];
			$DATE1 = $_POST["searchDATE1"];
			$DATE2 = $_POST["searchDATE2"];
			$TIME1 = $_POST["searchTIME1"];
			$TIME2 = $_POST["searchTIME2"];

			if ($RFID == 'delete'){
			$stmt = "DELETE FROM lab.tracking";
			$tsql = sqlsrv_query($conn,$stmt);
			if ($tsql)
			{
				echo "<h3><center><font face='verdana' color='#66FF33'>Table deleted!</font></center></h3>";
			}
			else
			{
				echo "<h3><center><font face='verdana' color='#FF0000'>Connection Fail!</font></center></h3>";
			}
			}
			else
			{





			$A = "RFID = '$RFID' ";
			$B = "UPC = '$UPC' ";
			$C = "location = '$LOC' ";
			$D = "thedate = '$DATE1' ";
			$E = "thedate = '$DATE2' ";
			$F = "thedate between '$DATE1' and '$DATE2' ";
			// $G = "thetime = '$TIME1' ";
			// $H = "thetime = '$TIME2' ";
			$I = "thetime between '$TIME1' and '$TIME2' ";


			$count = 0;
			$stmt1 = "select * from lab.tracking where ";

			//////////////////////////////////////////////
			// CHECK FOR CONNECTION
			$stmt = $stmt1;


			//////////////////////////////////////////////
			// BUILD SQL SERVER SEARCH QUERY DYNAMICALLY
			if (empty($RFID) and empty($UPC) and empty($LOC) and empty($DATE1) and empty($DATE2) and empty($TIME1)and empty($TIME2))
			{
			$temp1 = "select * from lab.tracking order by thedate,thetime ASC";

			//echo "<h2><center><font face='verdana'>No results found. Please try again.</font></center></h2>"
			$stmt2 = sqlsrv_query($conn, $temp1);
			}

			else
			{
			if (!empty($RFID))
			{
				if ($count == 1)
				{
				  $temp1 = "and " . $A;
				  $stmt .= $temp1;
				}
				else
			    {
				  $stmt .= $A;
				  $count = 1;
			    }
			}

			if ($UPC)
			{
				if ($count == 1)
				{
				  $temp2 = "and " . $B;
				  $stmt .= $temp2;
				}
				else
			    {
				  $stmt .= $B;
				  $count = 1;
			    }
			}

			if ($LOC)
			{
				if ($count == 1)
				{
				  $temp3 = "and " . $C;
				  $stmt .= $temp3;
				}
				else
			    {
				  $stmt .= $C;
				  $count = 1;
			    }
			}

			if ($DATE1 or $DATE2)
			{
				if ($DATE1 and $DATE2)
				{
					if ($count == 1)
					{
						$temp4 = "and " . $F;
						$stmt .= $temp4;
					}
					else
					{
					$stmt .= $F;
					$count = 1;
					}
				}
				elseif ($DATE1)
				{
					if ($count == 1)
					{
						$temp5 = "and " . $D;
						$stmt .= $temp5;
					}
					else
					{
					$stmt .= $D;
					$count = 1;
					}
				}
				else
				{
					if ($count == 1)
					{
						$temp6 = "and " . $E;
						$stmt .= $temp6;
					}
					else
					{
					$stmt .= $E;
					$count = 1;
					}
				}
			}

			if ($TIME1 and $TIME2)
			{
				if ($count == 1)
				{
					$temp7 = "and " . $I;
					$stmt .= $temp7;
				}
				else
				{
				$stmt .= $I;
				$count = 1;
				}
			}

			//$stmt .= " order by thedate,thetime"
				
			$stmt2 = sqlsrv_query($conn,$stmt);
			}


			echo " <table class='gridtable'><tr><th>Index</th><th>RFID</th><th>UPC</th><th>Location</th><th>Date</th><th>Time</th></tr>";

			$counter = 1;

			while($row = sqlsrv_fetch_array($stmt2))
			{
				echo "<tr><td>" . $counter . "</td><td>" . $row[RFID] . "</td><td>" . $row[UPC] . "</td><td>" . $row[location] . "</td><td>" . $row[thedate] . "</td><td>" . $row[thetime] . "</td></tr>";
				$counter = $counter+1;
			}

			sqlsrv_free_stmt($stmt);

			echo "</table>";

			} //else
			?>

			<br><br>
			<div id="footer">
				<p class="foottext">Copyright &copy; 2014 | All Rights Reserved</p>
			</div>
		</div>
	</body>
</html>
