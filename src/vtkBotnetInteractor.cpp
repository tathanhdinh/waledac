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
		
		
	//vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}

