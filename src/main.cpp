#include "BotnetStaticConfiguration.h"
#include "Spammer.h"
#include "Repeater.h"

#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

int main(int argc, char **argv) {
	unsigned int rlist_size;
	unsigned int plist_size;
	unsigned int spammers_number;
	
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
	 "Spammers number");
	
	boost::program_options::variables_map vars_map;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), 
								  vars_map);
	boost::program_options::notify(vars_map);
	
	if (vars_map.count("help")) {
		std::cout << desc << std::endl;
	}
	else {
		std::cout << "Waldac botnet simulation" << std::endl;
		
		std::cout << "Initialise hardcoded parameters" << std::endl;
		std::cout << "RList : " << rlist_size << " repeaters" << std::endl;
		std::cout << "PList : " << plist_size << " protecters" << std::endl;
		waledac::hardcoded_config.reset(new 
					waledac::BotnetStaticConfiguration(rlist_size, plist_size));
		
		std::cout << "Start all repeaters ..." << std::endl;
		std::vector< boost::shared_ptr<waledac::Bot> > repeaters = 
														waledac::hardcoded_rlist();
		for (unsigned int i = 0; i < repeaters.size(); ++i) {
			repeaters[i]->start();
		}
		
		std::cout << "Start all protecters ..." << std::endl;
		std::vector< boost::shared_ptr<waledac::Bot> > protecters = 
														waledac::hardcoded_plist();
		for (unsigned int i = 0; i < protecters.size(); ++i) {
			protecters[i]->start();
		}
		
		std::cout << "Start C&C server ..." << std::endl;
		boost::shared_ptr<waledac::Bot> server = waledac::servercc();
		server->start();
		
		std::cout << "Botnet startup with 5 spammers" << std::endl;
		std::vector<boost::shared_ptr<waledac::Spammer> > spammers(5);
		for (unsigned int i = 0; i < spammers.size(); ++i) {
			(spammers[i]).reset(new waledac::Spammer());
			(spammers[i])->start();
		}
		
		
		std::cout << "Botnet running ..." << std::endl;
		/*for (unsigned int i = 0; i < spammers.size(); ++i) {
			spammers[i]->wait();
		}
		
		for (unsigned int i = 0; i < repeaters.size(); ++i) {
			repeaters[i]->wait();
		}
		
		for (unsigned int i = 0; i < protecters.size(); ++i) {
			protecters[i]->wait();
		}*/
		
		server->wait();
	}
	
    return 0;
}
