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
	char cmd[300];

	// parameter check
	if (argc != 2) {
		printf("Enter userID\n");
		exit(0);
	}

    userID = argv[1];

}

int exploit(){
	printf("[Team 9] Dummy Function for PoC\n");
}