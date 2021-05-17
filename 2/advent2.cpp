#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Password
{
    int lower;
    int upper;
    char policy;
    std::string code;
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

inline int extractValue(std::string line, int start_index, int end_index)
{
    std::string value;
    if (start_index == (end_index - 1))
    {
        value = line[start_index];
    }
    else
    {
        value = line.substr(start_index, 2);
    }
    return std::stoi(value);
}

int main() 
{
    //get input
    const auto input = getInput();
    //process
    std::vector<Password> passwords;
    for (std::string line : input)
    {
        Password password;
        int index = 0;
        //find lower limit
        for (int i = 0; i < line.length(); i++)
        {
            const auto c = line[i];
            if (c == '-')
            {
                password.lower = extractValue(line, index, i);
                index = i + 1;
                break;
            }
        }
        //find upper limit
        for (int i = index; i < line.length(); i++)
        {
            const auto c = line[i];
            if (c == ' ')
            {
                password.upper = extractValue(line, index, i);
                index = i + 1;
                break;
            }
        }
        password.policy = line[index]; //policy is always a space after the upper limit
        password.code = line.substr(index + 2, line.length()-1); //code is the rest of the line after ':', which is always a space after the policy
        passwords.push_back(password);
    }
    int valid_passwords = 0;
    //count the valid passwords
    for (const auto password : passwords)
    {
        std::cout << "password: " << password.lower << " " << password.upper << " " << password.policy << " " << password.code << std::endl;
        //count occurances of policy within the code
        int occurances = 0;
        for (const auto c : password.code)
        {
            occurances += (c == password.policy);
        }
        if (password.lower <= occurances && occurances <= password.upper)
        {
            valid_passwords++;
            std::cout << "valid" << std::endl;
        }
    }
    std::cout << "valid passwords: " << valid_passwords;

}