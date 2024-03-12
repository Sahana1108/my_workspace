<!DOCTYPE html>
<html>
<head>
    <title>Two-Factor Authentication</title>
    <style>        
input[type=text] {
        border: 2px solid blue;
        border-radius: 3px;
             }
</style>
</head>
<body>
    <h1 style="color:blue;" > Two factor Authentication</h1>
    <h3 style="color:blue;" > Verify your identity </h3>
    
     <hr width="70%" color="blue" align ="left"/>
     <h4> Open the Goolge Authentication app on your device to view you authentication code and enter
     it here to verify your identity. </h4>
    <form action="verify_otp.php" method="POST">
        <label for="otp">Two Factor Code:</label>
        <br>
        <br>
        <input type="text" id="otp" name="otp" required><br>
        <br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
