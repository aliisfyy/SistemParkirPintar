#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>	//time libary
using namespace std;

//parking slot variable
int nSlot = 20, availableSlot = nSlot;
string plateNum[20];
string num_plate = "";
float currentTime[20];
string userName[20];

//statistic
string plateHistory[20];
float durationHistory[20], feeHistory[20];
int historyIndex=0;

//page function
int menu();	
void masuk();
void keluar();
void resit(int i, int p);
void help();
void statistic();
void payment(int x, float p);

//calc function
float calcPrice(float t);
void date();
float calcTime(int x);
//calc element
int hour, fee;

//search engin
void rearrange(int x);
void searching(string);
int findIndex(string x);
void initializeSlot();
int anomalicheck(string);

//hiasan
void dash(char x);
void graft(int x);

int main()
{
	int y;
	initializeSlot();
	cout<<fixed<<showpoint<<setprecision(2);
	
	do{
	dash('_');
	dash('*');
    cout << "\t!! WELCOME TO OUR SHOPPING MALL !!" << endl;
	dash('-');
	y=menu();				//collect input from user

	if (y==1)				//user enter parking slot
	{
		if (plateNum[19]==" ")			// check if the parking slot are full
			masuk();
		else 
			cout << "!! Parking Slot FULL !!" << endl;
	}
	else if (y==2)			//user get out from parking slot
		keluar();
	else if (y==3)			//help page
		help();
	else if (y==4)			//program stop
	{
		cout<<"Thank you!! See you next time.";
    	return 0;
	}
	else if (y==5)			//statistic overview
    	statistic();
		
} while(y>=1&&y<=5);

return 0;	
}

int menu()
{
	string input;
   
    do{
    cout<< "Enter 1 to register parking\nEnter 2 to pay for parking\nEnter 3 for Help page\n\nInput: ";
    getline(cin,input);												//input from user
    
    if(input=="1")
    	return 1;
	else if(input=="2")
    	return 2;
    else if (input=="3")
    	return 3;
    else if (input=="616")
    	return 4;
    else if (input=="587")
    	return 5;
	else
    	cout<<"Invalid Input!! Please enter again.\n\n";			//check for invalid input
}
	while(input!="1" || input!="2" || input!="3" || input!="616" || input!="587");
}

void masuk()
{
	int l=0;
	
	cout << "OCCUPIED SLOTS " << "[ " << nSlot - availableSlot << "/" << nSlot << " ]"<< endl;		//show occupied slot
		
	cout << "Please Enter Car Plate's Number : ";
	cin.ignore(0);
	getline(cin,num_plate);										// user plate number

	int y = anomalicheck(num_plate);							//check if the plate number already entered
	
	if (y==20)					//if plate no entered, 
	{
	searching(num_plate);		//search for available slot
	cout << "Date : ";
	date();
	availableSlot--;
	}
}

void keluar()
{
	string checkCar;
	int r=0;
	
	dash('-');
    cout<<"Please enter car's plate number : ";
    cin.ignore(0);
    getline(cin,checkCar);						//user plate number
	int index = findIndex(checkCar);			//find the plate number from array
	float fee = calcPrice(calcTime(index));		//calc fee
	
	if (index < 20)
	{
		plateHistory[historyIndex]=plateNum[index];		//store plate number for statistic
		payment(index, fee);							//make payment
		resit(index, fee);								//display resit
    	rearrange(index);								//clear all data from the user from all array
    	availableSlot++;
    	historyIndex++; 								//for statistic
	}
}

//display resit
void resit(int i, int p)
{
	dash('_');
	dash('*');
    cout << right << setfill(' ') << setw(30) << "PARKING RECEIPT" << endl;
    dash('-');
    
    cout << left << setfill(' ') << setw(20) << "Name : " << userName[i] << endl;
    cout << left << setw(20) << "Car Plate:" << plateNum[i] << endl;
    cout << left << setw(20) << "Exit Time:"; 
    date();
    cout << left << setw(20) << "Total Fee:" << "RM " << p << endl;
    
    dash('-');
    cout << right << setfill(' ') << setw(17) << "THANK YOU" << endl;
    dash('-');
}

//help user
void help()
{
	dash('-');
	cout << right << setfill(' ') << setw(30) << "HELP PAGE" << endl;
	dash('-');
	cout << endl;
	cout << "#How to check in car :" << endl;
	cout << "\tStep 1 --> Enter code --1--" << endl;
	cout << "\tStep 2 --> Enter car plate number to store" << endl;
	cout << "\tStep 3 --> Enjoy your shopping hour" << endl;
	
	cout << "#How to check out car :" << endl;
	cout << "\tStep 1 --> Enter code --2--" << endl;
	cout << "\tStep 2 --> Enter car plate to find your car" << endl;
	cout << "\tStep 3 --> Resit will pop up and the fee will be displayed" << endl;
	
	cout << "#Fee calculation :" << endl;
	cout << "\t1-2 Min --> RM2/hour" << endl;
	cout << "\t3-4 Min --> RM1/hour" << endl;
	cout << "\t5+ Min  --> RM0.5/hour" << endl;
}

//current statistic
void statistic()
{
	dash('_');
	dash('*');
    cout << right << setfill(' ') << setw(35)<< "BERJAYA MALL STATISTIC" << endl;
    cout << "\t    ";
    date();
    dash('-');
    cout << "ID\tCAR_PLATE\tDURATION\tTOTAL_FEE"<< endl;
    cout<<fixed<<showpoint<<setprecision(2);
    int i=0;
    while (feeHistory[i]!=0)					//display all pass user data from array
    {
    	cout << i+1 << "\t"<<plateHistory[i] << "\t\t" << durationHistory[i] << " min\tRM " << feeHistory[i] << endl;
    	i++;
	}
	dash('-');
	
	//calculation for average duration, total earning, and average fee
	float sumDur=0, sumFee=0;
	int count1=0, count2=0, count3=0;
	for (int j=0; j<=i; j++)
	{
		sumDur = sumDur + durationHistory[j];
		sumFee = sumFee + feeHistory[j];
		
		if (durationHistory[j]<=2)
			count1++;
			
		else if (durationHistory[j]<=4)
			count2++;

		else
			count3++;
			
	}
	
	//display graft
	float avgDur = sumDur/(i+1);
	float avgFee = sumFee/(i+1);
	dash('-');
	cout << "##Graph Analysis##" << endl;
	cout << "  1-2 Min | " ;
	graft(count1-1);
	cout << "  3-4 Min | " ;
	graft(count2);
	cout << "  5++ Min | " ;
	graft(count3);
	dash('-');
	dash('-');
	cout << "Total Car : " << i << endl;
	cout << "Average Parking Duration : " << avgDur << " min" << endl;
	cout << "Average Fee Per Car : RM " << avgFee << endl;
	cout << "Total Earning : RM " << sumFee <<  endl;
	dash('-');
}

float calcPrice(float t)		//calc parking fee 
{
	float min, parking_price, price=2.00;
	
	min=t/60;					//covert into minit
	
	if (min<=2)					//calculation
	parking_price=price;
	
	else if (min>2 && min<=4)
	parking_price=price+(1*(min-2));
	
	else if (min>4)
	parking_price=price+(1*2)+(0.5*(min-4));
	
	durationHistory[historyIndex]=t/60;				//store duration into pass array for statistic
	feeHistory[historyIndex]=parking_price;			//store fee into pass array for statistic
	return parking_price;
}

float calcTime(int x)		//calc parking duration in seconds
{
	int totalSec = time(NULL) - currentTime[x];   
	cout << totalSec << endl << endl;
	return totalSec;
}

void date()					//display current time
{
	time_t timestamp;
	time(&timestamp);
	cout << ctime(&timestamp);
}

void rearrange(int i)		//vacate car slot
{
	plateNum[i]=" ";
	currentTime[i]=0;
}

int findIndex(string x)		//find car park slot index
{
	int r=0;
    do
	{
		r++;
	}
	while(x!=plateNum[r-1]&&r!=20);
	if (r==20)
	{
		cout << "Plate Car not found" << endl;
		return 20;
	}
	return r-1;
}

void searching(string plate)	//search for available slot
{
	int i=0;
	
	do{
    	if(plateNum[i]==" ")
		{
			plateNum[i]=plate;
   			currentTime[i]= time(NULL);
		}
   		i++;
	}while (plateNum[i-1]!=plate&&i<20);
	
}

void initializeSlot()	//initialize all park slot to "[blank]"
{
	for (int i=0; i<20; i++)
	{
		plateNum[i]=" ";
		plateHistory[i]=" ";
	}
}

void dash(char x)	//hiasan
{
	cout << left << setfill(x) << setw(50) << "" << endl;
}

void graft(int x)	//statistic
{
	cout << left << setfill((char)254)<< setw(x) << "" << " (" << x << ")" << endl;
}

int anomalicheck(string plate){
	
	int r=0;
  
do{
	if (plate==plateNum[r])
	{
		cout << "Plate already entered... Please enter again!!" << endl;
	}
	r++;
} while (plate!=plateNum[r-1] && r<=18);
if (r==19)
	{
		return 20;
	}
	return r;
}

//payment section using master card
void payment(int x, float p){
	string name, cardNumb, exDate, cvv;				//varible used
	bool validity = false;
	
	dash('_');
	dash('*');
    cout << "\t\tP A Y M E N T" << endl;
	dash('-');
	cout<<"TOTAL PARKING FEE : RM "<< p <<endl;
	dash('-');
	cout << "MASTER CARD DETAIL :" << endl;
	
	//check name
	while (validity == false)
	{
		cout << "Full Name : ";
		cin.ignore(0);
		getline(cin,name);						//user full name
		userName[x] = name;
		
		int i = 0, wordCount=0, otherCount=0, spaceCount=0, numbCount=0;
		while (i!= name.length())				//detect invalid input
		{
			if (name[i]>=48 && name[i]<=57) //48 & 57 is ascii number for 0 & 9
				numbCount++;
			else if ((name[i]>=65 && name[i]<=90) || (name[i]>=97 && name[i]<=122) ) //65,90,97,122 is ascii number for a,z,A,Z
				wordCount++;
			else if (name[i]>=' ')
			{
				spaceCount++;
			}
			else 
			{
				otherCount++;
			}
			i++;
		}
		
		if (otherCount>0 || numbCount>0)
		{
			cout << "Invalid, Please re-enter" << endl;
			validity = false;
		}
		else
		{
			validity = true;
		}
	}
	
	//check card number
	validity = false;
	while (validity == false)
	{
		cout<<"Bank Card Number [16 digit]: ";
		cin.ignore(0);
		getline(cin,cardNumb);
	
		int i = 0, otherCount=0,spaceCount=0, numbCount =0;
		while (i!= cardNumb.length())				//detect invalid input
		{
			if (cardNumb[i]>=48 && cardNumb[i]<=57) //48 & 57 is ascii number for 0 & 9
				numbCount++;
			else if (cardNumb[i]>=' ')
				spaceCount++;
			else 
				otherCount++;
			i++;
		}
		if (otherCount>0 || (spaceCount>0 && spaceCount!=3) )
		{
			cout << "Card Invalid, Please re-enter" << endl;
		}
		else if (numbCount==16)
		{
			validity = true;
		}
		else 
		{
			cout << "Card Invalid, Please re-enter" << endl;
		}
	}
	
	//check expired date
	validity = false;
	while (validity == false)
	{
		cout<<"Expiry Date [MM/YY]: ";
		cin.ignore(0);
		getline(cin,exDate);
	
		int i = 0, numbCount=0, otherCount=0, slashCount=0;
		while (i!= exDate.length())				//detect invalid input
		{
			if (exDate[i]>=48 && exDate[i]<=57) //48 & 57 is ascii number for 0 & 9
				numbCount++;
			else if (exDate[i]>='/')
				slashCount++;
			else 
				otherCount++;
			i++;
		}
		//to make sure it not expired
		if (otherCount>0 || (slashCount!=1&&exDate.at(3)!='/') ||exDate.at(0)>=50 || (exDate.at(0)==49 && exDate.at(1)>=51) || exDate.at(4)<=49 || (exDate.at(4)==50 && exDate.at(5)<53))
		// if (contain other symbol || slash not at index 3 || the month initial >= 2 || the month initial == 1 but not valid || the year initial is 1 || the year initial is 25 but not valid
		{
			cout << "Card Invalid, Please re-enter" << 0 << endl;
		}
		else if (numbCount==4)
		{
			validity = true;
		}
		else 
		{
			cout << "Card Invalid, Please re-enter" << 1 << endl;
		}
	}
	
	//check cvv
	validity = false;
	while (validity == false)
	{
		cout<<"Card Verification Value [XXX]: ";
		cin.ignore(0);
		getline(cin,cvv);
		
		
		int i = 0, numbCount=0, otherCount=0;
		while (i!= cvv.length())
		{
			if (cvv[i]>=48 && cvv[i]<=57) //48 & 57 is ascii number for 0 & 9
				numbCount++;
			else 
				otherCount++;
			i++;
		}
		if (otherCount>0)
		{
			cout << "Card Invalid, Please re-enter" << endl;
		}
		else if (numbCount==3)
		{
			validity = true;
		}
		else 
		{
			cout << "Card Invalid, Please re-enter" << endl;
		}
		dash('-');
		cout << "\t !! Payment Successful !!" << endl; 
		dash('-');
	}
}
