<!DOCTYPE html>
<html>
<head>
   <meta charset="utf-8">
   <title></title>
</head>
<body>
	<?php
	session_start();
      
      //login.php에서 입력받은 id, password
      $id = $_POST['id'];
      $userpass = $_POST['pw'];
      
	  $id = preg_replace('/[^A-Za-z0-9% ]/', '', $id);
      $userpass = preg_replace('/[^A-Za-z0-9% ]/', '', $userpass);
	
      $cmd = "./login $id $userpass";
      //echo "<script>alert('$cmd')</script>";
      exec($cmd, $retArr, $retVal);
      
      //결과가 존재하면 세션 생성
      if ($retVal == 1) {
         $_SESSION['userID'] = $retArr[0];
         $_SESSION['name'] = $retArr[1];
         $_SESSION['id'] = $retArr[2];

         echo "<script>location.replace('index.php');</script>";
         exit;
      }
      //결과가 존재하지 않으면 로그인 실패
      else {
         echo "<script>alert('Invalid username or password')</script>";
         echo "<script>location.replace('login.php');</script>";
         exit;
      }
      ?>
   </body>