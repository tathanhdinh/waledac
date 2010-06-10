#include "vtkTimerCallback.h"
#include "vtkBotnetGraph.h"

vtkTimerCallback::vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
	this->first_time = true;
}
 
vtkTimerCallback::~vtkTimerCallback()
{
}

void vtkTimerCallback::Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData))
{
	if(vtkCommand::TimerEvent == eventId)
	{
		if(this->first_time)
		{
			/* on laisse vtk positionner la caméra */
			this->ptrbotnetgraph->botnet->start();
			this->ptrbotnetgraph->update_graph();
			this->ptrbotnetgraph->graphLayoutView->ResetCamera();
			this->ptrbotnetgraph->graphLayoutView->Render();
			
			/* hack = on attrape le renderer */
			this->ptrbotnetgraph->interactor->FindPokedRenderer(this->ptrbotnetgraph->interactor->GetInteractor()->GetEventPosition()[0], this->ptrbotnetgraph->interactor->GetInteractor()->GetEventPosition()[1]);
			if (this->ptrbotnetgraph->interactor->GetCurrentRenderer() == NULL)
    			return;		
  	
  			/* on sauvegarde le coefficient du zoom au départ */
    		vtkCamera *camera = this->ptrbotnetgraph->interactor->GetCurrentRenderer()->GetActiveCamera();
			if(camera->GetParallelProjection())
				this->ptrbotnetgraph->interactor->zoom_save = camera->GetParallelScale();

			this->first_time = false;
		}
		else
		{	
			this->ptrbotnetgraph->update_graph();
			//this->ptrbotnetgraph->graphLayoutView->ResetCamera();
			
			vtkCamera *camera = this->ptrbotnetgraph->interactor->GetCurrentRenderer()->GetActiveCamera();
			if(camera->GetParallelProjection())
				camera->SetParallelScale(this->ptrbotnetgraph->interactor->zoom_save);
			
			this->ptrbotnetgraph->graphLayoutView->Render();
		}
	}
}

