<?php
require_once 'PHPGangsta/GoogleAuthenticator.php'; 

// Key must be placed here and in userprofile.php every time it is generated.
$secret = 'RCLITNDBFMTMVUSM';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $otp = $_POST['otp'];

    $ga = new PHPGangsta_GoogleAuthenticator();
    $result = $ga->verifyCode($secret, $otp, 2); 
    if ($result) {
        // Successful login.
        echo "Login successful!";
    } else {
        // Incorrect OTP.
        echo "Login failure: Invalid OTP.";
    }
}
?>
