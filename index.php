<!--Before log in, go to login.php. After log in, show name, user ID, account number, balance-->

<?php
session_start();
if(!isset($_SESSION['userID'])) {//before log in, go to login.php
    echo "<script>location.replace('login.php');</script>";            
	
}

else {//after log in
	$name = $_SESSION['name'];
} 
?>


<body>
	<form method="post" action="money_transfer.php" class="moneytransfer">
    <div class="base">
        <!--show name, user ID, account number, balance-->
		<h2><?php echo "Hi, $name";?></h2><br>
			<h3>
				<?php // If Log in successed, show user's account number and balance
					$userID = preg_replace('/[^A-Za-z0-9% ]/', '', $userID);
				
					$userID = $_SESSION["userID"];

					$cmd = "./checkBalance $userID";
					// $q = "SELECT * FROM ACCOUNT WHERE userID=";
					// $result = $mysqli->query($q);
					// $row = mysqli_fetch_array($result);

					exec($cmd, $retArr, $retVal);
					$_SESSION['accountNumber'] = $retArr[1];
					$_SESSION['balance'] = (int)$retArr[2];

					$accountNumber = $_SESSION['accountNumber'];
					$balance = $_SESSION['balance'];

					echo 'Account number : '.$accountNumber.'<br>';
					echo 'Balance :'.$balance;
					
					//save sender's account number and balance and use when sending money
					// $sender_account=$row['account_number'];
					// $sender_balance=$row['balance'];
				?>
				
			</h3>
		<!---->
		<h3>Receiver's account num</h3>
		
		<!--hidden data : sender's account and balance. use when sending money-->
		
		<h3>How much to Send?</h3>
		<!--input receiver's account and money-->
		<div class="account_num_Form">
		  <input type="text" name="receiver_account" class="receiver_account" placeholder="Account number">
		</div>
		
		<div class="MoneyFrom">
		  <input type="number" name="money" class="money" placeholder="Money">
		</div>
		<button type="submit" class="btn" onclick="button()">
		  Send
		</button>
		<br>
		
        <button type="button" class="btn" onclick="location.href='logout.php'">
         LOGOUT
        </button>
    </div>
	</form>
</body>