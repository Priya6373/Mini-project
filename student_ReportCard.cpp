#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#define Max 50
using namespace std;
class Student
{
	int roll_no;
	char name[Max];
	int m1,m2,m3,m4,m5,m6;
	float avg;
	char grade;
	void calculate();	
    public:
	void getdata();		
	void showdata();	
	void show_tab();
	int ret_r_no();
}; 
void Student::calculate()
{
	avg=(float)((m1+m2+m3+m4+m5+m6)/6.0);
    if(avg>85)
        grade='O';
	else if(avg>=60)
		grade='A';
	else if(avg>=50)
		grade='B';
	else if(avg>=33)
		grade='C';
	else
		grade='F';
}

void Student::getdata()
{
	cout<<"\n\t\tEnter the roll number of student: ";
	cin>>roll_no;
	cout<<"\t\tEnter the Name of student: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\t\tEnter the marks in physics: ";
	cin>>m1;
	cout<<"\t\tEnter the marks in chemistry: ";
	cin>>m2;
	cout<<"\t\tEnter the marks in maths: ";
	cin>>m3;
	cout<<"\t\tEnter the marks in english: ";
	cin>>m4;
	cout<<"\t\tEnter the marks in computer science: ";
	cin>>m5;
    cout<<"\t\tEnter the marks in social science: ";
	cin>>m6;
	calculate();
}

void Student::showdata() 
{
	cout<<"\n\t\tRoll number of student : "<<roll_no;
	cout<<"\n\t\tName of student : "<<name;
	cout<<"\n\t\tMarks in Physics : "<<m1;
	cout<<"\n\t\tMarks in Chemistry : "<<m2;
	cout<<"\n\t\tMarks in Maths : "<<m3;
	cout<<"\n\t\tMarks in English : "<<m4;
	cout<<"\n\t\tMarks in Computer Science : "<<m5;
	cout<<"\n\t\tPercentage of student is  : "<<avg;
	cout<<"\n\t\tGrade of student is : "<<grade;
}

void Student::show_tab() 
{
	cout<<roll_no<<setw(8)<<" "<<name<<setw(14)<<m1<<setw(4)<<m2<<setw(4)<<m3<<setw(4)
		<<m4<<setw(4)<<m5<<setw(4)<<m6<<setw(8)<<avg<<setw(6)<<grade<<endl;
}

int  Student::ret_r_no() 
{
	return roll_no;
}
void introduction()
{
	cout<<"\n\n\n\t\t\t\t====================================================\n";
	cout<<"\t\t\t\t STUDENT REPORT CARD HANDLING SYSTEM PROJECT IN C++";
	cout<<"\n\t\t\t\t====================================================\n";
	cout<<"\n\n\t\t\t\t MADE BY : PRIYA KIMOTHI";
	cout<<"\n\t\t\t\t ROLL NO.: 2018577";
	cout<<"\n\t\t\t\t UNIVERSITY : GRAPHIC ERA HILL UNIVERSITY\n\n";
    cout<<"\n\t\t\t\t Press enter to continue....";
	cin.get();
}	
void result();		
void entry();
void class_result();
void write_data()
{
	Student s;
	ofstream outF;
	outF.open("Student_data.dat",ios::binary|ios::app);
	s.getdata();
	outF.write((char*) (&s), sizeof(Student));
	outF.close();
    cout<<"\n\n\t\tStudent record has been created........ ";
    cout<<"\n\t\tPress enter to continue....";
	cin.ignore();
	cin.get();
}

void display_all()
{
	Student s;
	ifstream op;
	op.open("Student_data.dat",ios::out);
	if(!op)
	{
		cout<<"File can not be opened!!\nPress enter...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\t==========================";
	cout<<"\n\t\tDISPLAYING ALL RECORDS!!!";
	cout<<"\n\t\t==========================\n\n";
	while(op.read((char*) (&s), sizeof(Student)))
	{
		s.showdata();
		cout<<"\n\n\t\t====================================\n";
	}
	op.close();
	cout<<"\n\t\tPress enter to continue....";
	cin.ignore();
	cin.get();
}
void display_part(int n)
{
	Student s;
	ifstream op;
	op.open("Student_data.dat",ios::binary);
	if(!op)
	{
		cout<<"File can not be opened!!\nPress enter...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(op.read((char*) (&s), sizeof(Student)))
	{
		if(s.ret_r_no()==n)
		{
	  		 s.showdata();
			 flag=true;
		}
	}
	op.close();
	if(flag==false)
    {
		cout<<"\n\n\t\tStudent record does not exist!!";
    }
	cout<<"\n\t\tPress enter to continue....";
	cin.ignore();
	cin.get();
}
void modify_record(int n)
{
	bool found=false;
	Student s;
	fstream File;
	File.open("Student_data.dat",ios::in|ios::out);
	if(!File)
	{
		cout<<"\n\t\tFile can not be opened!!\n\t\tPress enter...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read((char*) (&s), sizeof(Student));
		if(s.ret_r_no()==n)
		{
			s.showdata();
			cout<<"\n\n\t\tEnter the new details of the student"<<endl;
			s.getdata();
			int pos=(-1)*static_cast<int>(sizeof(s));
			File.seekp(pos,ios::cur);
			File.write((char*) (&s), sizeof(Student));
			cout<<"\n\n\t\tRecord Updated!";
			found=true;
		}
	}
	File.close();
	if(found==false)
    {
		cout<<"\n\n\t\tRecord Not Found! ";
    }
    cout<<"\n\t\tPress enter to continue....";
	cin.ignore();
	cin.get();
}

void delete_record(int n)
{
	Student s;
	ifstream op;
	op.open("Student_data.dat",ios::binary);
	if(!op)
	{
		cout<<"\n\t\tFile can not be opened!!\n\t\tPress enter...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outF;
	outF.open("Temp.dat",ios::out);
	op.seekg(0,ios::beg);
	while(op.read((char*) (&s), sizeof(Student)))
	{
		if(s.ret_r_no()!=n)
		{
			outF.write((char*) (&s), sizeof(Student));
		}
	}
	outF.close();
	op.close();
	remove("Student_data.dat");
	rename("Temp.dat","Student_data.dat");
	cout<<"\n\n\t\tRecord Deleted ..";
    cout<<"\n\t\tPress enter to continue....";
	cin.ignore();
	cin.get();
}
int main()
{
    int ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	system("cls");
	introduction();
	do
	{
		system("cls");
		cout<<"\n\n\n\t=============";
		cout<<"\n\t  MAIN MENU";
		cout<<"\n\t=============";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT MENU";
		cout<<"\n\n\tPlease Select Your Option [1/2/3] ";
		cin>>ch;
		switch(ch)
		{
			case 1: 
                result();
				break;
			case 2: 
                entry();
				break;
			case 3:
				break;
			default :
                break;
		}
    }while(ch!=3);
	return 0;
}

void class_result()
{
	Student s;
	ifstream op;
	op.open("Student_data.dat",ios::binary);
	if(!op)
	{
		cout<<"\t\tFile can not be opened!!\n...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\t================";
	cout<<"\n\t\t  CLASS RESULT \n";
	cout<<"\t\t================\n";
	cout<<"=======================================================================\n";
	cout << "R.No        Name                P   C   M   E   CS   S   avg     Grade\n"; 
	cout<<"=======================================================================\n";
	while(op.read((char*) (&s), sizeof(Student)))
	{
		s.show_tab();
	}
    cout<<"Press enter to continue....";
	cin.ignore();
	cin.get();
	op.close();
}
void result()
{
	int ch;
	int r_no;
	system("cls");
	cout<<"\n\n\n\t===============";
	cout<<"\n\t  RESULT MENU";
	cout<<"\n\t===============";
	cout<<"\n\n\n\t1. CLASS RESULT";
	cout<<"\n\n\t2. STUDENT REPORT CARD";
	cout<<"\n\n\t3. BACK TO MAIN";
	cout<<"\n\n\n\tPlease select any option (1-3) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case 1 :	
        class_result(); 
        break;
	case 2 :	
        cout<<"\n\n\t\tEnter roll number of the student: ";
        cin>>r_no;
		display_part(r_no); 
        break;
	case 3 :	
        break;
	default:	
        break;
	}
}
void entry()
{
	int ch;
	int n;
	system("cls");
	cout<<"\n\n\n\t============\n";
	cout<<"\t ENTRY MENU";
	cout<<"\n\t============";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case 1:	
        write_data(); 
        break;
	case 2:	
        display_all(); 
        break;
	case 3:	    
        cout<<"\n\n\t\tEnter the roll number of the student: "; 
        cin>>n;
		cout<<"\n\n\t\t======================\n";
		cout<<"\t\tSEARCHING FOR A RECORD\n";
		cout<<"\t\t======================\n\n";
		display_part(n); 
        break;
	case 4:	
        cout<<"\n\n\t\tEnter the roll number of the student: "; 
        cin>>n;
		cout<<"\n\n\t\t====================\n";
		cout<<"\t\t MODIFYING A RECORD\n";
		cout<<"\t\t====================\n\n";
		modify_record(n);
        break;
	case 5:	
        cout<<"\n\n\t\tEnter the roll number of the student: "; 
        cin>>n;
		cout<<"\n\n\t\t======================\n";
		cout<<"\t\t  DELETING A RECORD\n";
		cout<<"\t\t======================\n\n";
		delete_record(n);
        break;
	case 6:	
        break;
	default:	
        break; 
	}
}