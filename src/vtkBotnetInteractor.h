#ifndef VTKBOTNETINTERACTOR_H
#define VTKBOTNETINTERACTOR_H

#include <vtkInteractorStyleTrackballCamera.h>

class vtkBotnetGraph;

class vtkBotnetInteractor : public vtkInteractorStyleTrackballCamera
{
	public:
   
   		vtkBotnetInteractor();
   		~vtkBotnetInteractor();
   		
   		void setbotnet(vtkBotnetGraph *ptrbotnetgraph);
   		virtual void OnLeftButtonDown();
   		
   		vtkBotnetGraph *ptrbotnetgraph;
};

#endif



