// problem #4: Task Manager
// Author: Omar Mohamed Elgammal - FCAI
// Description: Displays current proccess running on your OS 
//              and shows the memory usage of them.
// Note: comment line #48 if you are not using windows

// Importing necessary libraries
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// Class for each process and its (name, id, memory used)
class process{
    protected:
        string name;
        int id;
        string memory;
    public:
        // Constructor that takes process members
        process(string name_, int id_, string memory_){
            name = name_;
            id = id_;
            memory = memory_;
        }

        // Getters
        string getMemory(){
            return memory;
        }
        int getID(){
            return id;
        }
        string getName(){
            return name;
        }
};

// Class to manage running processes
class taskManager{
    protected:
        vector<process> tasks;
    public:

        // Constructor that stores process into vector
        void addProcess(process p){
            tasks.push_back(p);
        }

        // Function that displays all processes in tasks
        void print(){
            cout << left << setw(35) << "Program Name";
            cout << right << setw(10)<< "PID";
            cout << right << setw(15) << "MemoryUsed"<< endl;
            for(auto i : tasks){
                cout << left << setw(35) << i.getName();
                cout << right << setw(10)<< i.getID();
                cout << right << setw(15) << i.getMemory() << "K" << endl;
            }
    }

    // Function that gets all current processes and stores them in tasks
    void getCurrentTasks(){
        // Command to get all running processes and store them in text file
        system("tasklist > tasks.txt");
        ifstream file("tasks.txt"); // opening file
        string line;
        string trash;
        // ignoring first 3 lines
        getline(file, line);
        getline(file, line);
        getline(file, line);
        // using stringstream to get each word
        while(getline(file, line)){
            string name, memory;
            int id;
            // getting process name and removing extra spaces
            name = line.substr(0, 25);
            while(name.back() == ' '){
                name.pop_back();
            }
            line = line.substr(25, line.length() - 1); // removing name from line
            stringstream ss(line);
            
            // Getting id and memory from line and neglecting other elements
            ss >> id >> trash >> trash >> memory; 
            process p(name, id, memory); // creating process object
            addProcess(p); // adding process to tasks
        }
    }

    // Function that sorts tasks by memory used (a for ascending and d for desending)
    void sort_by_memory(char order = 'd'){
        if(order == 'a'){
            sort(tasks.begin(), tasks.end(), [](process a, process b){
            if(a.getMemory().size() < b.getMemory().size()){
                return true;
            }
            else if(a.getMemory().size() == b.getMemory().size()){
                return a.getMemory() < b.getMemory();
            }
            return false;
        });
        }
        else{
            sort(tasks.begin(), tasks.end(), [](process a, process b){
            if(a.getMemory().size() > b.getMemory().size()){
                return true;
            }
            else if(a.getMemory().size() == b.getMemory().size()){
                return a.getMemory() > b.getMemory();
            }
            return false;
        });
        }
        
    }

    // Function that sorts tasks by process id
    void sort_by_id(){
        sort(tasks.begin(), tasks.end(), [](process a, process b){
            return a.getID() < b.getID();
        });
    }
    
    // Function that sorts tasks by process name
    void sort_by_name(){
        sort(tasks.begin(), tasks.end(), [](process a, process b){
            return a.getName() < b.getName();
        });
    }
};

int main(){
    taskManager tm;
    tm.getCurrentTasks();
    tm.sort_by_memory();
    // tm.sort_by_name();
    // tm.sort_by_id();
    tm.print();

}