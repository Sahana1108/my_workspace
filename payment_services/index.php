<?php
//main page
// Include configuration file
//include_once "config.php";
// Include database file
include_once "data.php";
?>

<!doctype html>
<html>
<head>
	<style>
		.grid-container {
			display: grid;
			grid-template-columns: auto auto auto;
			padding: 10px;
		}
		
		.grid-item {
			border: 1px solid rgba(0, 0, 0, 0.8);
			padding: 20px;
			text-align: center;
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
	<meta charset="utf-8">
	<title>Question 1 - Secure Payment Method Integration</title>
</head>

<body>
	<div class="grid-container">
		<?php foreach ($item as $i) { ?>
		<div class="grid-item"?>
			<form action="confirm.php" method="post">
				<p>
					<img src=<?php echo $i["image"] ?> alt="" width="150" height="150"/>
				</p>
				<p>
					<?php echo $i["name"] ?>
				<h3>$<?php echo $i["price"] ?></h3>
				</p>
			
			<input type="hidden" name="item_image" value="<?php echo $i["image"]; ?>" />
			<input type="hidden" name="item_name" value="<?php echo $i["name"]; ?>" />
			<input type="hidden" name="item_number" value="<?php echo $i["id"]; ?>" />
			<input type="hidden" name="amount" value="<?php echo $i["price"]; ?>" />
			
			<button type="submit" name="button<?php echo $i["id"] ?>">BUY</button>
			</form>
		</div>
		<?php } ?>
	</div>
</body>
</html>