// SERVER

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <mysql/mysql.h>

#define maxClientNo 4



MYSQL *connection;
MYSQL_RES *result;
MYSQL_ROW *row;
const int True = 1;

static char *host = "localhost";
static char *user = "root";
static char *pass = "1234";
static char *dbname = "wow";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;



// Initialized database
void DBInit(){
	//create database if non-existent
	connection = mysql_init(NULL);

	if(!(mysql_real_connect(connection, host, user, pass, dbname, port, unix_socket, flag))){
		mysql_real_connect(connection, host, user, pass, NULL, port, unix_socket, flag);
		mysql_query(connection, "CREATE DATABASE wow;");	
	}

	//create users and sessions tables if non-existent

	mysql_query(connection, "show tables;");

	result = mysql_store_result(connection);

	int tableFlag = 0;
	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if(strcmp((char *)row[0], "users") == 0){
			tableFlag = 1;
			break;
		}
	}
	
	if(tableFlag == 0){
		mysql_query(connection, "CREATE TABLE users(username varchar(9) NOT NULL PRIMARY KEY, password varchar(9) NOT NULL);");
	}

	tableFlag = 0;
	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if(strcmp((char *)row[0], "sessions") == 0){
			tableFlag = 1;
			break;
		}
	}
	
	if(tableFlag == 0){
		mysql_query(connection, "CREATE TABLE sessions(username_1 varchar(9) NOT NULL, username_2 varchar(9) NOT NULL, username_3 varchar(9) NOT NULL, username_4 varchar(9) NOT NULL, level int NOT NULL, session_id int NOT NULL, primary key (username_1, username_2, username_3, username_4));");
	}
}


// Loads board into the database
void putBoard(int * board1,int * board2,int * board3,int * board4, char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT session_id FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		activeSession = atoi((char *)row[0]);
	}

	int i,j;

	for(i = 0; i < 4; i++){

		memset(tableName, '\0', sizeof(tableName));

		sprintf(tableName, "%s_%d", players[i], activeSession);

		memset(query, '\0', sizeof(query));

		mysql_query(connection, "show tables;");

		result = mysql_store_result(connection);

		int tableFlag = 0;
		while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
			if(strcmp((char *)row[0], tableName) == 0){
				tableFlag = 1;
				break;
			}
		}
		
		if(tableFlag == 0){
			sprintf(query, "CREATE TABLE %s(index int PRIMARY KEY, piece int, move int)", tableName);
			mysql_query(connection, query);
		}
		for( j =0;j<100;j++){
			memset(query,'\0',sizeof(query));
			sprintf(query,"INSERT INTO %s(index,piece,move) VALUES('%d', '%d', '%d');",tableName,i,board[i],0);
			mysql_query(cinnection,query);
		}
	}

}

void getBoard(int * board){

}

// Authenticates user account
int authenticate(char* uname, char* pass){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT * FROM users WHERE username = '%s';", uname);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if(!strcmp(pass, (char *)row[1])){
			return 1;
		}
	}
	return 0;
}



int signup(char* uname, char* pass){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT * FROM users WHERE username = '%s';", uname);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if(!strcmp(uname, (char *)row[0])){
			return 0;
		}
	}

	memset(query, '\0', sizeof(query));
	sprintf(query, "INSERT INTO users(username, password) VALUES('%s', '%s');", uname, pass);
	mysql_query(connection, query);

	return 1;
}



// Sorts the list of usernames in place
void userSort(char ** username, int * clientSocket){
	int i,j;
	int temp2;
	char * min;
	int minpos;
	for(i = 0; i < maxClientNo; i++){
		min = username[i];
		minpos = i;
		for( j = i; j < maxClientNo; j++){
			if(strcmp(min,username[j])>0){
				min = username[j];
				minpos = j;
			}
		}
		temp2 = clientSocket[minpos];
		min = username[minpos];
		clientSocket[minpos] = clientSocket[i];
		username[minpos] = username[i];
		username[i] = min;
		clientSocket[i] = temp2;
	}
}



int checkSave(char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT session_id FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		 return atoi((char *)row[0]);
	}
	return 0;
}

int newSession(char ** username){
	int sessions = 1;

	mysql_query(connection, "SELECT session_id from sessions;");

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		sessions = atoi((char *)row[0]) + 1;
	}
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "INSERT INTO sessions(username_1, username_2, username_3, username_4, level, session_id) VALUES('%s', '%s', '%s', '%s', '%d', '%d');", username[0], username[1], username[2], username[3], 1, sessions);
	mysql_query(connection, query);

}

int main(int argc, char* argv[]){
	int serverSocket = 0;
	int i,j;
	int clientSocket[maxClientNo] = {0};
	int clientNo = 0;
	int BufSize = 40;
	socklen_t addr_size[maxClientNo];
	char ** username = (char**)malloc(sizeof(char*)*maxClientNo);
	char * password = (char *)malloc(sizeof(char)*20);
	for( i = 0; i < maxClientNo; i++){
		username[i] = (char *)malloc(sizeof(char)*20);
	}

	int board[100] = {0};
	int * board2D[10];
	for(j = 0; j<10; j++){
		board2D[j] = &board[j*10];
	}

	// Position, Vehicle and Player
	char * recvBuf = (char *)malloc(sizeof(char)*BufSize);

	// H/M/I, Player1, Player2, nextPlayers
	char * sendBuf = (char *)malloc(sizeof(char)*BufSize);

	struct sockaddr_in serverAddr;
    struct sockaddr_storage clientAddr[maxClientNo];
    fd_set game;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    /* Set port number */
    serverAddr.sin_port = htons(9000);
    //Localhost
    serverAddr.sin_addr.s_addr = inet_addr ( "127.0.0.1" );

    //Initialize to zero
    memset(serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero) );
    memset(recvBuf, '\0', BufSize);
    memset(sendBuf, '\0', BufSize);

    // Binds the server
    bind ( serverSocket, ( struct sockaddr *) &serverAddr, sizeof ( serverAddr ) );

    DBInit();
    listen ( serverSocket, maxClientNo);

    // First Connect
    while(clientNo == 0){
		clientSocket[0] = accept ( serverSocket, (struct sockaddr *) &clientAddr[0], &addr_size[0]);
		setsockopt(clientSocket[0],SOL_SOCKET,SO_REUSEADDR,&True,sizeof(int));
		recv( clientSocket[0], username[0], 20, 0);
		if(strcmp(username[0], "_SignUp")==0){
			recv( clientSocket[0], username[i], 20, 0);
			recv( clientSocket[0], password, 20, 0);
			if(signup(username[0],password)==0){
				strcpy(sendBuf,"_UsernameInUse");
				send(clientSocket[0], sendBuf, BufSize, 0);
    			close(clientSocket[0]);
    			i--;
    		}
    		else{
				clientNo++;	
				continue;
			}
		}
		recv( clientSocket[0], password, 20, 0);
		if(authenticate(username[i], password) == 0){
			strcpy(sendBuf,"_AuthenticationFailed");
			send(clientSocket[0], sendBuf, BufSize, 0);
			close(clientSocket[i]);
			i--;
		}
		else{
			strcpy(sendBuf,"_Authenticated");
			send(clientSocket[0], sendBuf, BufSize, 0);
			clientNo++;
		}

	}

	int NewGame = 0;
	recv( clientSocket[0], recvBuf, 20, 0);
	if(strcmp( recvBuf, "_New")==0){
		NewGame = 1;
	}



    for(i = 1; i < maxClientNo; i++){
    	clientSocket[i] = accept ( serverSocket, (struct sockaddr *) &clientAddr[i], &addr_size[i]);
    	setsockopt(clientSocket[i],SOL_SOCKET,SO_REUSEADDR,&True,sizeof(int));
    	recv( clientSocket[i], username[i], 20, 0);
    	if(strcmp(username[i], "_SignUp")==0){
    		recv( clientSocket[i], username[i], 20, 0);
    		recv( clientSocket[i], password, 20, 0);
    		if(signup(username[i],password)==0){
    			strcpy(sendBuf,"_UsernameInUse");
				send(clientSocket[0], sendBuf, BufSize, 0);
    			close(clientSocket[0]);
    			i--;
    			continue;
    		}
    		else{
	    		clientNo++;	
	    		continue;
    		}
    	}
    	recv( clientSocket[i], password, 20, 0);
    	if(authenticate(username[i], password) == 0){
    		strcpy(sendBuf,"_AuthenticationFailed");
    		send(clientSocket[i], sendBuf, BufSize, 0);
    		close(clientSocket[i]);
    		i--;
    	}
    	else{
    		strcpy(sendBuf,"_Authenticated");
    		send(clientSocket[i], sendBuf, BufSize, 0);
    		clientNo++;
    	}
    }
	
	userSort(username,clientSocket);
	sprintf(sendBuf, "%s %s %s %s", username[0], username[1],username[2],username[3]);
	send(clientSocket[i], sendBuf, BufSize, 0);

    // Check for saved game here else start new session
    int sessionID;
    if(((sessionID = checkSave(username))!=0)&&(NewGame!=1)){
    	int lvl = 0;
    	int team = 0;
    	int turn = 0;
    	// Send message to all that saved game to be loaded
		for(board = 1 to 4)	{
			for(i = 0; i < maxClientNo; i++){
				getBoard(board);
				sprintf(sendBuf, "%s %s", lvl, turn);
    			send(clientSocket[i], sendBuf, BufSize, 0);
    			// This board has only the hit or miss data that needs to be displayed
				send(clientSocket[i],board,100,0);
			}
		}
    }
	else{
		newSession(username);
		strcpy(sendBuf,"_New");
		for(i = 0; i < maxClientNo; i++){
    		send(clientSocket[i], sendBuf, BufSize, 0);
    	}
    	int board1[100] = {0};
    	int board2[100] = {0};
    	int board3[100] = {0};
    	int board4[100] = {0};
    	// This board will contain the piece placement data and Hit or Miss board loaded to null on client side
    	recv(clientSocket[0], board1, BufSize, 0);
    	recv(clientSocket[1], board2, BufSize, 0);
    	recv(clientSocket[2], board3, BufSize, 0);
    	recv(clientSocket[3], board4, BufSize, 0);
    	putBoard(board1,board2,board3,board4,username);

	}



}