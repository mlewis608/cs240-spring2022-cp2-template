#include "Parser.h"
#include <string>
#include <iostream>
using namespace std;

void do_zero() {
   cout << "do_zero: " << endl;
}

void do_one(string a) {
   cout << "do_one: " << a << endl;
}

void do_two(string a, int b) {
   cout << "do_two: " << a << " " << b << endl;
}

void do_three(string a, string b, string c) {
   cout << "do_three: " << a << " " << b << " " << c << endl;
}

void do_four(string a, string b, string c, string d) {
   cout << "do_four: " << a << " " << b << " " << c << " " << d << endl;
}

int main() {
   string line;  
   string command;  
   int int_param;

   while (1) {
      cout << endl << "Enter a command" << endl;
      cout << "Choose from [\"zero\"" << std::endl <<
	      "             \"one <string>\"" << std::endl << 
	      "             \"two <string> <int>\"" << std::endl << 
	      "             \"three <string> <string> <string> [<string>]" << std::endl << 
	      "             \"quit\"]" << endl; 
      cout << ": "; 

      getline(cin, line);
      Parser command(line);
      if (command.getOperation().empty()) {
         if (std::cin.fail())
	    break;
         continue;
      }

      if (command.getOperation() == "quit") {
         if (command.numArgs() > 0) 
            cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
         break;
      }

      if (command.getOperation() == "zero") {
         if (command.numArgs() > 0) 
            cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
	 do_zero(); 
      }

      else if (command.getOperation() == "one") {
         if (command.numArgs() < 1) 
            cout << std::endl << MISSING_ARGS << endl;
	 else 
            do_one(command.getArg1()); 
         if (command.numArgs() > 1) 
            cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
      }

      else if (command.getOperation() == "two") {
         if (command.numArgs() < 2) 
            cout << std::endl << MISSING_ARGS << endl;
	 else {
           if (Parser::isInteger(command.getArg2())) {
              int_param = stoi(command.getArg2()); 
	      do_two(command.getArg1(), int_param);
           }
           else 
	      cout << "Error: arg2: " << command.getArg2() << " is not an integer" << endl;
           if (command.numArgs() > 2) 
              cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
         }
      }

      else if (command.getOperation() == "three") {
         if (command.numArgs() < 3) 
            cout << std::endl << MISSING_ARGS << endl;
	 else 
            if (command.numArgs() == 3)
               do_three(command.getArg1(), command.getArg2(), command.getArg3());
	    else 
               do_four(command.getArg1(), command.getArg2(), command.getArg3(), command.getArg4());
         if (command.numArgs() > 4) 
            cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
      }

      else {
         cout << std::endl << 
		 "Command not recognized. Please try again." << endl; 
      }
   }
}
