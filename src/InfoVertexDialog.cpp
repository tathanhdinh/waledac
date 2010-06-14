#include "InfoVertexDialog.h"
#include "vtkBotnetGraph.h"
#include "vtkRenderWindowInteractor.h"
#include "Spammer.h"

InfoVertexDialog::InfoVertexDialog(vtkBotnetGraph *ptrbotnetgraph, bot_t bot) : QDialog()
{
	this->ptrbotnetgraph = ptrbotnetgraph;
	this->setWindowTitle("Bot"); 

    QLabel *bot_label = new QLabel;
   	bot_label->setText("<font color=\"white\"><b>Bot</b></font>");	
   
   	QLabel *bot_type_label = new QLabel;
   
    bool info_perc_rlist = false;
    bots_t rlist;
    
    if(in_list(this->ptrbotnetgraph->botnet->repeaters_list(), bot))
    {
    	bot_type_label->setText("<font color=\"white\">Repeaters</font>");
    }
    else if(in_list(this->ptrbotnetgraph->botnet->protecters_list(), bot))
    {
    	bot_type_label->setText("<font color=\"white\">Protecters</font>");
    }
    else if(in_list(this->ptrbotnetgraph->botnet->spammers_list(), bot))
    {
    	bot_type_label->setText("<font color=\"white\">Spammers</font>");
    	info_perc_rlist = true;
    	waledac::Spammer *spammer = dynamic_cast<waledac::Spammer*>(bot.get());
    	rlist = spammer->rlist();
    }
    else if(in_list(this->ptrbotnetgraph->botnet->attackers_list(), bot))
    {
    	bot_type_label->setText("<font color=\"white\">Attackers</font>");
    }
    else if(unique_bot(this->ptrbotnetgraph->botnet->server(), bot))
    {
    	bot_type_label->setText("<font color=\"white\">Server</font>");
    }
    
    QGridLayout *diagLayout = new QGridLayout; 
	diagLayout->addWidget(bot_label, 0, 0);
	diagLayout->addWidget(bot_type_label, 0, 1);
    
    if(info_perc_rlist)
    {
    	QLabel *rlist_compromised_perc_label = new QLabel;
    	QLabel *rlist_compromised_label = new QLabel;
    	rlist_compromised_label->setText("<font color=\"white\"><b>Rlist compromised</b></font>");
    
    	QString rlist_compromised_perc_text("<font color=\"white\">");
		rlist_compromised_perc_text.append(QString::number(get_stats_compromised(rlist)));
    	rlist_compromised_perc_text.append("</font>");
    	rlist_compromised_perc_label->setText(rlist_compromised_perc_text);
    	
    	diagLayout->addWidget(rlist_compromised_label, 1, 0);
		diagLayout->addWidget(rlist_compromised_perc_label, 1,1);
    }
    
    QPushButton *closeButton = new QPushButton(tr("Fly to"));
	closeButton->setDefault(true);
	closeButton->setEnabled(true);
	
	diagLayout->addWidget(closeButton, 2, 0);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(click_flyto()));

	this->setLayout(diagLayout);
}

InfoVertexDialog::~InfoVertexDialog()
{

}

void InfoVertexDialog::click_flyto()
{
    this->ptrbotnetgraph->interactor_style->FlyToLastClick();
}

void InfoVertexDialog::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QColor black = Qt::black;
	painter.fillRect(event->rect(), black);
}
  		
  		
  		

