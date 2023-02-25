#include <iostream>
#include <vector>

using namespace std;

int abs(int a)
{
    if (a < 0)
    {
        return -a;
    }
    else
    {
        return a;
    }
}

// Returns the 4 new "corners".
int *f(int a, int b, int c, int d)
{
    return new int[4]{abs(a - b), abs(b - c), abs(c - d), abs(d - a)};
}

int sum(int *arr)
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += arr[i];
    }
    return sum;
}

struct StepSolution
{
    int steps;
    vector<vector<int>> path;
};

// Gives you the numbers of steps and steps taken to get to a zero sum square.
StepSolution steps(int a, int b, int c, int d)
{
    int count = 1;
    vector<vector<int>> path = vector<vector<int>>{vector<int>{a, b, c, d}};
    bool stop = true;
    while (stop)
    {
        int *arr = f(a, b, c, d);
        a = arr[0];
        b = arr[1];
        c = arr[2];
        d = arr[3];
        count++;
        path.push_back(vector<int>{a, b, c, d});
        if (sum(arr) == 0)
        {
            stop = false;
        }
    }
    return StepSolution{count, path};
}

// Maximizes steps taken.
StepSolution maximise_steps(int n)
{
    StepSolution best = StepSolution{0, vector<vector<int>>{}};

    for (int a = 1; a < int(n / 3); a++)
    {
        for (int b = 1; b < int(n / 2) * a; b++)
        {
            for (int c = 1; c < n - a - b; c++)
            {
                StepSolution soln = steps(0, a, a + b, a + b + c);
                if (soln.steps > best.steps)
                {
                    best = soln;
                }
            }
        }
    }

    return best;
}

//
vector<vector<int>> denormalize(vector<vector<int>> data)
{
    if ((data[0][3] - data[0][2] - data[0][1]) % 2 == 1)
    {
        int add = (2 * data[0][3] - 2 * data[0][2] - 2 * data[0][1]) / 2;
        vector<int> second;
        for (int i = 0; i < data[0].size(); i++)
        {
            second.push_back(data[0][i] * 2 + add);
        }
        vector<int> top = {0, second[0], second[0] + second[1], second[3]};
        vector<vector<int>> new_rows = {top, second};
        for (int i = 1; i < data.size(); i++)
        {
            vector<int> new_row;
            for (int j = 0; j < data[i].size(); j++)
            {
                new_row.push_back(data[i][j] * 2);
            }
            new_rows.push_back(new_row);
        }
        return new_rows;
    }
    else
    {
        int add = (data[0][3] - data[0][2] - data[0][1]) / 2;
        vector<int> second;
        for (int i = 0; i < data[0].size(); i++)
        {
            second.push_back(data[0][i] + add);
        }
        vector<int> top = {0, second[0], second[0] + second[1], second[3]};
        vector<vector<int>> new_rows = {top, second};
        for (int i = 1; i < data.size(); i++)
        {
            vector<int> new_row;
            for (int j = 0; j < data[i].size(); j++)
            {
                new_row.push_back(data[i][j]);
            }
            new_rows.push_back(new_row);
        }
        return new_rows;
    }
}

int main()
{
    int n = 1000;
    StepSolution best = maximise_steps(n);

    vector<vector<int>> data = best.path;

    while (true)
    {
        vector<vector<int>> n = denormalize(data);

        if (n[0][3] > 10000000)
        {
            break;
        }
        else
        {
            data = n;
        }
    }

    for (int i = 0; i < data[0].size(); i++)
    {
        cout << data[0][i] << " ";
    }

    cout << endl;

    return 0;
}