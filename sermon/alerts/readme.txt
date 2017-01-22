
 - SERMON will use (execute) all the files ending with ".php" in this folder
   (Please move un-wanted alerts in the "disabled" folder)

 - You can't declare functions() in your custom alert!
   Alerts (PHP files in the "alerts" folder) are included many times by the main 
   script and declaring a function in an alert will result in a PHP error

 - Use the constant BASE_DIR to get the root folder of SERMON
 
 - Use the variable "$alert_out" to print something.
 

