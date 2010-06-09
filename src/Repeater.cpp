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

#include "Repeater.h"
#include "Botnet.h"

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include <algorithm>

namespace waledac
{


std::vector< boost::shared_ptr< Bot > > repeater_merge_list(
									std::vector< boost::shared_ptr< Bot > > &existing_rlist, 
									std::vector< boost::shared_ptr< Bot > > &received_rlist)
{
	return merge_list(existing_rlist, received_rlist);
}


/*
 * constructor
 */
Repeater::Repeater() : Bot()
{
	m_rlist.clear();
	m_plist.clear();	
}


/*
 * extract a random subset of repeaters from rlist
 */
std::vector< boost::shared_ptr< Bot > > Repeater::sub_rlist()
{
	const unsigned int max_try = 10;
	std::vector< boost::shared_ptr< Bot > > sub_list;
	
	// take a dice
	if (random_number(max_try) != 0) {
		// create a random permutation of RList
		std::vector< boost::shared_ptr< Bot > > tmp_list = m_rlist;
		std::random_shuffle(tmp_list.begin(), tmp_list.end());
		
		// and insert itself to this permutation
		tmp_list.insert(tmp_list.begin(), Bot::shared_from_this());
		
		// extract a sublist from this permutation
		sub_list.resize(tmp_list.size() / 5);
		std::copy(tmp_list.begin(), tmp_list.begin() + sub_list.size(), 
				  sub_list.begin());
	}
	else {
		sub_list.clear(); // send a empty sublist
	}
	
	return sub_list;
}


/*
 * extract a subset of protecter from plist
 */
std::vector< boost::shared_ptr< Bot > > Repeater::sub_plist()
{
	const unsigned int max_try = 10;
	std::vector< boost::shared_ptr< Bot > > sub_list;
	
	// take a dice
	if (random_number(max_try) != 0) {
		// create a random permutation of PList
		std::vector< boost::shared_ptr< Bot > > tmp_list = m_plist;
		std::random_shuffle(tmp_list.begin(), tmp_list.end());
		
		// extract a sublist from this permutation
		sub_list.resize(tmp_list.size() / 5);
		std::copy(tmp_list.begin(), tmp_list.begin() + sub_list.size(), 
				  sub_list.begin());
	}
	else {
		sub_list.clear(); // send a empty sublist
	}
		
	return sub_list;
}


/*
 * update rlist from other repeaters
 */
void Repeater::update_rlist()
{	
	if (m_rlist.size() > 0) {
		// takes a random repeater from rlist
		boost::shared_ptr<Bot> repeater_target;
		repeater_target = random_bot(m_rlist);
		
		std::cout << "\033[01;31m" 
					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
					% "repeater" % Bot::id() % "updates RList from repeater" % repeater_target->id();
		
		// get subset of rlist from this repeater
		std::vector< boost::shared_ptr<Bot> > received_rlist;
		received_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
		
		// merge new rlist and existing rlist
		m_rlist = repeater_merge_list(m_rlist, received_rlist);
	}
	
	return;
}


/*
 * update plist from other repeaters
 */
void Repeater::update_plist()
{	
	if (m_rlist.size() > 0) {
		// takes a random repeater from rlist
		boost::shared_ptr< Bot > repeater_target;
		repeater_target = random_bot(m_rlist);
		
		std::cout << "\033[01;34m" 
					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
					% "repeater" % Bot::id() % "updates PList from repeater" % repeater_target->id();
		
		// get subset of plist from this repeater
		std::vector< boost::shared_ptr< Bot > > received_plist;
		received_plist = dynamic_cast<Repeater*>(repeater_target.get())->sub_plist();
		
		// merge new plist and existing plist
		m_plist = repeater_merge_list(m_plist, received_plist);
	}
	
	return;
}


/*
 * get command from C&C server
 */
command_code Repeater::request_command()
{
	return COMMAND_FROM_REPEATER;
}


/*
 * initialise rlist and plist of repeater before running
 */
void Repeater::init()
{
	m_plist = Botnet::protecters_list();
	m_rlist = Botnet::repeaters_list();
	return;
}


/*
 * life of repeater
 */
void Repeater::execute()
{
	while (true) {
		update_rlist();
		update_plist();
		sleep(5);
	}
	
	return;
}


/*
 * start repeater thread
 */
void Repeater::start()
{
	std::cout << "start repeater with id : " << Bot::id() << std::endl;
	m_repeater_thread.reset(new boost::thread(boost::bind(&Repeater::execute, 
														  *this)));
	return;
}


/*
 * wait until repeater thread stop
 */
void Repeater::wait()
{
	m_repeater_thread->join();
	return;
}



}