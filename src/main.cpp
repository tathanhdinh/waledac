#include "Spammer.h"
#include "BotnetStaticConfiguration.h"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    std::cout << "Waldac botnet simulation" << std::endl;
	
	waledac::hardcoded_config.reset(new waledac::BotnetStaticConfiguration());
	
	std::vector<boost::shared_ptr<waledac::Spammer> > spammers(100);
	for (int i = 0; i < 100; ++i) {
		(spammers[i]).reset(new waledac::Spammer());
		(spammers[i])->start();
	}
	
	/*for (int i = 0; i < 100; ++i) {
		spammers[i]->wait();
	}*/
	
    return 0;
}
