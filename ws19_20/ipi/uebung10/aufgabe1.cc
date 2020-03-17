#include<iostream>
#include<fstream>
#include<string>

int main(int argc, char** argv)
{
    std::ifstream input;
    std::ofstream output;
    input.open("test.txt");
    output.open("test-a.txt");
    int counter = 0;
    bool firstline = true;
    while (input.good())
    {
        if (firstline)
        {
            std::string line;
            std::getline(input, line);
            ++counter;
            output << counter << ": " << line;
            firstline = false;
        }
        else
        {
            std::string line;
            std::getline(input, line);
            ++counter;
            output << std::endl << counter << ": " << line;
            firstline = false;
        }
    }
    input.close();
    output.close();
}