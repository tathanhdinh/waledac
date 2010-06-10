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

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <boost/thread/pthread/mutex.hpp>

namespace waledac
{

static std::vector< boost::shared_ptr< Bot > > repeaters;
static std::vector< boost::shared_ptr< Bot > > protecters;
static std::vector< boost::shared_ptr< Bot > > spammers;
static std::vector< boost::shared_ptr< Bot > > attackers;
boost::shared_ptr< ServerCC > server_cc;
	
Botnet::Botnet(unsigned int repeaters_number, unsigned int protecters_number, 
			   unsigned int spammers_number, int attackers_number)
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


std::vector< boost::shared_ptr< Bot > > Botnet::protecters_list()
{
	return protecters;
}


std::vector< boost::shared_ptr< Bot > > Botnet::repeaters_list()
{
	return repeaters;
}


std::vector< boost::shared_ptr< Bot > > Botnet::spammers_list()
{
	return spammers;
}


std::vector< boost::shared_ptr< Bot > > Botnet::attackers_list()
{
	return attackers;
}


boost::shared_ptr< Bot > Botnet::server()
{
	return server_cc;
}


void Botnet::init()
{
	server_cc->init();
	
	for (unsigned int i = 0; i < protecters.size(); ++i) {
		protecters[i]->init();
	}
	
	for (unsigned int i = 0; i < repeaters.size(); ++i) {
		repeaters[i]->init();
	}
	
	for (unsigned int i = 0; i < spammers.size(); ++i) {
		spammers[i]->init();
	}
	
	return;
}


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



}