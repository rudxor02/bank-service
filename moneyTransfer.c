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

}

int exploit(){
	printf("[Team 9] Dummy Function for PoC\n");
}