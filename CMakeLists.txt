cmake_minimum_required(VERSION 2.8)

project(waledac)

find_package(Boost REQUIRED)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
FIND_PACKAGE(Qt4 REQUIRED) 
INCLUDE(${QT_USE_FILE})

set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_FLAGS "-Wall -W -Wno-deprecated -D THREAD_VERSION")

include_directories(/usr/local/include/vtk-5.6/)
link_directories(/usr/local/lib/vtk-5.6/)

set(waledac_botnet_src src/UpdatingBotList.cpp src/Connection.cpp src/Connection.cpp
	src/Bot.cpp src/Spammer.cpp src/Repeater.cpp src/Protecter.cpp
	src/ServerCC.cpp src/Attacker.cpp src/Botnet.cpp
	src/OptionsDialog.cpp src/vtkTimerCallback.cpp src/vtkBotnetGraph.cpp src/vtkBotnetInteractorStyle.cpp src/main.cpp
)

set(waledac_botnet_libraries
	boost_system-mt boost_thread-mt boost_program_options-mt boost_date_time-mt ossp-uuid++
)

set(waledac_botnet_vtk_libraries
	vtkHybrid vtkViews
)

set(waledac_botnet_qt_libraries
	${QT_LIBRARIES}
)

SET(waledac_botnet_moc_srcs src/OptionsDialog.h)
  
QT4_WRAP_CPP(waledac_botnet_src ${waledac_botnet_moc_srcs})

add_executable(waledac ${waledac_botnet_src})
target_link_libraries(waledac ${waledac_botnet_libraries} ${waledac_botnet_qt_libraries} ${waledac_botnet_vtk_libraries})




