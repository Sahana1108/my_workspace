<?php

# Include the Autoloader and PHPMailer libraries
require 'vendor/autoload.php';
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

# Anti-XSS measure.
function sanitiseInput($value) {
	return htmlspecialchars(strip_tags($value));
}

# Get the data from the user's input (POST request)
$code = sanitiseInput($_POST["code"]);

# comparing to cookie which stores the actual value
if ($code === $_COOKIE["VerificationCode"]) {
	echo "You have entered the code correctly. Login successful!";
} else {
	echo "You have entered the wrong code. Login failed!";
}

?>