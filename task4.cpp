#include <iostream>
#include <vector>
#include <algorithm>

class Task {
private:
    std::string description;
    bool completed;
public:
    Task(const std::string& desc) : description(desc), completed(false) {}

    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    std::string getDescription() const {
        return description;
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;
public:
    void addTask(const std::string& desc) {
        tasks.emplace_back(desc);
    }

    void viewTasks() const {
        if(tasks.empty()) {
            std::cout << "No tasks in the list." << std::endl;
            return;
        }

        std::cout << "Tasks:" << std::endl;
        for(size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i+1 << ". ";
            if(tasks[i].isCompleted()) {
                std::cout << "[X] ";
            } else {
                std::cout << "[ ] ";
            }
            std::cout << tasks[i].getDescription() << std::endl;
        }
    }

    void markTaskCompleted(size_t index) {
        if(index < tasks.size()) {
            tasks[index].markAsCompleted();
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

    void removeTask(size_t index) {
        if(index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }
};

int main() {
    ToDoList todoList;
    int choice;
    std::string taskDescription;

    do {
        std::cout << "\n1. Add Task\n2. View Tasks\n3. Mark Task as Completed\n4. Remove Task\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore();
                std::getline(std::cin, taskDescription);
                todoList.addTask(taskDescription);
                break;
            case 2:
                todoList.viewTasks();
                break;
            case 3:
                size_t markIndex;
                std::cout << "Enter the index of the task to mark as completed: ";
                std::cin >> markIndex;
                todoList.markTaskCompleted(markIndex - 1);
                break;
            case 4:
                size_t removeIndex;
                std::cout << "Enter the index of the task to remove: ";
                std::cin >> removeIndex;
                todoList.removeTask(removeIndex - 1);
                break;
            case 0:
                std::cout << "Exiting...";
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

    } while(choice != 0);

    return 0;
}
