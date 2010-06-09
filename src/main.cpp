#include "Botnet.h"
#include "Spammer.h"
#include "Repeater.h"
#include "Attacker.h"
#include "BotnetVisual.h"
#include "vtkBotnetGraph.h"

#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

int main(int argc, char **argv) {
	unsigned int rlist_size;
	unsigned int plist_size;
	unsigned int spammers_number;
	unsigned int attackers_number;
	
	
	boost::program_options::options_description desc("Options");
	desc.add_options()
	("help,h", "Display help")
	
	("rlist,r", 
	 boost::program_options::value<unsigned int>(&rlist_size)->default_value(20), 
	 "RList size")
	 
	("plist,p", 
	 boost::program_options::value<unsigned int>(&plist_size)->default_value(7), 
	 "PList size")
	
	("spam,s", 
	 boost::program_options::value<unsigned int>(&spammers_number)->default_value(20), 
	 "Spammers number")
	 
	 ("attack,a", 
	  boost::program_options::value<unsigned int>(&attackers_number)->default_value(1), 
	  "Attackers numbers");
	
	boost::program_options::variables_map vars_map;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), 
								  vars_map);
	boost::program_options::notify(vars_map);
	
	if (vars_map.count("help")) {
		std::cout << desc << std::endl;
	}
	else {
		std::cout << "Waldac botnet simulation" << std::endl;
		
		
		vtkBotnetGraph *botnetgraph = new vtkBotnetGraph(rlist_size, plist_size, spammers_number, attackers_number);
	
	botnetgraph->botnet->wait();
	}
    return 0;
}
