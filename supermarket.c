
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
#include<stdlib.h>
#include"market.h"
#include<string.h>
#define ENTERMENU 2
int login(){					//Function for: OTHER LOGIN
	char username[24], pasward[24];		//USERNAME : 1, PASWARD : 2
	char orgpasward[] = "2";
	char orguser[] = "1";
	mvprintw(10,25,"Please Enter the username\n");
	mvprintw(11,25,":>   ");
	getstr(username);
	mvprintw(12,25,"Username : %s\n",username);
	mvprintw(13,25,"Please Enter the Passward\n");
	mvprintw(14,25,":>   ");
	getstr(pasward);
	if((strcmp(pasward,orgpasward) == 0) && (strcmp(username,orguser) == 0)){
		addstr("Login sucessful\n");
		return 1;
	}
	else{
		addstr("Login Unsecussfull\n");
		return -1;
	}
}
int adminlogin(){							//Function for AADMIN LOGIN
	char username[24], pasward[24];					//USERNAME : 1, PASWARD : 2
        char orgpasward[] = "2";
        char orguser[] = "1";
        mvprintw(10,25,"Please Enter the username\n");
	mvprintw(11,25,":>   ");
        getstr(username);
        mvprintw(12,25,"Username : %s\n",username);
        mvprintw(13,25,"Please Enter the Passward\n");
	mvprintw(14,25,":>   ");
        getstr(pasward);
        if((strcmp(pasward,orgpasward) == 0) && (strcmp(username,orguser) == 0)){
                mvprintw(15,25,"Login sucessful\n");
		mvprintw(16,25,"Press enter to continue\n");
		getch();
                return 1;
        }
        else{
                mvprintw(16,25,"Login Unsecussfull\n");
		refresh();
		napms(1000);
                return -1;
        }
}
void drawnew(int item){					//Function called from ENTERNEW product information function to SHOW menu of MODIYING DETAILS 
	int c;
	char mainmenu[] = "Enetered ID already exist please enter correct ID or Modify the existing ID information";
	char menu[ENTERMENU][50] = { "Modify the information", 
					"Go back to previous Menu"};
	clear();
	mvprintw(1,10,mainmenu);
	for(c=0;c<ENTERMENU;c++){
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
void enternew(){					//Function for entering new product information 
	int ID, ID1,qua,qua1, enterkey, menuitem = 0;
	FILE *fp, *cp;
	cp = fopen("statistic.txt","a+");
	//FILE *fopen(char *name, char *mode);
	float price,price1, tax, tax1, dis,dis1;
	char name[24], name1[24]; 
	addstr("Enter item ID\n");
	fp = fopen("file.txt","r");
	scanw("%d",&ID);
	while(fscanf( fp,"%d	%s      %f      %d      %f      %f",&ID1,name1,&price1,&qua1,&tax1,&dis1) != EOF){
		if(ID1 == ID){				//Checking if the entered ID is already in the data or not
			addstr("Enetered ID already exist please enter correct ID or Modify the existing ID information\n");
			printw("ID : %d\nName of product : %s\n",ID,name1);
			drawnew(menuitem);			//Printing the menu if entered ID is already in stock		
			do{
				addstr("Please select -Modify- To modify the existing product");
				refresh();
				enterkey = getch();
				switch(enterkey){
					case KEY_DOWN:
						menuitem++;
						if(menuitem > ENTERMENU-1) menuitem = 0;
					break;
					case KEY_UP:
						menuitem--;
						if(menuitem < 0) menuitem = ENTERMENU-1;
					break;
					default :
					break;
				}
			drawnew(menuitem);
			}
		while( enterkey != '\n');
		fclose(fp);
		if( (enterkey == '\n') && (menuitem == 0)){
			clear();
			refresh();
			modify();
		}
		else{
			refresh();
			clear();
			return;
			exit(0);
		}	
		refresh();	
		getch();	
		return;
		exit(0);
		}
		
	}
	fclose(fp);
	//scanw("%d",&ID);
	addstr("Name of the product\n");
	scanw("%s",name);
	addstr("Enter the price\n");
	scanw("%f",&price);
	addstr("Enter quantities that will be stored\n");
	scanw("%d",&qua);
	addstr("Enter tax to be calculated in % \n");
	scanw("%f",&tax);
	addstr("Enter discount to be given for the product\n");
	scanw("%f",&dis);
	fp = fopen("file.txt","a+");
	fprintf( fp, "%d	%s	%f	%d	%f	%f\n",ID,name,price,qua,tax,dis);
	fprintf(cp,"%s  %d\n",name,0);
	fclose(fp);
	fclose(cp);
}
void removepro(){				//Function for REMOVING DATA from stock
	int ID, orgid,qua;
	float price, tax, dis;
	char name[24];
	//char ch;
	FILE *fp;
	FILE *fpp;
	addstr("Enter the ID of the product that has to be removed\n");
	scanw("%d",&orgid);
	fp = fopen("file.txt","r");
	rename("file.txt","file1.txt");
	fpp = fopen("file.txt","a+");
	while(fscanf( fp,"%d	%s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
		if(orgid == ID){
			addstr("Match found\n");
			refresh();
			 //fprintf( fpp, "%d	%s      %f      %d      %f      %f\n",0,"noproduct",0.0,0,0.0,0.0);
		}
		else{
			fprintf( fpp, "%d	%s	%f	%d	%f	%f\n",ID,name,price,qua,tax,dis);
		}
	}	
	fclose(fp);
	fclose(fpp);
	remove("file1.txt");	
}
void information(){				//Function for PRINTING THE DATA OF COSTOMERS who  have purchased with their total ammount
	FILE *fp;
	char name[16];
	float total;
	fp = fopen("information.txt","r");
	while(fscanf(fp,"%s	%f",name,&total) != EOF){
		printw("%s	%f\n",name,total);
	}
	refresh();
	getch();
	fclose(fp);
}
void display(){					//Function for PRINTING WHOLE STOCK DATA on screen
	int ID, qua;
        float price, tax, dis;
        char name[24];
        //char ch;
        FILE *fp;
	fp = fopen("file.txt","r");
	addstr("ID	name		Rate		quantity	Tax			Discount\n");
	while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
		printw("%d\t%s\t\t%f\t\t%d\t%f\t\t%f\n",ID,name,price,qua,tax,dis);
	}
	getch();
}
void searching(){				//Function for SEARCHING For some product in stock 
	int ID, orgid,qua;
        float price, tax, dis;
        char name[24];
        //char ch;
        FILE *fp;
        fp = fopen("file.txt","r");
	addstr("Enter the ID\n");
	scanw("%d",&orgid);
	while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
		if(orgid == ID){
			printw("ID : %d\nName : %s\nRate : %f\nQuantity : %d\nTax : %f\nDiscount given : %f\n",ID,name,price,qua,tax,dis);
		}
	}
	getch();
}
void modify(){					//Function for MODIFYING THE DETAILS
	int ID, orgid,qua, choice;
        float price, tax, dis;
        char name[24];
        //char ch;
        FILE *fp;
        FILE *fpp;
	fp = fopen("file.txt","r");
	rename("file.txt","file1.txt");
	fpp = fopen("file.txt","a+");
	addstr("Enter the ID of the product that has to be modified\n");
	scanw("%d",&orgid);
	addstr("Press coresponding number\n1. Modify name\n2. Modify Price\n3. Modify quantity\n4. Modify tax applied\n5. Modify discount applied\n6. Ro do nothing\n");
	scanw("%d",&choice);
	switch(choice){
		case 1:
			while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
                		if(orgid == ID){
					char newname[16];
					addstr("Enter new name");
					getstr(newname);
					//strcpy(name,newname);
					fprintf( fpp,"%d      %s      %f      %d      %f      %f\n",ID,newname,price,qua,tax,dis);
				}
				else{
					 fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
                		}
			}
		break;
		case 2:
			 while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
                                if(orgid == ID){
					float p;
					printw("Old price is : %f\nEnter new price",price);
					scanw("%f",&p);
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,p,qua,tax,dis);
				}
				else{
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
				}
			}
		break;
		case 3:
			while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
                                if(orgid == ID){
					int newqua;
					printw("Old quantity is : %d\nEnter new quantity",qua);
					scanw("%d",&newqua);
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,newqua,tax,dis);
				}
				else{
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
				}
			}
		break;
		case 4:
			 while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
                                if(orgid == ID){
					float newtax;
					printw("Old tax applied is %f\nEnter new tax to be applied",tax);
					scanw("%f",&newtax);
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,newtax,dis);
				}
				else{
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
				}
			}
		break;
		case 5:
			while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
                                if(orgid == ID){
					float newdis;
					printw("Old discount applied is : %f\nEnter new discount to be applied",dis);
					scanw("%f",&newdis);
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,newdis);
				}
				else{
					fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
				}
			}
		break;
		case 6:
			while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
				fprintf( fpp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
			}
			/*Do nothing*/
		break;
	}
		fclose(fp);	
		fclose(fpp);
		remove("file1.txt");
}	
/*void makebill(){
	//FILE *fp;
	int choice, i = 0;
	float item[50];
	float totalam = 0;
	//costomer = fopen("information.txt","a+");
	//fp = fopen("costomerinfo.txt","w");
        //fprintf(fp, "Sr. Name   Qua  Rate  Amount\n");
        //fclose(fp);
	while(1){
		printf("Select one\n");
		//printting();
		scanf("%d",&choice);
		getchar();
		switch(choice){
			case 1:
				additem();
				break;
			case 2:
				removeitem();
				break;
			case 3:
				totalam = preview();
				break;
			case 4:
				last(totalam);
				return;
				break;
		}	
	}
}*/
static int j = 1;	
void additem(){					//Fuction for ADDING THE ITEM IN THE CART
	char name[24];
	FILE *fp;
	FILE *cp;
	int COSID, ID, qua, cosqua;
	float price, tax, dis;
	addstr("\nEnter the ID of the product\n");
	scanw("%d",&COSID);
	addstr("Enter the quantity taken in kgs/units	\n 1 for 1kg\n");
	scanw("%d",&cosqua);
	fp = fopen("file.txt","r");
	cp = fopen("costomerinfo.txt","a+");
	while((fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF)){
		if(COSID == ID){		//Function for CHECKING IF the required quantity in less than we have in the stock
		if(qua > cosqua){
			mvprintw(10,0,"\nName of Item : %s\nRate per unit/kg : %f\n",name,price);
			if(tax){
				price = (tax/100)*price + price;
			}
			if(dis){
				price = price - (dis/100)*dis;
			}
			fprintf(cp, "%d  %s	%d  %f  %f\n", j, name, cosqua, price, cosqua*price);
			j++;
		}
		else addstr("Less stock\n");
	}
	}
	refresh();
	getch();
	fclose(fp);
	fclose(cp);
}
float preview(){			//Function to PREVIEW THE CART
	FILE *fp;
	fp = fopen("costomerinfo.txt","r");
	int j;
	int i =0, k, cosqua;
	char name[16];
	float price, tot[10], total = 0;
	addstr("Sr  Name  Qua  Rate  Amount\n");	
	fp = fopen("costomerinfo.txt","r");
	while((fscanf(fp,"%d %s  %d  %f  %f",&j,name,&cosqua,&price,&tot[i]) != EOF)){
		printw("%d. %s  %d  %f  %f\n",j,name,cosqua,price,tot[i]);
	i++;
	}
	if( i == 0 ){
		i++;
	}
	for(k = 0; k < i; k++){
		total = total + tot[k];
	}
	printw("Total amount = %f\n",total);
	fclose(fp);
	refresh();
	getch();
	return total;
}				
void last(float totalam){		//Function for UPdating the stock information in the stock and updating STATISTICS and etc
	if( totalam == 0){
		endwin();
		return;
	}
	FILE *costomer;
	char cosname[16];
	costomer = fopen("information.txt","a+");
	addstr("Please enter the name of costomer\n");
	scanw("%s",cosname);
	fprintf(costomer,"%s	%f\n",cosname,totalam);
	printw("Total amount to be paid = %f\n",totalam);
	refresh();
	getch();
	fclose(costomer);
	makechange();
	statistics();
	rename("costomerinfo.txt",cosname);
}
struct name{
	char prod[16];
	int quan;
	};
void makechange(){				///Function for updating stock
	struct name pro[50];
	char name1[24];
        FILE *costomer;
        int cosqua;
        int k, i = 0;
        float price, total;
	costomer = fopen("costomerinfo.txt","r");
	
	while((fscanf(costomer,"%d %s  %d  %f  %f",&k,name1,&cosqua,&price,&total) != EOF)){
		change(name1,cosqua);
		strcpy(pro[i].prod,name1);
		
		pro[i].quan = cosqua;
		i++;
	} 
	fclose(costomer);		
}
int searchs(char name[]){			//Function for searching in costomer bill
	char name1[16];
	int cosqua, k;
	float price, total;
	FILE *fp;
	fp = fopen("costomerinfo.txt","r");
	while((fscanf(fp,"%d %s  %d  %f  %f",&k,name1,&cosqua,&price,&total) != EOF)){
		if(strcmp(name,name1) == 0){
			return cosqua;
		}
	}
	fclose(fp);
	return 0;
}
void statistics(){			//Function of STATISTICS
	int cosqua, s;
	char name[16];
	FILE *fp, *cp, *new;
	fp = fopen("statistic.txt","a+");
	rename("statistic.txt","statistic1.txt");
	new = fopen("statistic.txt","a+");
	cp = fopen("costomerinfo.txt","r");
	while((fscanf(fp,"%s  %d",name,&cosqua) != EOF)){
		s = searchs(name);
		fprintf(new,"%s  %d\n",name,s+cosqua);
	}
	fclose(fp);
	fclose(new);
	fclose(cp);
	remove("statistic1.txt");
}
void printstatistics(){			//Function for PRINTING THE STATISTICS
	FILE *fp, *cp;
	char name[16];
	int qua;
	fp = fopen("statistic.txt","r");
	rename("statistic.txt","statistic1.txt");
	cp = fopen("statistic.txt","a+");
	addstr("Name	Quantity sold\n");
	while(fscanf(fp,"%s  %d",name,&qua) != EOF){
		printw("%s	%d\n",name,qua);
		fprintf(cp,"%s  %d\n",name,0);
	}
	fclose(cp);
	fclose(fp);
	remove("statistic1.txt");
	refresh();
	getch();
}	
void change(char name1[],int cosqua){
	FILE *fp, *cp;
	char name[16];
	int ID, qua;
	float price, tax, dis;
	fp = fopen("file.txt","r");
	rename("file.txt","file1.txt");
	cp = fopen("file.txt","a+");
	while(fscanf( fp,"%d    %s      %f      %d      %f      %f",&ID,name,&price,&qua,&tax,&dis) != EOF){
		if(strcmp(name,name1) == 0){
			fprintf( cp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua - cosqua,tax,dis);
		}
		else{
			fprintf( cp, "%d       %s      %f      %d      %f      %f\n",ID,name,price,qua,tax,dis);
		}
	}
	fclose(fp);
	fclose(cp);
	remove("file1.txt");

}			 
void removeitem(){				//Function for REMOVING AN ITEM FROM THE CART
	char name[24], remo[24];
        FILE *fp;
        FILE *cp;
        int cosqua;
        int j = 1, k;
        float price, total;
        fp = fopen("costomerinfo.txt","r");
	rename("costomerinfo.txt","costomerinfo1.txt");
	cp = fopen("costomerinfo.txt","a+");	
	addstr("Enter the name of the product that has to be removed from billing\n");
	scanw("%s",remo);
	while((fscanf(fp,"%d %s  %d  %f  %f",&k,name,&cosqua,&price,&total) != EOF)){
		if(strcmp(name,remo) == 0){
			printw("Match found");
			/* Do nothing*/
		}
		else{
			fprintf(cp,"%d  %s     %d  %f  %f\n", j, name, cosqua, price, total);
			j++;
		}
	}
	refresh();
	getch();
	fclose(fp);
	fclose(cp);
	remove("costomerinfo1.txt");
}
			
