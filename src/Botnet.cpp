/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "Botnet.h"
#include "Spammer.h"
#include "Repeater.h"
#include "Attacker.h"
#include "Protecter.h"
#include "ServerCC.h"

#include <iostream>

namespace waledac
{
	
Botnet::Botnet(unsigned int repeaters_number, unsigned int protecters_number, 
			   unsigned int spammers_number, unsigned int attackers_number)
{
	repeaters.resize(repeaters_number);
	for (unsigned int i = 0; i < repeaters.size(); ++i) {
		repeaters[i].reset(new Repeater());
	}
	
	protecters.resize(protecters_number);
	for (unsigned int i = 0; i < protecters.size(); ++i) {
		protecters[i].reset(new Protecter());
	}
	
	spammers.resize(spammers_number);
	for (unsigned int i = 0; i < spammers.size(); ++i) {
		spammers[i].reset(new Spammer());
	}
	
	attackers.resize(attackers_number);
	for (unsigned int i = 0; i < attackers.size(); ++i) {
		attackers[i].reset(new Attacker());
		repeaters.push_back(attackers[i]);
	}

	server_cc.reset(new ServerCC());
}


bots_t Botnet::protecters_list()
{
	return protecters;
}


bots_t Botnet::repeaters_list()
{
	return repeaters;
}


bots_t Botnet::spammers_list()
{
	return spammers;
}


bots_t Botnet::attackers_list()
{
	return attackers;
}


boost::shared_ptr< Bot > Botnet::server()
{
	return server_cc;
}


void Botnet::init()
{
	this->server_cc->init(server_cc, protecters, repeaters);
	
	for (unsigned int i = 0; i < this->attackers.size(); ++i) {
		this->attackers[i]->init(server_cc, protecters, repeaters);
	}
	
	for (unsigned int i = 0; i < this->protecters.size(); ++i) {
		this->protecters[i]->init(server_cc, protecters, repeaters);
	}
	
	for (unsigned int i = 0; i < repeaters.size(); ++i) {
		this->repeaters[i]->init(server_cc, protecters, repeaters);
	}
	
	for (unsigned int i = 0; i < spammers.size(); ++i) {
		this->spammers[i]->init(server_cc, protecters, repeaters);
	}

	return;
}


/*
 * add an attacker (repeater) into botnet
 */
void Botnet::add_attacker(bot_t attacker)
{
	bot_t target_repeater;
	target_repeater = random_bot(repeaters);
}




#ifdef THREAD_VERSION
void Botnet::start()
{
	server_cc->start();
	
	for (unsigned int i = 0; i < protecters.size(); ++i) {
		protecters[i]->start();
	}
	
	for (unsigned int i = 0; i < repeaters.size(); ++i) {
		repeaters[i]->start();
	}
	
	for (unsigned int i = 0; i < spammers.size(); ++i) {
		spammers[i]->start();
	}
	
	return;
}


void Botnet::wait()
{
        server_cc->wait();
        return;
}
#else
void Botnet::start()
{
	waledac::Attacker *attacker;	
	waledac::Protecter *protecter;	
	waledac::Repeater *repeater;
	waledac::Spammer *spammer;
	
	
	//server_cc->start();	

	for(unsigned int i = 0; i < attackers.size(); ++i) 
	{
		attacker = dynamic_cast<waledac::Attacker*>(attackers[i].get());
		attacker->update_rlist();
		attacker->request_command();
		attacker->send_message(MESSAGE_TASKREQ);
	}
	
	for(unsigned int i = 0; i < protecters.size(); ++i) 
	{
		protecter = dynamic_cast<waledac::Protecter*>(protecters[i].get());
		// rien pour l'instant
	}

	for(unsigned int i = 0; i < repeaters.size(); ++i) 
	{
		repeater = dynamic_cast<waledac::Repeater*>(repeaters[i].get());
		repeater->update_rlist();
		repeater->update_plist();
	}
	
	for(unsigned int i = 0; i < spammers.size(); ++i) 
	{
		spammer = dynamic_cast<waledac::Spammer*>(spammers[i].get());
		spammer->update_rlist();
		spammer->request_command();
		spammer->send_message(MESSAGE_TASKREQ);
	}

	return;
}
#endif


}
