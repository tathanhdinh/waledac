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
 * compare two entries by their timestamps
 */
bool compare_entry(const entry_t& entry_a, const entry_t& entry_b)
{
	return (entry_a.first > entry_b.first);
}


/*
 * update RList from other repeaters
 */
void Repeater::update_rlist()
{
	// select random repeater
	bots_t current_rlist = this->rlist();
	bot_t selected_bot = random_bot(current_rlist);
	repeater_t selected_repeater = boost::dynamic_pointer_cast<Repeater>(selected_bot);
	
	// get sub_rlist from this repeater
	updatingbotlist_t requested_rlist = selected_repeater->sub_rlist();
	
	// get UpdateTS
	boost::posix_time::ptime update_ts = boost::posix_time::from_iso_string(requested_rlist->update_timestamp());
	
	// get CurrentTS
	boost::posix_time::ptime current_ts = boost::posix_time::second_clock::local_time();
	
	// concat two requested bot entries and current bot entries
	entries_t concated_entries = m_bot_rlist->bot_list();
	concated_entries.insert(concated_entries.end(), requested_rlist->bot_list().begin(), requested_rlist->bot_list().end());
	
	// update all timestamp in concated list
	boost::posix_time::ptime ts_i;
	boost::posix_time::ptime new_ts;
	for (unsigned int i = 0; i < concated_entries.size(); ++i) {
		ts_i = boost::posix_time::from_iso_string(concated_entries[i].first);
		new_ts = current_ts - (update_ts - ts_i);
		concated_entries[i].first = boost::posix_time::to_iso_string(new_ts);
	}
	
	// sort all entries in concated list
	std::sort(concated_entries.begin(), concated_entries.end(), compare_entry);
	
	// update RList
	unsigned int rlist_size;
	rlist_size = m_bot_rlist->bot_list().size();
	
	m_bot_rlist->bot_list().clear();
	for (unsigned int i = 0; i < rlist_size; ++i) {
		m_bot_rlist->bot_list().push_back(concated_entries[i]);
	}
	m_bot_rlist->update_timestamp() = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
	
	return;
}


/*
 * update PList from other repeater
 */
void Repeater::update_plist()
{
	// select random repeater
	bots_t current_plist = this->plist();
	bot_t selected_bot = random_bot(current_plist);
	repeater_t selected_repeater = boost::dynamic_pointer_cast<Repeater>(selected_bot);
	
	// get sub_rlist from this repeater
	updatingbotlist_t requested_plist = selected_repeater->sub_plist();
	
	// get UpdateTS
	boost::posix_time::ptime update_ts = boost::posix_time::from_iso_string(requested_plist->update_timestamp());
	
	// get CurrentTS
	boost::posix_time::ptime current_ts = boost::posix_time::second_clock::local_time();
	
	// concat two requested bot entries and current bot entries
	entries_t concated_entries = m_bot_plist->bot_list();
	concated_entries.insert(concated_entries.end(), requested_plist->bot_list().begin(), requested_plist->bot_list().end());
	
	// update all timestamp in concated list
	boost::posix_time::ptime ts_i;
	boost::posix_time::ptime new_ts;
	for (unsigned int i = 0; i < concated_entries.size(); ++i) {
		ts_i = boost::posix_time::from_iso_string(concated_entries[i].first);
		new_ts = current_ts - (update_ts - ts_i);
		concated_entries[i].first = boost::posix_time::to_iso_string(new_ts);
	}
	
	// sort all entries in concated list
	std::sort(concated_entries.begin(), concated_entries.end(), compare_entry);
	
	// update RList
	unsigned int rlist_size;
	rlist_size = m_bot_plist->bot_list().size();
	
	m_bot_plist->bot_list().clear();
	for (unsigned int i = 0; i < rlist_size; ++i) {
		m_bot_plist->bot_list().push_back(concated_entries[i]);
	}
	m_bot_plist->update_timestamp() = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
}


/*
 * receive messages from other spammers
 */
// static void receive_message(bot_t& repeater)
// {
// 	repeater->status() = RECEIVING_MESSAGE;
// 	return;
// }
void Repeater::receive_message()
{
	this->status() = RECEIVING_MESSAGE;
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
	//m_rlist.resize(rlist_size);
	//m_plist.resize(plist_size);
	
	m_bot_rlist->bot_list().resize(rlist_size);
	m_bot_plist->bot_list().resize(plist_size);
	
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
	m_bot_rlist->bot_list().clear();
	m_bot_plist->bot_list().clear();
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
	
	// get current time in seconds
	std::string current_time = boost::posix_time::to_iso_string(
																		boost::posix_time::second_clock::local_time());
	
	// create a sublist
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
	
	// get current time in seconds
	std::string current_time = boost::posix_time::to_iso_string(
																		boost::posix_time::second_clock::local_time());
	
	// create a sublist
	updatingbotlist_t upd_sub_rlist(new UpdatingBotList(current_rlist, current_time));
	return upd_sub_rlist;
}


/*
 * return PList
 */
bots_t Repeater::plist()
{
	bots_t bots_in_plist;
	entries_t current_plist = m_bot_plist->bot_list();
	
	for (unsigned int i = 0; i < current_plist.size(); ++i) {
		bots_in_plist.push_back(current_plist[i].second);
	}
	return bots_in_plist;
}


/*
 * return RList
 */
bots_t Repeater::rlist()
{
	bots_t bots_in_rlist;
	entries_t current_rlist = m_bot_rlist->bot_list();
	
	for (unsigned int i = 0; i < current_rlist.size(); ++i) {
		bots_in_rlist.push_back(current_rlist[i].second);
	}
	return bots_in_rlist;
}


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
	
	// get current time in seconds
	m_bot_rlist->update_timestamp() = boost::posix_time::to_iso_string(
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
		//update_rlist(current_bot);
		update_rlist();
		boost::this_thread::sleep(boost::posix_time::seconds(m_upd_rlist_time));
		
		//update_plist(current_bot);
		update_plist();
		boost::this_thread::sleep(boost::posix_time::seconds(m_upd_plist_time));
		
		receive_message();
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
