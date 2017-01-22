<?php

function SendAlerts($pName, $pError)
{
	$alert_folder = BASE_DIR . 'alerts' . DIRECTORY_SEPARATOR;

	$in_alert_out = "";
	if ( $handle = opendir ( $alert_folder ) ) 
	{
		while ( false !== ( $file = readdir ( $handle ) ) ) 
		{
			if ( strtolower(substr($file, strlen($file)-4,4)) == ".php" )
			{
				$alert_msg = $pError;
				$source_alert = $pName;
				$alert_out = "";				
				include( $alert_folder . $file );
				$in_alert_out .= $alert_out;
			}
		}
		closedir($handle);
	}
	
	return $in_alert_out;
}

function writeLastLog($w, $m)
{
	// Log last status
	$fh = fopen( LASTLOG_FULL_PATH, $m);
	if( $fh != FALSE )
	{
		fwrite($fh, $w . "\r\n");
		fclose($fh);
	}
	else
	{
		echo "Unable to write LASTLOG: " . LASTLOG_FULL_PATH . "<br />";
	}

}

function drawNavBar()
{
	$alert_folder = BASE_DIR . 'plugin' . DIRECTORY_SEPARATOR;

	$strJSHideAll = "";

	if ( $handle = opendir ( $alert_folder ) ) 
	{
	
		$strJSHideAll = "<script type=\"text/javascript\">
function showHideAll(dispStyle)
{
";

		echo "<span class='navBarEl' onclick=\"showHideAll('');\"> All </span>";

		while ( false !== ( $file = readdir ( $handle ) ) ) 
		{
			if ( strtolower(substr($file, strlen($file)-4,4)) == ".php" )
			{
				echo "<span onclick=\"showHideAll('none');showDiv('div_" . md5( $file ) . "');\" class='navBarEl'> " . $file . " </span>";
				$strJSHideAll .= "document.getElementById(\"div_" . md5( $file ) . "\").style.display = dispStyle;";
			}
		}
		closedir($handle);
		
		$strJSHideAll .= "}
</script>";
	echo $strJSHideAll;
	}
}

?>