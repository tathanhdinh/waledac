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

#ifndef SERVERCC_H
#define SERVERCC_H

#include "Bot.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "botnet_types.h"



namespace waledac {

/*
 * Structure of server C&C.
 * Remark : the server C&C should be implemented as a singleton class,
 */
class ServerCC : public Bot
{
private:
	#ifdef THREAD_VERSION
	boost::shared_ptr<boost::thread> m_servercc_thread;
	#endif	 

public:
	ServerCC();
	
	response_code process_message(message_code message);
	virtual response_code send_message(message_code message);
	
	virtual void init(bot_t& server, bots_t& plist, bots_t& rlist);

	#ifdef THREAD_VERSION
	virtual void execute();
	virtual void start();
	virtual void wait();
	#endif

};

}

#endif // SERVERCC_H
