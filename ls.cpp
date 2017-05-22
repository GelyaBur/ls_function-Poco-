#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include <iostream>
#include <vector>

const int MAX = 10;
const std::string NORM_MODE = "\x1b[0m";
const std::string BLUE_BOLD = "\x1b[34;1m";
const std::string RED_BOLD = "\x1b[31;1m";
const std::string GREEN_BOLD = "\x1b[32;1m";

using Poco::Path;
using Poco::File;
using Poco::DirectoryIterator;

class Text_Mode
{
private:
    const std::string mode;
public:
    Text_Mode(const std::string & Mode);
    ~Text_Mode();
};

Text_Mode::Text_Mode(const std::string & Mode) : mode(Mode)
{
    std::cout << "   " + mode;
};

Text_Mode::~Text_Mode()
{
    
    std::cout << NORM_MODE << ' ';
};

void dirwalk(const std::string & dir, std::vector<std::string> & arr)
{
    File file(dir);
    Path p(dir);
    std::cout << dir << '\n';
    DirectoryIterator it(dir);
    DirectoryIterator end;
    while (it != end)
    {
        
        if (!it->isFile()) { 
            arr.push_back(dir + "/" + it.name());
            Text_Mode blue(BLUE_BOLD);
            std::cout << it.name();
            //std::cout << "   " + BLUE_BOLD << it.name()  << NORM_MODE << ' ';
        }    
        else {
        
            if (it.name().find(".txt") != std::string::npos) {
                Text_Mode red(RED_BOLD);
                std::cout << it.name();
                //std::cout  << it.name();
            }    
            else if (it.name().find('.') != std::string::npos) {
                std::cout << "   " << it.name() << " ";
            }
            else {
                Text_Mode green(GREEN_BOLD);
                std::cout << it.name();
                //std::cout << it.name();
            }    
            std::cout << it->getSize();
        }    
        std::cout << std::endl;
        
        ++it;
    }

}

void fsize(const std::string & dir)
{
    Path p(dir);
    File file(dir);
    std::vector<std::string> arr;
    std::cout  << std::endl;
    if (file.isDirectory()) {        
        dirwalk(dir, arr);
    }    
    else {        
        std::cout << p.getFileName() << " " << file.getSize() << std::endl;
    }    
    if (arr.empty()) {
        return;
    }    
      
    else {
        for (int i = 0; i < arr.size(); i++) {
            File f(arr[i]);            
            if (f.isDirectory())
                fsize(arr[i]);
        }        
            
                    
    }    
        
            
}

int main(int argc, char** argv)
{
    std::string cwd("..");
    fsize(cwd);
    //Path p("/usr/6");
    //std::cout << p.isDirectory() ;
    return 0;
}
