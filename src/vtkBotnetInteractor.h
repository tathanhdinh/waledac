#ifndef VTKBOTNETINTERACTOR_H
#define VTKBOTNETINTERACTOR_H

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMapper.h>
#include <vtkDataSet.h>
#include <vtkCamera.h>

class vtkBotnetGraph;

class vtkBotnetInteractor : public vtkInteractorStyleTrackballCamera
{
	public:
   
   		vtkBotnetInteractor();
   		~vtkBotnetInteractor();
   		
   		void setbotnet(vtkBotnetGraph *ptrbotnetgraph);
   		void FindBot(int point);
   		
   		virtual void OnLeftButtonDown();
   		virtual void OnRightButtonDown();
   		virtual void OnMouseWheelForward();
		virtual void OnMouseWheelBackward();
   		
   		vtkBotnetGraph *ptrbotnetgraph;
   		
   		bool first_time;
   		double zoom_save;
};

#endif



