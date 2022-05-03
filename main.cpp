/*
Dan Bui
4/30/22
Dr. T @ TCC

Program to process payment and print a receipt for ordering food

Learned how to work with vectors
*/

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<math.h>
#include <fstream>
using namespace std; 

/*struct MenuItem
{
  string name;
  double itemCost; 
  string desc; 
  char addLetter; 
  char removeLetter;
  int count; 
};*/

class MenuItem
{
  private:
    string name;
    double itemCost; 
    string desc; 
    char addLetter; 
    char removeLetter;
    int count;
  public:
    MenuItem()
    {
      desc = "delicious"; 
      count = 0;
    }
    void setName(string n) { name = n; }
    void setItemCost(double iC) { itemCost = iC; }
    void setDesc(string d) { desc = d; }
    void setAddLetter(char aL) { addLetter = aL; }
    void setRemoveLetter(char rL) { removeLetter = rL; }
    void setCount(int c) { count = c; }
    string getName() { return name; }
    double getItemCost() { return itemCost; }
    string getDesc() { return desc; }
    char getAddLetter() { return addLetter; }
    char getRemoveLetter() { return removeLetter; }
    int getCount() { return count; }
    int addCount() { return count++; }
    int subtractCount() { return count--; }
};

//function definitions
void populateMenu(vector<MenuItem> &entireMenu)
{
  //put some default values in our Menu
  const int numItems = 7; 
  MenuItem Item1; 
  MenuItem Item2;
  MenuItem Item3; 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;    

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2); //add to the end of list the Item2
  entireMenu.push_back(Item3); //add to the end of list the Item3
  entireMenu.push_back(Item4); //add to the end of list the Item4
  entireMenu.push_back(Item5); //add to the end of list the Item5
  entireMenu.push_back(Item6); //add to the end of list the Item6
  entireMenu.push_back(Item7); //add to the end of list the Item7

  vector<string> defaultMenuNames = {"Green Tea", "Burrito", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7"}; 
  vector<char> defaultAddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; 
  vector<char> defaultRemoveLetters = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently 
    entireMenu[i].setName(defaultMenuNames[i]); 
    entireMenu[i].setAddLetter(defaultAddLetters[i]); 
    entireMenu[i].setRemoveLetter(defaultRemoveLetters[i]); 
    entireMenu[i].setItemCost(3.00 + i); //set a random starter cost for each item
  }
}

void showMenu(vector<MenuItem> &m)
{
  string red = "\x1b[31;1m";
  string green = "\x1b[32;1m";
  string brown = "\x1b[33;1m";
  string blue = "\x1b[34;1m";
  string pink = "\x1b[35;1m";
  string reset = "\x1b[0m";
  cout << fixed << setprecision(2);//set doubles to 2 decimal places
  cout << green << "DrT's Effcient Menu" << reset << endl; 
  cout << blue << "ADD  \tNAME \t COST \tREMOVE\tCOUNT\tDESC" << reset << endl; 
  for(int i = 0; i < m.size(); i++)
  {
    cout << brown << m[i].getAddLetter() << reset << ")" << setw(10) << m[i].getName() 
    << setw(5) << "$" << m[i].getItemCost() << setw(5) << "(" << pink << m[i].getRemoveLetter()
    << reset << ")" << setw(7) << m[i].getCount() << setw(13) << m[i].getDesc() 
    <<endl; 
  }

}

void printReciept(vector <MenuItem> &m, double subtotal, double tip, double totalDue, double change)
{
  string red = "\x1b[31;1m";
  string green = "\x1b[32;1m";
  string blue = "\x1b[34;1m";
  string reset = "\x1b[0m";
  ofstream outfile;
  outfile.open("Reciept.txt");
	if (outfile.is_open())
	{
    cout << green << "\n\n********************Reciept********************" << reset;
    outfile << "********************Reciept********************";
    cout << blue << left << setw(19) << "\n\nItem"
         << "Item Count"
         << right << setw(22) << "Item Cost\n\n" << reset;
    outfile << left << setw(19) << "\n\nItem"
            << "Item Count"
            << right << setw(22) << "Item Cost\n\n";
    for(int i = 0; i < m.size(); i++)
    {
      if(m[i].getCount() > 0)
      {
        cout << left << setw(20) << m[i].getName()
             << right << setw(7) << m[i].getCount()
             << setw(20) << m[i].getCount() * m[i].getItemCost() << endl;
        outfile << left << setw(20) << m[i].getName()
             << right << setw(7) << m[i].getCount()
             << setw(20) << fixed << setprecision(2) << m[i].getCount() * m[i].getItemCost() << endl;
      }
    }
    cout << "\n" << red << setw(37) << "Subtotal: " << reset << setw(10) << subtotal << endl;
    outfile << "\n" << setw(37) << "Subtotal: " << setw(10) << fixed << setprecision(2) << subtotal << endl;
    cout << red << setw(37) << "Tax: " << reset << setw(10) << subtotal * 1.0825 << endl;
    outfile << setw(37) << "Tax: " << setw(10) << fixed << setprecision(2) << subtotal * 1.0825 << endl;
    cout << red << setw(37) << "Total Due: " << reset << setw(10) << totalDue << endl;
    outfile << setw(37) << "Total Due: " << setw(10) << fixed << setprecision(2) << totalDue << endl;
    cout << red << setw(37) << "Change: " << reset << setw(10) << change << endl;
    outfile << setw(37) << "Change: " << setw(10) << fixed << setprecision(2) << change << endl;
  }
  outfile.close();
}

void acceptOrder(vector<MenuItem> &m)
{
  char option = '\0';// the user-selected menu item
  double subtotal = 0.0;
  double totalDue = 0.0;
  double tip = 0.0;
  double tender = 0.0;
  double change = 0.0;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option; 

    for(int i=0; i < m.size(); i++)
    {
      if(option == m[i].getAddLetter())
      {
        cout << "\nMenu Item " << m[i].getAddLetter() << " selected."; 
        m[i].addCount(); //increment the count by 1
        cout << "\033[2J\033[1;1H"; //clear screen 
        cout << "\n1 UP on " << m[i].getName() << endl;
        subtotal += m[i].getItemCost(); //increment the subtotal by the cost of the item 
        showMenu(m); //show the updated menu
        cout << "\nSubtotal: $" << subtotal << endl;  
      }
      else if(option == m[i].getRemoveLetter())
      {
        cout << "\nRemove Item " << m[i].getRemoveLetter() << " selected."; 
        if(m[i].getCount() > 0) //subtract if and only if the count is > 0
        {
          m[i].subtractCount(); //decrement the count by 1
          cout << "\033[2J\033[1;1H"; //clear screen 
          cout << "\n1 DOWN on " << m[i].getName() << endl;
          subtotal -= m[i].getItemCost(); //decrement the subtotal by the cost of the item
          showMenu(m); //show the updated menu
          cout << "\nSubtotal: $" << subtotal << endl;  
        }
        else //the the user why you blocked item removal 
        {
            
            cout << "\nItem count must be > 0 to remove: " << m[i].getName() << endl;
        }
      }
      else if(
                option != m[i].getAddLetter() && 
                option != m[i].getRemoveLetter() &&
                option != 'x' &&
                option != 'X'
            ) //test for all of my valid inputs
            {
              if(i == 0)
              {
                cout << "\nInvalid input (" << option << "). Please try again." << endl; 
              }  
            }
    }
  }while(option != 'x' && option != 'X'); 
  cout << "\nThank you for placing your order." << endl; 
  //handle the tip process here
  if(subtotal > 0.0)
  {
    cout << "\nPlease enter tip % (recommended 20%): ";
    cin >> tip;
  
    totalDue = (subtotal * 1.0825) * ((tip / 100.0) + 1.0);
    totalDue = trunc(totalDue * 100.0) / 100.0;
  
    cout << "\nPayment options:";
    cout << "\nA) Credit Card";
    cout << "\nB) Cash" << endl;
    while(true)
    {
      cin >> option;
      if(option == 'A' || option == 'a')
      {
        cout << "\nPlease provide $" << totalDue << ": ";
        while(true)
        {
          cin >> tender;
          if(tender >= totalDue)
          {
            cout << "\nProcessing payment...";
            break;
          }
          else
          {
            cout << "Please provide the required amount: ";
          }
        }
        break;
      }
      else if(option == 'B' || option == 'b')
      {
        cout << "\nPlease provide $" << totalDue << ": ";
        while(true)
        {
          cin >> tender;
          if(tender >= totalDue)
          {
            change = tender - totalDue;
            cout << "\nYour change is: " << change;
            cout << "\nProcessing payment...";
            break;
          }
          else
          {
            cout << "Please provide the required amount (): ";
          }
        }
        break;
      }
      else
      {
        cout << "\nPlease enter a valid option: ";
      }
    }
  }
  
  //handle reciept generation here
  printReciept(m, subtotal, tip, totalDue, change);
}

int main() 
{
  char option = '\0';
  while(true)
  {
    cout << "New customer? (y/n): ";
    cin >> option;
    if(option == 'Y' || option == 'y')
    {
      system("clear");
      vector<MenuItem> wholeMenu; 
      populateMenu(wholeMenu); //put some default values in the menu
      showMenu(wholeMenu); //print the current data of the menu on screen 
      acceptOrder(wholeMenu);
    }
    else if(option == 'N' || option == 'n')
    {
      cout << "\nExiting...";
        break;
    }
    else
      cout << "Invalid option...\n";
  }
  
  return 0; 
}