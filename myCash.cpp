#include <bits/stdc++.h>
#include <fstream> 
#include <string>
#include <sstream>

using namespace std;

int memct = 0,loggedMemPos;

struct member{
public:
    string number;
    string name;
    string pin;
    float amount;
}mem[10000];

class histry{
public:
    int  transID; 
    string description;
    float transAmount;
    float presentBalance;

    histry(string y,float z,float x){
        transID = (((rand() % 10 + 1000000) + (rand() + 100)) % 1000000) + 1000000 ;
        description = y;
        transAmount = z;
        presentBalance = x;
    }
};
vector<histry> v[100];

int logre(){
    int choice_login;
    cout << "_________________" << endl;
    cout << "Welcome To MyCash" << endl;
    cout << "*****************" << endl;
    cout << "1.Login\n";
    cout << "2.Register\n";
    cout << "3.Exit\n";
    cout << "Enter Your option(1 - 3) : ";
    cin >> choice_login;
    return choice_login; 
}

int menu(){
    cout << "<-----Menu----->" << endl;
    cout << "1. Update Me\n";
    cout << "2. Remove Me\n";
    cout << "3. Send Money\n";
    cout << "4. Cash-in\n";
    cout << "5. Cash-out\n";
    cout << "6. Pay Bill\n";
    cout << "7. Check Balance\n";
    cout << "8. History\n";
    cout << "9. Statement\n";
    cout << "10.Logout\n";
    cout << "Enter Your option(1 - 10) : ";
    int op;
    cin >> op;
    return op;
}

int search(string num){
    int flag = 0;
    for(int i = 0; i <= memct; i++){
        if(mem[i].number == num){
            flag = 1;
            return i;
        }
    }
    if(flag == 0){
        return -1;
    }
}

bool login(){
    cout << "Enter Your Mobile Number(11 Digit) : ";
    string num;
    cin >> num;
    cout << "Enter Your PIN(5 Digit) : ";
    string pin;
    cin >> pin;
    int pos = search(num);
    loggedMemPos = pos;
    if(pos != -1 && mem[pos].pin == pin){
        cout << "Login Successful!" << endl;
        return true;
    }
    else{
        cout << "Invalid Mobile Number or PIN!" << endl;
        return false;
    }
}

void registration(){
    cout << "Welcome to MyCash Registration." << endl;
    cout << "Start Here By Providing Some Basic Information." << endl;
    string num,nme,pin;
    float taka;
    getnum:
    cout << "Enter Your Mobile Number(11 Digit) : ";
    cin >> num;
    if(search(num) != -1){
        cout << "Mobile Number Already Exists!\nPlease Try Again with Different One." << endl;
        getchar();
        getchar();
        goto getnum;
    }
    if(num.size() != 11){
        cout << "Invalid Mobile Number.\nPlease Try Again." << endl;
        getchar();
        goto getnum;
    }
    mem[memct].number = num;
    getchar();
    cout << "Enter Your Name : ";
    getline(cin,nme); 
    mem[memct].name = nme;
    getpin:
    cout << "Enter Your PIN(5 Digit) : ";
    cin >> pin;
    if(pin.size() != 5){
        cout << "\aInvalid Pin! Please Enter a Valid Pin of Length 5." << endl;
        goto getpin;
    }
    string p2;
    cout << "Re-Enter PIN : ";
    cin >> p2;
    if(pin == p2){
        int OTP = rand() % 10000 + 1000;
        cout << "myCash OTP : " << OTP << endl;
        cout << "Enter OTP : "; 
        int otp;
        cin >> otp;
        if (otp == OTP){
            cout << "Registration Successful." << endl;
            cout << "You Have Got BDT 100 Registration Bonus." << endl; 
            mem[memct].pin = p2;
            mem[memct].amount = 100;
            memct++;
            int loggedMemPos = search(num);
        }
        else{
            cout << "OTP  Does NOT Matched." << endl;
            goto getpin;
        }
    }
    else{
        cerr << "PIN Must Be Same!" << endl;
        goto getpin;
    }

}

void update(){
    cout << "Old Name : " << mem[loggedMemPos].name << endl;
    cout << "New Name (Press Enter to Ignore) : ";
    getchar();
    string newname;
    getline(cin,newname);
    if(!newname.empty()){
        mem[loggedMemPos].name = newname;
    }
    cout << "Old PIN : " << mem[loggedMemPos].pin << endl;
    cout << "New PIN (Press Enter to Ignore) : ";
    string newpin;
    getline(cin,newpin);
    if(!newpin.empty()){
        cout << "Reconfirm Pin : ";
        string p2;
        cin >> p2;
        if(newpin == p2){ 
            int OTP = rand() % 10000 + 1000;
            cout << "myCash OTP : " << OTP << endl;
            cout << "Enter OTP : ";
            int otp;
            cin >> otp;
            if(otp == OTP){
                mem[loggedMemPos].pin = newpin;
            }
        }
    }
    cout << "Update Successful!" << endl;

}

void remove(){
    int OTP = rand() % 10000 + 1000;
    cout << "myCash OTP : " << OTP << endl;
    cout << "Enter OTP : ";
    int otp;
    cin >> otp;
    if (otp == OTP){
        cout << "Remove is Successful." << endl;
        mem[loggedMemPos].number = "0"; 
    }
}

void sent(){
    cout << "Enter Destination Number(11-digit) : ";
    string desNum;
    cin >> desNum;
    int desPos = search(desNum);
    if(desPos == -1){
        cerr << "Destination number not found in database.\n" ;
    }
    else{
        sentTop:
        cout << "Enter Amount : ";
        float koto;
        cin >> koto;
        cout << "Sending " << koto << " To " << desNum << endl;
        cout << "Are You Sure(Y/N)? ";
        char x;
        cin >> x;
        if(x == 'y' || x == 'Y'){
            if(mem[loggedMemPos].amount < koto){
                cout << "Insufficient Fund\n";
                goto sentTop;
            }
            int OTP = rand() % 10000 + 1000;
            cout << "myCash OTP : " << OTP << endl;
            cout << "Enter OTP : ";
            int otp;
            cin >> otp;
            if (otp == OTP){
                mem[loggedMemPos].amount -= koto;
                mem[desPos].amount += koto;
                // cout << loggedMemPos << " " << desPos << endl;
                // cout << mem[loggedMemPos].amount << " " << mem[desPos].amount << endl;
                v[loggedMemPos].push_back(histry("Send Money",koto,mem[loggedMemPos].amount)); 
                cout << "Transaction Successful!" << endl;
                cout << "Press any key go to main menu.....\n";
                getchar();
            }
        }
        else{
            cout << "Transaction Cancelled!" << endl;
            cout << "Press any key go to main menu.....";
        }
    }
}

void cashin(){
    cout << "Enter Amount : ";
    float koto;
    cin >> koto;
    cout << "Are You Sure(Y/N)? ";
    char x;
    cin >> x;
    if (x == 'y' || x == 'Y'){
        mem[loggedMemPos].amount += koto;
        v[loggedMemPos].push_back(histry("Cash-In   ",koto,mem[loggedMemPos].amount));
        cout << "Cash-in is Successful." << endl;
        cout << "Press any key go to main menu....."; 
        getchar();
        getchar();
    }
}

void cashout(){
    outtop:
    cout << "Enter Amount : ";
    float koto;
    cin >> koto;
    cout << "Are You Sure(Y/N)? ";
    char x;
    cin >> x;
    if (x == 'y' || x == 'Y'){
        if (mem[loggedMemPos].amount < koto){
            cout << "Insufficient Fund\n";
            goto outtop;
        }
        mem[loggedMemPos].amount -= koto;
        v[loggedMemPos].push_back(histry("Cash-Out  ",koto,mem[loggedMemPos].amount));
        cout << "Cash Out is Successful." << endl;
        cout << "Press any key go to main menu.....";
        getchar();
        getchar();
    }
}

void paybill(){
    cout << "Enter Bill Type (Gas/Electricity/Water/Internet-1/2/3/4) : ";
    int op;
    cin >> op;
    billtop:
    if(op == 1){
        cout << "Your Gas Bill : ";
    }
    else if(op == 2){
        cout << "Your Electricity Bill : ";
    }
    else if(op == 3){
        cout << "Your Water Bill : ";
    }
    else if(op == 4){
        cout << "Your Internet Bill : ";
    }
    float koto;
    cin >> koto;
    cout << "Want to pay(Y/N)? ";
    char x;
    cin >> x;
    if (x == 'y' || x == 'Y'){
        if (mem[loggedMemPos].amount < koto){
            cout << "Insufficient Fund\n";
            goto billtop;
        }
        int OTP = rand() % 10000 + 1000;
        cout << "myCash OTP : " << OTP << endl;
        cout << "Enter OTP : ";
        int otp;
        cin >> otp;
        if (otp == OTP){
            mem[loggedMemPos].amount -= koto;
            v[loggedMemPos].push_back(histry("Bill Pay  ",koto,mem[loggedMemPos].amount));
            cout << "Biull Payment Successful!" << endl;
            cout << "Press any key go to main menu.....\n";
            getchar();
        }
    }

}

void checkbal(){
    cout << "You Have ";
    cout << mem[loggedMemPos].amount << " BDT" << endl;
    getchar();
}

void history(){
    vector <histry> print = v[loggedMemPos];
    cout << "Tran ID    Description     Amount      Balance" << endl  << endl;
    for(auto val : print){
        cout << val.transID << "    " << val.description << "         " << val.transAmount << "        " << val.presentBalance << endl;
    }
}

void statement(){
    cout << "Your myCash Information : " << endl;
    cout << "Name : " << mem[loggedMemPos].name << endl;
    cout << "Phone Number : " << mem[loggedMemPos].number << endl;
    cout << "Balance : " << mem[loggedMemPos].amount << endl;
}

void option(int n){
    switch (n){
        case 1:
            update();
            break;
        case 2:
            remove();
            break;
        case 3:
            sent();
            break;
        case 4:
            cashin();
            break;
        case 5:
            cashout();
            break;
        case 6:
            paybill();
            break;
        case 7:
            checkbal();
            break;
        case 8:
            history();
            break;
        case 9:
            statement();
            break;
    }

}



int main(){
    system("cls");
    start:
    int choice = logre();
    if(choice == 1){
        system("cls");
        if (login()){
        menstart:
            int op = menu();
            if (op == 10){
                system("cls");
                goto start;
            }
            else{
                system("cls");
                option(op);
                if(op == 2) goto start;
                else goto menstart;
            }
        }
        else{
            goto start;
        }
    }
    else if(choice == 2){
        registration();
        getchar();
        cout << "Press any key go to Login menu.....";
        getchar();
        system("cls"); 
        goto start;        
    }
    else{
        exit(EXIT_SUCCESS);
    }

    return 0;
}
