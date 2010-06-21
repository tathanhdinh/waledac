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
// 	repeater_t current_repeater;
// 	current_repeater = boost::dynamic_pointer_cast<Repeater>(repeater);
// 	
// 	bots_t rlist;
// 	rlist = current_repeater->rlist();
// 	
// 	if (rlist.size() > 0) {
// 		// takes a random repeater from rlist
// 		bot_t destination_bot;
// 		repeater_t destination_repeater;
// 		
// 		destination_bot = random_bot(rlist);
// 		destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
// 		
// 		// get subset of rlist from this repeater
// 		bots_t received_rlist;
// 		received_rlist = destination_repeater->sub_rlist();
// 		
// 		if (received_rlist.size() > 0) {
// 			connections_t connections;
// 			connections = current_repeater->connections();
// 			
// 			connection_t current_connection;
// 			current_connection = find_connection(connections, repeater, destination_bot);
// 			
// 			current_connection->type() = CONNECTION_UPDATE_RLIST;
// 		
// 			// merge new rlist and existing rlist
// 			current_repeater->rlist() = repeater_merge_list(rlist, received_rlist);
// 		}
// 	}
// 	
// 	repeater->status() = UPDATE_RLIST;
	return;
}


/*
 * update PList from other repeater
 */
static void update_plist(bot_t& repeater)
{
// 	repeater_t current_repeater;
// 	current_repeater = boost::dynamic_pointer_cast<Repeater>(repeater);
// 	
// 	bots_t rlist;
// 	rlist = current_repeater->rlist();
// 	
// 	if (rlist.size() > 0) {
// 		// takes a random repeater from rlist
// 		bot_t destination_bot;
// 		repeater_t destination_repeater;
// 		
// 		destination_bot = random_bot(rlist);
// 		destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
// 		
// 		// get subset of plist from this repeater
// 		bots_t received_plist;
// 		received_plist = dynamic_cast<Repeater*>(destination_bot.get())->sub_plist();
// 		
// 		if (received_plist.size() > 0) {
// 			// merge new plist and existing plist
// 			bots_t plist;
// 			plist = current_repeater->plist();
// 			current_repeater->plist() = repeater_merge_list(plist, received_plist);
// 		}
// 	}
// 	
// 	repeater->status() = UPDATE_PLIST;
	return;
}


/*
 * receive messages from other spammers
 */
static void receive_message(bot_t& repeater)
{
	repeater->status() = RECEIVING_MESSAGE;
	return;
}


/*
 * constructor with parameters
 */
Repeater::Repeater(unsigned int rlist_size, 
									 unsigned int plist_size,
									 unsigned int sub_rlist_size,
									 unsigned int sub_plist_size,
									 unsigned int update_rlist_time, 
									 unsigned int update_plist_time, 
									 unsigned int receive_msg_time, 
									 unsigned int send_msg_time): Bot()
{
	m_rlist.resize(rlist_size);
	m_plist.resize(plist_size);
	
	m_sub_rlist_size = sub_rlist_size;
	m_sub_plist_size = sub_plist_size;
	
	m_upd_rlist_time = update_rlist_time;
	m_upd_plist_time = update_plist_time;
	m_rec_msg_time = receive_msg_time;
	m_sed_msg_time = send_msg_time;
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
 * extract a random subset of repeater with timestamp from PList
 */
updatingbotlist_t Repeater::sub_plist()
{
	entries_t current_plist = m_bot_plist->bot_list();
	std::random_shuffle(current_plist.begin(), current_plist.end());
	
	entries_t new_plist;
	for (unsigned int i = 0; i < m_sub_plist_size; ++i) {
		new_plist.push_back(current_plist[i]);
	}
	
	std::string current_time = boost::posix_time::to_simple_string(
																		boost::posix_time::second_clock::local_time());
	
	updatingbotlist_t upd_sub_plist(new UpdatingBotList(current_plist, current_time));
	return upd_sub_plist;
}


/*
 * extract a random subset of repeater with timestamp from RList
 */
updatingbotlist_t Repeater::sub_rlist()
{
	entries_t current_rlist = m_bot_rlist->bot_list();
	std::random_shuffle(current_rlist.begin(), current_rlist.end());
	
	entries_t new_rlist;
	for (unsigned int i = 0; i < m_sub_rlist_size; ++i) {
		new_rlist.push_back(current_rlist[i]);
	}
	
	std::string current_time = boost::posix_time::to_simple_string(
																		boost::posix_time::second_clock::local_time());
	
	updatingbotlist_t upd_sub_rlist(new UpdatingBotList(current_rlist, current_time));
	return upd_sub_rlist;
}


/*
 * return PList
 */
// bots_t Repeater::plist()
// {
// 	return m_plist;
// }


/*
 * return RList
 */
// bots_t Repeater::rlist()
// {
// 	return m_rlist;
// }


/*
 * forward message from spammer to protecter
 */
response_code Repeater::send_message(message_code message)
{
	response_code response = RESPONSE_FAILED;
	
	if (Bot::status() == RECEIVING_MESSAGE) {
		if (m_plist.size() > 0) {
			boost::shared_ptr< Protecter > protecter_proxy;
			protecter_proxy = boost::dynamic_pointer_cast<Protecter>(random_bot(m_plist));
			
			response = protecter_proxy->send_message(message);
		}
	}
	
	return response;
}


/*
 * initialise m_bot_rlist and m_bot_plist of repeater before running
 */
void Repeater::init(bot_t& server, bots_t& plist, bots_t& rlist)
{
	bots_t rlist_init;
	rlist_init = random_bots(rlist, m_rlist.size());
	
	for (unsigned int i = 0; i < rlist_init.size(); ++i) {		
		m_bot_rlist->bot_list().push_back(entry_t(rlist_init[i]->timestamp(), rlist_init[i]));
	}
	
	m_bot_rlist->update_timestamp() = boost::posix_time::to_simple_string(
																						boost::posix_time::second_clock::local_time());
	
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
		update_rlist(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(m_upd_rlist_time));
		
		update_plist(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(m_upd_plist_time));
		
		receive_message(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(m_rec_msg_time));
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
