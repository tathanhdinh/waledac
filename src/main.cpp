#include "Spammer.h"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    std::cout << "Waldac botnet simulation" << std::endl;
	
	std::vector<boost::shared_ptr<waledac::Spammer> > spammers(100);
	for (int i = 0; i < 100; ++i) {
		(spammers[i]).reset(new waledac::Spammer());
		(spammers[i])->start();
		(spammers[i])->wait();
	}
	
    return 0;
}
