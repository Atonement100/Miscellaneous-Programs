// autoWTFriday.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> getStaffTeam(){
	std::ifstream staff;
	std::vector<std::string> staffTeam;
	std::string temp;

	staffTeam.clear();
	staff.open("staff.txt");

	std::fstream debug;
	debug.open("debug.txt");


	if (!staff){
		std::cout << "Error opening staff file\n"
			<< "Please make sure there is a 'staff.txt' in the same folder as the executable\n"
			<< "If there already is, please yell at Tim to fix." << std::endl;
	}
	else {
		std::cout << "staff.txt opened successfully, processing . . .\n" << std::endl;
	}

	while (!staff.eof()){
		std::getline(staff, temp);
		staffTeam.push_back(temp);
		debug << temp << std::endl;
	}

	debug << "\n\n\n LOOP \n\n\n" << std::endl;

	for (unsigned int i = 0; i < staffTeam.size(); i++){
		debug << staffTeam[i] << std::endl;
	}

	return staffTeam;
}

std::ifstream openWTFriday(){
	std::ifstream inputfile;
	inputfile.open("wtfriday.txt");

	if (!inputfile){
		std::cout << "Error while opening input file\n"
			<< "Please make sure there is a 'wtfriday.txt' in the same folder as the executable\n"
			<< "If there already is, please yell at Tim to fix." << std::endl;
	}
	else {
		std::cout << "wtfriday.txt opened successfully, processing . . .\n" << std::endl;
	}


	return inputfile;
}


int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> staffTeam = getStaffTeam();
	std::ifstream wtinput = openWTFriday();
	std::string lineinput, lineoutput, temp;
	std::fstream wtoutput;

	wtoutput.open("wtoutput.txt");
	//wtoutput.clear();

	while (!wtinput.eof()){
		std::getline(wtinput, lineinput);

		if (std::find(staffTeam.begin(), staffTeam.end(), lineinput.substr(0, lineinput.find(' '))) != staffTeam.end()){
			lineoutput = "<strong style = \"font-size: 11px; \">" + lineinput.substr(0, lineinput.find("- ")-1) 
				+ "&nbsp;</strong><span style=\"font-size: 11px; \">" + lineinput.substr(lineinput.find("- "), lineinput.length()-1)
				+ "</span><br />";
		}
		else{
			temp = lineinput.substr(0, lineinput.find(' '));
			lineoutput = "<p style=\"margin: 0px; padding-bottom: 1em; \"><span style=\"background-color: initial; \"><strong><a href=\"http://boon.pw/home/"
				+ temp + "\">" + temp + "</a>&nbsp;</strong>asks: " + lineinput.substr(lineinput.find(':') + 1, lineinput.length() - 1) + "<br />";
		}
		
		std::cout << lineoutput << std::endl;

		wtoutput << lineoutput;

	}

	wtinput.close();
	wtoutput.close();
	return 0;
}

