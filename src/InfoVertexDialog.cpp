#include "InfoVertexDialog.h"
#include "vtkBotnetInteractorStyle.h"

InfoVertexDialog::InfoVertexDialog(vtkBotnetInteractorStyle *irenstyle) : QDialog()
{
	this->ptrirenstyle = irenstyle;
	this->setWindowTitle("Bot"); 

    QLabel *symbol_vertex_label = new QLabel;
    symbol_vertex_label->setText("<font color=\"white\"><b>Bot</b></font>");	
   
    QPushButton *closeButton = new QPushButton(tr("Fly to"));
	closeButton->setDefault(true);
	closeButton->setEnabled(true);
	
	QGridLayout *diagLayout = new QGridLayout; 
	diagLayout->addWidget(symbol_vertex_label, 0, 0);
	diagLayout->addWidget(closeButton, 1, 0);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(click_flyto()));

	this->setLayout(diagLayout);
}

InfoVertexDialog::~InfoVertexDialog()
{

}

void InfoVertexDialog::click_flyto()
{
    this->ptrirenstyle->FlyToLastClick();
}

void InfoVertexDialog::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QColor black = Qt::black;
	painter.fillRect(event->rect(), black);
}
  		
  		
  		

