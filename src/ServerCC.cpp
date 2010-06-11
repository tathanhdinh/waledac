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

#include "ServerCC.h"

#include <iostream>

namespace waledac
{

/*
 * ServerCC constructor
 * Remark : It should be implemented as singleton class
 */
ServerCC::ServerCC() : Bot()
{
}


/*
 *
 */
response_code ServerCC::process_message(message_code message)
{
	response_code response = RESPONSE_OK;
	switch (message)
	{
		case MESSAGE_GETKEY:
			response = RESPONSE_OK; // server always generate key for new spammer
			break;
			
		case MESSAGE_FIRST:
			response = RESPONSE_OK; // server always accepts new spam
			break;
			
		case MESSAGE_NOTIFY:
			response = RESPONSE_FAILED; // not yet implemented behaviour
			break;
		
		case MESSAGE_EMAILS:
			response = RESPONSE_FAILED; // not yet implemented behaviour
			break;
			
		case MESSAGE_TASKREQ:
			response = RESPONSE_FAILED; // not yet implemented behaviour
			break;
			
		default:
			response = RESPONSE_FAILED;
			break;
	}
	
	return response;
}

/*
 * C&C server never takes the initiative of communication
 */
response_code ServerCC::send_message(message_code message)
{
        // do nothing
        return RESPONSE_FAILED;
}

/*
 * initialiser C&C server
 */
void ServerCC::init(bot_t server, bots_t plist, bots_t rlist)
{
	return;
}


#ifdef THREAD_VERSION
/*
 * life of C&C server
 */
void ServerCC::execute()
{
        while (true) {
                // wait for request from protecter
                sleep(5);
        }
        return;
}


/*
 * start serverCC thread
 */
void ServerCC::start()
{
        std::cout << "start servercc with id : " << Bot::id() << std::endl;
        m_servercc_thread.reset(new boost::thread(boost::bind(&ServerCC::execute, this)));
        return;
}


/*
 * wait until serverSS stop
 */
void ServerCC::wait()
{
        m_servercc_thread->join();
        return;
}
#endif


}
