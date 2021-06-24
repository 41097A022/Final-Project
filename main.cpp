#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;

class FriendsRoster{
public:
    FriendsRoster():accountNumber(0),bornYear(0),lastName(""),firstName(""),job(""),annualIncome(0.0){};
    void setAccountNuber(int _accountNumber){accountNumber=_accountNumber;}
    void setBornYear(int _Year){bornYear=_Year;}
    void setLastName(char _lastName[]){strcpy(lastName,_lastName);}
    void setFirstName(char _firstName[]){strcpy(firstName,_firstName);}
    void setJob(char _job[]){strcpy(job,_job);}
    void setAnnualIncome(double _annualIncome){annualIncome=_annualIncome;}
    int getAccountNumber()const{return accountNumber;}
    int getBornYear()const{return bornYear;}
    string getLastName()const{return lastName;}
    string getFirstName()const{return firstName;}
    string getJob()const{return job;}
    double getAnnuslIncome()const{return annualIncome;}
private:
    int accountNumber;
    int bornYear;
    char lastName[15];
    char firstName[10];
    char job[15];
    double annualIncome;
};
void outputLine(ostream &output,const FriendsRoster &record)
{
    output << left << setw(3) << record.getAccountNumber()
    << setw(8) << record.getBornYear()
    << setw(8) << record.getLastName()
    << setw(10) << record.getFirstName()
    << setw(10) << record.getJob()
    << setw(8) << record.getAnnuslIncome() << endl;
}
enum Options{ADDNEW = 1, QUERY, LIST , UPDATE , CLEAR ,STOP };
void _create(){
    int accountNumber;
    int bornYear;
    char lastName[15];
    char firstName[10];
    char job[15];
    double annualIncome;

    ofstream creatFriendsRoster("Friends_Roster.dat",ios::in|ios::out|ios::binary);
    if(!creatFriendsRoster){
        cout<<"File cannot be opend!"<<endl;
        exit(1);
    }
    cout << "Enter account number" << "(1 to 100 , 0 to end input)\n";
    FriendsRoster friends;
    cin >> accountNumber;
    friends.setAccountNuber(accountNumber);

    while(friends.getAccountNumber() >= 1 && friends.getBornYear() <= 100){
        cout << "Enter born year, lastname, firstname, job, annual income(k) \n";
        cin >> bornYear;
        cin >> lastName;
        cin >> firstName;
        cin >> job;
        cin >> annualIncome;
        friends.setBornYear(bornYear);
        friends.setLastName(lastName);
        friends.setFirstName(firstName);
        friends.setJob(job);
        friends.setAnnualIncome(annualIncome);
        creatFriendsRoster.seekp((friends.getAccountNumber()-1)*sizeof(FriendsRoster),ios::beg);
        creatFriendsRoster.write(reinterpret_cast<const char*>(&friends),sizeof(FriendsRoster));
        cout << "Enter account number" << "(1 to 100 , 0 to end input)\n";
        cin >> accountNumber;
        friends.setAccountNuber(accountNumber);
    }
    creatFriendsRoster.close();
}
void _query(){
    int accountNumber;
    int bornYear;
    char lastName[15];
    char firstName[10];
    char job[15];
    double annualIncome;

    ifstream inRoster("Friends_Roster.dat",ios::binary);

    if(!inRoster){
        cout << "File could not be opened." << endl;
        exit(1);
    }
    int searchNumber;
    cout << "Enter account number" <<"(1 to 100, 0 to end input):";
    cin >> searchNumber;
    while(searchNumber>0&&searchNumber<=100)
    {
        FriendsRoster friends;
        inRoster.seekg((searchNumber-1)*sizeof(FriendsRoster),ios::beg);
        inRoster.read(reinterpret_cast<char*>(&friends),sizeof(FriendsRoster));
        if(friends.getAccountNumber()!=0){
            outputLine(cout,friends);
        }
        cout << "Enter account number" << "(1 to 100, 0 to end input):";
        cin >> searchNumber;
    }
    inRoster.close();
}

void _list(){
    int counter = 0;
    ifstream inRoster("Friends_Roster.dat",ios::binary);

    if(!inRoster){
        cout << "File could not be opened." << endl;
        exit(1);
    }
    FriendsRoster friends;
    inRoster.read(reinterpret_cast<char*>(&friends),sizeof(FriendsRoster));

    cout << "---------------------------------------------------"<< endl;
    cout << left << setw(3) << "ID" << setw(8) << "出生年" <<setw(8) << "姓" << setw(10) << "名" << setw(10) << "工作" << setw(8) << "年收入 (k) " <<endl;
    cout << "---------------------------------------------------"<< endl;
    while(!inRoster.eof()){
        if(friends.getAccountNumber()!=0){
            counter++;
            outputLine(cout,friends);
        }
        inRoster.read(reinterpret_cast<char*>(&friends),sizeof(FriendsRoster));
    }
    cout << "---------------------------------------------------" <<endl;
    cout << "Total: " <<counter << " Record(s)" <<endl;
    cout << "---------------------------------------------------" <<endl;
    inRoster.close();
}
void _update(){
    double annualIncome;
    char Job[15];
    fstream inRoster("Friends_Roster.dat",ios::in|ios::out|ios::binary);

    if ( !inRoster ) {
    cout << "File could not be opened." << endl;
    exit( 1 );
    }

    FriendsRoster friends;
    int searchNumber;
    char confirm='Y';

    cout << "Enter account number(update existing record)" << "(1 to 100, 0 to end input)\n";
    cin >> searchNumber;

    while (searchNumber>0 && searchNumber<=100){
        inRoster.seekg((searchNumber-1)*sizeof(FriendsRoster),ios::beg);
        inRoster.read(reinterpret_cast<char*>(&friends), sizeof(FriendsRoster));
        if (friends.getAccountNumber() != 0 && friends.getAccountNumber() == searchNumber){
            outputLine(cout,friends);
            cout << "Do you want to update data? (Y/N)";
            cin >> confirm;
            if (confirm =='Y'){
            cout << "new Job: ";
            cin >> Job;
            cout << "new annual income: ";
            cin >> annualIncome;
            friends.setJob(Job);
            friends.setAnnualIncome(annualIncome);
            inRoster.seekp((friends.getAccountNumber()-1)*sizeof(FriendsRoster),ios::beg);
            inRoster.write(reinterpret_cast<const char*>(&friends), sizeof(FriendsRoster));
            }
        }

        cout << "Enter account number(update existing record)" << "(1 to 100, 0 to end input)\n";
        cin >> searchNumber;
  }


  inRoster.close();
}
/*void _delete(){
    int searchNumber;
    char confirm='Y';
    ofstream creatFriendsRoster("Friends_Roster.dat",ios::in|ios::out|ios::binary);
    if(!creatFriendsRoster){
        cout<<"File cannot be opend!"<<endl;
        exit(1);
    }
    cout << "Enter account number" << "(1 to 100 , 0 to end input)\n";
    cin >> searchNumber;
    cout << "Are you sure to delete the data?(Y/N)";
    cin >> confirm;
     while(searchNumber>0&&searchNumber<=100)
    {
        FriendsRoster friends(0,"","","",0);
        inRoster.seekg((searchNumber-1)*sizeof(FriendsRoster),ios::beg);
        inRoster.read(reinterpret_cast<char*>(&friends),sizeof(FriendsRoster));
        cout << "Enter account number" << "(1 to 100, 0 to end input):";
        cin >> searchNumber;

    }

}*/
int main ()
{
    //第二次執行可以註解掉以下11行
    ofstream creatRoster("Friends_Roster.dat",ios::binary);
    if(!creatRoster){
        cout<< "File cannot be opend" << endl;
        exit(1);
    }

    FriendsRoster blankRoster;

    for (int i=0;i<100;i++){
        creatRoster.write(reinterpret_cast<const char*>(&blankRoster),sizeof(FriendsRoster));
    }
    cout << "這是一款可以記錄及存取朋友基本信息的簡單程式"<<endl;
    cout << "-----------以下為執行注意事項----------------"<<endl<<endl;
    cout << "若是第一次執行程式請消除第181到第192行之註解"<<endl;
    cout << "  並在結束第一次程式後重新註解該段程式碼"<<endl;
    cout << endl;
    system("pause");
    system("CLS");
    while(1){
        cout << "Enter your choice:" << endl
              << "1-Add new record"<<endl
              << "2-Query an exiting record"<<endl
              << "3-List all records"<<endl
              << "4-Update job and income"<<endl
              << "5-Clean the console"<<endl
              << "6-Quit"<<endl;
        int opt;
        cin>>opt;
        switch (opt){
            case ADDNEW: _create(); break;
            case QUERY: _query(); break;
            case LIST: _list(); break;
            case UPDATE: _update(); break;
            case STOP: exit(EXIT_SUCCESS);
            case CLEAR: system("CLS");break;
            default: cerr << "Invalid Option! Try again."; break;

        }
    }
    return 0;
}
