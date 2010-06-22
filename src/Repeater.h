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

#ifndef REPEATER_H
#define REPEATER_H

#include "Bot.h"
#include "UpdatingBotList.h"

#include <vector>
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "botnet_types.h"



namespace waledac {

class Repeater : public Bot
{
friend class Attacker;

private:
	bots_t m_rlist;                        // Rlist
	
	bots_t m_plist;                        // PList
	
	updatingbotlist_t m_bot_rlist;         // New version of RList
	
	updatingbotlist_t m_bot_plist;         // New version of PList
	
	unsigned int m_sub_rlist_size;         // Size of sub RList 
	
	unsigned int m_sub_plist_size;         // Size of sub PList
	
	unsigned int m_upd_rlist_time;         // Time (in seconds) in which Bot has UPDATING_RLIST status
	
	unsigned int m_upd_plist_time;         // Time (in seconds) in which Bot has UPDATING_PLIST status
	
	unsigned int m_rec_msg_time;           // Time (in seconds) in which Bot has RECEIVING_MESSAGE status
	
	unsigned int m_sed_msg_time;           // Time (in seconds) in which Bot has SENDING_MESSAGE status
	
	virtual void update_rlist();
	virtual void update_plist();
	virtual void receive_message();
	
	#ifdef THREAD_VERSION
	boost::shared_ptr<boost::thread> m_repeater_thread;
	#endif

public:
	Repeater(unsigned int rlist_size, 
					 unsigned int plist_size,
					 unsigned int sub_rlist_size,
					 unsigned int sub_plist_size,
					 unsigned int update_rlist_time = 1,
					 unsigned int update_plist_time = 1,
					 unsigned int receive_msg_time = 1,
					 unsigned int send_msg_time = 1);
	
	Repeater();
	//virtual void update_rlist();
	//virtual void update_plist();
	
// 	virtual bots_t sub_rlist();
// 	virtual bots_t sub_plist();
	
	virtual updatingbotlist_t sub_rlist();
	virtual updatingbotlist_t sub_plist();
	
// 	virtual unsigned int default_sub_rlist_size();
// 	virtual unsigned int default_sub_plist_size();
	
	bots_t plist();
	bots_t rlist();
	
	virtual response_code send_message(message_code message);
	
	virtual void init(bot_t& server, bots_t& plist, bots_t& rlist);
	
	#ifdef THREAD_VERSION
	virtual void execute();
	virtual void start();
	virtual void wait();
	#endif
};

}

#endif // REPEATER_H
