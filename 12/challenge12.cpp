#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Ship
{
    int direction[2] = { 1, 0 }; //start east
    int x = 0;
    int y = 0;

public:
    void mulMatrix(const int mat[2][2])
    {
        const int tmp_x = direction[0] * mat[0][0] + direction[1] * mat[0][1];
        const int tmp_y = direction[0] * mat[1][0] + direction[1] * mat[1][1];
        direction[0] = tmp_x;
        direction[1] = tmp_y;
        //std::cout << tmp_x << " " << tmp_y << std::endl;
    }
    void rotateLeft(const int deg)
    {
        const int mat[2][2] = { 0, -1, 1, 0 };
        const int turns = deg / 90;
        for (int i = 0; i < turns; i++)
        {
            mulMatrix(mat);
        }
    }

    void rotateRight(const int deg)
    {
        const int mat[2][2] = { 0, 1, -1, 0 };
        const int turns = deg / 90;
        for (int i = 0; i < turns; i++)
        {
            mulMatrix(mat);
        }
    }

    void moveForward(const int value)
    {
        x += direction[0] * value;
        y += direction[1] * value;
    }

    void move(const char cmd, const int value)
    {
        if (cmd == 'N')
        {
            y += value;
        }
        else if (cmd == 'S')
        {
            y -= value;
        }
        else if (cmd == 'E')
        {
            x += value;
        }
        else if (cmd == 'W')
        {
            x -= value;
        }
        else if (cmd == 'L')
        {
            rotateLeft(value);
        }
        else if (cmd == 'R')
        {
            rotateRight(value);
        }
        else
        {
            moveForward(value);
        }
    }
};

std::vector<std::string> getInput()
{
    std::vector<std::string> input;
    std::fstream newfile;
    newfile.open("input.txt", std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open
        std::string tp;
        while (getline(newfile, tp)) {  //read data from file object and put it into std::string.
            input.push_back(tp);
        }
        newfile.close();   //close the file object.
    }
    return input;
}

int main()
{
    //get input
    const auto input = getInput();
    //process

    Ship ship;
    for (std::string line : input)
    {
        char cmd = line[0];
        const int value = std::stoi(line.substr(1, line.size() - 1));
        ship.move(cmd, value);
    }
    std::cout << ship.x << ", " << ship.y << std::endl;
    std::cout << "Manhattan: " << abs(ship.x) + abs(ship.y);
}