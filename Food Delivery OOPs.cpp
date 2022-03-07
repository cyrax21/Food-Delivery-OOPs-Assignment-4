#include<bits/stdc++.h>
using namespace std;

class Executive{
    int id; // id of this Executive
    int currentTasks; // currently active assigned to this executive
    int taskLimit; // maximum limit of this Executive
    int totalTaskDone;  // count of all the task done by this executive
    public:
    Executive(int id) {
        this->id = id;
        currentTasks = 0;
        taskLimit = 10;
        totalTaskDone = 0;
        cout<<"Executive "<<this->id<<" hired\n"<<endl;
    }

    // assign task to executive
    void assignTask() {
        // if task count exceeds limit
        if(currentTasks >= taskLimit) {
            cout<<"This Executive already delivered maximum orders\n"<<endl;
            return;
        }
        cout<<"Executive "<<id<<" was assigned a task\n"<<endl;
        currentTasks++;
        totalTaskDone++;
    }

    // complete task to executive
    void completeTask() {
        // if no task assigned return unsucess message
        if(currentTasks==0){
            cout<<"No task exist for Executive\n"<<id<<endl;
            return;
        }
        currentTasks--;
        cout<<"Executive "<<id<<" completed a task\n"<<endl;
    }

    // payment to the executive
    int makePayment(int amount) {
        // total amount to be payed to executive
        int pay = totalTaskDone*amount;

        // total task will be 0 now.
        totalTaskDone = 0;
        return pay;
    }

    // no of task is active to the executive
    int getTasks() {
        return currentTasks;
    }
};

class DeliverProduct{
    int currentEmpId; // it store te executive no to be assigned to nhew employee
    map<int, Executive*> mapEmp; // map the id with executive
    stack<int> newExecutive; // it store the newest employee
    int minEmp, maxEmp; // min and max employee limit
    int countOfActiveEmp; // it store the currently active employee
    public:
    DeliverProduct() {
        currentEmpId = 0;
        minEmp = 2, maxEmp = 10;
        countOfActiveEmp = 0;
    }

    // hire a employee
    void hire(){
        if(countOfActiveEmp>=10){
            cout<<"Maximum limit to hire executive reached\n"<<endl;
            return;
        }
        currentEmpId++;
        // create executive
        Executive* newEmp = new Executive(currentEmpId);

        mapEmp[currentEmpId] = newEmp; // map the id with Executive object
        newExecutive.push(currentEmpId); //push the newest
        countOfActiveEmp++;
    }

    // release an Executive with id
    void release(int id) {
        // if active participate is less than 2, we cant release this executive.
        if(countOfActiveEmp<=2){
            cout<<"More Executive can't be released\n"<<endl;
            return;
        }
        cout<<"Executive "<<id<<" was assigned a task\n"<<endl;
        delete(mapEmp[id]); // release the employee -> delete the object
        mapEmp.erase(mapEmp.find(id)); // erase it
        countOfActiveEmp--; // decreae the count of active Executive
    }

    // add task to newest executive
    void AddTask(){
        int id;
        if(mapEmp.size()!=0) {

            // get the newest executive using stack
            while(newExecutive.size()!=0){
                id = newExecutive.top();
                if(mapEmp.find(id)!=mapEmp.end()) break;
                else newExecutive.pop(); // if employee with id is release pop it simply
            }
        }
        else{
            cout<<"Sorry no executive found.\n"<<endl;
        }

        // assign task to executive
        mapEmp[id]->assignTask();
    }

    // complete a task with employee id
    void CompleteTask(int id) {
        mapEmp[id]->completeTask();

        // if there is no task for the employee we have to payout
        if(mapEmp[id]->getTasks()==0){
            int pay;
            cout<<"What is the amount to be payed to executive "<<id<<" per delivery ?"<<endl;
            cin>>pay;
            cout<<"Executive "<<id<<" completed all the tasks, so total payment is ";
            cout<<mapEmp[id]->makePayment(pay)<<"\n"<<endl;
        }
    }
};

int main() {
    DeliverProduct* dp = new DeliverProduct();
    while(1){
        int input;
        cout<<"-------Enter the operation you want to do ?---------"<<endl;
        cout<<"Press 1, Hire an Employee\nPress 2, Release an Employee\nPress 3, Assign Task\nPress 4, Complete Task\nPress 5, Quit"<<endl;
        cout<<"------------------------------------"<<endl;
        cin>>input;
        int id;

        switch(input) {
            case 1:
                dp->hire();
                break;
            case 2:
                cout<<"Enter the executive you want to release ? "<<endl;
                cin>>id;
                dp->release(id);
                break;
            case 3:
                dp->AddTask();
                break;
            case 4:
                cout<<"Enter the Executive who completed the task ? "<<endl;
                cin>>id;
                dp->CompleteTask(id);
                break;
            default:
                cout<<"Invalid Input ! Try Again"<<endl;
        }
        if(input==5){
            return 0;
        }
    }
}



