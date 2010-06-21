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

#ifndef BOT_H
#define BOT_H

#include "Connection.h"
#include "botnet_types.h"

#include <string>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/date_time.hpp>

namespace waledac 
{

enum message_code 
{
	MESSAGE_GETKEY = 0,
	MESSAGE_FIRST = 1,
	MESSAGE_NOTIFY = 2,
	MESSAGE_EMAILS = 3,
	MESSAGE_TASKREQ = 4,
	MESSAGE_WORDS = 5,
	MESSAGE_TASKREP = 6,
	MESSAGE_HTTPSTATS = 7,
	MESSAGE_CREDS = 8
};

enum response_code 
{
	RESPONSE_FAILED = 0, // response from not yet implemented methods
	RESPONSE_OK = 1,
	RESPONSE_GETKEY = 2,
	RESPONSE_STOP = 3
};

enum bot_status 
{
	SEND_MESSAGE_GETKEY = 0,
	SEND_MESSAGE_FIRST = 1,
	SEND_MESSAGE_NOTIFY = 2,
	SEND_MESSAGE_EMAILS = 3,
	SEND_MESSAGE_TASKREQ = 4,
	SEND_MESSAGE_WORDS = 5,
	SEND_MESSAGE_TASKREP = 6,
	SEND_MESSAGE_HTTPSTATS = 7,
	SEND_MESSAGE_CREDS = 8,
	
	UPDATE_RLIST = 9,
	UPDATE_PLIST = 10,
	
	STOPPED = 11,
	IDLE = 12,
	
	UPDATING_RLIST = 0,
	UPDATING_PLIST = 1,
	RECEIVING_MESSAGE = 2,
	SENDING_MESSAGE = 3,
	PROCESSING_TASK = 4
};


class Bot : public boost::enable_shared_from_this< Bot >
{
private :
	std::string m_id;                          // Id - each bot has a unique indentifier
	
	std::string m_timestamp;                   // Timestamp - timestamp of system in which bot locates
	
	bot_status m_status;                       // Status - in his life, each bot moves from one status to another one
	
	connections_t m_connections;               // Connections number - number of connection from bot to another ones

public :
	Bot();
	virtual const std::string& id() const;
	
	virtual const std::string& timestamp() const;
	
	virtual bot_status& status();
	
	virtual bool is_compromised();
	
	virtual connections_t& connections();
	
	virtual response_code send_message(message_code message) = 0;
	
	virtual void init(bot_t& server, bots_t& plist, bots_t& rlist) = 0;
	
	#ifdef THREAD_VERSION
		virtual void execute() = 0;
		virtual void start() = 0;
		virtual void wait() = 0;
	#endif

};

extern bot_t random_bot(bots_t & bot_list);
extern bots_t random_bots(bots_t& bot_list, unsigned int bot_number);
extern unsigned int random_number(unsigned int max);
extern bots_t merge_list(bots_t& original_list, bots_t& new_list);
extern bool compare_bot(bot_t a, bot_t b);
extern bool unique_bot(bot_t a, bot_t b);
extern bots_t remove_duplicate(bots_t& list);

extern void update_connections(bot_t& bot, bots_t& connected_bots);
extern void refresh_connections(bot_t& bot);


class compare_bot_class
{
public:
	bool operator()(const bot_t& bot_a, const bot_t& bot_b);
};

}


#endif // BOT_H
