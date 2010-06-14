#include "mainwindow.h"

#include <QDialog>
#include <QLabel>
#include <QMenuBar>
#include <QLabel>
#include <QLabel>
#include <QLabel>


MainWindow::MainWindow()
{
	this->grid_layout = new QGridLayout;   
	
	QWidget* widget = new QWidget();
    widget->setLayout(grid_layout);
    this->setCentralWidget(widget);
	this->setWindowTitle("Botnet Simulation :: Visualization");

	create_menus();
}

void MainWindow::slot_show_about()
{
	QDialog dlg;
	dlg.setWindowTitle("About");
	dlg.setStyleSheet("background-color: rgb(255,255,255)");
	
    QLabel *imgLabel = new QLabel;
    QPixmap loriapixmap("./data/imgs/lorialogo.jpeg");
    QPixmap scaledloriapixmap = loriapixmap.scaled(QSize(180,150));
    imgLabel->setPixmap(scaledloriapixmap);
       
    QLabel *txtLabel = new QLabel;
    txtLabel->setText("<center>INRIA Lorraine<br>Team Carte<br>Botnet Simulation</center>");
         
    QGridLayout *diagLayout = new QGridLayout;     
  	diagLayout->addWidget(imgLabel, 0, 0);
    diagLayout->addWidget(txtLabel, 1, 0);
    
	diagLayout->setSizeConstraint(QLayout::SetFixedSize);
    dlg.setLayout(diagLayout);
    dlg.adjustSize();
    
    dlg.exec();
}

void MainWindow::slot_start_simulation()
{	
	this->qvtkbotnetgraph_widget->botnet_graph->start_simulation();
}

void MainWindow::add_vtk_simulation(waledac::Botnet *botnet)
{
	this->qvtkbotnetgraph_widget = new QVTKBotnetGraphWidget(this);
	this->qvtkbotnetgraph_widget->botnet_graph->set_simulation(botnet);
	this->grid_layout->addWidget(this->qvtkbotnetgraph_widget, 0, 0);
}

void MainWindow::create_menus()
{	
	this->menu_simulation = this->menuBar()->addMenu(tr("Simulation"));
	
		this->start_simulation_action = new QAction(tr("Start"), this);
		this->start_simulation_action->setStatusTip(tr("start simulation"));
		connect(this->start_simulation_action, SIGNAL(triggered()), this, SLOT(slot_start_simulation()));
    	this->menu_simulation->addAction(this->start_simulation_action);
    
    this->menuBar()->addSeparator();
    this->menu_help = this->menuBar()->addMenu(tr("Help"));
    
    	this->about_action = new QAction(tr("About"), this);
		this->about_action->setShortcuts(QKeySequence::AddTab);
		this->about_action->setStatusTip(tr("About"));
		connect(this->about_action, SIGNAL(triggered()), this, SLOT(slot_show_about()));
    	this->menu_help->addAction(this->about_action);
}





