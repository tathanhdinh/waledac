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

#include "Attacker.h"

#include <iostream>

namespace waledac
{


/*
 * constructor
 */
Attacker::Attacker() : Repeater()
{
}


/*
 * extract a random subset of repeaters from rlist
 */
std::vector< boost::shared_ptr< Bot > > Attacker::sub_rlist()
{
	return Repeater::sub_rlist();
}


/*
 * extract a random subset of repeaters from plist
 */
std::vector< boost::shared_ptr< Bot > > Attacker::sub_plist()
{
	return Repeater::sub_plist();
}


/*
 * update plist from other repeaters
 */
void Attacker::update_plist()
{
	std::cout << "\033[01;34m" << "fake ";
	Repeater::update_plist();
	return;
}


/*
 * update rlist from other repeaters
 */
void Attacker::update_rlist()
{
	std::cout << "\033[01;31m" << "fake ";
	Repeater::update_rlist();
	return;
}


/*
 * get control command from C&C server
 */
std::string Attacker::get_control_command()
{
	std::cout << "\033[01;33m" << "request from spammer detected" << std::endl;
	exit(1);
	return Repeater::get_control_command();
}


/*
 * life of attacker
 */
void Attacker::execute()
{
	waledac::Repeater::execute();
	return;
}


/*
 * start attacker
 */
void Attacker::start()
{
	std::cout << "start attacker with id : " << Bot::id() << std::endl;
	m_attacker_thread.reset(new boost::thread(boost::bind(&Attacker::execute, 
														  this)));
	//waledac::Repeater::start();
	return;
}


/*
 * wait until attacker stop
 */
void Attacker::wait()
{
	m_attacker_thread->join();
	//Repeater::wait();
	return;
}


}