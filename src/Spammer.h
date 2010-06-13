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

#ifndef SPAMMER_H
#define SPAMMER_H

#include "Bot.h"
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "botnet_types.h"
class vtkBotnetGraph;



namespace waledac {

class Spammer : public Bot
{
private:
	bots_t m_rlist;
	void update_status(response_code code);
	
	#ifdef THREAD_VERSION
	boost::shared_ptr< boost::thread > m_spammer_thread;
	#endif
	
public:
	Spammer();
	//void update_rlist();
	
	bots_t& rlist();
	
	virtual response_code send_message(message_code message);
	
	virtual void init(bot_t& server, bots_t& plist, bots_t& rlist);
	
	#ifdef THREAD_VERSION
	virtual void execute();
	virtual void start();
	virtual void wait();
	#endif

};

}

#endif // SPAMMER_H
