// Server

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
const char delim[2] = " ";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;
int activeSession;
int level = 0;
int turn = 0;

// Returns the activesession ID
int getSessionID(char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT session_id FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);
	int id;
	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		id = atoi((char *)row[0]);
	}
	return id;
}


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
		mysql_query(connection, "CREATE TABLE sessions(username_1 varchar(9) NOT NULL, username_2 varchar(9) NOT NULL, username_3 varchar(9) NOT NULL, username_4 varchar(9) NOT NULL, level int NOT NULL, session_id int NOT NULL, turn int NOT NULL primary key (username_1, username_2, username_3, username_4));");
	}
}

// Check if the move hit or missed
int checkHit(char * target, char * attacker, int pos){
	char query[512];
	char tableName[32];
	memset(tableName, '\0', sizeof(tableName));
	sprintf(tableName, "%s_%d", target, activeSession);

	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT * FROM %s WHERE index = %d;", tableName, pos);
	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if((atoi((char *)row[1]) != 0) && (atoi((char *)row[1]) == 0)) {
			memset(query, '\0', sizeof(query));
			sprintf(query, "UPDATE %s SET move = '%d' WHERE index = %d;", tableName, 1, pos);
			mysql_query(connection, query);

			memset(tableName, '\0', sizeof(tableName));
			sprintf(tableName, "%s_%d", "session", activeSession);

			memset(query, '\0', sizeof(query));
			sprintf(query, "SELECT * FROM %s WHERE username = %s;", tableName, attacker);
			mysql_query(connection, query);

			result = mysql_store_result(connection);

			while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
				memset(query, '\0', sizeof(query));
				sprintf(query, "UPDATE %s SET score = '%d' WHERE username = %s;", tableName, atoi((char *)row[2]) + 5, attacker);
				mysql_query(connection, query);
			}
			return 1;
		}
	}
	return 0;
}

// Loads board into the database
void putBoards(int ** board1, char ** username){
	char query[512];
	char tableName[32];

	int i,j;

	for(i = 0; i < maxClientNo; i++){

		memset(tableName, '\0', sizeof(tableName));

		sprintf(tableName, "%s_%d", username[i], activeSession);

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
			sprintf(query,"INSERT INTO %s(index,piece,move) VALUES('%d', '%d', '%d');",tableName,j,board1[i][j],0);
			mysql_query(connection,query);
		}
	}

}

//retrieve board
void getBoards(char ** username, int ** pieceBoards, int ** moveBoards){
	
	char query[512];
	char tableName[32];
	int i;
	
	for( i = 0 ;i < maxClientNo; i++){
		memset(tableName, '\0', sizeof(tableName));

		sprintf(tableName, "%s_%d", username[i], activeSession);

		memset(query, '\0', sizeof(query));
		sprintf(query, "SELECT * FROM %s;", tableName);
		mysql_query(connection, query);

		result = mysql_store_result(connection);

		while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
			pieceBoards[i][atoi((char *)row[0])] = atoi((char *)row[1]);
			moveBoards[i][atoi((char *)row[0])] = atoi((char *)row[2]);
		}
	}
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

// Checks if the game is over
int checkGameStatus(char ** username){
	//check if game is over
	int i;
	int arr[4] = {0};
	char tableName[32];
	char query[512];
	memset(tableName, '\0', sizeof(tableName));
	for( i = 0; i < maxClientNo; i++){
		sprintf(tableName, "%s_%d", username[i], activeSession);


		memset(query, '\0', sizeof(query));
		sprintf(query, "SELECT COUNT(move) FROM %s WHERE move = 1;", tableName);

		mysql_query(connection, query);

		result = mysql_store_result(connection);

		while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
			arr[i] = atoi((char *)row[0]);
		}
	}
	if(arr[0] + arr[1] == 32){
		return 1;
	}
	else if(arr[2] + arr[3] == 32){
		return 2;
	}
	else{
		return 0;
	}
}

// Removes saved game from database
void dropSaveGame(char ** username){
	char query[512];
	char tableName[32];	
	int i;
	for(i = 0; i < maxClientNo; i++){
		memset(tableName, '\0', sizeof(tableName));
		sprintf(tableName, "%s_%d", username[i], activeSession);

		memset(query, '\0', sizeof(query));
		sprintf(query, "DROP TABLE %s;", tableName);

		mysql_query(connection, query);
	}

	//remove entry from sessions table if game over

	memset(query, '\0', sizeof(query));
	sprintf(query, "DELETE FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);


}

// Add new username and password combination to database
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


int updateTurn(char ** username, int turn){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "UPDATE sessions SET turn = '%d' WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", turn, username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);
}

int updateLevel(char ** username, int level){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "UPDATE sessions SET level = '%d' WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", level, username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);
}

// Returns the ID of the player whose turn is next
int getTurn(char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT turn FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		 return atoi((char *)row[0]);
	}
	return 0;
}

// Gets the level of stored game
int getLevel(char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT level FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		 return atoi((char *)row[0]);
	}
	return 0;
}

// Checks if a saved game is present
int checkSave(char ** username){
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT session_id FROM sessions WHERE username_1 = '%s' AND username_2 = '%s' AND username_3 = '%s' AND username_4 = '%s';", username[0], username[1], username[2], username[3]);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		 return atoi((char *)row[0]);
	}
	return -1;
}

// Starts a new game
int newSession(char ** username){
	int sessions = 1;

	mysql_query(connection, "SELECT session_id from sessions;");

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		sessions = atoi((char *)row[0]) + 1;
	}
	char query[512];
	memset(query, '\0', sizeof(query));
	sprintf(query, "INSERT INTO sessions(username_1, username_2, username_3, username_4, level, session_id, turn) VALUES('%s', '%s', '%s', '%s', '%d', '%d', '%d');", username[0], username[1], username[2], username[3], 1, sessions, 0);
	mysql_query(connection, query);

}

// Scans the block and returns piece information
int scanBlock(char * target, int pos){
	char tableName[32];
	char query[512];
	memset(tableName, '\0', sizeof(tableName));

	sprintf(tableName, "%s_%d", target, activeSession);

	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT * FROM %s WHERE index = %d;", tableName, pos);
	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		if((atoi((char *)row[1]) != 0) && (atoi((char *)row[1]) == 0)){
			return atoi((char *)row[1]);
		}
	}
}

// Check for validity of the move
int checkValidity(char * attacker, int VType){
	char tableName[32];
	char query[512];
	memset(tableName, '\0', sizeof(tableName));

	sprintf(tableName, "%s_%d", attacker, activeSession);

	memset(query, '\0', sizeof(query));
	sprintf(query, "SELECT * FROM %s WHERE piece = %d AND move = 0;", tableName, VType);

	mysql_query(connection, query);

	result = mysql_store_result(connection);

	while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
		return 1;
	}
	return 0;
}


// Checks the score
void checkScore(char ** username, int * scores){
	char query[512];
	char tableName[32];	
	int i;
	for(i = 0; i < maxClientNo; i++){
		memset(tableName, '\0', sizeof(tableName));
		sprintf(tableName, "%s_%d", "session", activeSession);

		memset(query, '\0', sizeof(query));
		sprintf(query, "SELECT score FROM %s WHERE  username = '%s';", tableName, username[i]);

		mysql_query(connection, query);

		result = mysql_store_result(connection);

		while(row = (MYSQL_ROW *)mysql_fetch_row(result)){
			scores[i] = atoi((char *)row[0]);
		}
	}
}



int main(int argc, char* argv[]){
	int serverSocket = 0;
	int i,j;
	int clientSocket[maxClientNo] = {0};
	int clientNo = 0;
	int BufSize = 80;
	int turn = 0;
	socklen_t addr_size[maxClientNo];
	char query[512];
	char * target;
	char * attacker;
	char * tag;
	int pos,VType,attackRes;
	char ** username = (char**)malloc(sizeof(char*)*maxClientNo);
	char * password = (char *)malloc(sizeof(char)*20);
	for( i = 0; i < maxClientNo; i++){
		username[i] = (char *)malloc(sizeof(char)*20);
	}

	int board[100] = {0};
/*	int * board2D[10];
	for(j = 0; j<10; j++){
		board2D[j] = &board[j*10];
	}
*/
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

    //// Can add code to select the host address
    //Localhost
    serverAddr.sin_addr.s_addr = inet_addr ( "127.0.0.1" );

    //Initialize to zero
    memset(serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero) );
    memset(recvBuf, '\0', BufSize);
    memset(sendBuf, '\0', BufSize);

    // Binds the server to localhost
    bind ( serverSocket, ( struct sockaddr *) &serverAddr, sizeof ( serverAddr ) );

    // Initialize the database
    DBInit();
    listen ( serverSocket, maxClientNo);

    // First Connection and authentication
    while(clientNo == 0){
    	// Accepts first client
		clientSocket[0] = accept ( serverSocket, (struct sockaddr *) &clientAddr[0], &addr_size[0]);
		setsockopt(clientSocket[0],SOL_SOCKET,SO_REUSEADDR,&True,sizeof(int));
		// Receive login
		recv( clientSocket[0], username[0], 20, 0);

		// Check for Signup attempt
		if(strcmp(username[0], "_SignUp")==0){
			// Recieve signup data
			recv( clientSocket[0], username[0], 20, 0);
			recv( clientSocket[0], password, 20, 0);

			if(signup(username[0],password)==0){
				// Send already in use
				strcpy(sendBuf,"_UsernameInUse");
				send(clientSocket[0], sendBuf, BufSize, 0);
    			close(clientSocket[0]);
    			i--;
    		}
    		else{
    			// Send sign up confirmation
    			strcpy(sendBuf,"_SignedUp");
				send(clientSocket[0], sendBuf, BufSize, 0);
				clientNo++;	
				continue;
			}
		}

		// Not signup, receive password
		recv( clientSocket[0], password, 20, 0);

		// Check for valid login information
		if(authenticate(username[i], password) == 0){
			// Send login failed
			strcpy(sendBuf,"_AuthenticationFailed");
			send(clientSocket[0], sendBuf, BufSize, 0);
			close(clientSocket[i]);
			i--;
		}
		else{
			// Send logged in
			strcpy(sendBuf,"_Authenticated_Select");
			send(clientSocket[0], sendBuf, BufSize, 0);
			clientNo++;
		}

	}

	int NewGame = 0;

	// Receive value for continue or new game
	recv( clientSocket[0], recvBuf, 20, 0);
	if(strcmp( recvBuf, "_New")==0){
		NewGame = 1;
	}


	// Waiting for the other 3 connections and authentications
    for(i = 1; i < maxClientNo; i++){
    	clientSocket[i] = accept ( serverSocket, (struct sockaddr *) &clientAddr[i], &addr_size[i]);
    	setsockopt(clientSocket[i],SOL_SOCKET,SO_REUSEADDR,&True,sizeof(int));
    	recv( clientSocket[i], username[i], 20, 0);
    	// Checks for signup attempt
    	if(strcmp(username[i], "_SignUp")==0){
    		recv( clientSocket[i], username[i], 20, 0);
    		recv( clientSocket[i], password, 20, 0);
    		if(signup(username[i],password)==0){
    			// Send already in use
    			strcpy(sendBuf,"_UsernameInUse");
				send(clientSocket[i], sendBuf, BufSize, 0);
    			close(clientSocket[i]);
    			i--;
    			continue;
    		}
    		else{
    			strcpy(sendBuf,"_SignedUp");
				send(clientSocket[i], sendBuf, BufSize, 0);
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
	
	// Sorts the usernames to keep order constant
	userSort(username,clientSocket);

	sprintf(sendBuf, "%s-%s-%s-%s", username[0], username[1],username[2],username[3]);

	// Send game participant names
	for( i = 0 ;i < maxClientNo; i++){
		send(clientSocket[i], sendBuf, BufSize, 0);	
	}
	

////////////////////////////////////////////////////////////////////////

    // Check for saved game here else start new session
    if(((activeSession = checkSave(username))!=-1)&&(NewGame!=1)){
    	level = getLevel(username);
   		turn = getTurn(username);
    	// Send message to all that saved game to be loaded
    	int * pieceBoards[maxClientNo];
    	int * moveBoards[maxClientNo];
  		for( i = 0; i < maxClientNo; i++){
  			pieceBoards[i] = (int*) malloc ( sizeof(int)* 100);
  			moveBoards[i] = (int*) malloc ( sizeof(int)* 100);
  		}
		getBoards(username, pieceBoards, moveBoards);
		for(i = 0; i < maxClientNo; i++){
			
			// Send the level and turn data
			sprintf(sendBuf, "_Load-%d-%d", level, turn);
			send(clientSocket[i], sendBuf, BufSize, 0);

			// This board has only the piece information
			send(clientSocket[i],pieceBoards[i],100,0);

			for( j = 0; j < maxClientNo; j++){
				// Send the hit or miss data to all
				send(clientSocket[i],moveBoards[j],100,0);
			}
		}
    }
	else{

		// Sets the activeSession ID and initiates a new session.
		newSession(username);
		activeSession = getSessionID(username);

		// Send information for new session
		strcpy(sendBuf,"_New");
		for(i = 0; i < maxClientNo; i++){
    		send(clientSocket[i], sendBuf, BufSize, 0);
    	}

    	int * pieceBoards[maxClientNo];
  		for( i = 0; i < maxClientNo; i++){
  			pieceBoards[i] = (int*) malloc ( sizeof(int)* 100);
  		}
    	// This board will contain the piece placement data and Hit or Miss board loaded to null on client side
    	for( i = 0; i < maxClientNo; i++){
			// Send the hit or miss data to all
			send(clientSocket[i],pieceBoards[i],100,0);
		}
		putBoards(pieceBoards,username);

	}

	while(1){
		memset(query, '\0', sizeof(query));
		recv(clientSocket[turn%4],recvBuf,BufSize,0);
		tag = strtok(recvBuf,delim);
		if(strcmp(tag,"_Quit")){
			////
			// Save to database
			for( i = 0; i < maxClientNo; i++){
				strcpy(sendBuf,"_Quit");
				send(clientSocket[i],sendBuf,BufSize,0);
				close(clientSocket[i]);
			}
			updateTurn(username,turn);
			exit(0);
		}
		target = strtok(NULL,delim);
		attacker = strtok(NULL,delim);
		pos = atoi(strtok(NULL,delim));
		VType = atoi(strtok(NULL,delim));

		if(strcmp(tag,"_Scan")){
			sprintf(sendBuf, "%d",scanBlock(target, pos));
			send(clientSocket[turn%4],sendBuf,BufSize,0);
			continue;
		}
		else if(strcmp(tag,"_Hit")){
			if(checkValidity(attacker,VType)==1){
				attackRes = checkHit(target,attacker,pos);	
			}
			else{
				strcpy(sendBuf,"_Invalid");
				send(clientSocket[turn%4],sendBuf,BufSize,0);
				continue;
				// Turn has not been incremented, so still same turn.
			}
			if(attackRes == 1){
				sprintf(sendBuf, "_HIT-%d-%d-HIT %s attacked %s", pos, turn + 1, attacker, target);
			}
			else{
				sprintf(sendBuf, "_MISS-%d-%d-MISS %s attacked %s", pos, turn + 1, attacker, target);	
			}
		}
		else if(strcmp(tag,"_Mine")){
			attackRes=0;
			attackRes = attackRes + checkHit(target,attacker,pos);	
			attackRes = attackRes + checkHit(target,attacker,pos+1);	
			attackRes = attackRes + checkHit(target,attacker,pos+10);	
			attackRes = attackRes + checkHit(target,attacker,pos+11);	
			
			sprintf(sendBuf, "_MINE-%d-%d-%d-MINE %s attacked %s", attackRes, pos, turn + 1, attacker, target);
		}
		
		turn++;

		int Status = checkGameStatus(username);
		if(Status != 0){
			if(level < 2){
				updateLevel(username,++level);
				updateTurn(username,turn);
				sprintf(sendBuf, "_WINS-Team %d wins this level", Status);
			}
			else{
				sprintf(sendBuf, "_WINS-Team %d wins", Status);	
				dropSaveGame(username);
			}
		}

		for(i = 0; i < maxClientNo; i++){
			send(clientSocket[i],sendBuf,BufSize,0);
		}
	}











	mysql_free_result(result);
	mysql_close(connection);
}