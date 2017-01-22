<?php

	if( trim( SENDEMAIL001_TO ) != "" )
	{
		$mail_body = "SERverMONitor Notification Email\r\n";
		$mail_body .= date('l jS \of F Y h:i:s A') . "\r\n\r\n";
		$mail_body .= "-[\r\n" . "Plugin Name: [" . $source_alert . "]\r\nError Message: " .  $alert_msg . "\r\n]-\r\n";
		
		$alert_out = "Sending email to: " . SENDEMAIL001_TO . "\r\n";
		$alert_out .= "Email Subject: " . SENDEMAIL001_SUBJECT . "\r\n";
		$alert_out .= "Email Message: \r\n{\r\n" . $mail_body  . "\r\n}\r\n\r\n";

		if (mail(SENDEMAIL001_TO, SENDEMAIL001_SUBJECT, $mail_body))
		{
			$alert_out .= "Message successfully sent!\r\n";
		}
		else
		{
			$alert_out .= "Message delivery failed...\r\n";
		}
	
	}
	
		
?>