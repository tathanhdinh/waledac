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
#include "BotnetStaticConfiguration.h"

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include <algorithm>

namespace waledac
{


std::vector< boost::shared_ptr< Bot > > repeater_merge_rlist(
									std::vector<boost::shared_ptr<Bot> > &existing_rlist, 
									std::vector<boost::shared_ptr<Bot> > &new_rlist)
{
	// not yet implemented
	return existing_rlist;
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
	// create a random permutation of RList
	std::vector< boost::shared_ptr< Bot > > tmp_list = m_rlist;
	std::random_shuffle(tmp_list.begin(), tmp_list.end());
	
	// and insert itself to this permutation
	tmp_list.insert(tmp_list.begin(), Bot::shared_from_this());
	
	// extract sublist from this permutation
	std::vector< boost::shared_ptr< Bot > > sub_list(tmp_list.size() / 5);
	std::copy(tmp_list.begin(), tmp_list.begin() + sub_list.size() - 1, sub_list.begin());
	
	return sub_list;
}


/*
 * extract a subset of repeaters from rlist
 */
std::vector< boost::shared_ptr< Bot > > Repeater::sub_plist()
{
	std::vector< boost::shared_ptr<Bot> > sublist(100);
	return sublist;
}


/*
 * update rlist from other repeaters
 */
void Repeater::update_rlist()
{
	if (m_rlist.empty()) {
		m_rlist = hardcoded_rlist();
	}
	
	// takes a random repeater from rlist
	boost::shared_ptr<Bot> repeater_target;
	repeater_target = random_bot(m_rlist);
	
	std::cout << "\033[01;31m" 
				<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
				% "repeater" % Bot::id() % "updates RList from repeater" % repeater_target->id();
	
	// get subset of rlist from this repeater
	std::vector<boost::shared_ptr<Bot> > new_rlist;
	new_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
	
	// merge new rlist and existing rlist
	m_rlist = repeater_merge_rlist(m_rlist, new_rlist);
	
	return;
}


/*
 * update plist from other repeaters
 */
void Repeater::update_plist()
{
	if (m_plist.empty()) {
		m_plist = hardcoded_plist();
	}
	
	// takes a random repeater from rlist
	boost::shared_ptr<Bot> repeater_target;
	repeater_target = random_bot(m_plist);
	
	std::cout << "\033[01;34m" 
				<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
				% "repeater" % Bot::id() % "updates PList from repeater" % repeater_target->id();
	
	// get subset of plist from this repeater
	std::vector<boost::shared_ptr<Bot> > new_plist;
	new_plist = dynamic_cast<Repeater*>(repeater_target.get())->sub_plist();
	
	// merge new rlist and existing rlist
	m_plist = repeater_merge_rlist(m_plist, new_plist);
	
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