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
#include "Protecter.h"
#include "Botnet.h"

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include <algorithm>


namespace waledac
{


/*
 * merge the lists of repeater
 */
bots_t repeater_merge_list(bots_t &existing_rlist, bots_t &received_rlist)
{
	return merge_list(existing_rlist, received_rlist);
}


/*
 * update RList from other repeaters
 */
static void update_rlist(bot_t& repeater)
{
	repeater_t current_repeater;
	current_repeater = boost::dynamic_pointer_cast<Repeater>(repeater);
	
	bots_t rlist;
	rlist = current_repeater->rlist();
	
	if (rlist.size() > 0) {
		// takes a random repeater from rlist
		bot_t destination_bot;
		repeater_t destination_repeater;
		
		destination_bot = random_bot(rlist);
		destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
		
		/*
		std::cout << "\033[01;31m" 
					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
					% "repeater" % Bot::id() % "updates RList from repeater" % repeater_target->id();
		*/
		// get subset of rlist from this repeater
		bots_t received_rlist;
		received_rlist = destination_repeater->sub_rlist();
		//received_rlist = dynamic_cast<Repeater*>(destination_bot.get())->sub_rlist();
		
		if (received_rlist.size() > 0) {
			connections_t connections;
			connections = current_repeater->connections();
			
			connection_t current_connection;
			current_connection = find_connection(connections, repeater, destination_bot);
			
			current_connection->type() = CONNECTION_UPDATE_RLIST;
		
			// merge new rlist and existing rlist
			current_repeater->rlist() = repeater_merge_list(rlist, received_rlist);
		}
	}
	
	repeater->status() = UPDATE_RLIST;
	
	return;
}


/*
 * update PList from other repeater
 */
static void update_plist(bot_t& repeater)
{
	repeater_t current_repeater;
	current_repeater = boost::dynamic_pointer_cast<Repeater>(repeater);
	
	bots_t rlist;
	rlist = current_repeater->rlist();
	
	if (rlist.size() > 0) {
		// takes a random repeater from rlist
		bot_t destination_bot;
		repeater_t destination_repeater;
		
		destination_bot = random_bot(rlist);
		destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
		
		/*
		std::cout << "\033[01;34m" 
					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
					% "repeater" % Bot::id() % "updates PList from repeater" % repeater_target->id();
		*/
		
		// get subset of plist from this repeater
		bots_t received_plist;
		received_plist = dynamic_cast<Repeater*>(destination_bot.get())->sub_plist();
		
		if (received_plist.size() > 0) {
			
			// merge new plist and existing plist
			bots_t plist;
			plist = current_repeater->plist();
			current_repeater->plist() = repeater_merge_list(plist, received_plist);
		}
	}
	
	current_repeater->status() = UPDATE_PLIST;
	//this->status() = UPDATE_PLIST;
}


/*
 * constructor with parameters
 */
Repeater::Repeater(unsigned int rlist_size, unsigned int plist_size): Bot()
{
	m_rlist.resize(rlist_size);
	m_plist.resize(plist_size);
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
bots_t Repeater::sub_rlist()
{
	const unsigned int max_try = 10;
	bots_t sub_list;
	
	// take a dice
	if (random_number(max_try) != 0) {
		// create a random permutation of RList
		bots_t tmp_list = m_rlist;
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
bots_t Repeater::sub_plist()
{
	const unsigned int max_try = 10;
	bots_t sub_list;
	
	// take a dice
	if (random_number(max_try) != 0) {
		// create a random permutation of PList
		bots_t tmp_list = m_plist;
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
// void Repeater::update_rlist()
// {
// 	if (m_rlist.size() > 0) {
// 		// takes a random repeater from rlist
// 		bot_t repeater_target;
// 		repeater_target = random_bot(m_rlist);
// 		
// 		
// // 		std::cout << "\033[01;31m" 
// // 					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
// // 					% "repeater" % Bot::id() % "updates RList from repeater" % repeater_target->id();
// 		
// 		// get subset of rlist from this repeater
// 		bots_t received_rlist;
// 		received_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
// 		
// 		// merge new rlist and existing rlist
// 		m_rlist = repeater_merge_list(m_rlist, received_rlist);
// 	}
// 	
// 	this->status() = UPDATE_RLIST;
// 
// 	return;
// }


/*
 * update plist from other repeaters
 */
void Repeater::update_plist()
{	
	if (m_plist.size() > 0) {
		// takes a random repeater from rlist
		bot_t repeater_target;
		repeater_target = random_bot(m_rlist);
		
		/*
		std::cout << "\033[01;34m" 
					<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
					% "repeater" % Bot::id() % "updates PList from repeater" % repeater_target->id();
		*/
		
		// get subset of plist from this repeater
		bots_t received_plist;
		received_plist = dynamic_cast<Repeater*>(repeater_target.get())->sub_plist();
		
		// merge new plist and existing plist
		m_plist = repeater_merge_list(m_plist, received_plist);
	}
	
	this->status() = UPDATE_PLIST;
	
	return;
}


/*
 * return PList
 */
bots_t Repeater::plist()
{
	return m_plist;
}


/*
 * return RList
 */
bots_t Repeater::rlist()
{
	return m_rlist;
}


/*
 * forward message from spammer to protecter
 */
response_code Repeater::send_message(message_code message)
{
	response_code response = RESPONSE_FAILED;
	
	if (m_plist.size() > 0) {
		boost::shared_ptr< Protecter > protecter_proxy;
		protecter_proxy = boost::dynamic_pointer_cast<Protecter>(random_bot(m_plist));
		
		response = protecter_proxy->send_message(message);
	}
	
	return response;
}


/*
 * initialise rlist and plist of repeater before running
 */
void Repeater::init(bot_t& server, bots_t& plist, bots_t& rlist)
{
	if ((m_plist.size() == 0) && (m_rlist.size() == 0)) {
		this->m_plist = plist;
		std::vector< boost::shared_ptr<Bot>  > all_repeaters = rlist;
		m_rlist = random_bots(all_repeaters, all_repeaters.size() / 2);
	}
	else {
		m_rlist = random_bots(rlist, m_rlist.size());
		m_plist = random_bots(plist, m_plist.size());
	}
	
	return;
}


#ifdef THREAD_VERSION
/*
 * life of repeater
 */
void Repeater::execute()
{
	bot_t current_bot;
	current_bot = Bot::shared_from_this();
	
	while (true) {
		//update_rlist();
		update_rlist(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
		update_plist();
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}
	
	return;
}


/*
 * start repeater thread
 */
void Repeater::start()
{
	std::cout << "start repeater with id : " << Bot::id() << std::endl;
	m_repeater_thread.reset(new boost::thread(boost::bind(&Repeater::execute, this)));
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
#endif


}
