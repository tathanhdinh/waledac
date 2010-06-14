#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QGridLayout>
#include "Botnet.h"
#include "QVTKBotnetGraphWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
		MainWindow();
		void add_vtk_simulation(waledac::Botnet *botnet);
		
		QGridLayout *grid_layout;
		
	private slots:
		void slot_start_simulation();   
		void slot_show_about(); 

	private:
		void create_menus();
    
    	QVTKBotnetGraphWidget *qvtkbotnetgraph_widget;
    	QMenu *menu_simulation;
   		QMenu *menu_help;
   		
   		QAction *start_simulation_action;
		QAction *about_action;
};

#endif
