#include "vtkBotnetInteractor.h"
#include "vtkBotnetGraph.h"

vtkBotnetInteractor::vtkBotnetInteractor()
{
	this->first_time = true;
}

vtkBotnetInteractor::~vtkBotnetInteractor()
{
}

void vtkBotnetInteractor::setbotnet(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
}

void vtkBotnetInteractor::OnLeftButtonDown()
{
	printf("ALLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAAAAAAL LEFT\n");
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}

void vtkBotnetInteractor::OnRightButtonDown()
{
	printf("ALLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAAAAAAL RIGHT\n");
	if(this->first_time)
	{
		this->ptrbotnetgraph->botnet->start();
		//this->ptrbotnetgraph->botnet->wait();
		printf("FINITO\n");
		this->first_time = false;
	}
	else
	{
		this->ptrbotnetgraph->update_graph();
		this->ptrbotnetgraph->graphLayoutView->ResetCamera();
		this->ptrbotnetgraph->graphLayoutView->Render();
	}	
		
	//vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}

