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

	char specialChar[] = ",.?!@#$%^&*(){}[];'\"";
    char* ptr;
    for(int i = 1; i < argc; i++){
        ptr = strpbrk(argv[i], specialChar);
        if(ptr) {
            printf("Special Character Detected\n");
            exit(0);
        }
    }

    userID = argv[1];
	printf(userID);
	printf("\n");

	//mysql connection check
	MYSQL mysql;
	mysql_init(&mysql);
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0) == NULL)
	{
		printf("connection failed\n");
		printf("%s\n", mysql_error(&mysql));
		exit(0);
	}
	//query construction
	snprintf(cmd, 290, "select * from %s where userID = %s;", TABLE_ACCOUNT, userID);

	//query, fetch
	mysql_query(&mysql, cmd);
	MYSQL_RES *sql_result = mysql_store_result(&mysql);
	if (sql_result == NULL || mysql_affected_rows(&mysql) == 0) {
		printf("CheckBalance Failed\n");
		mysql_close(&mysql);
		exit(0);
	}

	MYSQL_ROW sql_row;

	sql_row = mysql_fetch_row(sql_result);
	// db scheme : acc_num	userID	balance
	printf("%s\n%s\n", sql_row[0], sql_row[2]);
	printf("CheckBalance Success\n");
	mysql_close(&mysql);
	return 1;

}

int exploit(){
	printf("[Team 9] Dummy Function for PoC\n");
}