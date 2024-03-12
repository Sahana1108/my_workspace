<?php
    require_once 'PHPGangsta/GoogleAuthenticator.php';

/*
 * Generate secret. Save this secret for filling the user dummy data later.
 */
    $ga = new PHPGangsta_GoogleAuthenticator();
    $secret = $ga->createSecret();
    echo "<div>Secret is: ".$secret."</div>";

/*
 * Generate QR code for you to scan from the google authenticator app
 */
    $qrCodeUrl = $ga->getQRCodeGoogleUrl('Blog', $secret);
    echo '<img src="'.$qrCodeUrl.'" />';

/*
 * This one time code is just to check if the system is running properly
 */
    $oneCode = $ga->getCode($secret);
    echo "<div>Checking Code is: ".$oneCode."</div>";


/*
 * This is the code whenever you want to validate your user using their registered secret and one time password
 */
    $checkResult = $ga->verifyCode($secret, $oneCode, 2);    // 2 = 2*30sec clock tolerance

    if ($checkResult) {
        echo 'OK';
    } else {
        echo 'FAILED';
    }
?>