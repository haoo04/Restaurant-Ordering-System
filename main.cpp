#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;

//global variable
const int MAXSIZE = 100;        //set the maximum size for an array
double total_price = 0;         //assign 0 to variable total_price
double totalPayment = 0;        //assign 0 to variable totalPayment
int o = 0;
int orderCount = 0;             //assign 0 to variable orderCount
double totalTips = 0;           //assign 0 to variable totalTips

//group together variables menuItemIndex and quantiti with data types int under name Order
struct Order
{
    int menuItemIndex;
    int quantity;
};

string total_order[MAXSIZE];    //set the maximum size of array total_order
Order orders[MAXSIZE];          //Declare an array total_order of type order

//group together some different variables with different data types int under name Customer
struct Customer
{
    string name;
    int table = 0;
    string foodNames[MAXSIZE];
    double foodPrices[MAXSIZE];
    double totalPrice = 0.0;
    int foodCount = 0;  // To keep track of the number of foods ordered by this customer
};

Customer customers[MAXSIZE];        //Declare an array customers of type Customer
int customerCount = 0;

//decoration purpose
void show()
{
    cout << "==============================================" << endl;
    cout << "    Welcome to Paradise Restaurant" << endl;
    cout << "==============================================" << endl;
}

//decoration purpose
void showCus(string& name)
{
    cout << "==============================================" << endl;
    cout << "   Welcome to Paradise Restaurant -- " << name << endl;
    cout << "==============================================" << endl;
}

//decoration purpose
void showAdmin()
{
    cout << "***********************************************" << endl;
    cout << "         You Are In The Admin Mode." << endl;
    cout << "***********************************************" << endl;
}

//Allow user leave a rating and comment for our service
void captureFeedback()
{
    int rating;
    string comment;
    cout << "----------------------------------" << endl;
    cout << "  Please rate our service (1-5): ";
    cin >> rating;
    cout << "----------------------------------" << endl;
    cout << endl;
    cin.ignore();
    cout << "PLease give us some comment to improve: ";
    getline(cin, comment);
    ofstream review;
    review.open("review.txt", ios::app);
    if (review.is_open())
    {
        review << rating << endl;
        review << comment << endl;
    }
    review.close();
}

//display menu to customer and record the order into array, calculate the total price
void displayMenu(const string& filename, double& total_price, string total_order[], int& o)
{
    int choice, j = 0;
    double price[MAXSIZE]{};
    string items[MAXSIZE];

    ifstream menu_file(filename);       //open the file by the filename that pass by function menu()
    cout << endl;
    cout << " Number\t| Price     |\tMenu" << endl;
    cout << "-------------------------------------------------" << endl;
    while (!menu_file.eof())
    {
        getline(menu_file, items[j]);
        menu_file >> price[j];
        menu_file.ignore();
        cout << " " << j + 1 << ".\t| RM" << price[j] << "    |\t" << items[j] << endl;
        j++;
    }
    cout << "-------------------------------------------------" << endl;
    cout << endl;
    cout << "==============================================" << endl;
    cout << "Please select an option: ";
    cin >> choice;
    cout << endl;
    if (choice <= j && choice > 0)
    {
        total_price += price[choice - 1];
        total_order[o] = items[choice - 1];

        customers[customerCount].foodNames[o] = items[choice - 1];
        customers[customerCount].foodPrices[o] = price[choice - 1];
        customers[customerCount].foodCount++;
        o++;
    }
    else 
    {
        cout << "Invalid Number !" << endl;
    }

    menu_file.close();
}

//show the order items of customer and the total price
void cus_order(string total_order[], int o, int& table, double total_price, string& name)
{
    cout << "This is your bill :" << endl;
    cout << "***************************************" << endl;
    cout << "          Paradise Restaurant          " << endl;
    cout << "***************************************" << endl;
    cout << "Table: " << table << endl;
    cout << "Name: Mr/Ms " << name << endl;
    cout << "Your order food is: " << endl;
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << " Number\t| Price     |\tMenu" << endl;
    cout << "-------------------------------------------------" << endl;
    for (int i = 0; i < o; ++i)
    {
        cout << "   " << i + 1 << ".\t| RM"
            << customers[customerCount].foodPrices[i]
            << "    |\t" << total_order[i] << endl;
    }

    cout << "-------------------------------------------------" << endl;
    cout << showpoint << fixed << setprecision(2);
    cout << "Your Total Price of Food is: RM " << total_price << endl;

}

//allow customer cancel the ordered items 
void cancel_order(string total_order[], int& o, int& table, string& name)
{
    int cancel;
    cus_order(total_order, o, table, total_price, name);
    cout << "Enter the number of the item you wish to cancel: ";
    cin >> cancel;

    if (cancel > 0 && cancel <= o)
    {
        // Shift all items down in the array to "remove" the chosen item
        for (int i = cancel - 1; i < o - 1; i++)
        {
            total_order[i] = total_order[i + 1];
            total_price -= customers[customerCount].foodPrices[i];
        }

        // Decrement the total order count
        o--;
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}

//show the menu by category, pass the filename to function displaymenu() to show the details manu
void menu(int table, double& total_price, string total_order[], int& o, string& name)
{
    int choice;
    char cont, conti;

    customers[customerCount].name = name;
    customers[customerCount].table = table;

    do
    {
        showCus(name);      //call function showCus()
        //show available service
        cout << "           Customer Menu Table -- " << table << ": " << endl;
        cout << "==============================================" << endl;
        cout << "           1. Main Food" << endl;
        cout << "           2. Snak" << endl;
        cout << "           3. Beverage" << endl;
        cout << "           4. Special" << endl;
        cout << "           5. exit" << endl;
        cout << "==============================================" << endl;
        cout << endl;
        cout << "Choose the category you want: ";       //enter the service needed
        cin >> choice;

        system("cls");
        showCus(name);
        switch (choice)
        {
            //call function displayMenu() by following category
        case 1:
            displayMenu("main.txt", total_price, total_order, o);
            break;
        case 2:
            displayMenu("snak.txt", total_price, total_order, o);
            break;
        case 3:
            displayMenu("bev.txt", total_price, total_order, o);
            break;
        case 4:
            displayMenu("special.txt", total_price, total_order, o);
            break;
        case 5:
            break;;
        default:
            cout << "Invalid number!!!" << endl;
            break;
        }
        cout << "Do you want to continue order? (y-yes/n-no): ";
        cin >> cont;
        system("cls");
    } while (tolower(cont) == 'y');     //loop when customer need to continue order other item

    customers[customerCount].totalPrice = total_price;

    system("cls");

    do
    {
        cus_order(total_order, o, table, total_price, name);
        char cancel;
        cout << "Do you want to cancel any item? (y-yes/n-no): ";
        cin >> cancel;

        if (tolower(cancel) == 'y')
        {
            system("cls");
            cancel_order(total_order, o, table, name);      //call function cancel_order()
        }
        else
            break;
        cout << "Do you want to continue? (y-yes/n-no): ";
        cin >> conti;
    } while (tolower(conti) == 'y');        //loop while customer want to cancel another item

    cout << "Thanks for your ordering, your order is being prepared\n";
    cout << "Remember return to main menu and select service 2 to make payment ^_^" << endl;
    system("pause");
    system("cls");
}

void make_payment()
{
    totalPayment = total_price * 1.06;      //calculate the total payment that include 6% service tax
    double pay, change = 0;
    char tipChoice;
    cout << "-----------------------------------------------------" << endl;
    cout << "Please enter the amount that you want to pay: RM ";     //customer can enter the amount that need to pay
    cin >> pay;

    //reject the payment while the payment amount not enough
    while (pay < totalPayment)
    {
        cout << "your payment amount are not enough" << endl;
        cout << "Please enter again: RM";
        cin >> pay;
    }
    change = pay - totalPayment;        //calculate the change when the payment amount more than the total payment

    //When the change is not equal to 0, ask the customer if they are willing to leave tips
    if (change != 0)
    {
        double tips;
        cout << "This is the balance: RM" << change << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << endl;
        cout << "Would You like to pay some tips? " << endl;
        cout << "Yes (y) / No (n) : ";
        cin >> tipChoice;
        if (tolower(tipChoice) == 'y')
        {
            cout << "Please enter the amount of tips that you are willing to pay:" << endl;     //cuastomer can enter the tips that want to leave
            cout << "RM ";
            cin >> tips;
            totalTips += tips;
            cout << "Thank you for your recognition of our service !!! ^_^" << endl;    //show the thanks message to customer
            system("pause");
            system("cls");
        }
        else {
            system("cls");
        }
    } 
    else{    
    cout << "Your payment is successful !" << endl;
    system("pause");
    system("cls");
    }
}

void payment(int& table, string& name, double total_price)
{
    double total_payment = total_price * 1.06;      //calculate the total payment that include 6% service tax
    cus_order(total_order, o, table, total_price, name);
    cout << showpoint << fixed << setprecision(2);
    cout << "The total amount need to pay is: RM " << total_payment     //show the amount that the customer need to pay
        << " (include 6% service tax)" << endl;
    make_payment();         //call function make_payment()
    captureFeedback();      //call function captureFeedback()
    cout << "Thanks for your support and please come again!" << endl;      //show thanks message
    customerCount++;
    system("pause");
    system("cls");
}

void customerMenu(int& table, string& name)
{
    int choice;
    show();
    cout << endl;
    cout << "How can we address you: ";     //ask customer enter name
    cin >> name;
    cout << endl;
    cout << "Please enter the number of your table: ";      //ask customer enter table
    cin >> table;
    while (table > 0 && table < 100)
    {
        //show the available service
        cout << "==============================================" << endl;
        cout << "            1. Order Food" << endl;
        cout << "            2. Payment" << endl;
        cout << "            3. Exit" << endl;
        cout << "==============================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3)
        {
            break;
        }
        system("cls");

        switch (choice)
        {
        case 1:
            menu(table, total_price, total_order, o, name);     //call function menu() to continue order
            break;
        case 2:
            payment(table, name, total_price);      //call function payment() to make payment
            return;
        case 3:
            break;
        default:
            cout << "Invalid number!" << endl;
            system("pause");
            break;
        }
    }
    system("cls");
}

//declare array with the suitable data type
string menuList[MAXSIZE];
double menuListPrice[MAXSIZE];
string employeeID[MAXSIZE];
string employeeName[MAXSIZE];
string employeePass[MAXSIZE];
int index = 0;
int menuCount = 0;
int employeeCount = 0;

void calculateTotalRevenue()
{
    double totalRevenue = 0;      //initialize totalRevenue to 0
    for (int i = 0; i < customerCount; i++)
    {
        totalRevenue += customers[i].totalPrice;        //calculate total revenue
    }
    cout << "Total Revenue: " << totalRevenue << endl;      //show the total revenue
}

void disMenu(const string& menuFileName)
{
    ifstream menufile(menuFileName);        //open menufile by the filname pass by function viewmenu()
    if (!menufile.is_open())
    {
        cout << "Error opening file " << menuFileName << endl;
        return;
    }

    menuCount = 0;
    cout << endl;
    cout << showpoint << fixed << setprecision(2);
    cout << "-------------------------------------------------" << endl;
    cout << " Number\t|\tPrice\t|\tMenu" << endl;
    cout << "-------------------------------------------------" << endl;
    while (getline(menufile, menuList[menuCount])) // Read a menu item
    {
        menufile >> menuListPrice[menuCount]; // Read the price
        menufile.ignore(); // Ignore the newline character after the price
        menuCount++;
    }
    for (int k = 0; k < menuCount; k++)
    {
        cout << "   " << k + 1 << ".\t|\t" << menuListPrice[k]
            << "\t|\t" << menuList[k] << endl;
    }
    cout << "-------------------------------------------------" << endl;

}

void viewMenu()
{
    bool view = true;
    while (view)
    {
        int cat;
        showAdmin();
        cout << endl;
        //show all the category of menu
        cout << "\t -------------------------- " << endl;
        cout << "\t|         Category         |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << "\t|      1. Main Menu        |" << endl;
        cout << "\t|      2. Snak Menu        |" << endl;
        cout << "\t|      3. Beverage Menu    |" << endl;
        cout << "\t|      4. Special Menu     |" << endl;
        cout << "\t|      5. Exit             |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << endl;
        //ask customer enter the category
        cout << "Enter the category you want: ";
        cin >> cat;

        system("cls");

        if (cat == 5)
        {
            break;
        }
        switch (cat)
        {
            //call function disMenu and pass the filename
        case 1:
            disMenu("main.txt");
            break;
        case 2:
            disMenu("snak.txt");
            break;
        case 3:
            disMenu("bev.txt");
            break;
        case 4:
            disMenu("special.txt");
            break;
        default:
            cout << "Invalid number!!!" << endl;
            continue;
        }
    }

}

void addItem(const string& menuname)
{
    system("cls");
    showAdmin();    //call function showAdmin()
    cout << endl;
    cout << "\t       Add Item Menu" << endl;
    cout << "\t__________________________" << endl;
    cout << endl;
    if (menuCount >= MAXSIZE)
    {
        cout << "Menu is full.\n";
    }

    ofstream menufile(menuname, ios::app);
    if (!menufile.is_open())
    {
        cout << "Error opening file " << menuname << endl;
    }
    //enter the name of new item that need to added
    cout << "Enter the name of the new menu item: ";
    cin.ignore();
    getline(cin, menuList[menuCount]);

    //enter the price of new item that need to added
    cout << "Enter the price of the new menu item: ";
    cin >> menuListPrice[menuCount];

    menufile << endl << menuList[menuCount] << endl
        << menuListPrice[menuCount];
    menufile.close();

}

void addMenu()
{
    while (true)
    {
        int cat;
        if (menuCount >= MAXSIZE)
        {
            cout << "Menu is full.\n";
        }
        showAdmin();        //call function showAdmin()
        cout << endl;
        //show the available service
        cout << "\t -------------------------- " << endl;
        cout << "\t|      Menu Management     |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << "\t|     1. Main Menu         |" << endl;
        cout << "\t|     2. Snak Menu         |" << endl;
        cout << "\t|     3. Beverage Menu     |" << endl;
        cout << "\t|     4. Special Menu      |" << endl;
        cout << "\t|     5. Exit              |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << endl;
        cout << "Select the menu you want to add: ";    //ask user to select menu that needed
        cin >> cat;

        if (cat == 5)
        {
            break;
        }
        switch (cat)
        {
            //call function addItem() and pass the filename
        case 1:
            addItem("main.txt");
            break;
        case 2:
            addItem("snak.txt");
            break;
        case 3:
            addItem("bev.txt");
            break;
        case 4:
            addItem("special.txt");
            break;
        case 5:
            break;
        default:
            cout << "Invalid number!!!" << endl;
            break;
        }

        menuCount++;
        cout << "Item added successfully.\n";
        system("cls");
    }
}

//Edit the name and price of item that now available in menu
void editMenu()
{
    showAdmin();
    cout << "\t      Edit item Menu" << endl;
    cout << "\t__________________________" << endl;
    viewMenu();

    int index;
    cout << "Enter the index of the menu item to edit : ";
    cin >> index;
    if (index >= 0 && index <= menuCount)
    {
        cout << "Enter the new name of the menu item: ";
        cin.ignore();
        getline(cin, menuList[index - 1]);
        cout << "Enter the new price of the menu item: ";
        cin >> menuListPrice[index - 1];
        cout << "Item edited successfully.\n";
    }
    else
    {
        cout << "Invalid index.\n";
    }
    system("cls");

}

//Delete the item that now available in menu
void deleteMenu()
{
    showAdmin();
    cout << "\t     Delete item Menu" << endl;
    cout << "\t__________________________" << endl;
    viewMenu();

    int del;
    cout << "Enter the index of the menu item to delete: ";
    cin >> del;

    if (del > 0 && del <= menuCount)
    {
        // Shift items to fill the gap
        for (int i = del - 1; i < menuCount - 1; i++)
        {
            menuList[i] = menuList[i + 1];
            menuListPrice[i] = menuListPrice[i + 1];
        }

        menuCount--;

        cout << "Item deleted successfully.\n";
    }
    else
    {
        cout << "Invalid index.\n";
    }
    system("cls");
}

void menuManagement()
{
    while (true)
    {
        int choice;
        showAdmin();
        cout << endl;
        //show available service for menu management
        cout << "\t -------------------------- " << endl;
        cout << "\t|      Menu Management     |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << "\t|     1. View menu         |" << endl;
        cout << "\t|     2. Add Item          |" << endl;
        cout << "\t|     3. Edit Item         |" << endl;
        cout << "\t|     4. Delete Item       |" << endl;
        cout << "\t|     5. Exit              |" << endl;
        cout << "\t -------------------------- " << endl;
        cout << endl;
        cout << "Select an option: ";
        cin >> choice;

        system("cls");

        if (choice == 5)
        {
            break;
        }
        switch (choice) {
        case 1:
            viewMenu();     //call function viewMenu()
            break;
        case 2:
            addMenu();      //call function addMenu()
            break;
        case 3:
            editMenu();     //call function editMenu()
            break;
        case 4:
            deleteMenu();   //call function deleteMenu()
            break;
        case 5:
            system("cls");
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

}

//view the rate and review that leave by customer
void viewReview()
{
    showAdmin();
    cout << endl;
    cout << "\t ------------------------------ " << endl;
    cout << "\t|   Customer rate and review   |" << endl;
    cout << "\t ------------------------------ " << endl;
    cout << endl;
    int i = 0;
    int rate[MAXSIZE]{};
    string rev[MAXSIZE];
    ifstream view;
    view.open("review.txt");
    if (!view.is_open())
    {
        cout << "File is not exits!!!";
    }
    else
    {
        //read the data from review.txt
        int rateVal;
        string revVal;
        while (!view.eof())
        {
            view >> rateVal;
            view.ignore();
            getline(view, revVal);
            if (i < MAXSIZE)
            {
                rate[i] = rateVal;
                rev[i] = revVal;
                i++;
            }
            else
            {
                cout << "Max review capacity reached. Skipping the rest.\n";
                break;
            }
        }
    }
    for (int j = 0; j < i; j++)
    {
        cout << "\tThe Customer [" << j + 1 << "] rate is -- "
                << rate[j] << endl;
        cout << "\tThe Customer comment: " << rev[j] << "." << endl;
    }
    cout << endl;
    view.close();
    system("pause");
    system("cls");
}

//read the data from employee.txt and store in array
void readFile()
{
    ifstream employee("employee.txt");
    string id, name, password;
    while (employee >> id >> name >> password)
    {
        employeeID[index] = id;
        employeeName[index] = name;
        employeePass[index] = password;
        index++;
    }
    employee.close();
}

//write the data into employee.txt
void writeFile()
{
    ofstream employee("employee.txt");
    if (!employee.is_open())
    {
        cout << "Error opening file for writing." << endl;
        return;
    }
    for (int i = 0; i < index; ++i)
    {
        employee << employeeID[i] << "\n";
        employee << employeeName[i] << "\n";
        if (i == index - 1)
        {  // If we're on the last record
            employee << employeePass[i];  // Don't append a newline
        }
        else
        {
            employee << employeePass[i] << "\n";  // Otherwise, do append a newline
        }
    }
    employee.close();
}

//display the current employee in restaurant
void displayEmployees()
{
    cout << " -------------------------- " << endl;
    cout << "|     Current Employees    | " << endl;
    cout << " -------------------------- " << endl;
    for (int i = 0; i < index; ++i)
    {
        cout << "|      ID: " << employeeID[i] << "-- Name: "
            << employeeName[i] << endl;  // Not displaying passwords for security
    }
    system("pause");
    system("cls");
}
bool check(string id) 
{
    for (int i = 0; i < index; ++i) 
    {
        if (employeeID[i] == id) 
        {
            return true; // ID is a duplicate
        }
    }
    return false; // ID is not a duplicate
}
//add the new employee
void addEmployee()
{
    string id, name, password;
    cout << "Enter employee ID: ";
    cin >> id;
    cout << "Enter employee name: ";
    cin >> name;
    cout << "Enter employee password: ";
    cin >> password;
    if (index >= MAXSIZE)
    {
        cout << "Employee database is full." << endl;
        return;
    }
    if (!check(id)) 
    {
        employeeID[index] = id;
        employeeName[index] = name;
        employeePass[index] = password;
        index++;    
        cout << "Employee added." << endl;
        writeFile();        //call function writefile()
    }
    else{
        cout << "Employee id already exist!"<<endl;
        cout << "Please try again" << endl;
    }
}

//delete the current employee
void deleteEmployee(string id)
{
    bool found = false;
    for (int i = 0; i < index; i++)
    {
        if (employeeID[i] == id)
        {
            found = true;
            for (int j = i; j < index - 1; j++)
            {
                employeeID[j] = employeeID[j + 1];
                employeeName[j] = employeeName[j + 1];
                employeePass[j] = employeePass[j + 1];
            }
            index--;
            cout << "Employee deleted." << endl;
            writeFile();      //call function writeFile()
            return;
        }
    }
    if (!found)
    {
        cout << "Employee ID not found." << endl;
    }
    system("pause");
    system("cls");
}

void employeeManagement()
{
    readFile();     //call function readFile()
    string name, id, password;
    int choice;
    while (true)
    {
        showAdmin();        //call function showAdmin()
        //show the available service for menu management
        cout << "\t ------------------------------ " << endl;
        cout << "\t|     Employee Management      |" << endl;
        cout << "\t ------------------------------ " << endl;
        cout << "\t|     1. Add employee          |" << endl;
        cout << "\t|     2. Delete employee       |" << endl;
        cout << "\t|     3. Display employee      |" << endl;
        cout << "\t|     4. Exit                  |" << endl;
        cout << "\t ------------------------------ " << endl;
        cout << endl;
        cout << "Choose the service you want: ";
        cin >> choice;

        if (choice == 4)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            cout << endl;
            cout << "\t    Add Employee Menu" << endl;
            cout << "\t__________________________" << endl;
            cin.ignore();
            addEmployee();        //call function addEmployee()
            system("pause");
            system("cls");
            break;
        case 2:
            showAdmin();        //call function showAdmin()
            displayEmployees(); //call function displayEmployee()
            cout << endl;
            cout << "\t   Delete Employee Menu" << endl;
            cout << "\t__________________________" << endl;
            cout << "Enter employee ID to delete: ";
            cin >> id;
            deleteEmployee(id); //call function deleteEmployee and pass the parameter id
            break;
        case 3:
            displayEmployees(); //call function displayEmployee()
            break;
        case 4:
            system("cls");
            return;
        default:
            cout << "Invalid number!!!" << endl;
        }
    }
}

//display the customer data include Name, Table, and Total Price
void displayCusData()
{
    cout << " --------------------------------------------- " << endl;
    cout << "|              Customer Data                  |" << endl;
    cout << " --------------------------------------------- " << endl;
    cout << setw(15) << "Name" << setw(10) << "Table"
        << setw(15) << "Total Price" << endl;
    cout << " --------------------------------------------- " << endl;

    for (int i = 0; i < customerCount; ++i)
    {
        cout << setw(15) << customers[i].name << setw(10)
            << customers[i].table << setw(15)
            << customers[i].totalPrice << endl;
        cout << "Food Orders:" << endl;
        for (int j = 0; j < customers[i].foodCount; ++j)
        {
            cout << "  - " << customers[i].foodNames[j] << ": $"
                << customers[i].foodPrices[j] << endl;
        }
        cout << "---------------------------------------------" << endl;
    }
    system("pause");
    system("cls");
}

//show the total sales for today
void todaySales()
{
    showAdmin();
    cout << " ---------------------------------- " << endl;
    cout << "|          Today's Sales           |" << endl;
    cout << " ---------------------------------- " << endl;

    double totalSales = 0.0;

    for (int i = 0; i < customerCount; ++i)
    {
        totalSales += customers[i].totalPrice;      //calculate the totalSales
    }

    cout << "Total Sales for Today: $" << fixed
        << setprecision(2) << totalSales << endl;
    system("pause");
    system("cls");
}

void adminMenu()
{

    int choice;
    while (true)
    {
        showAdmin();        //call function showAdmin()
        cout << endl;
        //Show the available service
        cout << " ----------------------------------------------- " << endl;
        cout << "|         Welcome back to the Admin menu        |" << endl;
        cout << " ----------------------------------------------- " << endl;
        cout << "|            1. Menu Management                 |" << endl;
        cout << "|            2. View Customer review            |" << endl;
        cout << "|            3. Employee management             |" << endl;
        cout << "|            4. Today Sales                     |" << endl;
        cout << "|            5. Customer data                   |" << endl;
        cout << "|            6. Exit                            |" << endl;
        cout << " -----------------------------------------------" << endl;
        cout << "Select an option: ";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
            menuManagement();       //call function menuManagement()
            break;
        case 2:
            viewReview();           //call function viewreview()
            break;
        case 3:
            employeeManagement();   //call function employeeManagement()
            break;
        case 4:
            todaySales();           //call function todaySales()
            break;
        case 5:
            displayCusData();       //call function displayCusData()
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

void loadEmployees()
{
    ifstream employee("employee.txt");
    while (!employee.eof())
    {
        getline(employee, employeeID[employeeCount]);  // Read the employee ID
        getline(employee, employeeName[employeeCount]);  // Read the employee name
        getline(employee, employeePass[employeeCount]);  // Read the employee password
        employeeCount++;
    }
    employee.close();
}

//admin login interface
bool adminLogin()
{
    loadEmployees();
    string enterID, enterPass;
    cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "|        Admin authentication         |" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;
    cout << "      Enter your Employee ID: ";
    cin >> enterID;
    cout << "_______________________________________" << endl;
    cout << endl;
    for (int i = 0; i < employeeCount; ++i)
    {
        if (employeeID[i] == enterID)
        {
            cout << "      Welcome back -- " << employeeName[i]
                << " ^_^ " << endl;
            cout << "    Enter password -- ";
            cin >> enterPass;
            cout << "_______________________________________" << endl;
            cout << endl;

            if (enterPass == employeePass[i])
            {
                cout << "     Authentication successful.\n";
                return true;
            }
            else
            {
                cout << " Invalid password.\n";
                cout << "Please try it again." << endl;
                return false;
            }
        }
    }
    cout << " Employee ID not found.\n";
    return false;
}

//main function
int main()
{
    int serv, table;
    string name;
    bool loop = true;
    while (loop)
    {
        show();     //call function show()
        //display available service
        cout << "        1. Customer Ordering Service " << endl;
        cout << "        2. System Management Service" << endl;
        cout << "        3. Exit" << endl;
        cout << "==============================================" << endl;
        cout << endl;
        cout << "Choose the service you want: ";
        cin >> serv;

        if (serv == 3)
        {
            break;
        }

        system("cls");

        switch (serv)
        {
        case 1:
            customerMenu(table, name);      //call function customerMenu(table,name)
            break;
        case 2:
            if (adminLogin())       //if return value of adminLogin() = true
            {
                cout << "        Admin access granted\n";
                cout << " Now you can go in to the admin menu." << endl;
                cout << endl;
                system("pause");
                system("cls");
                adminMenu();    //call function adminMenu()
            }
            else
            {
                cout << "Access denied.\n";
            }
            break;
        case 3:
            break;
        default:
            cout << "Invalid input number!!!" << endl;
            system("pause");
            main();     //call function main()
        }
    }
    cout << endl;
    system("pause");
    return 0;
}