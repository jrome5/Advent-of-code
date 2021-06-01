#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
using namespace std;

struct Vertex
{
public:
    string color;
    std::vector<string> parent_colors;
    std::vector<string> child_colors;
    bool visited = false;
};
class Graph
{
public:
    map<string, Vertex> vertices;
    void addEdge(string parent, string child);
};


void Graph::addEdge(string parent, string child)
{
    const auto parent_it = vertices.find(parent);
    if (parent_it != vertices.cend())
    {
        auto& v = parent_it->second;
        v.child_colors.push_back(child);
    }
    else
    {
        Vertex v;
        v.color = parent;
        v.child_colors.push_back(child);
        vertices.emplace(parent, v);
    }
    const auto child_it = vertices.find(child);
    if (child_it != vertices.cend())
    {
        auto& v = child_it->second;
        v.parent_colors.push_back(parent);
    }
    else
    {
        Vertex v;
        v.color = child;
        v.parent_colors.push_back(parent);
        vertices.emplace(child, v);
    }
        
}


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

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void find_items(Vertex& v, Graph& graph, int& count)
{
    for (auto& p : v.parent_colors)
    {
        const auto p_it = graph.vertices.find(p);
        if (p_it != graph.vertices.cend())
        {
            auto& v_parent = p_it->second;
            if (v_parent.visited == false) 
            {
                count++;
                find_items(v_parent, graph, count);
            }
            v_parent.visited = true;      
        }
    }
}

int main()
{
    Graph graph;

    //get input
    const auto input = getInput();
    for (const auto line : input)
    {
        std::string buf;                 // Have a buffer string
        std::stringstream ss(line);       // Insert the string into a stream

        int bag_index = 0;
        int comma_index = 0;
        int bags_found = 0;
        std::string parent_color;
        std::string child_color;
        int bag_quantity = 0;
        while (ss >> buf)
        {
            if (buf == "," || buf == "contain" || buf == ".")
            {
                continue;
            }
            else if (buf.find("bag") != string::npos)
            {
                if (bags_found > 0)
                {
                    graph.addEdge(parent_color, child_color);
                }
                bags_found++;
                child_color = "";
                bag_quantity = 0;
            }
            else if (is_number(buf))
            {
                bag_quantity = std::stoi(buf);
            }
            else if (bags_found == 0)
            {
                parent_color += buf;
            }
            else if (bag_quantity != 0)
            {
                child_color += buf;
            }
        }
    }
    int shiny_gold = 0;
    const auto it = graph.vertices.find("shinygold");
    if (it != graph.vertices.cend())
    {
        Vertex& shiny_gold_vertex = it->second;
        find_items(shiny_gold_vertex, graph, shiny_gold);
    }
    cout << shiny_gold;
    //graph.display();
}