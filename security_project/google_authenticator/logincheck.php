<?php

/*
 * include files needed
 */
require_once 'PHPGangsta/GoogleAuthenticator.php';
require_once 'userprofile.php';

/*
 * Get the data posted from index.php
 */
$email = $_POST["email"];
$password = $_POST["password"];



/*
 * Define authenticator object
 */
$ga = new PHPGangsta_GoogleAuthenticator();


/*
 * Check if username and password and secret are correct based on the userprofile.php
 */
if($email === $dummy_user['email'] && $password === $dummy_user['password']){

	  header("Location:otp.php");
}else{
	echo "Enter the correct Email and Password";
}


?>