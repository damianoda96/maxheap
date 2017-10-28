#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
//# include <bits/stdc++.h>

using namespace std;

/*int stoi(string str)
{
   stringstream ss(str);
   int N;
   ss<<str;
   ss>>N;
   return N;
}*/

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
        maxHeapVect.push_back(s);

        int i = size() - 1;

        max_heapify(i);
    }

    void buildHeap(vector<string> fileVect)
    {
        for(int i = 0; i < fileVect.size(); i++)
        {
            insertKey(fileVect[i]);
        }
    }

    int size()
    {
        return maxHeapVect.size();
    }

    void swap(string& s1, string& s2)
    {
        string temp = s2;
        s2 = s1;
        s1 = temp;
    }

    string grab_lname(string element)
    {
        string lname;
        int spaceCounter = 0;

        for(int j = 0; j < element.size(); j++)
        {
            if(isspace(element[j]))
            {
                spaceCounter++;
            }
            if(spaceCounter == 2)
            {
                break;
            }
            if(isalpha(element[j]) && spaceCounter == 1)
            {
                lname += element[j];
            }
        }

        return lname;

    }

    void print_in_order()
    {
        for(int i = 0; i < size(); i++)
        {
            cout << maxHeapVect[i] << endl;
        }
    }

    void delete_by_id(string s)
    {
        for(int i = 0; i < size(); i++)
        {
            cout << convert_for_ID(maxHeapVect[i]);
            if(stoi(s) == convert_for_ID(maxHeapVect[i]))
            {

                maxHeapVect.erase(remove(maxHeapVect.begin(), maxHeapVect.end(), maxHeapVect[i]), maxHeapVect.end());
            }
        }
    }

    void delete_by_lname(string s)
    {
        for(int i = 0; i < size(); i++)
        {
            if(s == grab_lname(maxHeapVect[i]))
            {
                cout << "found match" << endl;
                maxHeapVect.erase(remove(maxHeapVect.begin(), maxHeapVect.end(), maxHeapVect[i]), maxHeapVect.end());
            }
        }
    }

    void max_heapify(int i)
    {
        if(build_by_id)
        {
            if (i && convert_for_ID(maxHeapVect[parent(i)]) < convert_for_ID(maxHeapVect[i]))
            {
                swap(maxHeapVect[i], maxHeapVect[parent(i)]);

                max_heapify(parent(i));
            }
        }
        else if(build_by_name)
        {
            if (i && convert_for_lname(maxHeapVect[parent(i)]) < convert_for_lname(maxHeapVect[i]))
            {
                swap(maxHeapVect[i], maxHeapVect[parent(i)]);

                max_heapify(parent(i));
            }
        }
    }

    int convert_for_ID(string element)
    {
        string idS;
        int id;
        int spaceCounter = 0;

        for(int j = 0; j < element.size(); j++)
        {
            if(isspace(element[j]))
            {
                spaceCounter++;
            }
            if(isdigit(element[j]))
            {
                idS+=element[j];
            }
            if(spaceCounter == 3)
            {
                break;
            }
        }

        id = stoi(idS);

        return id;

    }

    char convert_for_lname(string element)
    {
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
void addRecord(maxHeap&);
void deleteRecord(maxHeap&);
void printSortedList(maxHeap);
void saveSortedList(maxHeap);
void loadAndPrintFile();
void clearBinaryFile();


int main()
{
    int selection;
    bool running = true;

    vector<string> fileVect;
    vector<string> heaped_vect;
    maxHeap m_heap;

    while(running)
    {
        cout << "Please follow steps 1-9 in order" << endl;
        cout << "Select one of the following options and hit enter:" << endl;
        cout << "(1) Read data from an external file" << endl;
        cout << "(2) Build max heap in terms of ID or LastName" << endl;
        cout << "(3) Add record to max heap" << endl;
        cout << "(4) Delete Record from max heap" << endl;
        cout << "(5) Print sorted list from max heap in ascending order based on ID or last name" << endl;
        cout << "(6) Save sorted list in external file" << endl;
        cout << "(7) Load binary file and print records one line at a time" << endl;
        cout << "(8) Clear Binary" << endl;
        cout << "(9) Exit program" << endl;

        cin >> selection;

        cin.ignore(1000, '\n');

        switch (selection)
        {
            case 1:
                fileVect = readExternal();
                break;
            case 2:
                m_heap = build_Heap(fileVect);
                m_heap.print_in_order();
                break;
            case 3:
                addRecord(m_heap);
                m_heap.print_in_order();
                break;
            case 4:
                deleteRecord(m_heap);
                m_heap.print_in_order();
                break;
            case 5:
                printSortedList(m_heap);
                break;
            case 6:
                saveSortedList(m_heap);
                break;
            case 7:
                loadAndPrintFile();
                break;
            case 8:
                clearBinaryFile();
                break;
            case 9:
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
        cout << "You selected ID" << endl;
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

    m_heap.buildHeap(fileVect);

    return m_heap;
}

void addRecord(maxHeap& m_heap)
{
    string newRecord;
    cout << "Please enter the new record in correct format: Firstname Lastname id(integer) gpa(float)" << endl;
    getline(cin, newRecord);

    cout << endl;

    m_heap.insertKey(newRecord);
}

void deleteRecord(maxHeap& m_heap)
{
    string recordToDelete;
    cout << "Please enter the ID or last name of the record being deleted:" << endl;
    getline(cin, recordToDelete);

    if(isdigit(recordToDelete[0]))
    {
        m_heap.delete_by_id(recordToDelete);
    }
    else if(isalpha(recordToDelete[0]))
    {
        m_heap.delete_by_lname(recordToDelete);
    }
    else
    {
        cout << "You inputed an incorrect string..";
    }
}

void printSortedList(maxHeap m_heap)
{
    m_heap.print_in_order();
}

void saveSortedList(maxHeap m_heap)
{
    fstream myFile("316p2.rec", ios::out | ios::binary);
    myFile.write((char*)&m_heap, sizeof(maxHeap));
    myFile.close();
}

void loadAndPrintFile()
{
    ifstream myFile;
    
    maxHeap* readHeap = new maxHeap[10];

    myFile.open("316p2.rec", ios::in | ios::binary);
    
    myFile.read((char*)readHeap, sizeof(maxHeap) * 10);
    
    for(int i = 0; i < readHeap->size(); i++)
    {
        cout << readHeap->maxHeapVect[i] << endl;
    }
        
    myFile.close();
}

void clearBinaryFile()
{
    ofstream myFile;
    
    myFile.open("316p2.rec", ofstream::out | ofstream::trunc);
    
    myFile.close();
}




