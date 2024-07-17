#include <iostream> 
#include <unistd.h> 
#include <termios.h> 
#include <string>
#include <vector>
#include <fstream> 
#include <cstdio>  
#include <cstdlib> 
//helper function 

//fileExists() - function to check if file exists in current stream

bool fileExists(std::string fname){ 
    if(std::ifstream(fname)){
        return true
    }else{
        return false 
    }
}
//getch() - takes a single input character 
char getch() {
    char buf = 0;
    struct termios old = {0};

    if (tcgetattr(0, &old) < 0) {
        perror("tcgetattr()");
        exit(1);
    }
    //store original terminal settings 
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
        exit(1);
    }

    if (fread(&buf, 1, 1, stdin) != 1) {
        perror("fread()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0) {
            perror("tcsetattr ~ICANON");
        }
        exit(1);
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
        exit(1);
    }

    return buf;
}

int main(){ 
    std:: fstream file; 
    std::string filename; 

    //File mode flags, combined w bitwise or 
 
    //ios::in- allows the file to be read from. 
    //ios:: out- allows file to be written to 
    //ios::app - ensuring data appends to the end of a file  
    std::cout <<"Please enter the name of the file which you want to edit.\n";
    std::cin >> filename 
   while(!fileExists(filename)){ 
        std::cout <<"Sorry, this file does not exist. Please enter the name of an exisiting file.\n";
        std::cin >>filename; 
   }

    file.open(filename, ios::in | ios::out | ios::app);

    if(!file.open()){ 
        std::cerr << "Failed to open this file. \n "  ; 
        return 1; 
    }
    
    std::cout << "Text Editor. Press CTRL + H for a list of commands " ; 
    

    std:: string text; 
    while (true){
        char input = getch(); 

        //CTRL + H 
        if(input == 8){
            bool acknowledge = false; 
            std::cout<< "Here are the following commands \n CTRL + S- Save any modifications
            made to the file \n CTRL + Q- quit program \n Press c to continue editing. "
            while (!acknowledge){
                char userInput = getch(); 
                 //enters c 
                if (ok == 99 ){
                   ackowledge = true; 
                }
            }

        }
        //CTRL + Q 
        if(input == 17){ 
            bool acknowledge = false; 
            std::cout<< "About to exit text editor. Are you sure about this? Please respond with y/n \n "
            while (!acknowledge){ 
                userInput = getch(); 

                if(userInput == 121){ 
                    std::cout<< "Changes will not be saved. Exiting Program. \n"
                    return 0; 
                }
                if(userInput == 110){
                    break; 
                }
            }
        }
        // Deleting a space
        if(input == 127 || input == '\b'){ 

        }
            
    }



   
}