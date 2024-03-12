<!doctype html>
<html>
<head>
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<style>
		.grid-container {
			display: grid;
			grid-template-columns: auto auto;
			padding: 10px;
		}
		
		.grid-item {
			border: 1px solid rgba(0, 0, 0, 0.8);
			padding: 20px;
			text-align: center;
			font-family: "Gill Sans", "Gill Sans MT", "Myriad Pro", "DejaVu Sans Condensed", Helvetica, Arial, "sans-serif"
		}
		
		h3 {
			font-family: "Gill Sans", "Gill Sans MT", "Myriad Pro", "DejaVu Sans Condensed", Helvetica, Arial, "sans-serif"
		}
		
		button {
			background-color: firebrick;
			border: none;
			color: white;
			font-size: 16px;
			font-weight: bold;
			padding: 8px 16px;
			text-align: center;
			display: inline-block;
			margin: 4px 2px;
			cursor: pointer;
		}
	</style>
	<title>Shopping cart</title>
</head>
	
	<body>
		<?php
		//Getting the details of the user's request. (From Tutorial 5)
		$raw_post_data = file_get_contents('php://input');
		$raw_post_array = explode('&', $raw_post_data);
		$myPost = array();
		foreach ($raw_post_array as $keyval) {
			$keyval = explode('=', $keyval);
			if (count($keyval) == 2)
				$myPost[$keyval[0]] = urldecode($keyval[1]);
		}
		?>
		<h3>Shopping cart</h3>
		<div class="grid-container">
			<div class="grid-item">
				<img src=<?php echo $myPost['item_image'] ?> alt="" width="250" height="250"/></div>
			<div class="grid-item">

			<form action="billing.php" method="post">
			        <p><b><?php echo $myPost['item_name'] ?></b></p>
					<p>Price: $<?php echo $myPost['amount'] ?></p>
					<p>Quantity: 1</p>
					<input type="hidden" name="price" value="<?php echo $myPost['amount']; ?>" />
					<input type="hidden" name="item_name" value="<?php echo htmlspecialchars($myPost['item_name']); ?>">
					<input type="hidden" name="amount" value="<?php echo htmlspecialchars($myPost['amount']); ?>">
					<input type="hidden" name="quantity" value="1">
                    <button type="submit">CHECKOUT NOW >>></button>
            </form>
                   
				
			</div>
		</div>
	</body>
	
</html>