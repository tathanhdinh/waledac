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

#include "Spammer.h"
#include "Repeater.h"
#include "Botnet.h"
#include "Bot.h"
#include "Connection.h"

#include <iostream>

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>

namespace waledac
{

/*
 * merge existing rlist with a new rlist
 */
static bots_t spammer_merge_rlist(bots_t &existing_rlist, bots_t &new_rlist)
{
	return merge_list(existing_rlist, new_rlist);
}


/*
 * spammer update its Rlist
 */
static void update_rlist(bot_t& spammer)
{
	spammer_t current_spammer;
	current_spammer = boost::dynamic_pointer_cast<Spammer>(spammer);
	
	bots_t rlist;
	rlist = current_spammer->rlist();
	
	// repeat
	if (rlist.size() > 0) {
		bot_t destination_bot;
		repeater_t destination_repeater;
		bots_t received_rlist;
		unsigned int nb_try = 0;
	
		while (true) {
			// takes a random repeater from rlist
			destination_bot = random_bot(rlist);
			destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
			
			/*std::cout << "\033[22;32m" 
						<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
						% "spammer" % Bot::id() % "updates RList from repeater" % repeater_target->id();*/
						
			// get subset of rlist from this repeater
			received_rlist = destination_repeater->sub_rlist();
			
			if (received_rlist.size() > 0) { // until received non-empty list
				// update status of connection from current spammer to destination repeater
				connections_t connections;
				connections = current_spammer->connections();
				connection_t current_connection = find_connection(connections, spammer, destination_bot);
				/*if (current_connection == 0) {
					std::cout << "failed" << std::endl;
				}
				else {
					std::cout << "found" << std::endl;
				}*/
				current_connection->type() = CONNECTION_UPDATE_RLIST;
				
				
				// merge new rlist and existing rlist
				current_spammer->rlist() = spammer_merge_rlist(rlist, received_rlist);
				
				break;
			}
			
			nb_try++;
			if (nb_try >= 10) break;
		}
	}
	
	current_spammer->status() = UPDATE_RLIST;
}


/*
 * update connections from spammer to its bots in RList
 */
static void update_rlist_connections(bot_t& spammer)
{
	spammer_t current_spammer;
	current_spammer = boost::dynamic_pointer_cast<Spammer>(spammer);
	
	bots_t current_rlist;
	current_rlist = current_spammer->rlist();
	
	//std::cout << "update rlist connections" << std::endl;
	update_connections(spammer, current_rlist);
	
	return;
}


/*
 * constructor
 */
Spammer::Spammer() : Bot()
{
	// initialise rlist
	m_rlist.clear();
}


/*
 * update rlist from other spammers
 */
// void Spammer::update_rlist()
// {
// 	// repeat
// 	if (m_rlist.size() > 0) {
// 		bot_t destination_bot;
// 		repeater_t destination_repeater;
// 		bots_t received_rlist;
// 		unsigned int nb_try = 0;
// 	
// 		while (true) {
// 			// takes a random repeater from rlist
// 			destination_bot = random_bot(m_rlist);
// 			destination_repeater = boost::dynamic_pointer_cast<Repeater>(destination_bot);
// 			
// // 			std::cout << "\033[22;32m" 
// // 						<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
// // 						% "spammer" % Bot::id() % "updates RList from repeater" % repeater_target->id();
// 						
// 			// get subset of rlist from this repeater
// 			received_rlist = destination_repeater->sub_rlist();
// 			
// 			if (received_rlist.size() > 0) { // until received non-empty list
// 				// update status of connection from current spammer to destination repeater
// 				bot_t current_spammer = Bot::shared_from_this();
// 				connection_t current_connection = find_connection(Bot::connections(), 
// 																													current_spammer, 
// 																													destination_bot);
// 				current_connection->type() = CONNECTION_RLIST;
// 				
// 				
// 				// merge new rlist and existing rlist
// 				m_rlist = spammer_merge_rlist(m_rlist, received_rlist);
// 				
// 				break;
// 			}
// 			
// 			nb_try++;
// 			if (nb_try >= 10) break;
// 		}
// 	}
// 	
// 	this->status() = UPDATE_RLIST;
// 
// 	return;
// }


/*
 * uptade spammer status which depends on response codes
 */
void Spammer::update_status(response_code code)
{
	switch (code) {
		case RESPONSE_STOP:
			this->status() = STOPPED;
			break;
			
		default:
			break;
	}
	return;
}


/*
 * return rlist
 */
bots_t& Spammer::rlist()
{
	return m_rlist;
}


/*
 * send a message to repeater and get response
 */
response_code Spammer::send_message(message_code message)
{
	response_code response = RESPONSE_FAILED;

	if (m_rlist.size() > 0) {
		// take a random repeater from RList
		bot_t bot_proxy;
		repeater_t repeater_proxy;

		bot_proxy = random_bot(m_rlist);
		repeater_proxy = boost::dynamic_pointer_cast< Repeater >(bot_proxy);
		
		// find connection from current spammer to proxy repeater
		connection_t current_connection;
		bot_t current_spammer = Bot::shared_from_this();
		current_connection = find_connection(Bot::connections(), current_spammer, bot_proxy);

		// get a response
		/*std::cout << "spammer " << this->id() 
								<< " send message to repeater " 
								<< repeater_proxy->id() << std::endl;*/
		response = repeater_proxy->send_message(message);

		switch (message) {
			case MESSAGE_GETKEY:
				this->status() = SEND_MESSAGE_GETKEY;
				current_connection->type() = CONNECTION_GETKEY;
				break;
							
			case MESSAGE_FIRST:
				this->status() = SEND_MESSAGE_FIRST;
				current_connection->type() = CONNECTION_FIRST;
				break;
							
			case MESSAGE_NOTIFY:
				this->status() = SEND_MESSAGE_NOTIFY;
				current_connection->type() = CONNECTION_NOTIFY;
				break;
							
			case MESSAGE_EMAILS:
				this->status() = SEND_MESSAGE_EMAILS;
				current_connection->type() = CONNECTION_EMAILS;
				break;
							
			case MESSAGE_TASKREQ:
				this->status() = SEND_MESSAGE_TASKREQ;
				current_connection->type() = CONNECTION_TASKREQ;
				break;
							
			case MESSAGE_WORDS:
				this->status() = SEND_MESSAGE_WORDS;
				current_connection->type() = CONNECTION_WORDS;
				break;
							
			case MESSAGE_TASKREP:
				this->status() = SEND_MESSAGE_TASKREP;
				current_connection->type() = CONNECTION_TASKREP;
				break;
							
			case MESSAGE_HTTPSTATS:
				this->status() = SEND_MESSAGE_HTTPSTATS;
				current_connection->type() = CONNECTION_HTTPSTATS;
				break;
							
			case MESSAGE_CREDS:
				this->status() = SEND_MESSAGE_CREDS;
				current_connection->type() = CONNECTION_CREDS;
				break;
		}
	}

	return response;
}


/*
 * initialise rlist before running
 */
void Spammer::init(bot_t& server, bots_t& plist, bots_t& rlist)
{
	// get a random sublist of all repeater
	bots_t all_repeater = rlist;
	m_rlist = random_bots(all_repeater, all_repeater.size() / 3);
	
// 	connections_t spammer_connections;
// 	spammer_connections = Bot::connections();
	bot_t current_spammer;
	current_spammer = Bot::shared_from_this();

	update_rlist_connections(current_spammer);
	//std::cout << current_spammer->connections().size() << std::endl;

#ifndef THREAD_VERSION
	this->send_message(MESSAGE_GETKEY);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	this->send_message(MESSAGE_FIRST);
#endif
	return;
}


#ifdef THREAD_VERSION
/*
 * life of spammer
 */
void Spammer::execute()
{	
	response_code response;
	bot_t current_bot;
	current_bot = Bot::shared_from_this();
	
	send_message(MESSAGE_GETKEY);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	
	send_message(MESSAGE_FIRST);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	
	while (status() != STOPPED) {
		update_rlist(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
		update_rlist_connections(current_bot);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
		response = send_message(MESSAGE_TASKREQ);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
		refresh_connections(current_bot);
		
		update_status(response);
	}
	
	return;
}


/*
 * start spammer thread
 */
void Spammer::start()
{
	std::cout << "start spammer with id : " << Bot::id() << std::endl;
	m_spammer_thread.reset(new boost::thread(boost::bind(&Spammer::execute, this)));
	return;
}


/*
 * wait until spammer thread stop
 */
void Spammer::wait()
{
	m_spammer_thread->join();
	return;
}
#endif


}
