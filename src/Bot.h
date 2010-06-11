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

#include <string>
#include <vector>
#include <boost/smart_ptr.hpp>

namespace waledac 
{

// obsolete codes
enum command_code 
{ 
	COMMAND_FROM_REPEATER = 0, 
	COMMAND_FROM_ATTACKER = 1 
};

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
	RESPONSE_OK = 0,
	RESPONSE_FAILED = 1, // not yet implemented methods
	RESPONSE_GETKEY = 0
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
	
	COMPROMISED = 11,
	IDLE = 12
};
	
class Bot : public boost::enable_shared_from_this< Bot >
{
private :
	std::string m_id;
	bot_status m_status;

public :
	Bot();
	const std::string& id() const;
	
	//virtual void update_status();
	virtual bot_status& status();
	
	// obsolete methods
	void compromise();
	bool is_compromised();
	
	virtual response_code send_message(message_code message) = 0;
	
	virtual void init() = 0;
	virtual void execute() = 0;
	virtual void start() = 0;
 	virtual void wait() = 0;
	
	//bool operator<(const Bot& other_bot);
};

extern boost::shared_ptr<Bot> random_bot(std::vector< boost::shared_ptr<Bot> >& 
										bot_list);
										
extern std::vector< boost::shared_ptr<Bot> > random_bots(
								std::vector< boost::shared_ptr<Bot> >& bot_list, 
								unsigned int bot_number);
										
extern unsigned int random_number(unsigned int max);

extern std::vector< boost::shared_ptr< Bot > > merge_list(
						std::vector< boost::shared_ptr< Bot > > &existing_rlist, 
						std::vector< boost::shared_ptr< Bot > > &received_rlist);
						
extern bool compare_bot(boost::shared_ptr<Bot> a, boost::shared_ptr<Bot> b);

extern bool unique_bot(boost::shared_ptr<Bot> a, boost::shared_ptr<Bot> b);

extern std::vector< boost::shared_ptr< Bot > > remove_duplicate(
									std::vector< boost::shared_ptr< Bot > > &list);

}


#endif // BOT_H
