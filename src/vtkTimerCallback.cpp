#include "vtkTimerCallback.h"
#include "vtkBotnetGraph.h"
#include "Botnet.h"
#include "vtkActor.h"

vtkTimerCallback::vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
}
 
vtkTimerCallback::~vtkTimerCallback()
{
}

void vtkTimerCallback::Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData))
{
	if(vtkCommand::TimerEvent == eventId)
	{
		#ifndef THREAD_VERSION
		this->ptrbotnetgraph->botnet->start();
		#endif
		this->ptrbotnetgraph->update_graph(this->ptrbotnetgraph->botnet->repeaters_list(),this->ptrbotnetgraph->botnet->protecters_list(),this->ptrbotnetgraph->botnet->spammers_list(),this->ptrbotnetgraph->botnet->attackers_list());
	}
}

