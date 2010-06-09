#include "vtkBotnetInteractor.h"
#include "vtkBotnetGraph.h"

vtkBotnetInteractor::vtkBotnetInteractor()
{
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
	unsigned int i, j;
	
	for(j = 0; j < 100; j++)
	{
		for(i = 0; i < this->ptrbotnetgraph->nb_repeaters; i++)
		{
			this->ptrbotnetgraph->repeaters[i]->update_random_rlist(this->ptrbotnetgraph->repeaters);
			this->ptrbotnetgraph->repeaters[i]->update_random_plist(this->ptrbotnetgraph->protecters);
		}
		
		for(i = 0; i < this->ptrbotnetgraph->nb_protecters; i++)	
		{
			this->ptrbotnetgraph->protecters[i]->update_random_rlist(this->ptrbotnetgraph->repeaters);
			this->ptrbotnetgraph->protecters[i]->update_random_plist(this->ptrbotnetgraph->protecters);
		}
		
		for(i = 0; i < this->ptrbotnetgraph->nb_spammers; i++)	
		{
			this->ptrbotnetgraph->spammers[i]->update_random_rlist(this->ptrbotnetgraph->repeaters);
			this->ptrbotnetgraph->spammers[i]->update_random_plist(this->ptrbotnetgraph->protecters);
		}
	
		this->ptrbotnetgraph->update_graph();
	
		this->ptrbotnetgraph->graphLayoutView->ResetCamera();
		this->ptrbotnetgraph->graphLayoutView->Render();
	}
	
	
		this->ptrbotnetgraph->graphLayoutView->GetInteractor()->Start();
	
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

