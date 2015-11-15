
/*****************************************************************************
 * Copyright (C) Lehanshu Khatri lehanshu@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

/* This program does not store records, but only stores "data" in the stock*/
#include<ncurses.h>
#include"market.h"
#include<stdlib.h>
#define MENUMAX 2
#define MENUMAXAD 8
#define MENU 4
/*Funtion for printing the billing menu*/
void drawother(int item){
	int c;
	char mainmenu[] = "BILLING Menu";
	char menu[MENU][50] = { "Add item in the cart", 
					"Remove item from cart",
					"Preview Cart",
					"Exit"};
	clear();
	mvprintw(1,25,mainmenu);
	for(c=0;c<MENU;c++){
	if( c==item )
		attron(A_REVERSE);
		/* highlight selection */
		mvaddstr(3+(c*2),20,menu[c]);
		attroff(A_REVERSE);
		/* remove highlight */
	}
	mvprintw(26,5,"Use arrow keys to move; Enter to select:");
	refresh();
}
/*Function for printing the ADMIN Menu*/
void drawmenuadmin(int item){
	int c;
	char mainmenu[] = "ADMIN Menu";
	char menu[MENUMAXAD][50] = { "Enter new product details", 
					"Remove product details from the data",
					"View Statistc of all product sold",
					"Modify product informatio",
					"Display all product on screen",
					" Search for a product",
					"Information of costomers",
					"Exit"};
	clear();
	mvaddstr(0,25,mainmenu);
	for(c=0;c<MENUMAXAD;c++){
	if( c==item )
		attron(A_REVERSE);
		/* highlight selection */
		mvaddstr(3+(c*2),20,menu[c]);
		attroff(A_REVERSE);
		/* remove highlight */
	}
	mvaddstr(20,10,"Use arrow keys to move; Enter to select:");
	refresh();
}
/*Function for printing the Menu*/
void drawmenu(int item){
	int c;
	char mainmenu[] = "Main Menu";
	char menu[MENUMAX][21] = { "Make a bill", 
					"Logout"};
	clear();
	mvprintw(0,20,mainmenu);
	for(c=0;c<MENUMAX;c++){
	if( c==item )
		attron(A_REVERSE);
		/* highlight selection */
		mvaddstr(3+(c*2),20,menu[c]);
		attroff(A_REVERSE);
		/* remove highlight */
	}
	mvaddstr(16,10,"Use arrow keys to move; Enter to select:");
	refresh();
}
int main(){
	initscr();
	FILE *fp;
	init_pair(1,COLOR_BLACK,COLOR_BLUE);
	init_pair(2,COLOR_BLACK,COLOR_RED);
	init_pair(3,COLOR_BLACK,COLOR_GREEN);
	init_pair(4,COLOR_BLACK,COLOR_CYAN);
	keypad(stdscr,TRUE);					//Keypad key's active
	int ID, qua, key, loginkey, menuitem = 0;
	float price, tax, dis, totallog;
	char name[16];
	fp = fopen("file.txt","r");
	int ln, log, admin;
	mvprintw(0,20,"Welcome to THE HOSTEL SUPERMARKET\n");
	refresh();
	start_color();						//Colours active
	napms(500);
	flash();
	mvprintw(2,30,"Please Login\n");
	flash();						//Flashing
	mvprintw(4,25,"Press 1 for ADMIN login\n");
	mvprintw(6,25,"Press 2 for OTHER login\n");
	refresh();
	mvprintw(8,25,":>   ");
	refresh();
	scanw("%d",&log);
	noecho();
	if( log == 2 ){
		ln = login();
		if( ln == -1){
			endwin();
			return 0;
		}
		//while(1){
		drawmenu(menuitem);		
		do{
			key = getch();
			switch(key){
				case KEY_DOWN:
					menuitem++;
					if(menuitem > MENUMAX-1) menuitem = 0;
				break;
				case KEY_UP:
					menuitem--;
					if(menuitem < 0) menuitem = MENUMAX-1;
				break;
				default :
				break;
			}
		drawmenu(menuitem);
		}
		while( key != '\n');
		echo();
		//endwin();
		if((key == '\n') && (menuitem == 0)){			//After selecting MAKE A BILL	
			clear();
			while(1){
			drawother(menuitem);				//Printing BILLING Menu
			do{
				loginkey = getch();
				switch(loginkey){
					case KEY_DOWN:
					menuitem++;
					if(menuitem > MENU-1) menuitem = 0;
				break;
				case KEY_UP:
					menuitem--;
					if(menuitem < 0) menuitem = MENU-1;
				break;
				default :
				break;
			}
		drawother(menuitem);
		}
		while( loginkey != '\n');				//Selecting ADD ITEM in the cart
		if((loginkey == '\n') && (menuitem == 0)){
			clear();
			refresh();
			additem();
			}
		if((loginkey == '\n') && (menuitem == 1)){		//Removing ITEMS from the cart
			clear();
			refresh();
			removeitem();
		}
		if((loginkey == '\n') && (menuitem == 2)){		//Preview The ITEMS in the cart 
			clear();
			refresh();
			totallog = preview();
		}
		if((loginkey == '\n') && (menuitem == 3)){		//Exist from the BILLING Menu
			clear();
			refresh();
			last(totallog);
			break;
		}
		}
	}	
		endwin();
		return 0;
	
	}
	if( log == 1){						//ADMIN LOGIN
		admin = adminlogin();	
		if(admin == -1){				//USERNAME : 1, PASWARD : 2
			endwin();
			return 0;
		}						//NOTIFICATION if some products in the store are less than 10
		while(fscanf(fp,"%d  %s  %f  %d  %f  %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
			if(qua < 10){
				addstr("*************************************************\n");
				printw("Quantity of-- %s-- is less than 10 please stock up\n",name);
				addstr("*************************************************\n");
			refresh();
			}
		refresh();
		}
		
		//fclose(fp);
		refresh();
		getch();
		fclose(fp);
		while(1){
		drawmenuadmin(menuitem);			//Printing ADMIN MENU
		do{
			key = getch();
			switch(key){
				case KEY_DOWN:
					menuitem++;
					if(menuitem > MENUMAXAD-1) menuitem = 0;
				break;
				case KEY_UP:
					menuitem--;
					if(menuitem < 0) menuitem = MENUMAXAD-1;
				break;
				default :
				break;
			}
		drawmenuadmin(menuitem);
		}
		while( key != '\n');
		echo();
		
			if((key == '\n') && (menuitem == 0)){		//Function call for ADDING NEW PRODUCT in stock
				clear();
				refresh();
				enternew();
			}
			if((key == '\n') && (menuitem == 1)){		//Function call for REMOVING A PRODUCT from stock
				clear();
				refresh();
				removepro();
			}
			if((key == '\n') && (menuitem == 2)){		//Function call for PRINTING the STATISTICS of sale Product wise
				clear();
				refresh();
				printstatistics();
			}
			if((key == '\n') && (menuitem == 3)){		//Function call for MODIFYING PRODUCT INFORMATION in the stock
				clear();
				refresh();
				modify();
			}
			if((key == '\n') && (menuitem == 4)){		//Function call for PRINTING WHOLE STOCK on SCREEN
				clear();
				refresh();
				display();
			}
			if((key == '\n') && (menuitem == 5)){		//Function call for SEARCHING FOR SOME PRODUCT 
				clear();
				refresh();
				searching();
			}
			if((key == '\n') && (menuitem == 6)){		//Function call for PRINTING DETAILS OF COSTOMER NAME WITH THEIR SHOPPING TOTAL on sceen 
				clear();
				refresh();
				information();
			}
			if((key == '\n') && (menuitem == 7)){		//EXIT 
				clear();
				refresh();
				break;
			}
		} 
		endwin();
		return 0;
		}
	
		endwin();
		exit(0);
}
