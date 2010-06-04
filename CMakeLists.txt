project(waledac)

set(waledac_botnet_src
	src/Bot.cpp
	src/Spammer.cpp
	src/Repeater.cpp
	src/Protecter.cpp
	src/Servercc.cpp
	src/BotnetStaticConfiguration.cpp
	src/main.cpp
)

add_executable(waledac ${waledac_botnet_src})
target_link_libraries(waledac boost_system-mt boost_thread-mt ossp-uuid++)

