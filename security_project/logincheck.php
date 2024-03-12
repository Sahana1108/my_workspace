<?php

# Include the Autoloader and PHPMailer libraries
require 'vendor/autoload.php';
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;

# Get the data from the index (POST request)
$email = $_POST["email"];
$password = $_POST["password"];

# Generate random 6-digit number and pass it in a cookie
$verCode = mt_rand(100000, 999999);
setcookie("VerificationCode", $verCode, time() + 300); # 300 = expires in 5 minutes

# Create mail object and set it
$mail = new PHPMailer(true);

try {
	$mail->SMTPDebug = 0;
	$mail->isSMTP();
	$mail->Host = 'smtp.gmail.com';
	$mail->SMTPAuth = TRUE;
	$mail->Username = 'angelojessica972@gmail.com';
	$mail->Password = 'hvewdmdamskosokx'; # app password
	$mail->SMTPSecure = 'tls';
	$mail->Port = 587;
	
	# sender and recipient (based on user specification)
	$mail->setFrom('angelojessica972@gmail.com', 'Test');
	$mail->addAddress($email);
	
	# set message
	$mail->isHTML(true);
	$mail->Subject = 'Verification code';
	$mail->Body = 'Your verification code is: '.$verCode;
	$mail->send();
	
	# configure input form
	?>
	
	<h3>We have sent a secret code to your email.</h3>
	<h3>Please check your email and insert the code in the following input field:</h3>
	<form method="post" action="loginfinal.php">
	  <input type="text" name="code" required/>
	  <button type="submit" name="btnVerify">Verify code</button>
	</form>
	
<?php

} catch (Exception $e) { # error handling
	echo "Message could not be sent. Error: {$mail->ErrorInfo}";
}

?>