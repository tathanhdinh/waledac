#ifndef BOTNETTYPES_H
#define BOTNETTYPES_H

#include <boost/smart_ptr.hpp>
#include <boost/date_time.hpp>

#include <vector>
#include <map>

namespace waledac
{
	class Bot;
	class Spammer;
	class Repeater;
	class Botnet;
	class Connection;
	class UpdatingBotList;
}

typedef std::vector< boost::shared_ptr< waledac::Bot > > bots_t;
typedef boost::shared_ptr< waledac::Bot > bot_t;
typedef boost::shared_ptr< waledac::Spammer > spammer_t;
typedef boost::shared_ptr< waledac::Repeater > repeater_t;

typedef std::vector< boost::shared_ptr< waledac::Connection > > connections_t;
typedef boost::shared_ptr< waledac::Connection > connection_t;

typedef boost::shared_ptr< waledac::Botnet > botnet_t;

typedef std::map< boost::posix_time::ptime, bot_t > entry_t;
typedef std::vector< entry_t > entries_t;

typedef boost::shared_ptr< waledac::UpdatingBotList > updatingbotlist_t;

#endif
