#include <iostream>
#include <string>

using namespace std;


class Date {
private:
    int year;
    int month;
    int day;

    bool isValidDate(int y, int m, int d) {
        if (y < 1300 || y > 1500) return false;
        if (m < 1 || m > 12) return false;
        if (d < 1 || d > 31) return false;

        else
            return true;
    }

public:

    Date(int y = 1403, int m = 1, int d = 1) {
        if (isValidDate(y, m, d)) {
            year = y;
            month = m;
            day = d;
        } else {
            year = 1403;
            month = 1;
            day = 1;
            cout << "The Date is invalid!" << endl;
        }
    }

    int getYear() {
         return year;
          }

    int getMonth() {
        return month;
         }

    int getDay() {
         return day;
          }

    void setDate(int y, int m, int d) {
        if (isValidDate(y, m, d)) {
            year = y;
            month = m;
            day = d;
        } else {
            cout << "The Date is invalid!" << endl;
        }
    }


    void show() {
        cout << year << "/" << month << "/" << day;
    }


    bool Comparison(Date d) {
        if (year < d.getYear()) return true;
        if (year > d.getYear()) return false;
        if (month < d.getMonth()) return true;
        if (month > d.getMonth()) return false;
        if (day < d.getDay()) return true;
        if (day > d.getDay()) return false;
        return false;
    }

};

class Task {
protected:
    string title;
    string description;
    bool done;
    Date createDate;
    Date deadline;
    string priority;

public:
    Task()
    {
        title = "";
        description = "";
        done = false;
        createDate = Date(1403, 1, 1);
        deadline = Date(1403, 1, 1);
        priority = "Low";
    }

    Task(string t, string desc, Date d, string p)
     {
        title = t;
        description = desc;
        deadline = d;
        priority = p;
        done = false;
        createDate = Date(1403, 1, 1);
    }

    string getTitle() {
        return title;
         }

    string getDescription() {
         return description;
          }

    bool isDone() {
        return done;
         }

    Date getDeadline() {
         return deadline;
          }

    string getPriority() {
         return priority;
          }

   void setStatus(bool status) {
      if (status == true)
        done = true;
      else
        done = false;
}

    bool isOverdue(Date currentDate) {
        return (!done && deadline.Comparison(currentDate));
    }

    virtual void show() {
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << (done ? "Done" : "Undone") << endl;
        cout << "DeadLine: ";
        deadline.show();
        cout << endl;
        cout << "Priority: " << priority << endl;
        cout << "------------------------" << endl;
    }

    virtual ~Task() {}
};


class Todo : public Task {
private:
    string category;

public:
    Todo() : Task() {
        category = "";
    }

    Todo(string t, string desc, Date d, string p, string cat): Task(t, desc, d, p) {
        category = cat;
    }

    void show() override {
        Task::show();
        cout << "Category: " << category << endl;
        cout << "------------------------" << endl;
    }
};

class TodoList {
private:
    Task* tasks[100];
    int taskCount;

    int priorityToNumber(string priority) {
        if (priority == "High") return 3;
        if (priority == "Medium") return 2;
        if (priority == "Low") return 1;
        return 0;
    }

public:

    TodoList() {
        taskCount = 0;
        for (int i = 0; i < 100; i++) {
            tasks[i] = NULL;
        }
    }


    void addTask() {
        if (taskCount >= 100) {
            cout << "The list is full!" << endl;
            return;
        }

        string title, desc, priority, category;
        int y, m, d;

        cout << "Add new task" << endl;

        cout << "Title: "<<endl;
        cin.ignore();
        getline(cin, title);

        cout << "Description: "<<endl;
        getline(cin, desc);

        cout << "Deadline date: "<<endl;
        cin >> y >> m >> d;

        cout << "Priority: "<<endl;
        cin >> priority;

        cout << "Category: "<<endl;
        cin.ignore();
        getline(cin, category);

        Date deadline(y, m, d);
        tasks[taskCount] = new Todo(title, desc, deadline, priority, category);
        taskCount++;

        cout << "Task Added!" << endl;
    }

    void deleteTask() {
        if (taskCount == 0) {
            cout << "The list is empty!" << endl;
            return;
        }

        cout << "Delete Task" << endl;
        showAllTasks();

        int index;
        cout << "Task number to delete: ";
        cin >> index;

        if (index > 0 && index <= taskCount) {
            delete tasks[index - 1];

            cout << "The tsak was deleted" << endl;
        }
    }


    void toggleTaskStatus() {
        if (taskCount == 0) {
            cout << "The task list is empty!" << endl;
            return;
        }

        cout << "Change of work status" << endl;
        showAllTasks();

        int index;
        cout << "Task number: ";
        cin >> index;

        if (index > 0 && index <= taskCount){
          if (!tasks[index - 1]->isDone()) {
            tasks[index - 1]->setStatus(true);
            cout << "Task done!" << endl;
        }

        } else {
            cout << "Invalid number!" << endl;
        }
        }



    void showAllTasks() {
        if (taskCount == 0) {
            cout << "The list is empty!" << endl;
            return;
        }

        cout << "List of all tasks" << endl;
        for (int i = 0; i < taskCount; i++) {
            cout << "Task number :" << i + 1 << endl;
            tasks[i]->show();
        }
    }

    void showDoneTasks() {
        bool found = false;
        cout << "Tasks done" << endl;

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i]->isDone()) {
                cout << "Task number: " << i + 1 << endl;
                tasks[i]->show();
                found = true;
            }
        }

        if (!found) {
            cout << "Task not done!" << endl;
        }
    }


    void showNotDoneTasks() {
        bool found = false;
        cout << "Tasks not done" << endl;

        for (int i = 0; i < taskCount; i++) {
            if (!tasks[i]->isDone()) {
                cout << "Task number: " << i + 1 << endl;
                tasks[i]->show();
                found = true;
            }
        }

        if (!found) {
            cout << "Task done" << endl;
        }
    }


    void showOverdueTasks(Date currentDate) {
        bool found = false;
        cout << "Overdue Tasks" << endl;

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i]->isOverdue(currentDate)) {
                cout << "Task number: " << i + 1 << endl;
                tasks[i]->show();
                found = true;
            }
        }

        if (!found) {
            cout << "There is no overdue task!" << endl;
        }
    }


    void sortByPriority() {
        if (taskCount == 0) {
            cout << "The task list is empty!" << endl;
            return;
        }


        for (int i = 0; i < taskCount - 1; i++) {
            for (int j = 0; j < taskCount - i - 1; j++) {
                int p1 = priorityToNumber(tasks[j]->getPriority());
                int p2 = priorityToNumber(tasks[j + 1]->getPriority());

                if (p1 < p2) {
                    Task* temp = tasks[j];
                    tasks[j] = tasks[j + 1];
                    tasks[j + 1] = temp;
                }
            }
        }

        cout << "Task by priority" << endl;
        for (int i = 0; i < taskCount; i++) {
            cout << "Task number: " << i + 1 << endl;
            tasks[i]->show();
        }
    }


    void sortByDeadline() {
        if (taskCount == 0) {
            cout << "The task list is empty!" << endl;
            return;
        }



        for (int i = 0; i < taskCount - 1; i++) {
            for (int j = 0; j < taskCount - i - 1; j++) {
                if (tasks[j + 1]->getDeadline().Comparison(tasks[j]->getDeadline())) {
                    Task* temp = tasks[j];
                    tasks[j] = tasks[j + 1];
                    tasks[j + 1] = temp;
                }
            }
        }

        cout << "Task by deadline" << endl;
        for (int i = 0; i < taskCount; i++) {
            cout << "Task number: " << i + 1 << endl;
            tasks[i]->show();
        }
    }



    ~TodoList() {
        for (int i = 0; i < taskCount; i++) {
            delete tasks[i];
        }
    }
};


void showMenu() {
    cout << "TODO LIST" << endl;
    cout << "1. ADD TASK" << endl;
    cout << "2. SHOW ALL TASKS" << endl;
    cout << "3. SHOW DONE TASKS" << endl;
    cout << "4. SHOW NOT DONE TASKS" << endl;
    cout << "5. SHOW OVERDUE TASKS" << endl;
    cout << "6. TOGGLE TASKS STATUS" << endl;
    cout << "7. DELETE TASK" << endl;
    cout << "8. SORT BY PRIORITY" << endl;
    cout << "9. SORT BY DEADLINE" << endl;
    cout << "0. EXIT" << endl;
}

int main() {
    TodoList todoList;
    int choice;

    int y, m, d;
    cout << "Today's date: ";
    cin >> y >> m >> d;
    Date currentDate(y, m, d);

    do {
        showMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                todoList.addTask();
                break;

            case 2:
                todoList.showAllTasks();
                break;

            case 3:
                todoList.showDoneTasks();
                break;

            case 4:
                todoList.showNotDoneTasks();
                break;

            case 5:
                todoList.showOverdueTasks(currentDate);
                break;

            case 6:
                todoList.toggleTaskStatus();
                break;

            case 7:
                todoList.deleteTask();
                break;

            case 8:
                todoList.sortByPriority();
                break;

            case 9:
                todoList.sortByDeadline();
                break;

            case 0:
                cout << "THE END" << endl;
                break;

            default:
                cout << "INVALID" << endl;
        }

    } while(choice != 0);

    return 0;
}

//Ehsan Fakhri
//Alireza Javaheri
