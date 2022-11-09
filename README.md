# bank-service


install mysql-server with empty password

```
sudo apt-get install nginx-full
sudo apt-get install php7.0
sudo apt-get install mysql-server
sudo apt-get install libmysqlclient-dev
```

# mysql configuration

connect to mysql with root user
```
sudo mysql -u root -p
```

Enable c programs to connect mysql

```
UPDATE mysql.user SET plugin = 'mysql_native_password' WHERE user = 'root' AND plugin = 'auth_socket';

flush privileges;
```

Enable transaction (remove autocommit)

```
set autocommit = 0;
```

Create DB
```
create database BANKSERVICE;
exit

```

# insert mysql data

```
mysql -u root -p BANKSERVICE < dump.sql
```

# check php7.0-fpm

if
```
sudo ls /run/php/php7.0-fpm.sock 
```
does not exist,

install php7.0-fpm

```
sudo apt-get install php7.0-fpm
```

# nginx configuration
```
sudo vi /etc/nginx/sites-available/default
```
change root path to directory
```
root /__path_to_this_project__
```
add index.php in file
```
index index.php index.html index.htm index.nginx-debian.html;
```  
enable php block, and block should look like this

```
location ~ \.php$ {
		include snippets/fastcgi-php.conf;
		fastcgi_pass unix:/run/php/php7.0-fpm.sock;
	}
```

# compile c programs
```
gcc -z execstack -fno-stack-protector -z norelro -g -O0 -w -o login login.c `mysql_config --cflags --libs`
gcc -z execstack -fno-stack-protector -z norelro -g -O0 -w -o moneyTransfer moneyTransfer.c `mysql_config --cflags --libs`
gcc -z execstack -fno-stack-protector -z norelro -g -O0 -w -o checkBalance checkBalance.c `mysql_config --cflags --libs`
```

# start nginx
```
sudo service nginx start
```
or
```
sudo service nginx restart
```  

# connect to bank service

turn on your web browser and connect to <http://localhost>