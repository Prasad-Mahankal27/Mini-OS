#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User
{
public:
    string uname;
    string pass;

    User(string u, string p)
    {
        uname = u;
        pass = p;
    }
};

class Process
{
public:
    int pid;
    string pname;

    Process(int id, string name)
    {
        pid = id;
        pname = name;
    }

    void display()
    {
        cout << "Running Process: " << pname << " (PID: " << pid << ")" << endl;
    }
};

class MemoryManager
{
public:
    int total;
    int used;

    MemoryManager(int t)
    {
        total = t;
        used = 0;
    }

    bool allocate(int amt)
    {
        if (used + amt > total)
        {
            return false;
        }
        used += amt;
        return true;
    }

    void free(int amt)
    {
        used -= amt;
        if (used < 0)
        {
            used = 0;
        }
    }

    void status()
    {
        cout << "Memory Used: " << used << "/" << total << endl;
    }
};

class Shell
{
    vector<User> users;
    User* logged;
    vector<Process> processes;
    MemoryManager memory;
    int nextPid;

public:
    Shell() : memory(1024)
    {
        users.push_back(User("admin", "admin"));
        logged = NULL;
        nextPid = 1;
    }

    void prompt()
    {
        if (logged)
        {
            cout << "[" << logged->uname << "@MiniOS] $ ";
        }
        else
        {
            cout << "[guest@MiniOS] $ ";
        }
    }

    void login()
    {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].uname == u && users[i].pass == p)
            {
                logged = &users[i];
                cout << "Login successful\n";
                return;
            }
        }
        cout << "Invalid credentials\n";
    }

    void runProcess()
    {
        string pname;
        cout << "Enter process name: ";
        cin >> pname;
        processes.push_back(Process(nextPid++, pname));
        cout << "Process " << pname << " started\n";
    }

    void listProcesses()
    {
        if (processes.empty())
        {
            cout << "No processes running\n";
        }
        else
        {
            for (int i = 0; i < processes.size(); i++)
            {
                processes[i].display();
            }
        }
    }

    void memoryStatus()
    {
        memory.status();
    }

    void allocMemory()
    {
        int amt;
        cout << "Enter memory to allocate: ";
        cin >> amt;
        if (memory.allocate(amt))
        {
            cout << "Memory allocated\n";
        }
        else
        {
            cout << "Not enough memory\n";
        }
    }

    void freeMemory()
    {
        int amt;
        cout << "Enter memory to free: ";
        cin >> amt;
        memory.free(amt);
        cout << "Memory freed\n";
    }

    void exitShell()
    {
        processes.clear();
        cout << "Goodbye!\n";
    }

    void run()
    {
        string cmd;
        while (true)
        {
            prompt();
            cin >> cmd;
            if (cmd == "login")
            {
                login();
            }
            else if (cmd == "run")
            {
                runProcess();
            }
            else if (cmd == "ps")
            {
                listProcesses();
            }
            else if (cmd == "mem")
            {
                memoryStatus();
            }
            else if (cmd == "alloc")
            {
                allocMemory();
            }
            else if (cmd == "free")
            {
                freeMemory();
            }
            else if (cmd == "exit")
            {
                exitShell();
                break;
            }
            else
            {
                cout << "Unknown command\n";
            }
        }
    }
};

int main()
{
    Shell shell;
    shell.run();
    return 0;
}
