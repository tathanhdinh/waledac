#include "OptionsDialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
	this->setWindowTitle("Timer option");
	
	this->parent = (QVTKBotnetWidget *) parent;
	
	timerbox = new QSpinBox;
	timerbox->setRange(100000,1000000);
	timerbox->setValue(500000);
	
    QLabel *txtLabel = new QLabel;
    txtLabel->setText("specify the latency during the modification of graphs");
    
	QPushButton *closeButton = new QPushButton(tr("Close"));
	closeButton->setDefault(true);
	closeButton->setEnabled(true);
         
    QGridLayout *diagLayout = new QGridLayout;     
  	diagLayout->addWidget(txtLabel, 0, 0);
    diagLayout->addWidget(timerbox, 1, 0);
    diagLayout->addWidget(closeButton, 2, 0);
	
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
  
	diagLayout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(diagLayout);
    this->adjustSize();
}

OptionsDialog::~OptionsDialog()
{

}










