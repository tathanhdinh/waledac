#ifndef BOTNETTYPES_H
#define BOTNETTYPES_H

#include <boost/smart_ptr.hpp>
#include <vector>

namespace waledac
{
	class Bot;
	class Repeater;
	class Botnet;
	class Connection;
}

typedef std::vector< boost::shared_ptr< waledac::Bot > > bots_t;
typedef boost::shared_ptr< waledac::Bot > bot_t;
typedef boost::shared_ptr< waledac::Repeater > repeater_t;

typedef std::vector< boost::shared_ptr< waledac::Connection > > connections_t;
typedef boost::shared_ptr< waledac::Connection > connection_t;

typedef boost::shared_ptr< waledac::Botnet > botnet_t;

#endif
