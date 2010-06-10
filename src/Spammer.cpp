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

namespace waledac
{

/*
 * merge existing rlist with a new rlist
 */
static std::vector< boost::shared_ptr<Bot> > 
spammer_merge_rlist(std::vector< boost::shared_ptr<Bot> > &existing_rlist, 
					std::vector< boost::shared_ptr<Bot> > &new_rlist)
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
	boost::shared_ptr<Bot> repeater_target;
	std::vector<boost::shared_ptr<Bot> > received_rlist;
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
			//received_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
			received_rlist = boost::dynamic_pointer_cast<Repeater>(repeater_target)->sub_rlist();
 			/*std::cout << "received list " << std::endl;
			for (unsigned int i = 0; i < received_rlist.size(); ++i) {
				std::cout << received_rlist[i]->id() << std::endl;
			}*/
			
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
	
	return;
}


/*
 * get command from C&C server
 */
void Spammer::request_command()
{
	if (m_rlist.size() > 0) {
		boost::shared_ptr<Bot> repeater_proxy;
		
		// take a random repeater from rlist
		repeater_proxy = random_bot(m_rlist);
		
		/*std::cout << "\033[01;36m" 
		<< boost::format("%1$'-'8s %2$'-'36s %3$'-'28s %4$'-'36s\n") 
		% "spammer" % Bot::id() % "get command through repeater" % repeater_proxy->id();*/
					
		unsigned int received_command = dynamic_cast<Repeater*>
											(repeater_proxy.get())->request_command();
		/*if (received_command == COMMAND_FROM_ATTACKER) {
			Bot::compromise();
			std::cout << "spammer is compromised" << std::endl;
		}*/
	}
	
	return;
}


/*
 * return rlist
 */
std::vector< boost::shared_ptr< Bot > > Spammer::rlist()
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
void Spammer::init()
{
	//m_rlist = Botnet::repeaters_list();
	
	// get a random sublist of all repeater
	std::vector< boost::shared_ptr<Bot> > all_repeater = Botnet::repeaters_list();
	m_rlist = random_bots(all_repeater, all_repeater.size() / 3);
	
	/*std::cout << "sdfsdfdsdfsdfsdfddddddddddddddddddddddd" << std::endl;
	for (unsigned int i = 0; i < m_rlist.size(); ++i) {
		std::cout << m_rlist[i]->id() << std::endl;
	}*/
	
	
	//std::cout << "spammer startup rlist size : " << m_rlist.size() << std::endl; 
	
	return;
}

/*
 * life of spammer
 */
void Spammer::execute()
{	
	// "getkey" message
	//std::cout << "spammer send MESSAGE_GETKEY to repeater" << std::endl;
	send_message(MESSAGE_GETKEY);
	//sleep(7);
	boost::this_thread::sleep(boost::posix_time::seconds(7));
	
	// "first" message
	//std::cout << "spammer send MESSAGE_FIRST to repeater" << std::endl;
	send_message(MESSAGE_FIRST);
	//sleep(7);
	boost::this_thread::sleep(boost::posix_time::seconds(7));
	
	while (true) {
		//std::cout << "address of current spammer : " << this << std::endl;
		/*std::cout << "before update : " << this->id() << std::endl;
		for (unsigned int i = 0; i < m_rlist.size(); ++i) {
			std::cout << m_rlist[i]->id() << std::endl;
		}*/
		update_rlist();
		/*std::cout << "after update : " << this->id() << std::endl;
		for (unsigned int i = 0; i < m_rlist.size(); ++i) {
			std::cout << m_rlist[i]->id() << std::endl;
		}*/
		//sleep(3);
		boost::this_thread::sleep(boost::posix_time::seconds(3));
		
		// obsolete, need to be replaced by send_message
		//request_command();
		//sleep(1);
		
		send_message(MESSAGE_TASKREQ);
		//sleep(2);
		boost::this_thread::sleep(boost::posix_time::seconds(2));
	}
	
	return;
}


/*
 * start spammer thread
 */
void Spammer::start()
{
	std::cout << "start spammer with id : " << Bot::id() << std::endl;
	//std::cout << "address of calling spammer : " << this << std::endl;
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

}
