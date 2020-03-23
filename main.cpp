#include <iostream>
#include <queue>
using namespace std;

struct process {
    string name; 
    int arrival;
    int burst;
    int waiting;
};

class circular_queue {
private:
    int head, tail, size;
    process* array;
public:
    circular_queue(int s) {
        head = -1;
        tail = -1;
        size = s;
        array = new process[s];
    }
    void push(process p) {
        if ((head == 0 && tail == size-1) || (tail == (head-1) % (size-1))) 
            cout << "queue is full" << endl;
        else if (head == -1) {
            head = tail = 0;
            array[tail] = p;
        }
        else if (tail == size-1 && head != 0) {
            tail = 0;
            array[tail] = p;
        }
        else {
            tail++;
            array[tail] = p;
        }
    }
    void pop() {
        if (head == -1) {
            cout << "queue is empty" << endl;
            return;
        }
        process temp = {"", -1, -1, -1};
        array[head] = temp;
        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else if (head == size-1) 
            head = 0;
        else
            head++;
    }
    process top() {
        if (head == -1) {
            process temp {"", -1,-1,-1};
            return temp;
        }
        return array[head];
    }
    void decrementBurst() {
        array[head].burst--;
    }
    void displayQueue() {
        if (head == -1) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "elements in circular queue: " << endl;
        if (tail >= head) {
            for (int i=0;i<=tail;i++) {
                if (array[i].name != "")
                    cout << array[i].name << "-" << array[i].burst << " ";
            }
        }
        else {
            for (int i=head;i<size;i++) {
                if (array[i].name != "")
                    cout << array[i].name << "-" << array[i].burst << " ";
            }
            for (int i=0;i<=tail;i++) {
                if (array[i].name != "")
                    cout << array[i].name << "-" << array[i].burst << " ";
            }
        }
        cout << endl;
    }
};

// assume p list is always sorted by arriving time
// assume there's a process arriving at time 0
string roundRobin(process p[], int size, int quantum) {
    queue<process> queue;
    int total = 0;
    for (int i=0;i<size;i++) {
        queue.push(p[i]);
        total += p[i].burst;
    }

    string chart = "";
    int time = 0;
    int counter = 0;
    circular_queue schedule(size);
    while (time < total) {
        while (!queue.empty() && queue.front().arrival <= time+1) {
            schedule.push(queue.front());
            queue.pop();
        }
        if (counter < quantum && schedule.top().burst != 0) {
            schedule.decrementBurst();
            chart += schedule.top().name + "(" + to_string(time) + ") ";
            counter++;
        }
        if (counter >= quantum || schedule.top().burst == 0){
            process temp = schedule.top();
            schedule.pop();
            if (temp.burst != 0)
                schedule.push(temp);
            counter = 0;
        }
        time++;
    }
    return chart;
}



int main() {
    process a {"p1", 0, 4, 0};
    process b {"p2", 1, 5, 0};
    process c {"p3", 2, 2, 0};
    process d {"p4", 3, 1, 0};
    process e {"p5", 4, 6, 0};
    process f {"p6", 6, 3, 0};

    int size = 6;
    int quantum_unit = 2;
    process list[size] = {a, b, c, d, e, f};
    cout << roundRobin(list, size, quantum_unit) << endl;


    return 0;
}
