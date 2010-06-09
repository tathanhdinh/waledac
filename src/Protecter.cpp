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

#include "Protecter.h"
#include "ServerCC.h"
#include "Botnet.h"

#include <iostream>

namespace waledac
{

/*
 * protecter constructor
 */
Protecter::Protecter() : Bot()
{
}


/*
 * send message to C&C server and get response
 */
response_code Protecter::send_message(message_code message)
{
	boost::shared_ptr<ServerCC> server;
	server = boost::dynamic_pointer_cast<ServerCC>(Botnet::server());
	
	response_code response;
	response = server->process_message(message);
	
	return response;
}


/*
 * 
 */
void Protecter::init()
{
	return;
}


/*
 * life of protecter
 */
void Protecter::execute()
{
	while (true) {
		// wait for request from repeater
		sleep(5);
	}
	return;
}


/*
 * start protecter thread
 */
void Protecter::start()
{
	std::cout << "start protecter with id : " << Bot::id() << std::endl;
	m_protecter_thread.reset(new boost::thread(boost::bind(&Protecter::execute, 
														   *this)));
	return;
}


/*
 * wait until protecter thread stop
 */
void Protecter::wait()
{
	m_protecter_thread->join();
	return;
}


}