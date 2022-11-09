#include <stdio.h>
#include <string.h>
#include <mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "BANKSERVICE"
#define DB_PORT 3306
#define TABLE_USER "user"
#define TABLE_ACCOUNT "account"

void exitErrorMysql(MYSQL* mysql);
int exploit();

int main(int argc, char ** argv) {

	char* userID;
	char* senderAccount;
	char* receiverAccount;
	char money[16];

	char lockCmd[100];
	char cmd[500];

	// parameter check
	if (argc != 5) {
		printf("Enter userID, senderAccount, receiverAccount, money\n");
		exit(0);
	}

	userID = argv[1];
	senderAccount = argv[2];
	receiverAccount = argv[3];
	strcpy(money,argv[4]);

    //mysql connection check
	MYSQL mysql;
	mysql_init(&mysql);
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		printf("connection failed\n");
		printf("%s\n", mysql_error(&mysql));
		exit(0);
	}


}

void exitErrorMysql(MYSQL* mysql) {
	printf("MoneyTransfer Failed\n");
	//rollback
	mysql_query(mysql, "ROLLBACK;");
	
	mysql_close(mysql);
	return;
}


int exploit(){
	printf("[Team 9] Dummy Function for PoC\n");
}