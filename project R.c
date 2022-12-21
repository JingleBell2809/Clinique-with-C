#include <stdio.h>
#include<windows.h>
#include <string.h>
#include <ctype.h>
#include<time.h>

void gotoxy(int x,int y){
  COORD c = { x, y };
  SetConsoleCursorPosition ( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

struct people{
    char Username[20],Pass[10],phone[20],email[20],c_name[20],c_sex[10],c_age[5];
}p1,p2;

struct item{
    char name_item[50];
    int stock,sell,price;
};

void topic(){
    gotoxy(0,0);printf("========================================================================================================================");
    gotoxy(50,2);printf("***  KITTY  CLINIC   ***");
    gotoxy(0,4);printf("========================================================================================================================");
}

int admin_member(){ //*1
    system("cls");
    int select;
    topic();
    gotoxy(54,8);printf("--------------");
    gotoxy(53,9);printf("|   1.ADMIN    |");
    gotoxy(54,10);printf("--------------");
    gotoxy(60,13);printf("OR");
    gotoxy(54,16);printf("--------------");
    gotoxy(53,17);printf("|   2.MEMBER   |");
    gotoxy(54,18);printf("--------------");
    gotoxy(0,21);printf("Please select '1' or '2' : ");scanf("%d",&select);
    return select;
}

admin_login(){
    int i=0;
    system("cls");
    topic();
    FILE *fp= fopen("pass_admin.txt","r");
    fscanf(fp,"%s %s", p1.Username,p1.Pass);
    fclose(fp);
    gotoxy(54,7);printf("---------------");
    gotoxy(53,8);printf("|   1.LOG IN    |");
    gotoxy(54,9);printf("---------------");
    gotoxy(40,12);printf("USERNAME : ");
    gotoxy(40,15);printf("PASSWORD : ");
    gotoxy(50,12);scanf("%s",&p2.Username);
    gotoxy(51,15);
    for(i=0;i<8;i++){
        p2.Pass[i]=getch();
        printf("*");
    }
    while(strcmp(p2.Username,p1.Username)!=0||strcmp(p2.Pass,p1.Pass)!=0){
        gotoxy(40,12);printf("USERNAME :                          ");
        gotoxy(40,15);printf("PASSWORD :                         ");
        gotoxy(47,17);printf("**Please enter again**");
        gotoxy(50,12);scanf("%s",&p2.Username);
        gotoxy(51,15);
        for(i=0;i<8;i++){
            p2.Pass[i]=getch();
            printf("*");
        }
    }
}

int admin_select(){ //*2

    //*************************************************
    system("cls");
    int select;
    topic();
    gotoxy(57,10);printf("1.EDIT");
    gotoxy(57,12);printf("2.DELETE");
    gotoxy(57,14);printf("3.ADD");
    gotoxy(57,16);printf("4.ACCOUNT");
    gotoxy(57,18);printf("5.LOGOUT");
    gotoxy(0,20);printf("Please select '1' '2' '3' '4' or '5' : ");scanf("%d",&select);
    return select;
}

admin_edit(){ //*3
    int count_line,num_edit,num_pro,i,num_price;
    char c[500],name_edit[50],h[50],y_n;

    do{system("cls");
        topic();
        FILE *fp= fopen("Stock.txt","r");
        count_line=0;
        while(fgets(c,500,fp)!=NULL){
            count_line+=1;
        }
        fseek( fp, 0, SEEK_SET );
        struct item items[count_line/2];

        for(int a=0;a<count_line/2;a++){
            fgets(items[a].name_item,50,fp);
            fscanf(fp,"%d %d %d",&items[a].stock,&items[a].sell,&items[a].price);
            fgets(h,50,fp);
        }fclose(fp);

        gotoxy(60,6);printf("EDIT");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }

        do{gotoxy(0,12+i);printf("Please select number to EDIT :        ");
        gotoxy(31,12+i);scanf("%d",&num_edit);
        }while(count_line/2<num_edit);
        fflush(stdin);
        gotoxy(0,13+i);printf("Enter product name :                                                  ");
        gotoxy(21,13+i);scanf("%s",&name_edit);
        strcat(name_edit,"\n");
        gotoxy(0,14+i);printf("Enter product quantity :                                                  ");
        gotoxy(25,14+i);scanf("%d",&num_pro);
        gotoxy(0,15+i);printf("Enter product price :                     ");
        gotoxy(23,15+i);scanf("%d",&num_price);
        gotoxy(37,10+num_edit);printf("                                                                       ");
        gotoxy(37,10+num_edit);printf("%s",name_edit);
        gotoxy(64,10+num_edit);printf("%d",num_price);
        gotoxy(85,10+num_edit);printf("%d",num_pro);

        strcpy(items[num_edit-1].name_item,name_edit);
        items[num_edit-1].stock=num_pro;
        items[num_edit-1].sell=0;
        items[num_edit-1].price=num_price;

        FILE *fp1= fopen("Stock.txt","w");
        for(int a=0;a<count_line/2;a++){
            fprintf(fp1,"%s%d %d %d\n",items[a].name_item,items[a].stock,items[a].sell,items[a].price);
        }fclose(fp1);
        gotoxy(0,16+i);printf("Do you want to continue editing(y/n) :   ");gotoxy(39,16+i);scanf("%s",&y_n);
    }while(tolower(y_n)=='y');

}

admin_delete(){//*3
    system("cls");
    int count_line,i,num;
    char c[500],name_edit[50],h[50],y_n;
    do{topic();
        FILE *fp= fopen("Stock.txt","r");
        count_line=0;
        while(fgets(c,500,fp)!=NULL){
            count_line+=1;
        }
        fseek( fp, 0, SEEK_SET );
        struct item items[count_line/2];

        for(int a=0;a<count_line/2;a++){
            fgets(items[a].name_item,50,fp);
            fscanf(fp,"%d %d %d",&items[a].stock,&items[a].sell,&items[a].price);
            fgets(h,50,fp);
        }fclose(fp);

        gotoxy(59,6);printf("DELETE");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        gotoxy(0,12+i);printf("Please select number to DELETE : ");gotoxy(33,12+i);scanf("%d",&num);
        for(int a=0;a<count_line/2-num;a++){
            items[num+a-1]=items[num+a];
        }
        FILE *fp1= fopen("Stock.txt","w");
        for(int a=0;a<count_line/2-1;a++){
            fprintf(fp1,"%s%d %d %d\n",items[a].name_item,items[a].stock,items[a].sell,items[a].price);
        }fclose(fp1);
        system("cls");
        topic();
        gotoxy(59,6);printf("DELETE");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2-1;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        gotoxy(0,13+i);printf("Please select number to DELETE : %d",num);
        gotoxy(0,14+i);printf("Do you want to continue editing(y/n) :   ");gotoxy(39,14+i);scanf("%s",&y_n);
        system("cls");}while(tolower(y_n)=='y');

}

admin_add(){//*3
    int count_line,i,num,price,many;
    char c[500],name_add[50],h[50],y_n;
    system("cls");

    do{topic();
        FILE *fp= fopen("Stock.txt","r");
        count_line=0;
        while(fgets(c,500,fp)!=NULL){
            count_line+=1;
        }
        fseek( fp, 0, SEEK_SET );
        struct item items[count_line/2+1];

        for(int a=0;a<count_line/2;a++){
            fgets(items[a].name_item,50,fp);
            fscanf(fp,"%d %d %d",&items[a].stock,&items[a].sell,&items[a].price);
            fgets(h,50,fp);
        }fclose(fp);
        gotoxy(59,6);printf("  ADD");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        gotoxy(0,12+i);printf("Please select number to ADD :         ");
        gotoxy(29,12+i);scanf("%d",&num);
        gotoxy(0,13+i);printf("Enter product name :                                               ");
        gotoxy(20,13+i);scanf("%s",&name_add);
        strcat(name_add,"\n");
        gotoxy(0,14+i);printf("Enter product quantity :                                                ");
        gotoxy(24,14+i);scanf("%d",&many);
        gotoxy(0,15+i);printf("Enter product price :                                                ");
        gotoxy(21,15+i);scanf("%d",&price);

        for(int a=0;a<count_line/2-num+1;a++){
            items[count_line/2-a]=items[count_line/2-a-1];
        }
        strcpy(items[num-1].name_item,name_add);
        items[num-1].stock=many;
        items[num-1].sell=0;
        items[num-1].price=price;
        FILE *fp1= fopen("Stock.txt","w");
        for(int a=0;a<count_line/2+1;a++){
            fprintf(fp1,"%s%d %d %d\n",items[a].name_item,items[a].stock,items[a].sell,items[a].price);
        }fclose(fp1);

        system("cls");
        topic();
        gotoxy(59,6);printf("   ADD");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2+1;i++){
                gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
                gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        gotoxy(0,11+i);printf("Please select number to ADD :%d",num);
        gotoxy(0,12+i);printf("Enter product name :%s",name_add);
        gotoxy(0,13+i);printf("Enter product quantity :%d",many);
        gotoxy(0,14+i);printf("Enter product price :%d",price);

        gotoxy(0,15+i);printf("Do you want to continue editing(y/n) :   ");gotoxy(39,15+i);scanf("%s",&y_n);
        system("cls");
    }while(tolower(y_n)=='y');
}

int member(){ //**1
    int select;
    topic();
    gotoxy(54,8);printf("--------------");
    gotoxy(53,9);printf("|   1.LOGIN    |");
    gotoxy(54,10);printf("--------------");
    gotoxy(60,13);printf("OR");
    gotoxy(53,16);printf("---------------");
    gotoxy(52,17);printf("|   2.SIGN IN   |");
    gotoxy(53,18);printf("---------------");
    gotoxy(0,21);printf("Please select '1' or '2' :   ");
    gotoxy(27,21);scanf("%d",&select);
    system("cls");
    return select;
}

member_signin(){ //**2
    topic();
    gotoxy(54,7);printf("---------------");
    gotoxy(53,8);printf("|   1.SIGN IN    |");
    gotoxy(54,9);printf("---------------");
    gotoxy(40,12);printf("USERNAME : ");scanf("%s",&p1.Username);
    gotoxy(40,14);printf("PASSWORD : ");
    for(int i=0;i<8;i++){
            p1.Pass[i]=getch();
            printf("*");
    }
    gotoxy(40,16);printf("TELEPHONE : ");scanf("%s",&p1.phone);
    gotoxy(40,18);printf("E-MAIL : ");scanf("%s",&p1.email);
    gotoxy(40,20);printf("CAT NAME : ");scanf("%s",&p1.c_name);
    gotoxy(40,22);printf("CAT SEX : ");scanf("%s",&p1.c_sex);
    gotoxy(40,24);printf("CAT AGE : ");scanf("%s",&p1.c_age);
    FILE *fp= fopen("pass_member.txt","a");
    fprintf(fp,"%s %s %s %s %s %s\n%s\n",p1.Username,p1.Pass,p1.phone,p1.email,p1.c_sex,p1.c_age,p1.c_name);
    fclose(fp);
    system("cls");
}

member_lognin(){
    topic();
    gotoxy(54,7);printf("---------------");
    gotoxy(53,8);printf("|   1.LOG IN    |");
    gotoxy(54,9);printf("---------------");
    gotoxy(40,12);printf("USERNAME : ");
    gotoxy(40,15);printf("PASSWORD : ");
    gotoxy(51,12);scanf("%s",&p2.Username);
    gotoxy(51,15);
    for(int i=0;i<8;i++){
            p2.Pass[i]=getch();
            printf("*");
    }

    FILE *fp= fopen("pass_member.txt","r");
    do{fscanf(fp,"%s %s %s %s %s %s",&p1.Username,&p1.Pass,&p1.phone,&p1.email,&p1.c_sex,&p1.c_age);
        fscanf(fp,"%s",p1.c_name);
        if(feof(fp)){
            gotoxy(40,12);printf("USERNAME :                 ");
            gotoxy(40,15);printf("PASSWORD :                 ");
            gotoxy(55,17);printf("**Please enter again**");
            gotoxy(51,12);scanf("%s",&p2.Username);
            gotoxy(51,15);
            for(int i=0;i<8;i++){
            p2.Pass[i]=getch();
            printf("*");}
            fseek( fp, 0, SEEK_SET );
            }
    }while(strcmp(p2.Username,p1.Username)!=0||strcmp(p2.Pass,p1.Pass)!=0);
    fclose(fp);
}

int menu_select(){ //**2
    system("cls");
    int select;
    topic();
    gotoxy(53,8);printf("1.MENU ");
    gotoxy(51,12);printf("2.LOG OUT");
    gotoxy(15,15);printf("Please select '1' or '2' : ");scanf("%d",&select);
    system("cls");
    return select;
}

menu_(int *items_stock,int *items_sell,int pro_quan){
    *items_stock-=pro_quan;
    *items_sell+=pro_quan;
}

char menu(){ //**3
    int count_line,i,total=0,line_income;
    //time
    time_t timer;
    struct tm* tm_info;
    char dmy_cp[20];
    time(&timer);
    tm_info = localtime(&timer);
    strftime(dmy_cp, 20, "%d/%m/%Y", tm_info);

    char c[500],h[50],c_p;
    FILE *fp= fopen("Stock.txt","r");
    count_line=0;
    while(fgets(c,500,fp)!=NULL){
        count_line+=1;
    }
    fseek( fp, 0, SEEK_SET );
    struct item items[count_line/2];
    for(int a=0;a<count_line/2;a++){
        fgets(items[a].name_item,50,fp);
        fscanf(fp,"%d %d %d",&items[a].stock,&items[a].sell,&items[a].price);
        fgets(h,50,fp);
    }fclose(fp);
    int buy_all[count_line/2];
    for(int a=0;a<count_line/2;a++){
        buy_all[a]=0;
    }
    do{system("cls");
        topic();
        gotoxy(60,6);printf(" MENU");
        gotoxy(59,7);printf("------");
        gotoxy(23,9);printf("NUMBER");
        gotoxy(43,9);printf("PRODUCT");
        gotoxy(63,9);printf("PRICE");
        gotoxy(83,9);printf("STOCK");
        for(i=0;i<count_line/2;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        int sel_menu,pro_quan;
        gotoxy(0,13+i);printf("Please select NUMBER '1-%d' : ",count_line/2);
        gotoxy(count_line/20+29,13+i);scanf("%d",&sel_menu);
        gotoxy(0,14+i);printf("Please select Product quantity : ");
        gotoxy(33,14+i);scanf("%d",&pro_quan);
        buy_all[sel_menu-1]+=pro_quan;
        total+=items[sel_menu-1].price;
        menu_(&items[sel_menu-1].stock,&items[sel_menu-1].sell,pro_quan);
        FILE *fp1= fopen("Stock.txt","w");
        for(int a=0;a<count_line/2;a++){
            fprintf(fp1,"%s%d %d %d\n",items[a].name_item,items[a].stock,items[a].sell,items[a].price);
        }fclose(fp1);

        line_income=0;
        char cc[100];
        FILE *fpp= fopen("Income.txt","r");
        while(fgets(cc,100,fpp)!=NULL){
            line_income+=1;
        }
        int price_in[line_income],v=0;
        char dmy[line_income][20];
        fseek( fp, 0, SEEK_SET );
        for(int a=0;a<line_income;a++){
            fscanf(fp,"%s %d",&dmy[a],&price_in[a]);
            if(strcmp(dmy[a],dmy_cp)==0){
                price_in[a]+=items[sel_menu-1].price;
                v=1;
            }
        }fclose(fpp);

        if(v==1){
            FILE *fpp1= fopen("Income.txt","w");
            for(int a=0;a<line_income;a++){
                fprintf(fpp1,"%s %d\n",dmy[a],price_in[a]);
            }fclose(fpp1);
        }else{
            FILE *fpp2= fopen("Income.txt","a");
            fprintf(fpp2,"%s %d\n",dmy_cp,items[sel_menu-1].price);
            fclose(fpp2);
        }
        for(i=0;i<count_line/2;i++){
            gotoxy(29,11+i);printf("                                                       ");
        }
        for(i=0;i<count_line/2;i++){
            gotoxy(25,11+i);printf("%d",1+i);gotoxy(37,11+i);printf("%s",items[i].name_item);
            gotoxy(64,11+i);printf("%d",items[i].price);gotoxy(85,11+i);printf("%d",items[i].stock);
        }
        gotoxy(0,15+i);printf("Select the next product, press 'C' or go to the payment page, press 'P' : ");
        gotoxy(74,15+i);scanf("%s",&c_p);}while(tolower(c_p)=='c');

        system("cls");
        int paid,change;
        topic();
        gotoxy(58,6);printf("PAYMENT");
        gotoxy(57,7);printf("---------");
        gotoxy(5,9);printf("Total amount : %d",total);
        gotoxy(5,10);printf("Enter amount of paid : ");scanf("%d",&paid);
        gotoxy(0,12);printf("------------------------------------------------------------------------------------------------------------------------");
        change=paid-total;
        gotoxy(5,14);printf("Change money total : %d",change);
        gotoxy(0,16);printf("------------------------------------------------------------------------------------------------------------------------");

        gotoxy(5,18);printf("1000  Baht : %d",change/1000);change%=1000;
        gotoxy(5,19);printf("500   Baht : %d",change/500);change%=500;
        gotoxy(5,20);printf("100   Baht : %d",change/100);change%=100;
        gotoxy(5,21);printf("50    Baht : %d",change/50);change%=50;
        gotoxy(5,22);printf("20    Baht : %d",change/20);change%=20;
        gotoxy(5,23);printf("10    Baht : %d",change/10);change%=10;
        gotoxy(5,24);printf("5     Baht : %d",change/5);change%=5;
        gotoxy(5,25);printf("2     Baht : %d",change/2);change%=2;
        gotoxy(5,26);printf("1     Baht : %d",change);
        getche();

        system("cls");
        int total_price=0,y=17;
        topic();
        gotoxy(58,6);printf("RECEIPT");
        gotoxy(57,7);printf("---------");
        gotoxy(10,10);printf("User Name : %s",p1.Username);
        gotoxy(46,10);printf("Telephone : %s",p1.phone);
        gotoxy(86,10);printf("E-mail : %s",p1.email);
        gotoxy(10,12);printf("Cat Name : %s",p1.c_name);
        gotoxy(46,12);printf("Cat Sex : %s",p1.c_sex);
        gotoxy(86,12);printf("Cat Age : %s",p1.c_age);
        gotoxy(10,15);printf("    #       |        Product Name            |    Unit Price    |    Quantity     |  Total Price");
        gotoxy(10,16);printf("___________________________________________________________________________________________________");
        for(int r=0;r<count_line/2;r++){
            if(buy_all[r]!=0){
                gotoxy(10,y);printf("            |                                |                  |                 |          ");
                gotoxy(15,y);printf("%d",y-16);gotoxy(25,y);printf("%s",items[r].name_item);
                gotoxy(63,y);printf("%d",items[r].price);gotoxy(83,y);printf("%d",buy_all[r]);
                gotoxy(100,y);printf("%d",buy_all[r]*items[r].price);
                total_price+=buy_all[r]*items[r].price;
                y++;
            }
        }
        gotoxy(70,y+2);printf("Total Amount :  %d  Baht",total_price);
        getche();
}

logout(){
    system("cls");
    topic();
    gotoxy(25,7);printf("*****   *   *    ****    **    *    *  *       *   *    ***     *   *");
    gotoxy(25,8);printf("  *     *   *    *  *    * *   *    * *        *   *   *   *    *   *");
    gotoxy(25,9);printf("  *     *****    ****    *  *  *    **          ***   *     *   *   *");
    gotoxy(25,10);printf("  *     *   *    *  *    *   * *    * *          *     *   *    *   *");
    gotoxy(25,11);printf("  *     *   *    *  *    *    **    *  *         *      ***     *****");
    getch();
    system("cls");
}

receipt_addmin(){
    system("cls");
   topic();
   char dmy[15],dmy_put[8],dmy2[15];
   int price_in,Total=0;
   gotoxy(58,6);printf("ACCOUNT");
   gotoxy(57,7);printf("---------");
   gotoxy(10,8);printf("Enter the month and year(12/2000) : ");scanf("%s",&dmy_put);
   int line_income=0;
   char cc[100];
   FILE *fpp= fopen("Income.txt","r");
   while(fgets(cc,100,fpp)!=NULL){
        line_income+=1;
    }fseek( fpp, 0, SEEK_SET );
    gotoxy(30,10);printf("date / month / year");
    gotoxy(70,10);printf("total amount in 1 day");gotoxy(0,12);
    for(int a=0;a<line_income;a++){
        fscanf(fpp,"%s %d",&dmy,&price_in);
        strcpy(dmy2,dmy+3);
        if(strcmp(dmy2,dmy_put)==0){
            printf("%44s%37d\n",dmy,price_in);
            Total+=price_in;
        }
    }
    printf("          total amount in 1 month : %d",Total);
    getche();
}

main(){
    int select;
    do{select=admin_member();
        if(select==1){
            admin_login();
            do{select=admin_select();
                if(select==1){
                    admin_edit();
                }
                else if(select==2){
                    admin_delete();
                }
                else if(select==3){
                    admin_add();
                }
                else if(select==4){
                    receipt_addmin();
                }
            }while(select!=5);
        }
        else if(select==2){

            select=member();
        if(select==1){
                member_lognin();
                select=menu_select();
                if(select==1){
                    menu();
                    logout();
                }
            }
            else if(select==2){
                member_signin();
                select=1;
            }
        }
    }while(1);
}
