<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="utf-8">
  <title>Money Transfer</title>
</head>
<body>
	<?php      
      //DB CONNECT
	  session_start();
	
      $receiverAccount =$_POST['receiver_account'];
      $money = (int)$_POST['money'];
	  $senderAccount= $_SESSION['accountNumber'];
	  $senderBalance= $_SESSION['balance'];
	  $userID = $_SESSION["userID"];

	  if($senderBalance<$money){
		echo "<script>alert('Lack of money')</script>";
        echo "<script>location.replace('index.php');</script>";
        exit;
	  }
	
    //   $q = "SELECT * FROM ACCOUNT WHERE account_number ='$receiver' ";
    //   $result = $mysqli->query($q);
    //   $row = $result->fetch_array(MYSQLI_ASSOC);
    //   $receiver_balance=(int) $row['balance'];
		$cmd = "./moneyTransfer $userID $senderAccount $receiverAccount $money";
		//echo "<script>alert('$cmd')</script>";
	  	exec($cmd, $retArr, $retVal);

		// $newsendermoney=$sender_balance-$money;
		// $newreceivermoney=$receiver_balance+$money;
	/*
	print_r($receiver); print_r(gettype($receiver));
	print_r($money);print_r(gettype($money));
	print_r($sender);print_r(gettype($sender));
	print_r($sender_balance);print_r(gettype($sender_balance));
	print_r($receiver_balance);print_r(gettype($receiver_balance));
	
	print_r($newsendermoney);print_r(gettype($newsendermoney));
	print_r($newreceivermoney);print_r(gettype($newreceivermoney));
	
	*/
	
      if ($retVal == 1) {
         
		  
		//  $minus_q="UPDATE ACCOUNT SET balance='$newsendermoney' WHERE account_number='$sender'";
		//  $plus_q="UPDATE ACCOUNT SET balance='$newreceivermoney' WHERE account_number='$receiver'";
		 
		//  $minusresult=$mysqli->query($minus_q); 
		//  $plusresult=$mysqli->query($plus_q);
		  
		 echo "<script>alert('Money sending finish')</script>";
         echo "<script>location.replace('index.php');</script>";
         exit;
      }
      //결과가 존재하지 않으면 로그인 실패
      else if($retVal == 0){
        echo "<script>alert('Invalid transfer')</script>";
        echo "<script>location.replace('index.php');</script>";
        exit;
      }
	else{
		echo "<script>alert('ERROR')</script>";
		echo "<script>location.replace('index.php');</script>";
        exit;
	}
	
      ?>
	 
   </body>
</html>