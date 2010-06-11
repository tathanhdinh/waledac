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
#include <vector>
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "botnet_types.h"



namespace waledac {

class Repeater : public Bot
{
private:
	bots_t m_rlist;
	bots_t m_plist;
	#ifdef THREAD_VERSION
	boost::shared_ptr<boost::thread> m_repeater_thread;
	#endif

public:
	Repeater();
	virtual void update_rlist();
	virtual void update_plist();
	
	virtual bots_t sub_rlist();
	virtual bots_t sub_plist();
	
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
