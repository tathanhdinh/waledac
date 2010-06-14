#include "QVTKBotnetGraphWidget.h"

QVTKBotnetGraphWidget::QVTKBotnetGraphWidget(QWidget *parent = NULL) : QVTKWidget(parent)
{		
	this->botnet_graph = new vtkBotnetGraph(this->GetInteractor());
	this->SetRenderWindow(this->botnet_graph->win);
	this->botnet_graph->set_interactor(this->GetInteractor());
	this->GetInteractor()->SetInteractorStyle(this->botnet_graph->interactor_style);
}

QVTKBotnetGraphWidget::~QVTKBotnetGraphWidget()
{
	
}

