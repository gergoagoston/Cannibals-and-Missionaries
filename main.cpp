#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Tstate
{
    bool side;
    int can, mis;                     //states
    struct Tstate *before;
};

int n = 3;
int m = 3;
int k = 2;

map<Tstate, int> levels;
queue<Tstate> qStates;

bool operator< (const Tstate &a, const Tstate &b)
{
    return a.side < b.side || (a.side==b.side && a.can<b.can) || (a.side==b.side && a.can==b.can && a.mis<b.mis);          //for the map
}

void printbhbh(Tstate t)
{
    if (t.before != nullptr)
        printbhbh(*t.before);                                //printing out the solution 
    cout << t.can << " " << t.mis << " " << t.side << endl;

}

int breadthFirstSearch()
{
    Tstate start, final;
    start.side = false;
    start.can = n;
    start.mis = m;
    start.before = nullptr;    //start state

    final.can = 0;
    final.mis = 0;              // final state
    final.side = true;
    qStates.push(start);

    levels[start] = 0;

    while (!qStates.empty() && !levels.count(final))
    {
        Tstate head = qStates.front();
        int aCan, aMis;

        if (!head.side)           // we are coming back from the left side or going to the left side 
        {
            aCan = head.can;
            aMis = head.mis;
        }
        else
        {
            aCan = n - head.can;
            aMis = m - head.mis;
        }
        for (int q = 0; q <= min(k, aMis); ++q)
        {
            for (int w = 0; w <= min(k - q, aCan); w++)
            {
                if ((q + w) == 0)              
                    continue;
                if (q && w > q)              //is there any missionaries and if there is then there are less then cannibals
                    break;
                start.side = !head.side;
                if (!head.side)      
                { 
                    start.can = head.can - w;               // calculating the new state
                    start.mis = head.mis - q;
                }
                else
                {
                    start.can = head.can + w;
                    start.mis = head.mis + q;
                }
                if ((start.can <= start.mis || start.mis == 0) && ((n - start.can) <= (m - start.mis) || start.mis == m) && !levels.count(start))
                {
                    start.before = new Tstate(head);          // checking if it is a valid state
                    levels[start] = levels[head] + 1;
                    qStates.push(start);
                }
            }
        }
        qStates.pop();
    }
    if (levels.count(final)){
        cout << "Solution:" << endl;
        printbhbh(start);
        return levels[final];
    }
    else
        return -1;
}

int main()
{
    int t = breadthFirstSearch();
    cout << "Solved in " << t<< " steps!";
}