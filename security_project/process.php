<?php

if($_SERVER["REQUEST_METHOD"] === "POST")
{

    $recaptcha_secret = "6LfhbWgnAAAAAF7P5-gJ-WfqXx6iAUbSmH8xND1-";
    $response = file_get_contents("https://www.google.com/recaptcha/api/siteverify?secret=".$recaptcha_secret."&response=".$_POST['g-recaptcha-response']);
    $response = json_decode($response, true);

    if($response["success"] === true){
		echo "Form Submit Successfully.";
    }else{
		echo "You are a robot";
    }
	
}
?>