#include <iostream>
#include <fstream>
#include <vector>
#include <string>
# include <bits/stdc++.h>

using namespace std;

int stoi(string str)
{
   stringstream ss(str);
   int N;
   ss<<str;
   ss>>N;
   return N;
}

struct maxHeap
{
    vector<string> maxHeapVect;
    int size_of_heap;

    bool build_by_id;
    bool build_by_name;

    maxHeap()
    {
        size_of_heap = 0;
    }

    int parent(int i)
    {
        return (i-1)/2;
    }

    int left(int i)
    {
        return (2*i)+1;
    }

    int right(int i)
    {
        return (2*i)+2;
    }

    void insertKey(string s)
    {
        size_of_heap++;

        int i= size_of_heap - 1;

        maxHeapVect.push_back(s);

        max_heapify(i);
    }

    void deleteKey(int i)
    {

    }

    void buildHeap(vector<string> fileVect)
    {
        for(int i = 0; i < fileVect.size() - 1; i++)
        {
            insertKey(fileVect[i]);
        }
    }

    void max_heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if(build_by_id == true)
        {
            if(convert_for_ID(maxHeapVect[l]) > convert_for_ID(maxHeapVect[i])) //do this for all comparisons in max_heapify!!!
            {
                largest = l;
            }
            if(convert_for_ID(maxHeapVect[r]) > convert_for_ID(maxHeapVect[largest]))
            {
                largest = r;
            }
            if(largest != i)
            {
                string temp = maxHeapVect[i];
                maxHeapVect[i] = maxHeapVect[largest];
                maxHeapVect[largest] = maxHeapVect[i];

                max_heapify(largest);
            }
        }
        else if(build_by_name == true)
        {
            if(convert_for_lname(maxHeapVect[l]) > convert_for_lname(maxHeapVect[i]))
            {
                largest = l;
            }
            if(convert_for_lname(maxHeapVect[r]) > convert_for_lname(maxHeapVect[largest]))
            {
                largest = r;
            }
            if(largest != i)
            {
                string temp = maxHeapVect[i];
                maxHeapVect[i] = maxHeapVect[largest];
                maxHeapVect[largest] = maxHeapVect[i];

                max_heapify(largest);
            }
        }
    }

    int convert_for_ID(string element)
    {
        //string element = maxHeapVect[i];
        string idS;
        int id;

        for(int j = 0; j < element.size(); j++)
        {
            if(isdigit(element[j]))
            {
                idS+=element[j];
            }
        }

        id = stoi(idS);

        return id;

    }

    char convert_for_lname(string element)
    {
        //string element = maxHeapVect[i];
        char lname;
        bool hit_first_space = false;

        for(int j = 0; j < element.size(); j++)
        {
            if(isspace(element[j]))
            {
                hit_first_space = true;
            }
            if(isalpha(element[j]) && hit_first_space)
            {
                lname = tolower(element[j]);
                break;
            }
        }

        return lname;
    }
};

vector<string> readExternal();
maxHeap build_Heap(vector<string>);
void addRecord();
void deleteRecord();
void sortList();
void printSortedList();
void saveSortedList();
void loadAndPrintFile();


int main()
{
    int selection;
    bool running = true;

    vector<string> fileVect;
    vector<string> heaped_vect;
    maxHeap m_heap;

    while(running)
    {

        cout << "Select one of the following options and hit enter:" << endl;
        cout << "(1) Read data from an external file" << endl;
        cout << "(2) Build max heap in terms of ID or LastName" << endl;
        cout << "(3) Add record to max heap" << endl;
        cout << "(4) Delete Record from max heap" << endl;
        cout << "(5) Print sorted list from max heap in ascending order based on ID or last name" << endl;
        cout << "(6) Save sorted list in external file" << endl;
        cout << "(7) Load binary file and print records one line at a time" << endl;
        cout << "(8) Exit program" << endl;

        cin >> selection;

        cin.ignore(1000, '\n');

        switch (selection)
        {
            case 1:
                fileVect = readExternal();
                break;
            case 2:
                m_heap = build_Heap(fileVect);
                break;
            case 3:
                addRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                printSortedList();
                break;
            case 6:
                saveSortedList();
                break;
            case 7:
                loadAndPrintFile();
                break;
            case 8:
                running = false;
                return 0;
                break;
            default:
                cout << "You entered an incorrect character..." << endl;
                break;


        }

    }

    return 0;
}

vector<string> readExternal()
{
    ifstream inFile;
    string fileName;
    string fileString;

    vector<string> fileVect;

    maxHeap m_heap;

    cout << "Enter external file name or type 'default' to use default external file:" << endl;
    getline(cin, fileName);
    cout << "You entered: " << fileName << endl;

    if(fileName == "default")
    {
        inFile.open("cs316p2.dat");
    }
    else
    {
        inFile.open(fileName);
    }

    if(!inFile)
    {
        cerr << "unable to open " << fileName << endl;
    }

    while(!inFile.eof())
    {
        getline(inFile, fileString);
        cout << fileString << endl;
        fileVect.push_back(fileString);
    }
    inFile.close();

    return fileVect;

}

maxHeap build_Heap(vector<string> fileVect)
{
    maxHeap m_heap;
    string choice;
    cout << "Type 'id' for heap built by id, or 'lastname' for heap built by last name:" << endl;
    getline(cin, choice);

    if(choice == "id")
    {
        m_heap.build_by_id = true;
        m_heap.build_by_name = false;
    }
    else if(choice == "lastname")
    {
        m_heap.build_by_id = false;
        m_heap.build_by_name = true;
    }
    else
    {
        cout << "you entered an incorrect string..";
        exit(0);
    }

    //implement buildHeap! use our vector to insert current listing into heap by either id or name.
    //to order, index each element for either id number, or first letter of last name, and use this char as the comparison
    //to order with the maximum element as the parent, and ordering down from there.
    m_heap.buildHeap(fileVect);
}

void addRecord()
{
    string newRecord;
    cout << "Please enter the new record in correct format:" << endl;
    getline(cin, newRecord);
}

void deleteRecord()
{
    string recordToDelete;
    cout << "Please enter the ID or last name of the record being deleted:" << endl;
    getline(cin, recordToDelete);

    if(isdigit(recordToDelete[0]))
    {
        cout << "An ID was inputed" << endl;
    }
    else if(isalpha(recordToDelete[0]))
    {
        cout << "A last name was inputed";
    }
    else
    {
        cout << "You inputed an incorrect string..";
    }
}

void printSortedList()
{

}

void saveSortedList()
{

}

void loadAndPrintFile()
{

}




