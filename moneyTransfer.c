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

    //start transaction
	mysql_query(&mysql, "START TRANSACTION;");

	//query construction
	snprintf(cmd, 490, 
		"(select * from %s where userID = \'%s\' and acc_num = \'%s\') union (select * from %s where acc_num = \'%s\');", TABLE_ACCOUNT, userID, senderAccount, TABLE_ACCOUNT, receiverAccount);

	//query, fetch
	mysql_query(&mysql, cmd);
	MYSQL_RES *sql_result = mysql_store_result(&mysql);

	// db scheme : acc_num	userID	balance

	if (sql_result == NULL || mysql_affected_rows(&mysql) != 2) {
		// params not matched
		exitErrorMysql(&mysql);
		exit(0);
	}	
    else if (atoi((mysql_fetch_row(sql_result))[2]) < atoi(money)) {
		//balance < money : lack of money
		printf("Lack of Money : Failed\n");
		exitErrorMysql(&mysql);
		exit(0);
	}
	else {
		//cmds for sender update, receiver update
		char senderUpdateCmd[300];
		char receiverUpdateCmd[300];

		snprintf(senderUpdateCmd, 290,
			"update %s set balance = balance - %s where acc_num = \'%s\'", TABLE_ACCOUNT, money, senderAccount);

		mysql_query(&mysql, senderUpdateCmd);

		if (mysql_affected_rows(&mysql) != 1) {
			printf("SenderUpdate : Failed\n");
			exitErrorMysql(&mysql);
			exit(0);
		}

    }

    //commit
	mysql_query(&mysql, "COMMIT;");

	mysql_close(&mysql);
	return 1;


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