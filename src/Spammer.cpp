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
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include <stdio.h>

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
void Spammer::update_rlist()
{
	bot_t repeater_target;
	bots_t received_rlist;
	unsigned int nb_try = 0;
	
	// repeat
	if (m_rlist.size() > 0) {
		while (true) {
			// takes a random repeater from rlist
			repeater_target = random_bot(m_rlist);
			
			/*std::cout << "\033[22;32m" 
						<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
						% "spammer" % Bot::id() % "updates RList from repeater" % repeater_target->id();*/
						
			// get subset of rlist from this repeater
			received_rlist = boost::dynamic_pointer_cast<Repeater>(repeater_target)->sub_rlist();
			
			if (received_rlist.size() > 0) { // until received non-empty list
				// merge new rlist and existing rlist
				m_rlist = spammer_merge_rlist(m_rlist, received_rlist);
				break;
			}
			
			nb_try++;
			if (nb_try >= 10) break;
		}
	}
	
	this->status() = UPDATE_RLIST;
	
	//std::cout << "received list size : " << received_rlist.size() << std::endl;
	
	return;
}


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
bots_t Spammer::rlist()
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
                boost::shared_ptr< Repeater > repeater_proxy;
                repeater_proxy = boost::dynamic_pointer_cast< Repeater >(random_bot(m_rlist));
                
                // get a response
                /*std::cout << "spammer " << this->id() 
                                << " send message to repeater " 
                                << repeater_proxy->id() << std::endl;*/
                response = repeater_proxy->send_message(message);
                
                switch (message) {
                        case MESSAGE_GETKEY:
                                this->status() = SEND_MESSAGE_GETKEY;
                                break;
                                
                        case MESSAGE_FIRST:
                                this->status() = SEND_MESSAGE_FIRST;
                                break;
                                
                        case MESSAGE_NOTIFY:
                                this->status() = SEND_MESSAGE_NOTIFY;
                                break;
                                
                        case MESSAGE_EMAILS:
                                this->status() = SEND_MESSAGE_EMAILS;
                                break;
                                
                        case MESSAGE_TASKREQ:
                                this->status() = SEND_MESSAGE_TASKREQ;
                                break;
                                
                        case MESSAGE_WORDS:
                                this->status() = SEND_MESSAGE_WORDS;
                                break;
                                
                        case MESSAGE_TASKREP:
                                this->status() = SEND_MESSAGE_TASKREP;
                                break;
                                
                        case MESSAGE_HTTPSTATS:
                                this->status() = SEND_MESSAGE_HTTPSTATS;
                                break;
                                
                        case MESSAGE_CREDS:
                                this->status() = SEND_MESSAGE_CREDS;
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
	std::vector< boost::shared_ptr<Bot> > all_repeater = rlist;
	m_rlist = random_bots(all_repeater, all_repeater.size() / 3);
	
#ifndef THREAD_VERSION
	this->send_message(MESSAGE_GETKEY);
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
	
	send_message(MESSAGE_GETKEY);
	boost::this_thread::sleep(boost::posix_time::seconds(7));
	
	send_message(MESSAGE_FIRST);
	boost::this_thread::sleep(boost::posix_time::seconds(7));
	
	while (status() != STOPPED) {
		update_rlist();
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
		response = send_message(MESSAGE_TASKREQ);
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		
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
