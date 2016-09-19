	       //*********** MEDICAL SHOP MANAGEMENT ****************\\

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
#include<string.h>
#include<process.h>

//__________________Global Variable_________________________________________\\
  int pos;
  char date[10],_time[10];
//__________________________________________________________________________\\

//______________________Functions for Date and Time_________________________\\

void set_date()
{
   ofstream fout("date.txt", ios::out);
   char *datestr;
   fout<<_strdate(datestr);
}
void get_date()
{  ifstream fin("date.txt", ios::in);
   fin.seekg(0);
   int i=0;
   while(fin)
   {  fin.get(date[i]);
      i++;
   }
}
void set_time()
{
   ofstream fout("time.txt", ios::out);
   char *timestr;
   fout<<_strtime(timestr);
}
void get_time()
{  ifstream fin("time.txt", ios::in);
   fin.seekg(0);
   int i=0;
   while(fin)
   {  fin.get(_time[i]);
      i++;
   }
}
//__________________________________________________________________________\\

//______________________Functions Prototypes________________________________\\
void front_page();
void refresh();
int  search(char n[20]);
void modify(char n[20],int q,int a);
void bill();
void sell();
void last_page();
//__________________________________________________________________________\\

//__________________Class for details of Medicines__________________________\\
class medi
{   char mname[20];
    char batch[10];
    struct exp{int mm,yy;}d;
    float mrp,rate,vat,amount;
  public:
    int stock;
    float total;
    char* get_mname()
     {  return mname;  }
    float get_mrp()
     {  return mrp;    }
    int check_date();
    void input();
    void display();
    void bill(int);
}me;
int medi::check_date()
{  get_date();
   int m,y;
   m=(date[0]*10)+date[1];
   y=(date[6]*10)+date[7];
   if(d.yy<=y)
     if(d.mm<=m)
       return 1;
   return 0;
}
void medi::input()
{
  char ename[8];
  cout<<"\n\tEnter name of Medicine::";
  cin>>mname;
  strcat(mname," ");
  cin>>ename;
  strcat(mname,ename);
  cout<<"\n\tEnter batch no::";
  cin>>batch;
  cout<<"\n\tEnter expiry date::";
  cout<<"\n\t\tEnter month::";
  cin>>d.mm;
  cout<<"\n\t\tEnter year::";
  cin>>d.yy;
  cout<<"\n\tEnter MRP::";
  cin>>mrp;
  cout<<"\n\tHow much are there in the stock::";
  cin>>stock;
  cout<<"\n\tEnter Rate::";
  cin>>rate;
  cout<<"\n\tEnter Value Added Tax::";
  cin>>vat;
}
void medi::display()
{
  cout<<"\n\n\n  Medicine name";
  cout<<"\t\tBatch no.";
  cout<<"\tExpiry Date";
  cout<<"\tMrp";
  cout<<"\t\tRate\n  ";
  cout.write(mname,20);
  cout<<"\t";
  cout.write(batch,10);
  cout<<"\t   "<<d.mm<<"/"<<d.yy<<"\t\t   "<<mrp<<"\t   "<<rate;
}
void medi::bill(int qty)
{
  cout.write(mname,20);
  cout<<"\t"<<d.mm<<"/"<<d.yy<<"\t"<<mrp<<"\t"<<qty<<"\t"<<total;
}
//__________________________________________________________________________\\



//__________________________Main Function___________________________________\\
void main()
{  front_page();
   set_date();
   set_time();
   refresh();
   menu:
   { clrscr();
     int c;
     char ch;
     fstream f;
     gotoxy(64,1);
     cout<<"DATE - "; get_date(); cout<<date;
     cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
     set_time(); get_time(); cout<<_time<<"_";
     cout<<"\n\n\t     MENU:\n";
     cout<<"\n\t\t1.Enter new stock";
     cout<<"\n\t\t2.Modify record";
     cout<<"\n\t\t3.See a record";
     cout<<"\n\t\t4.Sell a medicine";
     cout<<"\n\t\t5.Exit";
     cout<<"\n\n\t\tEnter your choice:";
     cin>>c;
     switch(c)
     {   case 1:medi ob;
		f.open("mdb.txt",ios::app);
		do
		{ clrscr();
		  gotoxy(64,1);
		  cout<<"DATE - "; get_date(); cout<<date;
		  cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
		  set_time(); get_time(); cout<<_time<<"_";
		  ob.input();
		  f.write((char*)&ob,sizeof(ob));
		  cout<<"\n\n\tDo you want to enter more(y/n):";
		  cin>>ch;
		}while(ch=='y' || ch=='Y');
		f.close();
		goto menu;
	 case 2:char mname[20],ename[8];
		int qty;
		do
		{ clrscr();
		  gotoxy(64,1);
		  cout<<"DATE - "; get_date(); cout<<date;
		  cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
		  set_time(); get_time(); cout<<_time<<"_";
		  cout<<"\n\n\tEnter name of medicine:";
		  cin>>mname;
		  strcat(mname," ");
		  cin>>ename;
		  strcat(mname,ename);
		  cout<<"\n\tEnter new stock:";
		  cin>>qty;
		  modify(mname,qty,1);
		  cout<<"\n\n\tDo you want to enter more(y/n):";
		  cin>>ch;
		}while(ch=='y' || ch=='Y');
		goto menu;
	 case 3:char name[20];
		int ans;
		do
		{ clrscr();
		  gotoxy(64,1);
		  cout<<"DATE - "; get_date(); cout<<date;
		  cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
		  set_time(); get_time(); cout<<_time<<"_";
		  cout<<"\n\t\tEnter the name of medicine:";
		  cin>>name;
		  char ename[8];
		  strcat(name," ");
		  cin>>ename;
		  strcat(name,ename);
		  ans=search(name);
		  if(ans)
		    me.display();
		  else
		    cout<<"\n\n\tSORRY!! Medicine not found";
		  cout<<"\n\n\n\n\n\n\tDo you want to search more(y/n):";
		  cin>>ch;
		}while(ch=='y' || ch=='Y');
		goto menu;
	 case 4:sell();
		goto menu;
	 case 5:goto exit;
	 default:cout<<"\n\n\tWrong choice!!!";
		 getch();
		 goto menu;
     }
   }
   exit:
   last_page();
   delay(720);
}
//__________________________________________________________________________\\

//________________________Functions Definitions_____________________________\\
void front_page()
{
   clrscr();
   char S=1,U=2;
   gotoxy(64,1);
   cout<<"DATE - "; get_date(); cout<<date;
   cout<<"\n_______________________________________________________________TIME - ";
   set_time(); get_time(); cout<<_time<<"_";
   cout<<"\n\n\tBY -- SAMARTH SANGHI "<<S<<"\n\t\t & UTKARSH KAHAR "<<U<<U;
   cout<<"\n\n\tKENDRIYA VIDYALAYA SEONI";
   cout<<"\n\n\tGUIDED BY : S.K.SAHU SIR";
   cout<<"\n\n\n\t\t*****************************************";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\tMEDICAL SHOP MANAGEMENT\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*\t\t\t\t\t*";
   cout<<"\n\t\t*****************************************";
   cout<<"\n\n\n\t\t\t\t\t\t      Press any key to continue";
   getch();
}

void refresh()
{
   int ans,i=1;
   char ch;
   medi ob;
   fstream f1("mdb.txt",ios::in);
   fstream f2("temp.txt",ios::out);
   f1.seekg(0);
   if(f1)
   { clrscr();
     gotoxy(64,1);
     cout<<"DATE - "; get_date(); cout<<date;
     cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
     set_time(); get_time(); cout<<_time<<"_";
     cout<<"\n\n\n\tYou have following expired medicines:-";
     while(f1)
     { f1.read((char*)&ob,sizeof(ob));
       ans=ob.check_date();
       if(ans)
       { cout<<"\n\n\t"<<i<<"."<<ob.get_mname();
	 cout<<"\n\t    Do you want to remove this medicine from the record(y/n):";
	 cin>>ch;
	 if(ch=='n' || ch=='N')
	   f2.write((char*)&ob,sizeof(ob));
       }
       else
	 f2.write((char*)&ob,sizeof(ob));
       i++;
     }
     f1.close();
     f2.close();
     remove("mdb.txt");
     rename("temp.txt","mdb.txt");
   }
}

int search(char n[20])
{
   int ans;
   medi ob;
   fstream f("mdb.txt",ios::in);
   f.seekg(0);
   while(f)
   { f.read((char*)&ob,sizeof(ob));
     if(ans!=strcmp(n,ob.get_mname()))
     {  ans=1;
	me=ob;
	pos=f.tellg();
	break;
     }
     else
       ans=0;
   }
   f.close();
   return ans;
}

void modify(char n[20],int q,int a)
{ int ans;
  fstream f1("mdb.txt",ios::in);
  fstream f2("temp.txt",ios::out);
  medi ob;
  ans=search(n);
  if(ans)
  {  if(a==1)
       me.stock+=q;
     if(a==2)
       me.stock-=q;
     f1.seekg(0);
     while(f1)
     {  if(f1.tellg()!=pos)
	{ f1.read((char*)&ob,sizeof(ob));
	  f2.write((char*)&ob,sizeof(ob));
	}
	else
	  f2.write((char*)&me,sizeof(me));
     }
     f1.close();
     f2.close();
     remove("mdb.txt");
     rename("temp.txt","mdb.txt");
  }
  else
    cout<<"\n\n\n\t\tMedicine not found!!!";
}

void sell()
{
   char name[20],ename[8];
   int qty[20],count=0,ans;
   float total=0;
   medi ob[20];
   char ch;
   do
   { clrscr();
     gotoxy(64,1);
     cout<<"DATE - "; get_date(); cout<<date;
     cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
     set_time(); get_time(); cout<<_time<<"_";
     cout<<"\n\n\tEnter name of medicine:";
     cin>>name;
     strcat(name," ");
     cin>>ename;
     strcat(name,ename);
     ans=search(name);
     if(ans)
     { cout<<"\n\n\tEnter Quantity:";
       cin>>qty[count];
       me.total=me.get_mrp()*qty[count];
       ob[count]=me;
       count++;
       modify(name,qty[count],2);
     }
     else
       cout<<"\n\n\n\tSorry not in stock!!!";
     cout<<"\n\n\n\tDo you want to sell more(y/n):";
     cin>>ch;
   }while((ch=='y' || ch=='Y') && count<=20);
   if(count==20)
     cout<<"\n\n\tSell only 20 medicines in one bill";
   cout<<"\n\n\n\t\tPress enter for bill";
   getch();
   clrscr();
   gotoxy(64,1);
   cout<<"DATE - "; get_date(); cout<<date;
   cout<<"\n_________MEDI SOFT_____________________________________________TIME - ";
   set_time(); get_time(); cout<<_time<<"_";
   cout<<"\n\n\n\t\t\t\tBILL\n\n";
   cout<<"\n\nS.No.  Medicine name";
   cout<<"\tExpiry Date";
   cout<<"\tMrp";
   cout<<"\tQuantity";
   cout<<"\tTotal\n";
   cout<<"________________________________________________________________________________\n";
   for(int i=0;i<count;i++)
   { cout<<"\n "<<i+1<<".  ";
     ob[i].bill(qty[i]);
   }
   for(i=0;i<count;i++)
     total+=ob[i].total;
   cout<<"\n________________________________________________________________________________\n";
   cout<<"\nTOTAL\t\t\t\t\t\t\t"<<total;
   cout<<"\n________________________________________________________________________________\n";
}

void last_page()
{
   char S=1,U=2;
   int x,y;
   for(x=0;x<25;x++)
   { clrscr();
     gotoxy(x,5);
     cout<<"BY -- UTKARSH KAHAR "<<U<<U;
     delay(70);
   }
   for(x=0;x<35;x++)
   { clrscr();
     gotoxy(25,5);
     cout<<"BY -- UTKARSH KAHAR "<<U<<U;
     gotoxy(x,7);
     cout<<" & SAMARTH SANGHI "<<S;
     delay(70);
   }
   delay(540);
   cout<<"\n\n\n\t\t\t<<<<< MEDICAL SHOP MANAGEMENT >>>>>";
   cout<<"\n\n\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t--------+--------";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\t\t\t\t\t|";
   cout<<"\n\n\n\t\t\t\t\t\t\t\tEnter ";
   getch();
   for(y=0;y<15;y++)
   { clrscr();
     gotoxy(30,y);
     cout<<"#### THANK YOU ####";
     delay(30);
   }
}
//__________________________________________________________________________\\

		      //********** THE END *************\\