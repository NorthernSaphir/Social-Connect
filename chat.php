<?php
$message = $_GET['message'];
$hwid = $_GET['hwid'];
$reset = $_GET['reset'];
$town = $_GET['town'];
$act = $_GET['act'];

$link = mysql_connect('localhost', 'sc_test', 'ouP1k27!');

if (!$link){
	echo 'linkerror';
	exit(-1);
}
        

$db_selected = mysql_select_db('sc', $link);
if (!$db_selected) {
	echo 'db error';
        exit(-1);
}

$res = mysql_query("select * from User where HWID='".$hwid . "'");

$row = mysql_fetch_assoc($res);
if (!$row){
	mysql_query("INSERT INTO User (hwid) VALUES ('".$hwid."')");
}

if ($reset == 1){
	mysql_query("UPDATE User SET town='".$town."' WHERE HWID = '". $hwid ."'");
	mysql_query("UPDATE User SET act='".$act."' WHERE HWID = '". $hwid ."'");
	
	mysql_query("UPDATE User SET conHWID=NULL WHERE conHWID = '". $hwid ."'");
	mysql_query("UPDATE User SET conHWID=NULL WHERE HWID = '". $hwid ."'");
	$res = mysql_query("select * from User WHERE conHWID IS NULL AND HWID != '" . $hwid . "' AND town='".$town."' AND act='".$act."'");
	$count = mysql_num_rows($res);
	$count = rand(1, $count);
	while ($row = mysql_fetch_array($res)){
	
	$c1 += 1;
	
	if ($c1 == $count){
		mysql_query("UPDATE User SET conHWID='" . $row['HWID'] . "' WHERE HWID = '". $hwid ."'");
		mysql_query("UPDATE User SET conHWID='" . $hwid . "' WHERE HWID = '". $row['HWID'] ."'");
	}
		
	}
}
else{
	$res = mysql_query("select * from User where HWID='".$hwid . "'");
	$row = mysql_fetch_assoc($res);
	if (!empty($message)){
		if ($row['Lastmessage'] == NULL)
			mysql_query("UPDATE User SET Lastmessage=CONCAT('".$row['Lastmessage']."','".$message."') WHERE HWID=".$hwid."");
		else
			mysql_query("UPDATE User SET Lastmessage=CONCAT('".$row['Lastmessage']."','<br>".$message."') WHERE HWID=".$hwid."");
	}
	$res = mysql_query("select * from User where HWID='". $row['conHWID'] . "'");
	$row = mysql_fetch_assoc($res);
	if ($row['Lastmessage'] != NULL){
		echo $row['Lastmessage'];
		mysql_query("UPDATE User SET Lastmessage=NULL WHERE HWID='".$row['HWID']."'");
	}
}

?>
