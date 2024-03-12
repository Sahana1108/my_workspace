<?php
//main page
// Include configuration file
include_once "config.php";
// configurations for razor pay
require 'r_config.php';
require 'razorpay/Razorpay.php';
// Include database file
include_once "data.php";
// include confirm.php
session_start();


use Razorpay\Api\Api;

?>
<!doctype html>
<html>
<head>
<meta charset="utf-8">
	<style>
		* {
			box-sizing: border-box;
		}

		body {
			padding: 1rem;
		}

		.contain {
			max-width: 1170px;
			margin-left: auto;
			margin-right: auto;
			padding: 1em;
			font-family: "Gill Sans", "Gill Sans MT", "Myriad Pro", "DejaVu Sans Condensed", Helvetica, Arial, "sans-serif"
		}
		
		@media (min-width: 600px) {
			.contain {
				padding: 0;
			}
		}

		h3 {
			margin: 0;
			margin-bottom: 1rem;
		}

		input, button {

		}

		.wrapper > * {
			padding: 1em;
		}

		@media (min-width: 700px) {
			.wrapper {
				display: grid;
				grid-template-columns: 2fr 1fr;
			}
  
			.wrapper > * {
				padding: 2em 2em;
			}
		}

		form {
			display: grid;
			grid-template-columns: 1fr 1fr;
			grid-gap: 20px;
		}
	
		form label {
			display: block;
		}
		
		form p {
			margin: 0;
		}

		.full-width {
			grid-column: 1 / 3;
		}

		button, input[type=text], input[type=email] {
			padding: 1em;
			width: 100%;
			border: 1px solid #000;
		}

		button {
			width: 100%;
			border: 0;
			background-color: firebrick;
			border: none;
			color: white;
			font-size: 16px;
			font-weight: bold;
			text-align: center;
			display: inline-block;
			cursor: pointer;
		}


				/* Customize the button color */
		.razorpay-payment-button {
			background-color: #f5a442 !important;
			width : 420px !important;
			height : 45px !important;
			border: solid 2px;

		}

		.razorpay-payment-button span {
		font-size: 24px;
		color: white;
		}

  

	</style>
	<title>Billing details</title>
</head>

<body>
	<?php 
	//Getting the details of the user's request.
	$raw_post_data = file_get_contents('php://input');
	$raw_post_array = explode('&', $raw_post_data); ?>
	
	<div class="contain">
		<div class="wrapper">
			<div>
				<h3>Billing details</h3>
				<form action="">
					<p>
						<label>First name</label>
						<input type="text">
					</p>
					<p>
						<label>Last name</label>
						<input type="text">
					</p>
					<p class="full-width">
						<label>Username</label>
						<input type="text">
					</p>
					<p class="full-width">
						<label>Email (optional)</label>
						<input type="text">
					</p>
					<p class="full-width">
						<label>Address</label>
						<input type="text">
					</p>
					<p>
						<label>Country</label>
						<input type="text">
					</p>
					<p>
						<label>State</label>
						<input type="text">
					</p>
					<?php
						if ($_SERVER['REQUEST_METHOD'] === 'POST') {
							$itemName = isset($_POST['item_name']) ? $_POST['item_name'] : '';
							$itemPrice = isset($_POST['amount']) ? $_POST['amount'] : '';
							$quantity = 1;
							$displayCurrency = "AUD";
							// Use these values for further processing or display
							// For example:
							echo " Purchase details <br>";
							echo "Item Name: $itemName<br>";
							echo "Item Price: $itemPrice<br>";
							echo "Item Quantity: $quantity";

						}
						?>
					
				</form>
			</div>
	  
			    <div>
				<h3>Select a payment option</h3>
				<div>
	
    <!--- PayPal integration-->
				         <form action="<?php echo PAYPAL_URL; ?>" method="post" style="padding: 0; margin: 0;">

                        <!-- Specify a Buy Now button. -->
	                    <input type="hidden" name="cmd" value="_xclick" />

                        <!-- Identify your business so that you can collect the payments. -->
	                    <input type="hidden" name="business" value="<?php echo PAYPAL_ID; ?>" />

						<!-- Item details -->
                        <input type="hidden" name="item_name" value="<?php echo $itemName; ?>" />
						<input type="hidden" name="amount" value="<?php echo $itemPrice; ?>" />
						<input type="hidden" name="quantity" value="<?php echo $quantity; ?>" />
	                    <input type="hidden" name="currency_code" value="<?php echo PAYPAL_CURRENCY; ?>" />

                                <!-- Specify URLs -->
	                    <input type="hidden" name="return" value="<?php echo PAYPAL_RETURN_URL; ?>">
	                    <input type="hidden" name="notify_url" value="<?php echo PAYPAL_NOTIFY_URL; ?>">                        
	                    <input type="image" name="submit" img src="paypal.jpg" height = "45px" width = "430px"/>
	                 </form>
				</div>
				<br>

	<!---- Google Pay integration--->
	<?php echo "Google Pay:" ; ?>
				<div id="container">
					
					<script src="googlepay.js"></script>
					<script async src="https://pay.google.com/gp/p/js/pay.js" onload="onGooglePayLoaded()"></script>
				</div>
			</div>
		</div>
	</div>
	
</body>
</html>