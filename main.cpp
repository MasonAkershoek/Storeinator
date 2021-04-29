
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

string temp;

void PressEnterToContinue()
  {
    cout << "\nPress ENTER to continue... " << flush;
    cin.ignore( numeric_limits <streamsize> ::max(), '\n' );
  }

struct info
{
  public:
  string iName;
  int iamount;

  void collect()
  {
    cout << "What is the item?" << endl;
    cout << ">";
    cin >> iName;
    cout << "\nHow many do you have?" << endl;
    cout << ">";
    cin >> iamount;
    cout << "\n\nItem " << iName << " has been added" << endl;
    PressEnterToContinue();
    getline(cin, temp);
  }
};

class Output
{
  public:
  
  vector< string > items;
  vector< int > amount;
  int del;

  void view(int index)
  {
    cout << "\n\nthis is what you have" << endl;
    cout << "------------------------------" << endl;
    cout << "INDEX      AMOUNT     ITEMS" << endl;
    for(int i = 0; i < index; ++i)
    {
      cout << i+1 << "            " << amount[i] << "          " << items[i] << endl;
    }
    PressEnterToContinue();
    getline(cin, temp);
  }

  int goaway(int index)
  {
    cout << "\n\nthis is what you have" << endl;
    cout << "What would you like to deleate?" << endl;
    cout << "------------------------------" << endl;
    cout << "INDEX      AMOUNT     ITEMS" << endl;
    for(int i = 0; i < index; ++i)
    {
      cout << i+1 << "            " << amount[i] << "          " << items[i] << endl;
    }
    cout << "\n\n>";
    cin >> del;
    cout << "\n\nItem " << items[del-1] << " has been deleted" << endl;
    return del;
  }

  void save(int index)
  {
    ofstream myFile;
    myFile.open("item.txt");
    for(int i = 0; i < index; ++i)
    {
      myFile << items[i] << endl;
    }
    myFile.close();

    myFile.open("amount.txt");
    for(int i = 0; i < index; ++i)
    {
      myFile << amount[i] << endl;
    }
    myFile.close();
  }
};

int main() {
  Output myOutput;
  info myInfo;
  int quit = 0;
  int quiting = 0;
  string qu;
  int index = 0;
  int del;

  do
  {
    START:
    int choice;
    cout << "\n\nWelcome to the storinator" << endl;
    cout << "-----------------------------------" << endl;
    cout << "choose an option\n" << endl;
    cout << "1. Chech your stored things." << endl;
    cout << "2. Add items" << endl;
    cout << "3. Deleate items" << endl;
    cout << "4. Save" << endl;
    cout << "5. Load" << endl;
    cout << "6. Quit" << endl;
    cout << endl << ">";
    cin >> choice;

    if(choice == 1)
    {
      myOutput.view(index);
    }
    else if(choice == 2)
    {
      myInfo.collect();
      myOutput.items.push_back(myInfo.iName);
      myOutput.amount.push_back(myInfo.iamount);
      ++index;
      quiting = 1;
    }
    else if(choice == 3)
    {
      del = myOutput.goaway(index);
      del = del - 1;
      myOutput.items.erase(myOutput.items.begin() + del);
      myOutput.amount.erase(myOutput.amount.begin() + del);
      --index;
      quiting = 1;
    }
    else if(choice == 4)
    {
      myOutput.save(index);
      quiting = 0;
    }
    else if(choice == 5)
    {
      string line;
      int lins;
      ifstream myFile;
      myFile.open("item.txt");
      while(getline (myFile,line))
      {
        myOutput.items.push_back(line);
      }
      myFile.close();

      myFile.open("amount.txt");
      int as;
      while (myFile >> as)
      {
        myOutput.amount.push_back(as);
        ++index;
      }
      myFile.close();
          }
    else if(choice == 6)
    {
      if (quiting == 1)
      {
        cout << "you have not saved yet are you sure you want to quit? (Y or N) >";
        cin >> qu;
        if(qu == "Y")
        {
          ++quit;
          cout << "you have quit.";
        }
        else if (qu == "N")
        {
          goto START;
        }
      }
      else if (quiting == 0)
      {
        ++quit;
        cout << "You have quit.";
      }
    }
  }while(quit == 0);
}
