#include<gtk/gtk.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<stdbool.h>

#define PORT 8080

GdkColor color;
char white[10] = "white";
char red[10] = "red";


GtkBuilder *ip_builder;
GtkBuilder *login_builder;
GtkBuilder *register_builder;
GtkBuilder *start_builder;
GtkBuilder *instructions_builder;
GtkBuilder *main_builder1;
GtkBuilder *main_builder2;
GtkBuilder *main_builder3;

GtkWidget *ip_window;
GtkWidget *login_window;
GtkWidget *register_window;
GtkWidget *start_window;
GtkWidget *instructions_window;
GtkWidget *main_window1;
GtkWidget *main_window2;
GtkWidget *main_window3;

// ip_window
GtkWidget *ip_address_entry;
GtkWidget *ip_error;

// login_window
GtkWidget *username_entry_login;
GtkWidget *password_entry_login;
GtkWidget *login_error;

// register_window
GtkWidget *username_entry_register;
GtkWidget *password_entry_register;
GtkWidget *confirm_password_entry_register;
GtkWidget *register_error;

// instructions_window
GtkWidget *instructions_image;


// main_window1

// players name labels
GtkWidget *player1name_label1;
GtkWidget *player2name_label1;
GtkWidget *player3name_label1;
GtkWidget *player4name_label1;

// cells of each player cell1_label[row][column]
GtkWidget *cell1_label1[10][10];
GtkWidget *cell2_label1[10][10];
GtkWidget *cell3_label1[10][10];
GtkWidget *cell4_label1[10][10];

// player input of position of each battleship

GtkWidget *aircraft_sr_comboboxtext1;
GtkWidget *aircraft_sc_comboboxtext1;
GtkWidget *aircraft_er_comboboxtext1;
GtkWidget *aircraft_ec_comboboxtext1;

GtkWidget *destroyer_sr_comboboxtext1;
GtkWidget *destroyer_sc_comboboxtext1;
GtkWidget *destroyer_er_comboboxtext1;
GtkWidget *destroyer_ec_comboboxtext1;

GtkWidget *frigate_sr_comboboxtext1;
GtkWidget *frigate_sc_comboboxtext1;
GtkWidget *frigate_er_comboboxtext1;
GtkWidget *frigate_ec_comboboxtext1;

GtkWidget *cruiser_sr_comboboxtext1;
GtkWidget *cruiser_sc_comboboxtext1;
GtkWidget *cruiser_er_comboboxtext1;
GtkWidget *cruiser_ec_comboboxtext1;

GtkWidget *submarine_sr_comboboxtext1;
GtkWidget *submarine_sc_comboboxtext1;
GtkWidget *submarine_er_comboboxtext1;
GtkWidget *submarine_ec_comboboxtext1;

// label for showing details like you won, hit and missed
GtkWidget *show_label1;

// player input for enemy s/he wants to target and position of hit row and column
GtkWidget *hitplayer_comboboxtext1;
GtkWidget *hitplayer_r_comboboxtext1;
GtkWidget *hitplayer_c_comboboxtext1;
GtkWidget *hitplayer_with_comboboxtext1;

GtkWidget *submit_button1;
GtkWidget *hit_button1;



// main_window2

// players name labels
GtkWidget *player1name_label2;
GtkWidget *player2name_label2;
GtkWidget *player3name_label2;
GtkWidget *player4name_label2;

// cells of each player cell1_label[row][column]
GtkWidget *cell1_label2[10][10];
GtkWidget *cell2_label2[10][10];
GtkWidget *cell3_label2[10][10];
GtkWidget *cell4_label2[10][10];

// player input of position of each battleship
GtkWidget *decoy1_r_comboboxtext2;
GtkWidget *decoy1_c_comboboxtext2;
GtkWidget *decoy2_r_comboboxtext2;
GtkWidget *decoy2_c_comboboxtext2;

GtkWidget *aircraft_sr_comboboxtext2;
GtkWidget *aircraft_sc_comboboxtext2;
GtkWidget *aircraft_er_comboboxtext2;
GtkWidget *aircraft_ec_comboboxtext2;

GtkWidget *destroyer_sr_comboboxtext2;
GtkWidget *destroyer_sc_comboboxtext2;
GtkWidget *destroyer_er_comboboxtext2;
GtkWidget *destroyer_ec_comboboxtext2;

GtkWidget *frigate_sr_comboboxtext2;
GtkWidget *frigate_sc_comboboxtext2;
GtkWidget *frigate_er_comboboxtext2;
GtkWidget *frigate_ec_comboboxtext2;

GtkWidget *cruiser_sr_comboboxtext2;
GtkWidget *cruiser_sc_comboboxtext2;
GtkWidget *cruiser_er_comboboxtext2;
GtkWidget *cruiser_ec_comboboxtext2;

GtkWidget *submarine_sr_comboboxtext2;
GtkWidget *submarine_sc_comboboxtext2;
GtkWidget *submarine_er_comboboxtext2;
GtkWidget *submarine_ec_comboboxtext2;

// label for showing details like you won, hit and missed
GtkWidget *show_label2;

// player input for enemy s/he wants to target and position of hit row and column
GtkWidget *hitplayer_comboboxtext2;
GtkWidget *hitplayer_r_comboboxtext2;
GtkWidget *hitplayer_c_comboboxtext2;
GtkWidget *hitplayer_with_comboboxtext2;

GtkWidget *submit_button2;
GtkWidget *hit_button2;
GtkWidget *scan_button2;




// main_window3

// players name labels
GtkWidget *player1name_label3;
GtkWidget *player2name_label3;
GtkWidget *player3name_label3;
GtkWidget *player4name_label3;

// cells of each player cell1_label[row][column]
GtkWidget *cell1_label3[10][10];
GtkWidget *cell2_label3[10][10];
GtkWidget *cell3_label3[10][10];
GtkWidget *cell4_label3[10][10];

// player input of position of each battleship
GtkWidget *decoy1_r_comboboxtext3;
GtkWidget *decoy1_c_comboboxtext3;
GtkWidget *decoy2_r_comboboxtext3;
GtkWidget *decoy2_c_comboboxtext3;

GtkWidget *aircraft_sr_comboboxtext3;
GtkWidget *aircraft_sc_comboboxtext3;
GtkWidget *aircraft_er_comboboxtext3;
GtkWidget *aircraft_ec_comboboxtext3;

GtkWidget *destroyer_sr_comboboxtext3;
GtkWidget *destroyer_sc_comboboxtext3;
GtkWidget *destroyer_er_comboboxtext3;
GtkWidget *destroyer_ec_comboboxtext3;

GtkWidget *frigate_sr_comboboxtext3;
GtkWidget *frigate_sc_comboboxtext3;
GtkWidget *frigate_er_comboboxtext3;
GtkWidget *frigate_ec_comboboxtext3;

GtkWidget *cruiser_sr_comboboxtext3;
GtkWidget *cruiser_sc_comboboxtext3;
GtkWidget *cruiser_er_comboboxtext3;
GtkWidget *cruiser_ec_comboboxtext3;

GtkWidget *submarine_sr_comboboxtext3;
GtkWidget *submarine_sc_comboboxtext3;
GtkWidget *submarine_er_comboboxtext3;
GtkWidget *submarine_ec_comboboxtext3;

GtkWidget *hitplayer_mine_comboboxtext3;

GtkWidget *hitplayer_mine_1r_comboboxtext3;
GtkWidget *hitplayer_mine_1c_comboboxtext3;
GtkWidget *hitplayer_mine_2r_comboboxtext3;
GtkWidget *hitplayer_mine_2c_comboboxtext3;

// label for showing details like you won, hit and missed
GtkWidget *show_label3;

// player input for enemy s/he wants to target and position of hit row and column
GtkWidget *hitplayer_comboboxtext3;
GtkWidget *hitplayer_r_comboboxtext3;
GtkWidget *hitplayer_c_comboboxtext3;
GtkWidget *hitplayer_with_comboboxtext3;

GtkWidget *submit_button3;
GtkWidget *hit_button3;
GtkWidget *scan_button3;
GtkWidget *mine_hit_button3;


char players[4][9];


int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);

	ip_builder = gtk_builder_new();
	login_builder = gtk_builder_new();
	register_builder = gtk_builder_new();
	start_builder = gtk_builder_new();
	main_builder1 = gtk_builder_new();
	main_builder2 = gtk_builder_new();
	main_builder3 = gtk_builder_new();

	gtk_builder_add_from_file (ip_builder, "glade/ip.glade", NULL);
	gtk_builder_add_from_file (login_builder, "glade/login.glade", NULL);
	gtk_builder_add_from_file (register_builder, "glade/register.glade", NULL);
	gtk_builder_add_from_file (start_builder, "glade/start.glade", NULL);
	gtk_builder_add_from_file (instructions_builder, "glade/instructions.glade", NULL);
	gtk_builder_add_from_file (main_builder1, "glade/main1.glade", NULL);
	gtk_builder_add_from_file (main_builder2, "glade/main2.glade", NULL);
	gtk_builder_add_from_file (main_builder3, "glade/main3.glade", NULL);

	ip_window = GTK_WIDGET(gtk_builder_get_object(ip_builder, "main_window"));
	login_window = GTK_WIDGET(gtk_builder_get_object(login_builder, "main_window"));
	register_window = GTK_WIDGET(gtk_builder_get_object(register_builder, "main_window"));
	start_window = GTK_WIDGET(gtk_builder_get_object(start_builder, "main_window"));
	instructions_window = GTK_WIDGET(gtk_builder_get_object(instructions_builder, "main_window"));
	main_window1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "main_window"));
	main_window2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "main_window"));
	main_window3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "main_window"));

	gtk_builder_connect_signals(ip_builder, NULL);
	gtk_builder_connect_signals(login_builder, NULL);
	gtk_builder_connect_signals(register_builder, NULL);
	gtk_builder_connect_signals(start_builder, NULL);
	gtk_builder_connect_signals(instructions_builder, NULL);
	gtk_builder_connect_signals(main_builder1, NULL);
	gtk_builder_connect_signals(main_builder2, NULL);
	gtk_builder_connect_signals(main_builder3, NULL);

// ip_window
	ip_address_entry = GTK_WIDGET(gtk_builder_get_object(ip_builder, "ip_address_entry"));
	ip_error = GTK_WIDGET(gtk_builder_get_object(ip_builder, "ip_error"));


// login_window
	username_entry_login = GTK_WIDGET(gtk_builder_get_object(login_builder, "username_entry"));
	password_entry_login = GTK_WIDGET(gtk_builder_get_object(login_builder, "password_entry"));
	login_error = GTK_WIDGET(gtk_builder_get_object(login_builder, "login_error"));


// register_window
	username_entry_register = GTK_WIDGET(gtk_builder_get_object(register_builder, "username_entry"));
	password_entry_register = GTK_WIDGET(gtk_builder_get_object(register_builder, "password_entry"));
	confirm_password_entry_register = GTK_WIDGET(gtk_builder_get_object(register_builder, "confirm_password_entry"));
	register_error = GTK_WIDGET(gtk_builder_get_object(register_builder, "register_error"));

// main_window1
	player1name_label1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "player1name_label"));
	player2name_label1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "player2name_label"));
	player3name_label1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "player3name_label"));
	player4name_label1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "player4name_label"));


// change background color
	//gdk_color_parse (red, &color);
	//gtk_widget_modify_bg (player4name_label1, GTK_STATE_NORMAL, &color);

	char numi[2];
	char numj[2];
	char boxNumber1[11];
	char boxNumber2[11];
	char boxNumber3[11];
	char boxNumber4[11];
	int i,j;

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber1,"b1");
			strcat(boxNumber1, numi);
			strcat(boxNumber1, numj);
			cell1_label1[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder1, strcat(boxNumber1,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber2,"b2");
			strcat(boxNumber2, numi);
			strcat(boxNumber2, numj);
			cell2_label1[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder1, strcat(boxNumber2,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber3,"b3");
			strcat(boxNumber3, numi);
			strcat(boxNumber3, numj);
			cell3_label1[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder1, strcat(boxNumber3,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber4,"b4");
			strcat(boxNumber4, numi);
			strcat(boxNumber4, numj);
			cell4_label1[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder1, strcat(boxNumber4,"_label")));
		}
	}

	aircraft_sr_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "aircraft_sr_comboboxtext"));
	aircraft_sc_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "aircraft_sc_comboboxtext"));
	aircraft_er_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "aircraft_er_comboboxtext"));
	aircraft_ec_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "aircraft_ec_comboboxtext"));

	destroyer_sr_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "destroyer_sr_comboboxtext"));
	destroyer_sc_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "destroyer_sc_comboboxtext"));
	destroyer_er_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "destroyer_er_comboboxtext"));
	destroyer_ec_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "destroyer_ec_comboboxtext"));

	frigate_sr_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "frigate_sr_comboboxtext"));
	frigate_sc_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "frigate_sc_comboboxtext"));
	frigate_er_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "frigate_er_comboboxtext"));
	frigate_ec_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "frigate_ec_comboboxtext"));

	cruiser_sr_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "cruiser_sr_comboboxtext"));
	cruiser_sc_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "cruiser_sc_comboboxtext"));
	cruiser_er_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "cruiser_er_comboboxtext"));
	cruiser_ec_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "cruiser_ec_comboboxtext"));

	submarine_sr_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submarine_sr_comboboxtext"));
	submarine_sc_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submarine_sc_comboboxtext"));
	submarine_er_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submarine_er_comboboxtext"));
	submarine_ec_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submarine_ec_comboboxtext"));

	show_label1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "show_label"));

	hitplayer_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_comboboxtext"));
	hitplayer_r_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_r_comboboxtext"));
	hitplayer_c_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_c_comboboxtext"));
	hitplayer_with_comboboxtext1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_with_comboboxtext"));

	submit_button1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submit_button"));
	hit_button1 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hit_button"));





// main_window2
	player1name_label2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "player1name_label"));
	player2name_label2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "player2name_label"));
	player3name_label2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "player3name_label"));
	player4name_label2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "player4name_label"));


// change background color
	//gdk_color_parse (red, &color);
	//gtk_widget_modify_bg (player4name_label2, GTK_STATE_NORMAL, &color);

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber1,"b1");
			strcat(boxNumber1, numi);
			strcat(boxNumber1, numj);
			cell1_label2[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder2, strcat(boxNumber1,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber2,"b2");
			strcat(boxNumber2, numi);
			strcat(boxNumber2, numj);
			cell2_label2[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder2, strcat(boxNumber2,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber3,"b3");
			strcat(boxNumber3, numi);
			strcat(boxNumber3, numj);
			cell3_label2[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder2, strcat(boxNumber3,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber4,"b4");
			strcat(boxNumber4, numi);
			strcat(boxNumber4, numj);
			cell4_label2[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder2, strcat(boxNumber4,"_label")));
		}
	}

	decoy1_r_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "decoy1_r_comboboxtext"));
	decoy1_c_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "decoy1_c_comboboxtext"));
	decoy2_r_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "decoy2_r_comboboxtext"));
	decoy2_c_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "decoy2_c_comboboxtext"));

	aircraft_sr_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "aircraft_sr_comboboxtext"));
	aircraft_sc_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "aircraft_sc_comboboxtext"));
	aircraft_er_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "aircraft_er_comboboxtext"));
	aircraft_ec_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "aircraft_ec_comboboxtext"));

	destroyer_sr_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "destroyer_sr_comboboxtext"));
	destroyer_sc_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "destroyer_sc_comboboxtext"));
	destroyer_er_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "destroyer_er_comboboxtext"));
	destroyer_ec_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "destroyer_ec_comboboxtext"));

	frigate_sr_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "frigate_sr_comboboxtext"));
	frigate_sc_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "frigate_sc_comboboxtext"));
	frigate_er_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "frigate_er_comboboxtext"));
	frigate_ec_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "frigate_ec_comboboxtext"));

	cruiser_sr_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "cruiser_sr_comboboxtext"));
	cruiser_sc_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "cruiser_sc_comboboxtext"));
	cruiser_er_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "cruiser_er_comboboxtext"));
	cruiser_ec_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "cruiser_ec_comboboxtext"));

	submarine_sr_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "submarine_sr_comboboxtext"));
	submarine_sc_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "submarine_sc_comboboxtext"));
	submarine_er_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "submarine_er_comboboxtext"));
	submarine_ec_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "submarine_ec_comboboxtext"));

	show_label2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "show_label"));

	hitplayer_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "hitplayer_comboboxtext"));
	hitplayer_r_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "hitplayer_r_comboboxtext"));
	hitplayer_c_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder2, "hitplayer_c_comboboxtext"));
	hitplayer_with_comboboxtext2 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_with_comboboxtext"));

	submit_button2 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submit_button"));
	hit_button2 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hit_button"));
	scan_button2 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "scan_button"));







// main_window3
	player1name_label3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "player1name_label"));
	player2name_label3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "player2name_label"));
	player3name_label3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "player3name_label"));
	player4name_label3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "player4name_label"));


// change background color
	//gdk_color_parse (red, &color);
	//gtk_widget_modify_bg (player4name_label3, GTK_STATE_NORMAL, &color);

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber1,"b1");
			strcat(boxNumber1, numi);
			strcat(boxNumber1, numj);
			cell1_label3[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder3, strcat(boxNumber1,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber2,"b2");
			strcat(boxNumber2, numi);
			strcat(boxNumber2, numj);
			cell2_label3[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder3, strcat(boxNumber2,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber3,"b3");
			strcat(boxNumber3, numi);
			strcat(boxNumber3, numj);
			cell3_label3[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder3, strcat(boxNumber3,"_label")));
		}
	}

	memset(numi,'\0',2);
	memset(numj,'\0',2);

	for(i = 0; i < 10; i++) {
		sprintf(numi, "%d", i);
		for(j = 0; j < 10; j++) {
			sprintf(numj, "%d", j);
			strcpy(boxNumber4,"b4");
			strcat(boxNumber4, numi);
			strcat(boxNumber4, numj);
			cell4_label3[i][j] = GTK_WIDGET(gtk_builder_get_object(main_builder3, strcat(boxNumber4,"_label")));
		}
	}

	decoy1_r_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "decoy1_r_comboboxtext"));
	decoy1_c_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "decoy1_c_comboboxtext"));
	decoy2_r_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "decoy2_r_comboboxtext"));
	decoy2_c_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "decoy2_c_comboboxtext"));

	aircraft_sr_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "aircraft_sr_comboboxtext"));
	aircraft_sc_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "aircraft_sc_comboboxtext"));
	aircraft_er_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "aircraft_er_comboboxtext"));
	aircraft_ec_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "aircraft_ec_comboboxtext"));

	destroyer_sr_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "destroyer_sr_comboboxtext"));
	destroyer_sc_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "destroyer_sc_comboboxtext"));
	destroyer_er_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "destroyer_er_comboboxtext"));
	destroyer_ec_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "destroyer_ec_comboboxtext"));

	frigate_sr_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "frigate_sr_comboboxtext"));
	frigate_sc_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "frigate_sc_comboboxtext"));
	frigate_er_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "frigate_er_comboboxtext"));
	frigate_ec_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "frigate_ec_comboboxtext"));

	cruiser_sr_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "cruiser_sr_comboboxtext"));
	cruiser_sc_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "cruiser_sc_comboboxtext"));
	cruiser_er_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "cruiser_er_comboboxtext"));
	cruiser_ec_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "cruiser_ec_comboboxtext"));

	submarine_sr_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "submarine_sr_comboboxtext"));
	submarine_sc_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "submarine_sc_comboboxtext"));
	submarine_er_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "submarine_er_comboboxtext"));
	submarine_ec_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "submarine_ec_comboboxtext"));

	hitplayer_mine_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_mine_comboboxtext"));

	hitplayer_mine_1r_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_mine_1r_comboboxtext"));
	hitplayer_mine_1c_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_mine_1c_comboboxtext"));
	hitplayer_mine_2r_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_mine_2r_comboboxtext"));
	hitplayer_mine_2c_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_mine_2c_comboboxtext"));

	show_label3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "show_label"));

	hitplayer_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_comboboxtext"));
	hitplayer_r_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_r_comboboxtext"));
	hitplayer_c_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder3, "hitplayer_c_comboboxtext"));
	hitplayer_with_comboboxtext3 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hitplayer_with_comboboxtext"));

	submit_button3 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "submit_button"));
	hit_button3 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "hit_button"));
	scan_button3 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "scan_button"));
	mine_hit_button3 = GTK_WIDGET(gtk_builder_get_object(main_builder1, "mine_hit_button"));


	g_object_unref(ip_builder);
	g_object_unref(main_builder1);
	g_object_unref(main_builder2);	
	g_object_unref(main_builder3);
	g_object_unref(login_builder);
	g_object_unref(register_window);
	g_object_unref(start_builder);

	memset(players, '\0', sizeof(players));
	
	gtk_widget_show(ip_window);
	gtk_main();

	return 0;
}








// ip_window

// called when signin_button in ip_window is clicked
int ip_address_button_clicked_cb() {

	char ip_address[16];

	memset(ip_address, '\0', sizeof(ip_address));

	strcpy(ip_address, gtk_entry_get_text((GtkEntry *)ip_address_entry));

	
    int clientSocket = 0;

    struct sockaddr_in server_addr;

	memset(buffer, '\0', sizeof(buffer));

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
    memset(&server_addr, '0', sizeof(server_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, ip_address, &serv_addr.sin_addr)<=0){
        gtk_label_set_text((GtkLabel *)ip_error,"Invalid IP Address");
        return -1;
    }
  
    if(connect(clientSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

	gtk_widget_hide(ip_window);

	gtk_widget_show(login_window);

	return 0;
}








// login_window

// called when signin_button in login_window is clicked
void signin_button_clicked_cb_login() {

	char username[9];
	char password[9];

	memset(username, '\0', sizeof(username));
	memset(password, '\0', sizeof(password));

	strcpy(username, gtk_entry_get_text((GtkEntry *)username_entry_login));
	strcpy(password, gtk_entry_get_text((GtkEntry *)password_entry_login));

	//validate using database

	gtk_widget_hide(login_window);

	gtk_widget_show(start_window);
}

// called when signup_button in login_window is clicked
void signup_button_clicked_cb_login() {
	gtk_widget_hide(login_window);
	gtk_widget_show(register_window);
}


// register_window

// called when signin_button in register_window is clicked
void signin_button_clicked_cb_register() {
	gtk_widget_hide(register_window);
	gtk_widget_show(login_window);
}

// called when signup_button in register_window is clicked
int signup_button_clicked_cb_register() {

	char username[9];
	char password[9];
	char confirm_password[9];

	memset(username, '\0', sizeof(username));
	memset(password, '\0', sizeof(password));
	memset(password, '\0', sizeof(confirm_password));

	strcpy(username, gtk_entry_get_text((GtkEntry *)username_entry_register));
	strcpy(password, gtk_entry_get_text((GtkEntry *)password_entry_register));
	strcpy(confirm_password, gtk_entry_get_text((GtkEntry *)confirm_password_entry_register));

	if(strcmp(password, confirm_password) != 0){
		gtk_label_set_text((GtkLabel *)register_error,"Password and Confirm Password Don't Match");
		return -1;
	}//else store in database, if username doesn't already exist

	gtk_widget_hide(register_window);
	gtk_widget_show(login_window);

	return 0;
}









// start_window

// called when new_button in start_window is clicked
void new_button_clicked_cb() {
	gtk_widget_hide(start_window);
	gtk_widget_show(main_window1);
	//gtk_widget_show(instructions_window);
	//call function to wait for server response
}

// called when continue_button in start_window is clicked
void continue_button_clicked_cb() {
	gtk_widget_hide(start_window);
	//gtk_widget_show(instructions_window);
	//call function to wait for server response
}

// called when signout_button in start_window is clicked
void signout_button_clicked_cb() {
	gtk_widget_hide(start_window);
	gtk_widget_show(login_window);
}





// main_window1

// called when submit_button in main_window1 is clicked
int submit_button_clicked_cb1() {

	int aircraft_sr, aircraft_sc, aircraft_er, aircraft_ec;
	int destroyer_sr, destroyer_sc, destroyer_er, destroyer_ec;
	int frigate_sr, frigate_sc, frigate_er, frigate_ec; 
	int cruiser_sr, cruiser_sc, cruiser_er, cruiser_ec;
	int submarine_sr, submarine_sc, submarine_er, submarine_ec;

	int player1_board[9][9];
	int i, j;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			player1_board[i][j] = 0;
		}
	}

	aircraft_sr = gtk_combo_box_get_active((GtkComboBox *)aircraft_sr_comboboxtext1);
	aircraft_sc = gtk_combo_box_get_active((GtkComboBox *)aircraft_sc_comboboxtext1);
	aircraft_er = gtk_combo_box_get_active((GtkComboBox *)aircraft_er_comboboxtext1);
	aircraft_ec = gtk_combo_box_get_active((GtkComboBox *)aircraft_ec_comboboxtext1);

	destroyer_sr = gtk_combo_box_get_active((GtkComboBox *)destroyer_sr_comboboxtext1);
	destroyer_sc = gtk_combo_box_get_active((GtkComboBox *)destroyer_sc_comboboxtext1);
	destroyer_er = gtk_combo_box_get_active((GtkComboBox *)destroyer_er_comboboxtext1);
	destroyer_ec = gtk_combo_box_get_active((GtkComboBox *)destroyer_ec_comboboxtext1);

	frigate_sr = gtk_combo_box_get_active((GtkComboBox *)frigate_sr_comboboxtext1);
	frigate_sc = gtk_combo_box_get_active((GtkComboBox *)frigate_sc_comboboxtext1);
	frigate_er = gtk_combo_box_get_active((GtkComboBox *)frigate_er_comboboxtext1);
	frigate_ec = gtk_combo_box_get_active((GtkComboBox *)frigate_ec_comboboxtext1);

	cruiser_sr = gtk_combo_box_get_active((GtkComboBox *)cruiser_sr_comboboxtext1);
	cruiser_sc = gtk_combo_box_get_active((GtkComboBox *)cruiser_sc_comboboxtext1);
	cruiser_er = gtk_combo_box_get_active((GtkComboBox *)cruiser_er_comboboxtext1);
	cruiser_ec = gtk_combo_box_get_active((GtkComboBox *)cruiser_ec_comboboxtext1);

	submarine_sr = gtk_combo_box_get_active((GtkComboBox *)submarine_sr_comboboxtext1);
	submarine_sc = gtk_combo_box_get_active((GtkComboBox *)submarine_sc_comboboxtext1);
	submarine_er = gtk_combo_box_get_active((GtkComboBox *)submarine_er_comboboxtext1);
	submarine_ec = gtk_combo_box_get_active((GtkComboBox *)submarine_ec_comboboxtext1);

	if((aircraft_sr == aircraft_er) && ((aircraft_ec - aircraft_sc) == 4)){

		i = aircraft_sr;
		j = aircraft_sc;

		while(j <= aircraft_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}
		
	}else if((aircraft_sc == aircraft_ec) && ((aircraft_er - aircraft_sr) == 4)){
		
		i = aircraft_sr;
		j = aircraft_sc;

		while(i <= aircraft_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
		return -1;
	}

	if((destroyer_sr == destroyer_er) && ((destroyer_ec - destroyer_sc) == 3)){

		i = destroyer_sr;
		j = destroyer_sc;

		while(j <= destroyer_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else if((destroyer_sc == destroyer_ec) && ((destroyer_er - destroyer_sr) == 3)){
		
		i = destroyer_sr;
		j = destroyer_sc;

		while(i <= destroyer_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
		return -1;
	}

	if((frigate_sr == frigate_er) && ((frigate_ec - frigate_sc) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(j <= frigate_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else if((frigate_sc == frigate_ec) && ((frigate_er - frigate_sr) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(i <= frigate_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
		return -1;
	}

	if((cruiser_sr == cruiser_er) && ((cruiser_ec - cruiser_sc) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(j <= cruiser_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else if((cruiser_sc == cruiser_ec) && ((cruiser_er - cruiser_sr) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
		return -1;
	}

	if((submarine_sr == submarine_er) && ((submarine_ec - submarine_sc) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(j <= submarine_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else if((submarine_sc == submarine_ec) && ((submarine_er - submarine_sr) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
		return -1;
	}

	int board1[100];

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			board1[10*i + j] = player1_board[i][j];
		}
	}

	//send the 1d array to the server

	gtk_widget_set_sensitive (submit_button1, FALSE);

	return 0;

}

// called when hit_button in main_window1 is clicked
void hit_button_clicked_cb1() {

	int hit_player, hit_r, hit_c, hit_ship;

	hit_player = gtk_combo_box_get_active((GtkComboBox *)hitplayer_comboboxtext1);
	hit_r = gtk_combo_box_get_active((GtkComboBox *)hitplayer_r_comboboxtext1);
	hit_c = gtk_combo_box_get_active((GtkComboBox *)hitplayer_c_comboboxtext1);


}

// main_window2

// called when submit_button in main_window2 is clicked
int submit_button_clicked_cb2() {

	int aircraft_sr, aircraft_sc, aircraft_er, aircraft_ec;
	int destroyer_sr, destroyer_sc, destroyer_er, destroyer_ec;
	int frigate_sr, frigate_sc, frigate_er, frigate_ec; 
	int cruiser_sr, cruiser_sc, cruiser_er, cruiser_ec;
	int submarine_sr, submarine_sc, submarine_er, submarine_ec;
	int decoy1_r, decoy1_c, decoy2_r, decoy2_c; 

	int player1_board[9][9];
	int i, j;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			player1_board[i][j] = 0;
		}
	}

	aircraft_sr = gtk_combo_box_get_active((GtkComboBox *)aircraft_sr_comboboxtext1);
	aircraft_sc = gtk_combo_box_get_active((GtkComboBox *)aircraft_sc_comboboxtext1);
	aircraft_er = gtk_combo_box_get_active((GtkComboBox *)aircraft_er_comboboxtext1);
	aircraft_ec = gtk_combo_box_get_active((GtkComboBox *)aircraft_ec_comboboxtext1);

	destroyer_sr = gtk_combo_box_get_active((GtkComboBox *)destroyer_sr_comboboxtext1);
	destroyer_sc = gtk_combo_box_get_active((GtkComboBox *)destroyer_sc_comboboxtext1);
	destroyer_er = gtk_combo_box_get_active((GtkComboBox *)destroyer_er_comboboxtext1);
	destroyer_ec = gtk_combo_box_get_active((GtkComboBox *)destroyer_ec_comboboxtext1);

	frigate_sr = gtk_combo_box_get_active((GtkComboBox *)frigate_sr_comboboxtext1);
	frigate_sc = gtk_combo_box_get_active((GtkComboBox *)frigate_sc_comboboxtext1);
	frigate_er = gtk_combo_box_get_active((GtkComboBox *)frigate_er_comboboxtext1);
	frigate_ec = gtk_combo_box_get_active((GtkComboBox *)frigate_ec_comboboxtext1);

	cruiser_sr = gtk_combo_box_get_active((GtkComboBox *)cruiser_sr_comboboxtext1);
	cruiser_sc = gtk_combo_box_get_active((GtkComboBox *)cruiser_sc_comboboxtext1);
	cruiser_er = gtk_combo_box_get_active((GtkComboBox *)cruiser_er_comboboxtext1);
	cruiser_ec = gtk_combo_box_get_active((GtkComboBox *)cruiser_ec_comboboxtext1);

	submarine_sr = gtk_combo_box_get_active((GtkComboBox *)submarine_sr_comboboxtext1);
	submarine_sc = gtk_combo_box_get_active((GtkComboBox *)submarine_sc_comboboxtext1);
	submarine_er = gtk_combo_box_get_active((GtkComboBox *)submarine_er_comboboxtext1);
	submarine_ec = gtk_combo_box_get_active((GtkComboBox *)submarine_ec_comboboxtext1);

	decoy1_r = gtk_combo_box_get_active((GtkComboBox *)decoy1_r_comboboxtext2);
	decoy1_c = gtk_combo_box_get_active((GtkComboBox *)decoy1_c_comboboxtext2);
	decoy2_r = gtk_combo_box_get_active((GtkComboBox *)decoy2_r_comboboxtext2);
	decoy2_c = gtk_combo_box_get_active((GtkComboBox *)decoy2_c_comboboxtext2);

	if((aircraft_sr == aircraft_er) && ((aircraft_ec - aircraft_sc) == 4)){

		i = aircraft_sr;
		j = aircraft_sc;

		while(j <= aircraft_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}
		
	}else if((aircraft_sc == aircraft_ec) && ((aircraft_er - aircraft_sr) == 4)){
		
		i = aircraft_sr;
		j = aircraft_sc;

		while(i <= aircraft_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
		return -1;
	}

	if((destroyer_sr == destroyer_er) && ((destroyer_ec - destroyer_sc) == 3)){

		i = destroyer_sr;
		j = destroyer_sc;

		while(j <= destroyer_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else if((destroyer_sc == destroyer_ec) && ((destroyer_er - destroyer_sr) == 3)){
		
		i = destroyer_sr;
		j = destroyer_sc;

		while(i <= destroyer_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
		return -1;
	}

	if((frigate_sr == frigate_er) && ((frigate_ec - frigate_sc) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(j <= frigate_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else if((frigate_sc == frigate_ec) && ((frigate_er - frigate_sr) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(i <= frigate_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
		return -1;
	}

	if((cruiser_sr == cruiser_er) && ((cruiser_ec - cruiser_sc) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(j <= cruiser_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else if((cruiser_sc == cruiser_ec) && ((cruiser_er - cruiser_sr) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
		return -1;
	}

	if((submarine_sr == submarine_er) && ((submarine_ec - submarine_sc) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(j <= submarine_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else if((submarine_sc == submarine_ec) && ((submarine_er - submarine_sr) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
		return -1;
	}

	i = decoy1_r;
	j = decoy1_c;

	if(player1_board[i][j] == 0){
		player1_board[i][j] = 6;
	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Decoy 1");
		return -1;
	}

	i = decoy2_r;
	j = decoy2_c;

	if(player1_board[i][j] == 0){
		player1_board[i][j] = 6;
	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Decoy 2");
		return -1;
	}

	int board1[100];

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			board1[10*i + j] = player1_board[i][j];
		}
	}

	//send the 1d array to the server

	gtk_widget_set_sensitive (submit_button2, FALSE);

	return 0;

}

// called when hit_button in main_window2 is clicked
void hit_button_clicked_cb2() {

}

// called when hit_button in main_window2 is clicked
void scan_button_clicked_cb2() {

}

// main_window3

// called when submit_button in main_window3 is clicked
int submit_button_clicked_cb3() {

	int aircraft_sr, aircraft_sc, aircraft_er, aircraft_ec;
	int destroyer_sr, destroyer_sc, destroyer_er, destroyer_ec;
	int frigate_sr, frigate_sc, frigate_er, frigate_ec; 
	int cruiser_sr, cruiser_sc, cruiser_er, cruiser_ec;
	int submarine_sr, submarine_sc, submarine_er, submarine_ec;
	int decoy1_r, decoy1_c, decoy2_r, decoy2_c;

	int player1_board[9][9];
	int i, j;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			player1_board[i][j] = 0;
		}
	}

	aircraft_sr = gtk_combo_box_get_active((GtkComboBox *)aircraft_sr_comboboxtext1);
	aircraft_sc = gtk_combo_box_get_active((GtkComboBox *)aircraft_sc_comboboxtext1);
	aircraft_er = gtk_combo_box_get_active((GtkComboBox *)aircraft_er_comboboxtext1);
	aircraft_ec = gtk_combo_box_get_active((GtkComboBox *)aircraft_ec_comboboxtext1);

	destroyer_sr = gtk_combo_box_get_active((GtkComboBox *)destroyer_sr_comboboxtext1);
	destroyer_sc = gtk_combo_box_get_active((GtkComboBox *)destroyer_sc_comboboxtext1);
	destroyer_er = gtk_combo_box_get_active((GtkComboBox *)destroyer_er_comboboxtext1);
	destroyer_ec = gtk_combo_box_get_active((GtkComboBox *)destroyer_ec_comboboxtext1);

	frigate_sr = gtk_combo_box_get_active((GtkComboBox *)frigate_sr_comboboxtext1);
	frigate_sc = gtk_combo_box_get_active((GtkComboBox *)frigate_sc_comboboxtext1);
	frigate_er = gtk_combo_box_get_active((GtkComboBox *)frigate_er_comboboxtext1);
	frigate_ec = gtk_combo_box_get_active((GtkComboBox *)frigate_ec_comboboxtext1);

	cruiser_sr = gtk_combo_box_get_active((GtkComboBox *)cruiser_sr_comboboxtext1);
	cruiser_sc = gtk_combo_box_get_active((GtkComboBox *)cruiser_sc_comboboxtext1);
	cruiser_er = gtk_combo_box_get_active((GtkComboBox *)cruiser_er_comboboxtext1);
	cruiser_ec = gtk_combo_box_get_active((GtkComboBox *)cruiser_ec_comboboxtext1);

	submarine_sr = gtk_combo_box_get_active((GtkComboBox *)submarine_sr_comboboxtext1);
	submarine_sc = gtk_combo_box_get_active((GtkComboBox *)submarine_sc_comboboxtext1);
	submarine_er = gtk_combo_box_get_active((GtkComboBox *)submarine_er_comboboxtext1);
	submarine_ec = gtk_combo_box_get_active((GtkComboBox *)submarine_ec_comboboxtext1);

	decoy1_r = gtk_combo_box_get_active((GtkComboBox *)decoy1_r_comboboxtext2);
	decoy1_c = gtk_combo_box_get_active((GtkComboBox *)decoy1_c_comboboxtext2);
	decoy2_r = gtk_combo_box_get_active((GtkComboBox *)decoy2_r_comboboxtext2);
	decoy2_c = gtk_combo_box_get_active((GtkComboBox *)decoy2_c_comboboxtext2);

	if((aircraft_sr == aircraft_er) && ((aircraft_ec - aircraft_sc) == 4)){

		i = aircraft_sr;
		j = aircraft_sc;

		while(j <= aircraft_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}
		
	}else if((aircraft_sc == aircraft_ec) && ((aircraft_er - aircraft_sr) == 4)){
		
		i = aircraft_sr;
		j = aircraft_sc;

		while(i <= aircraft_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 1;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Aircraft Carrier");
		return -1;
	}

	if((destroyer_sr == destroyer_er) && ((destroyer_ec - destroyer_sc) == 3)){

		i = destroyer_sr;
		j = destroyer_sc;

		while(j <= destroyer_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else if((destroyer_sc == destroyer_ec) && ((destroyer_er - destroyer_sr) == 3)){
		
		i = destroyer_sr;
		j = destroyer_sc;

		while(i <= destroyer_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 2;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Destroyer");
		return -1;
	}

	if((frigate_sr == frigate_er) && ((frigate_ec - frigate_sc) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(j <= frigate_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else if((frigate_sc == frigate_ec) && ((frigate_er - frigate_sr) == 2)){
		
		i = frigate_sr;
		j = frigate_sc;

		while(i <= frigate_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 3;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Frigate");
		return -1;
	}

	if((cruiser_sr == cruiser_er) && ((cruiser_ec - cruiser_sc) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(j <= cruiser_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else if((cruiser_sc == cruiser_ec) && ((cruiser_er - cruiser_sr) == 1)){
		
		i = cruiser_sr;
		j = cruiser_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 4;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Cruiser");
		return -1;
	}

	if((submarine_sr == submarine_er) && ((submarine_ec - submarine_sc) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(j <= submarine_ec){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				j++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else if((submarine_sc == submarine_ec) && ((submarine_er - submarine_sr) == 1)){
		
		i = submarine_sr;
		j = submarine_sc;

		while(i <= cruiser_er){
			if(player1_board[i][j] == 0){
				player1_board[i][j] = 5;
				i++;
			}else{
				gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
				return -1;
			}
		}

	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Submarine");
		return -1;
	}

	i = decoy1_r;
	j = decoy1_c;

	if(player1_board[i][j] == 0){
		player1_board[i][j] = 6;
	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Decoy 1");
		return -1;
	}

	i = decoy2_r;
	j = decoy2_c;

	if(player1_board[i][j] == 0){
		player1_board[i][j] = 6;
	}else{
		gtk_label_set_text((GtkLabel *)show_label1,"Invalid Positions for Decoy 2");
		return -1;
	}

	int board1[100];

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			board1[10*i + j] = player1_board[i][j];
		}
	}

	//send the 1d array to the server

	gtk_widget_set_sensitive (submit_button3, FALSE);

	return 0;

}

// called when hit_button in main_window3 is clicked
void hit_button_clicked_cb3() {

}

// called when hit_button in main_window3 is clicked
void scan_button_clicked_cb3() {

}

// called when hit_button in main_window3 is clicked
void mine_hit_button_clicked_cb3() {

}






// called when window is closed
void on_window_main_destroy() {
	gtk_main_quit();
}
