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

void vtkBotnetInteractor::OnMouseWheelForward() 
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
		
	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if(camera->GetParallelProjection())
		this->zoom_save = camera->GetParallelScale();
}

void vtkBotnetInteractor::OnMouseWheelBackward()
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
	
	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if(camera->GetParallelProjection())
		this->zoom_save = camera->GetParallelScale();
}

void vtkBotnetInteractor::OnLeftButtonDown()
{
	bool click_point = false;
	
	int* clickPos = this->GetInteractor()->GetEventPosition();
	vtkPointPicker* picker = (vtkPointPicker *)this->GetInteractor()->GetPicker();
	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	double* pos = picker->GetPickPosition();	
	vtkActor* pickedObject = picker->GetActor();
	
	if(pickedObject != NULL)
	{
		printf("get actor fini\n");
		int point = pickedObject->GetMapper()->GetInput()->FindPoint(pos[0],pos[1],pos[2]);
		
		/*
		printf("find point fini\n");
    	vtkDataArray *arr = pickedObject->GetMapper()->GetInput()->GetPointData()->GetArray("InputPointIds");
		printf("data array fini\n");
		if(arr != NULL && point >= 0 && point < arr->GetNumberOfTuples())
		{
			int ipid = (int)*(arr->GetTuple(point));
			printf("ipid = %d\n",ipid);
     			
			if(ipid >= 0)
     		{
     			printf("actor assoc\n");
     			int a = this->vtkcfg->actors_list[pickedObject];
     			printf("vrai ipid\n");
		 		int vrai_ipid = this->vtkcfg->vertex_symb_list[a][ipid];
		 		printf("node\n");
    			node_t *node = this->vtkcfg->vertex_list[vrai_ipid];
    		
				if(node != NULL)
				{
					printf("vertex\n");
					vertex_t *vertex = (vertex_t *) node->vertex;
    			
					printf("%d === %d === (%d)\n",ipid,vertex->symb,point);
					InfoVertexDialog info_vertex((int)vertex->add, vertex->code, vertex->code_length, vertex->symb);
					info_vertex.exec();
    			
    				click_point = true;
    				return;
				}
			}
		}*/
	}
	
	// forward events
	if(!click_point)
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();



	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}

void vtkBotnetInteractor::OnRightButtonDown()
{	
	printf("ALLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAAAAAAL RIGHT\n");
	
	this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
	if(this->CurrentRenderer == NULL)
    	return;
  
	//this->GrabFocus(this->EventCallbackCommand);
	//this->StartDolly();
	//double factor = this->MotionFactor * 0.2 * this->MouseWheelMotionFactor;
	//this->Dolly(pow(1.1, factor));	
	
	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if(camera->GetParallelProjection())
	{
		printf("scale = %f\n",camera->GetParallelScale());
		camera->SetParallelScale(camera->GetParallelScale()*2);
	}
	
	//this->EndDolly();
	//this->ReleaseFocus();		
		
		
		
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}











