
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstring>
#include<cstdlib> //for c_str() function that used in copy function 
#include<sstream>
#include<time.h>//for automatic date



using namespace std;

void temp_file_clear();//for clearing temp file
void copy_content(string a,string b); //global declaration
void number_system_put(int n1);//
int number_system_get();//account number automation 
string yearadd(string date1,int year) ;//for calculating year
void user_menu(int);
void clrscr();
int total1 = 0;
int pend = 0;
int block = 0;

void clrscr()
    {
    cout << string( 100, '\n' );
    }
/* user manual class Start*/
class manual
{
	public:
		 void userguide();
};
void manual :: userguide()
{
	
	cout<<string(26, '*');
	cout<<"* \nShared Wallet System *\n";
	cout<<string(26, '*');
	cout<<endl;
	cout.setf(ios::left);
	cout<<setw(10)<<"Name"<<":"<<setw(20)<<"SharedWallet"<<endl;
	cout<<setw(10)<<"Platform"<<":"<<setw(20)<<"Windows"<<endl;
	cout<<setw(10)<<"Language"<<":"<<setw(20)<<"C++"<<endl;
	cout<<endl<<endl<<endl;
	/*cout<<"* Related Topics:"<<endl;
	cout<<string(26,'-')<<endl;
	cout<<"1. How to Open New Account ?"<<endl;
	cout<<"-> Use second option \"Open New Account\" "<<endl;
	*/
}
/* user manual class Start*/
class user 
{
	public:
	
	char fname[10],lname[10];
	string phone;
	string dob;

		user()
		{
			phone = '\0';
			dob = '\0';
		}
		~user()
		{}	
};

class Account : public user
{
	int accountNumber ;
	int passcode ;
	int balance;
	string type; //for account type
	public:
	Account()
	{
		accountNumber = 0;
		balance = 0;
		passcode = 0;
	}
	~Account(){}
	
	void CurrentBalance(int);	//balance check
	void createAccount(); 		//function for openning new account
	void showDetails(); 		//function for showing account details
	void searchDetails(int);	//function to search details of particular user
	void delete_details();		//function for deleting record
	void update_details(int); 	//function for updating record
	void login_user(int,int);	//login function
	void add(int,int);          //Add Money
	void deduct(int,int);	 	//Deduct Money
	void viewTr(int); //view all transections 
	void fund_tr(int); //For transfering fund between two users
	void ministatement(int); //function for ministatement
	void ask(int);
	void pending(int);
	//void block(int);
	//void updateToBlock(int);
};


void Account :: ask(int user_no){
	
	int ch;
	int flag = 0;
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	
	////////////////////////////////////////////////
	
	while(file_read)
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;

	if(file_read.eof())
	{
		break;
	}

	if(user_no == accountNumber)
	{
		cout<<"\n\tAccount Number is :"<<accountNumber;
		cout<<"\n\tName              :"<<fname<<" "<<lname;
		cout<<"\n\tAccount Type      :"<<type;
		cout<<"\n\tBalance           :"<<balance<<"/-CAD$";
		cout<<"\n\n\n";
		flag  = 1;
	}
	
	cout<<"\n Request sent from"<<user_no<<" to Mom and Dad";
	pend = user_no;
	cout<<"\n Request sent to Mom and Dad !";
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_read.close();
	
	
	
	
	
	
	////////////////////////////////////////////////
}
////////////////////////////////*/

void Account :: login_user(int user, int pass)
{	
	int flag = 0;

	//getting data from file
	ifstream file_read("cus_details.txt" ,ios::in);
	while(!file_read.eof())
	{

		file_read >> fname;
		file_read >>lname;
		file_read >>phone;
		file_read >>dob;
		file_read >>type;
		file_read >>accountNumber;
		file_read >>passcode;
		file_read >>balance;
		if(file_read.eof())
		{
			break;
		}
		if(user == accountNumber && pass == passcode)
		{
			cout<<"\n Login sucessful !"<<endl;
			user_menu(user);
			flag = 1;
		}
	
	}
	
	if(flag == 0 )
	{
		cout<<"\n User name & Passcode Not matched !"<<endl;
		
	}
	file_read.close();
	
}

void Account :: createAccount()
{
	
	cout << "\n\tEnter your First name :";
	cin >>fname;
	cin.clear();

	cout << "\n\tEnter Last name :";
	cin >>lname;
	cin.clear();

	string temp_phone;
	cout << "\n\tEnter phone number :";
	cin >>temp_phone;
	cin.clear();
	if(temp_phone.length()==10)
	{
		phone = temp_phone;
		
	}
	else
	{
	
		while(temp_phone.length() != 10)
		{
			cout<<"phone number must be 10 digit\n";
			cout<<"\n input phone number:";
			cin >> temp_phone;
			phone = temp_phone;	
		}
	}

	
	
	cout << "\n\tEnter Date of Birth :";
	cin >>dob;
	cin.ignore();
	
	char atype ='\0';
	cout <<"\n\tSelect Account Type(Savings S/Other O) :";
	cin >>atype;
	if(tolower(atype) == 's' )
	{
		type = "SAVINGS";
	}
	else
	{
		type = "OTHER";
	}
	accountNumber = number_system_get();
	
	cout << "\n\t Your Account Number :"<<accountNumber;

	cout << "\n\t Enter 4 digit Passcode ::";
	cin >> passcode;
	
	cout <<"\n\t Enter Primary Balance :";
	cin >>balance;

	ofstream file("cus_details.txt",ios::out | ios :: app);
	file << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	
	number_system_put(accountNumber);
	file.close();
}

void Account :: CurrentBalance(int user_no)
{
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	while(file_read)
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;

	if(file_read.eof())
	{
		break;
	}

	if(user_no == accountNumber)
	{
		
		cout<<"\n\tCurrent Balance           :"<<balance<<"/-CAD$";
		cout<<"\n\n\n";
	}
	
	
	}
	
	file_read.close();
}
void Account :: searchDetails(int user_no) //user_no for user session for only specified user can show
{
	int ch;
	int flag = 0;
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	//cout <<"\n\tEnter account  number:";
	//cin >>ch;
	//cin.clear();
	
	while(file_read)
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;

	if(file_read.eof())
	{
		break;
	}

	if(user_no == accountNumber)
	{
		cout<<"\n\tAccount Number is :"<<accountNumber;
		cout<<"\n\tName              :"<<fname<<" "<<lname;
		cout<<"\n\tPhone             :"<<phone;
		cout<<"\n\tDate of birth     :"<<dob;
		cout<<"\n\tAccount Type      :"<<type;
		cout<<"\n\tBalance           :"<<balance<<"/-CAD$";
		cout<<"\n\n\n";
		flag  = 1;
	}
	
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_read.close();
	
}
void Account ::delete_details()
{
	char ch[10];
	char buff;
	int flag = 0;
	string a = "cus_details.txt";
	string b = "temp.txt";
	
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	cout <<"\n\tEnter name:";
	cin >>ch;
	cin.clear();
	
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
		if(strcmp(fname,ch) == 0)
		{
			cout <<fname<<" "<<lname<<"\t"<<dob<<"\t"<<phone<<"\t"<<type
			<<"\t"<<accountNumber<<"\t"<<balance<<endl;
			flag  = 1;
		}
		else{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
		}
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	
	cout<<"\n\t Done Account Is Removed !\n";
	temp_file_clear();
	
}

/*start operator overloading (transfering amount)*/
void Account :: add(int user_no,int amt)
{
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			balance = balance + amt;
			_strdate(tr_date);

			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			
			tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl; 

	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n\t Done ! Amount Added\n";
	temp_file_clear();
	
}
void Account :: deduct(int user_no,int amt)
{
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	int flag = 0;
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			if(balance != 0 && balance > amt)
			{
			
				balance = balance - amt;
				_strdate(tr_date); //saving current date

				file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
					<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
					
				tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"DR"<<endl; 

				flag = 1;
			}
			else
			{
				
				cout<<"\nYour transaction can not be completed balance is Zero or Less than withdrawal amount !\n ";
				file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			}
	}
		
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	if(flag == 1)
	{
		cout<<"\n\t Done ! Amount Deducted\n";
		
	}
	temp_file_clear();
}
	
}
/*end operator overload*/
/*Start mini statement function */
void Account::ministatement(int user_no)
{
	int number,amount,flag = 0,pbalance = 0;
	string date,status;
	char today[9];
	_strdate(today);
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);

	while(file_read)
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;

	if(file_read.eof())
	{
		break;
	}

		if(user_no == accountNumber)
		{
			pbalance = balance;
		}
	}
	
	file_read.close();
	//transaction part
	
	cout<<"\n\n\n\n\n\n\n\n\n\n"<<endl;
	cout<<"\n\t Mini statement for "<<today<<endl;
	cout<<"\n";
	cout<<"\n\tAccount Number : "<<user_no<<endl;                //accountNumber -> user_no
	cout<<"\n\n";	
	
	ifstream tr_file_read("transec.txt" ,ios::in);
	//cin.clear();
	cout<<"\n\t"<<"Date"
	<<" | "<<"Amount"<<" | "<<"CR / DR "<<endl;
	
	while(tr_file_read)
	{
		tr_file_read >>number;
		tr_file_read >>date;
		tr_file_read >>amount;
		tr_file_read >>status;	
	if(tr_file_read.eof())
	{
		break;
	}

	if(user_no == number)
	{
		cout<<"\t"<<date<<" | "<<amount
				<<" | "<<status<<" | "<<endl ;
		flag  = 1;
	}
	
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";	
	}
	cout<<"\n\n";
	cout<<"Total Primary Balance :"<<pbalance<<"/."<<endl;
	tr_file_read.close();
	
}

/*End mini statement function */
/*Start Fund transfer function */
void Account::fund_tr(int user_no)
{
	int user2_no ,amt =0,flag = 0;
	char ans;
	
	cout <<"\nEnter Friends Account Numbber: ";
	cin >> user2_no;
	
	cout <<"\nEnter Amount : ";
	cin >> amt;
	
	string a = "cus_details.txt";
	string b = "temp.txt";
	char tr_date[9];
	
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transec.txt",ios::out | ios::app);
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user2_no == accountNumber)
	{
		cout << "\nAccount Holder's name :"<<fname<< " "<<lname<<endl;
		cout<<"enter(Y/N): ";
		cin >>ans;
		
		if(ans == 'n')
		{
			flag = 1;
			break;
		}
		
		
			balance = balance + amt;
			_strdate(tr_date);

			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			
			tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl; 

	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	
	if(flag == 1)
	{
		cout <<"\n NO Account Found";
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n\t Done ! Amount Added\n";
	temp_file_clear();
	
	//now time for deducting amount from main user
	deduct(user_no,amt);
	cout << "\n Money Successfully Transferd !";	
}
/*End Fund transfer function */

/* Start View All Transactions */
void Account::viewTr(int user_no)
{
	
	int number,amount,flag = 0;
	string date,status;
	
	ifstream tr_file_read("transec.txt" ,ios::in);
	//cin.clear();
	cout<<"\n\t"<<"AccountNumber"<<" | "<<"Date"
	<<" | "<<"Amount"<<" | "<<"CR / DR "<<endl;
	
	while(tr_file_read)
	{
		tr_file_read >>number;
		tr_file_read >>date;
		tr_file_read >>amount;
		tr_file_read >>status;	
	if(tr_file_read.eof())
	{
		break;
	}

	if(user_no == number)
	{
		cout<<"\t"<<number<<" | "<<date<<" | "<<amount
				<<" | "<<status<<" | "<<endl ;
		flag  = 1;
	}
	
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";	
	}
	tr_file_read.close();
}

/* End View All Transection */
void Account ::update_details(int user_no)
{
	int ch;
	char buff;	
	int flag = 0;
	string a = "cus_details.txt";
	string b = "temp.txt";
	
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			cout <<"\n\tAccount Number is : "<<accountNumber;
			cout <<"\n\tFill up Details with new records :\n";
			
			cout<<"\n\n\t New First name:";
			
			cin >>fname;
			cin.clear();
				
			cout <<"\n\t New Last name:";
			cin >> lname;
			cin.clear();
			
			cout <<"\n\t New  phone:";
			cin >> phone;
			cin.clear();
			
			cout <<"\n\t New Dob";
			cin >> dob;
			cin.clear();
			
			cout <<"\n\t Current Account Type:"<<type;
			cout <<"\n\t Change Type (Saving S/Other O) otherwiese press (N) :";
			char ans; 
			cin >> ans;
			cin.clear();
				if(tolower(ans) == 'n')
				{
				cout <<"\n\tOk !account type is not chenged !\n ";
				}
				else if(tolower(ans) == 's')
				{
					type = "SAVING";
				}
				else
				{
					type = "OTHER";
				}
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			flag  = 1;
	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	
	cout<<"\n\t Done ! Details Updated THank You.\n";
	temp_file_clear();
	
}


////////////////////////////////////////////////////////////////////////////////////////////






void Account :: pending(int user_no){
	int choice;
	int user2_no ,amt =0,flag = 0;
	char ans;
	user2_no = pend;
	if(pend != 0){
		
		cout<<"\n Money Request from "<<pend<<" check below for details of the account";
		cout<<"\n\n";
		
		searchDetails(user2_no);
	
	    cout<<"\n Do you want to send money to "<<pend<<" 1) Yes 2) No";
		cin>>choice;
		
		if(choice == 1){
			
			fund_tr(user_no);
			pend = 0;
		
	   }
	
	}
}















////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////





/*void Account :: updateToBlock(int user_no){
	int ch;
	char buff;	
	int flag = 0;
	string a = "cus_details.txt";
	string b = "temp.txt";
	
	Account();//constructor call to empty variables;
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	
	while(!file_read.eof())
	{
		
	file_read >> fname;
	file_read >>lname;
	file_read >>phone;
	file_read >>dob;
	file_read >>type;
	file_read >>accountNumber;
	file_read >>passcode;
	file_read >>balance;
	
	if(file_read.eof())
	{
		break;
	}
	
	if(user_no == accountNumber)
	{
			cout <<"\n\t Change Type of account to:";
			char ans; 
			cin >> ans;
			cin.clear();
				if(tolower(ans) == 'n')
				{
				cout <<"\n\tOk !account type is not changed !\n ";
				}
				else if(tolower(ans) == 's')
				{
					type = "SAVING";
				}
				else
				{
					type = "OTHER";
				}
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
				<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
			flag  = 1;
	}	
	else
	{
			file_temp << fname <<" "<<lname<<" "<< phone<<" "<<dob<<" "<<type
			<<" "<<accountNumber<<" "<<passcode<<" "<<balance<<endl;
	}
	
	}
	if(flag != 1)
	{
		cout << "\n\tNo record found";
		
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	
	cout<<"\n\t Done ! Details Updated THank You.\n";
	temp_file_clear();
}*/

/*
void Account :: block(int user_no){
	int num;
	int choice;
	cout<<"\n Which account number do you want to block ?";
	cin>>num;
	searchDetails(num);
	cout<<"\n Is this correct ? 1) Yes 2) No";
	cin>>choice;
	if(choice == 1){
		updateToBlock(num);
	}
}
*/





























/////////////////////////////////////////////////////////////////////////////////////////////////
/*
copy content function for copy text to other file 
*/
void copy_content(string a,string b)
{
		char ch;
		int flag = 0;
	ifstream temp_read(a.c_str(),ios :: in);
	ofstream file_write(b.c_str(),ios::out);
	while(!temp_read.eof())
	{
		temp_read.get(ch);
		file_write.put(ch);
		flag = 1;
	}
	if(flag != 1)
	{
		cout <<"\n\tFile Error !";
	}
	
}
//functions for account number automation
int number_system_get()
{
	int number;
	ifstream number_read("number.txt",ios::in);
	number_read >>number;
	return number;
}

void number_system_put(int n1)
{
	n1 = n1+1;
	ofstream number_write("number.txt",ios::out);	
	number_write <<n1;
}
//function for clearing TEMP FILE
void temp_file_clear()
{

	char ch;
	int flag = 0;
	ofstream temp_write("temp.txt",ios :: out);

	temp_write <<" ";
	temp_write.close();
	
}
//function for calculating year
string yearadd(string date1,int year)
{
	int add ;
	string date2;
	stringstream ss(date1.substr(6,4));
	 stringstream ss2(date1.substr(0,6));
	 stringstream ss3;
	 string s2; //for remaining part
	 ss2 >> s2;
	 ss >> add;
	 add = add + year;
	 ss3 << add;
	 date2 = s2 + ss3.str();
	 
	 return date2;	 
}

//menu for register user
void user_menu(int user_sesstion)
{
	int ch;
	int amount = 0;
	Account a;
	if(user_sesstion == 16777216 || user_sesstion == 16777217){
	start:do{
		
		cout<<"\nWelcome Sir your account number is>>>>>>  "<<user_sesstion<<endl;
		cout<<"\n\t 1.View Your Account.";
		cout<<"\n\t 2.Update Your Details.";
		cout<<"\n\t 3.Transfer Fund.";
		cout<<"\n\t 4.Withdrawal.";
		cout<<"\n\t 5.Add Money.";
		cout<<"\n\t 6.View Transaction.";
		cout<<"\n\t 7.Close Account.";
		cout<<"\n\t 8.Ask";
		cout<<"\n\t 9.Pending Approvals";
		cout<<"\n\t 10.MiniStatement";
		cout<<"\n\t 11.Block user";
		cout<<"\n\t 0.Exit";
			
		cout<<"\n\t Enter your Choice (1-7)::";
	if(cin >> ch)
	{
		
		
		switch (ch)
		{
			case 1:
				system("cls");
				a.searchDetails(user_sesstion);
				break;
				
			case 2:
				system("cls");
				a.update_details(user_sesstion);
				break;
				
			case 3:
				system("cls");
				a.fund_tr(user_sesstion);
				break;
		
			case 4:
				cout<<"\n\tEnter Amount to withdraw :";
				cin >> amount;
				a.deduct(user_sesstion,amount);
				break;
			case 5:
				cout<<"\n\tEnter Amount to Add :=";
				cin >> amount;
				a.add(user_sesstion,amount);
				a.CurrentBalance(user_sesstion);
				break;
				
			case 6:
				a.viewTr(user_sesstion);
				break;
				
			case 7:
				a.delete_details();
				break;
			case 8:
			    cout<<"\n\tAsk";
				a.ask(user_sesstion);
				break;
			case 9:
			    cout<<"\n\tPending Approvals";
				a.pending(user_sesstion);
				break; 
			case 10:
				a.ministatement(user_sesstion);
				break;
			//case 11:
			//	a.block(user_sesstion);
			//	break;
			
			default :
				cout<<"\n\tWorng choise \n";		
				break;
		}
	}
		else
		{
			cout<<"\n\t Input only Digits please !";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15;
		}
	

	}while(ch != 0);
}
else {
	do{
		
		cout<<"\nWelcome Sir your account number is>>>>>>  "<<user_sesstion<<endl;
		cout<<"\n\t 1.View Your Account.";
		cout<<"\n\t 2.Update Your Details.";
		//cout<<"\n\t 3.Transfer Fund.";
		cout<<"\n\t 4.Withdrawal.";
		//cout<<"\n\t 5.Add Money.";
		cout<<"\n\t 6.View Transaction.";
		cout<<"\n\t 7.Close Account.";
		cout<<"\n\t 8.Ask";
		//cout<<"\n\t 9.Pending Approvals";
		cout<<"\n\t 10.MiniStatement";
		cout<<"\n\t 0.Exit";
			
		cout<<"\n\t Enter your Choice (1-7)::";
	if(cin >> ch)
	{
		
		
		switch (ch)
		{
			case 1:
				system("cls");
				a.searchDetails(user_sesstion);
				break;
				
			case 2:
				system("cls");
				a.update_details(user_sesstion);
				break;
				
			case 3:
				system("cls");
				a.fund_tr(user_sesstion);
				break;
		
			case 4:
				cout<<"\n\tEnter Amount to withdraw :";
				cin >> amount;
				a.deduct(user_sesstion,amount);
				break;
			case 5:
				cout<<"\n\tEnter Amount to Add :=";
				cin >> amount;
				a.add(user_sesstion,amount);
				a.CurrentBalance(user_sesstion);
				break;
				
			case 6:
				a.viewTr(user_sesstion);
				break;
				
			case 7:
				a.delete_details();
				break;
			case 8:
			    cout<<"\n\tAsk";
				a.ask(user_sesstion);
				break;
			case 9:
			    cout<<"\n\tPending Approvals";
				a.pending(user_sesstion);
				break; 
			case 10:
				a.ministatement(user_sesstion);
				break;
			
			default :
				cout<<"\n\tWorng choise \n";		
				break;
		}
	}
		else
		{
			cout<<"\n\t Input only Digits please !";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15;
		}
	

	}while(ch != 0);
	
	
}
}
int main()
{
	int ch;
	int login_state = 0;
	int user;
	int pass;
	int hello;
	Account a;
	//child1 c;
	manual m;
	
	do{
		//system("clear");
		system("cls");
		
		cout<<"\n\t\t\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
		cout<<"\n\t\t| Bank management System      		  |"<<endl;
		cout<<""<<endl;
		cout<<"\n\t\t\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
		
		cout<<"\n Who is using the system: \n 1) Dad \n 2) Mom \n 3)Children";
		cin>>hello;
		
		if(hello == 1 || hello == 2){
		cout <<"\n\t 1.Login To your Account.";
		cout <<"\n\t 2.Open An Account.";
		cout <<"\n\t 3.Help.";
		
		cout <<"\n\t 0.Exit";
		
		cout<<"\n\n\tEnter your choice ::";
	}
	else if(hello == 3){
		cout <<"\n\t 1.Login To your Account.";
		
		cout<<"\n\n\tEnter your choice ::";
	}
		if(cin >> ch )
		{
			switch (ch)
			{
				case 1:
					cout << "\n\t Enter Account Number:";
					cin >>user;
					cout <<"\n\t Enter 4-digit passcode :";
					cin >>pass;
					system("cls");
					a.login_user(user,pass);
					//cout<<"\n\t\twork in progress";
	
				break;
				case 2:
					a.createAccount();
					break;
					
				case 3:
				//	cout<<"\nWork is in Progress !";
				m.userguide();
				getch();
					break;
					
			}
		}
		else
		{
			cout<<"\n\t Input only Digits please ! Press Enter To continue";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15 ;
		}
		

			
	}while(ch !=0);

//	user_menu();
	return 0;
}