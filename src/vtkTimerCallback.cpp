#include "vtkTimerCallback.h"
#include "vtkBotnetGraph.h"

vtkTimerCallback::vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
	this->TimerCount = 0;
	this->first_time = true;
}
 
vtkTimerCallback::~vtkTimerCallback()
{
}

void vtkTimerCallback::Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData))
{
	if (vtkCommand::TimerEvent == eventId)
	{
		++this->TimerCount;
		
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
	}
	
	cout << this->TimerCount << endl;
}

