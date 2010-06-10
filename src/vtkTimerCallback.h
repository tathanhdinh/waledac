#ifndef VTKTIMERCALLBACK_H
#define VTKTIMERCALLBACK_H

#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTesting.h>

#include <vtkCamera.h>

class vtkBotnetGraph;
 
class vtkTimerCallback : public vtkCommand
{
  public:
    vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph);
 	~vtkTimerCallback();
 	
    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData));
 
    vtkBotnetGraph *ptrbotnetgraph;
    
    bool first_time;
 
};
 
#endif


