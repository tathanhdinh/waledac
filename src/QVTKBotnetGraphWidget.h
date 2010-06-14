#ifndef QVTKBOTNETGRAPHWIDGET_H
#define QVTKBOTNETGRAPHWIDGET_H

#include "QVTKWidget.h"
#include "vtkBotnetGraph.h"

class QVTKBotnetGraphWidget : public QVTKWidget
{
    Q_OBJECT

	public:
		QVTKBotnetGraphWidget(QWidget *parent);
		~QVTKBotnetGraphWidget();

		vtkBotnetGraph *botnet_graph;
};

#endif
