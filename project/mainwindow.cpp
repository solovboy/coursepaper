#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
MainWindow::~MainWindow()
{
       delete ui;
}
//������� ���������
void MainWindow::paintEvent(QPaintEvent* pe) {
    QPainter p(this);
   p.setPen(QPen(Qt::red));
   int h=this->menuBar()->height();
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
        {
    p.drawRect(50*i,50*j+h,50,50);
    if (C[i][j]>0)
        p.drawEllipse(QPoint(50*i+25,50*j+25+h),15,15);
}
   if ((sost>0)&&(sost<5))
       p.setPen(QPen(Qt::blue,2));
   if (sost==0) p.drawText(0, 350+h, "Draw segments by two mouse clics");
   else if (sost==1)
       p.drawText(0, 350+h, "Error in clicks and  lines");
   else if (sost==2)
       p.drawText(0, 350+h, "Bad rotations");
  else if (sost==3)
           p.drawText(0, 350+h, "Wrong subcontour");
  else if (sost==4)
      p.drawText(0, 350+h, "No rotation in circle");
  else
      p.drawText(0, 350+h, "Successful solution");

    if (!solved) p.setPen(QPen(Qt::red));
    else p.setPen(QPen(Qt::blue,2));
    for(int i=0;i<=35;i++)
        for(int j=0;j<=35;j++)
        {
        if (Q[i][j]>0)
        {
            int i1=i/6;int i2=i%6;
            int j1=j/6;int j2=j%6;
            p.drawLine(QPoint(i1*50+25,i2*50+25+h),
                       QPoint(j1*50+25,j2*50+25+h));

        }

    }
}
void MainWindow::createMenus()
   {


      Pl = menuBar()->addMenu(tr("&Play"));
      Fl = menuBar()->addMenu(tr("&File"));


   }
void MainWindow::createActions()
{
QAction* backAction = new QAction(tr("&back"), this);
connect(backAction, SIGNAL(triggered()), this, SLOT(back()));
Pl->addAction(backAction);
QAction* allbackAction = new QAction(tr("&frombegin"), this);
connect(allbackAction, SIGNAL(triggered()), this, SLOT(allback()));
Pl->addAction(allbackAction);
QAction* exitAction = new QAction(tr("&exit"), this);
connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));
Pl->addAction(exitAction);

QAction* saveAction = new QAction(tr("&save1"), this);
connect(saveAction, SIGNAL(triggered()),this, SLOT(save1()));
Fl->addAction(saveAction);
QAction* loadAction = new QAction(tr("&load"), this);
connect(loadAction, SIGNAL(triggered()),this, SLOT(load1()));
Fl->addAction(loadAction);
QAction* loadNewAction = new QAction(tr("&loadNew"), this);
connect(loadNewAction, SIGNAL(triggered()),this, SLOT(loadN()));
Fl->addAction(loadNewAction);
}
void MainWindow::setC()
{
Nh=0;
solved=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            C[i][j]=0;
    C[0][0]=1;C[2][0]=1;C[4][0]=1;
    C[1][1]=1;C[3][1]=1;
    C[4][2]=1;
    C[2][3]=1;
    C[1][4]=1;
    C[3][5]=1;C[5][5]=1;
    para=0;
    sost=0;
for(int i=0;i<=35;i++)for(int j=0;j<=35;j++)
    {Q[i][j]=0;A[i][j]=0;}
}

//�������� ������������� �������
 bool MainWindow::dfs1(int k)
 {
     int H;
     dost[k]=1;
     for(int i=0;i<36;i++)
     if ((A2[k][i]>0)&&(dost[i]==1)&&(i!=prev[k]))
     {
         H=1;
         int kk=k;
         while(kk!=i)  {H++;kk=prev[kk];}
         if (H<36)
             return true;
     }
     for(int i=0;i<36;i++)
         if ((A2[k][i]>0)&&(dost[i]==0)){prev[i]=k;if (dfs1(i)) return true;}
return false;
     }
bool MainWindow::Is_bad_Contur(int A1[36][36])
{
    for(int i=0;i<36;i++)for(int j=0;j<36;j++)A2[i][j]=A1[i][j];
    for(int k=0;k<36;k++)
    {
    for(int i=1;i<=36;i++)
    { dost[i-1]=0;prev[i-1]=-1;}
        if(dfs1(k))
            return true;

     }
    return false;
}
int MainWindow::deg(int i,int A1[36][36])
{
    int m=0;
    for(int j=0;j<36;j++)
        m=m+A1[i][j];
    return m;

}
  bool MainWindow::Is_bad_Circle(int A1[36][36])
  {
      int AA[36][36];
      for(int i=0;i<36;i++)for(int j=0;j<36;j++)AA[i][j]=A1[i][j];

      for(int i=0;i<6;i++)
          for(int j=0;j<6;j++)
              if (C[i][j]>0)
          {
          int ii=i*6+j;
          if (deg(ii,A1)>=2)
              if (this->povorot(ii,A1)==false)
              return true;
          }
      return false;

  }
//������� ������� ����
 void MainWindow::mousePressEvent (QMouseEvent* pe)
{
     QMessageBox msgBox;

     int h=this->menuBar()->height();
     int xx1=x1;int yy1=y1; int  ppara=para;
   int xx=pe->x();int yy=pe->y();
   int i=xx/50;
   int j=(yy-h)/50;

  if ((i>=0)&&(i<6)&&(j>=0)&&(j<6))
   {
      if (para==0)
      {x1=i;y1=j;para=1;}
      else if ((para==1)&&((i==xx1)||(j==yy1))&&((i!=xx1)||(j!=yy1)))

      {x2=i;y2=j;para=2;}
      else
      { sost=1; this->update();para=0;




          return;}
      if (para==2)
      {

          para=0;
          int m1=x1*6+y1;
          int m2=x2*6+y2;
          if (m1!=m2)
          {
          if (Q[m1][m2]>0)
          {
              Q[m1][m2]=0;
              Q[m2][m1]=0;
              int k=smeg(Q);
              int ii=1;
              while(ii<=Nh)
              {
                  if (((history[ii-1][0]==m1)&&(history[ii-1][1]==m2))
                      ||((history[ii-1][0]==m2)&&(history[ii-1][1]==m1)))
                      {
                      for(int ii1=ii+1;ii1<=Nh;ii1++)
                      {
                      history[ii1-2][0]=history[ii1-1][0];
                      history[ii1-2][1]=history[ii1-1][1];
                   Nh--;   }

                  }
                 ii++;
              }
          }
          else
          {

            if (this->Is_soed(m1,m2))
            {
               sost=1;this->update();
               Q[m1][m2]=0;Q[m2][m1]=0;
             //  msgBox.setText("Point2.");
            //   msgBox.exec();

               return;

            }
            Q[m1][m2]=1;
            Q[m2][m1]=1;
            }
            int k=smeg(Q);
            if (k>0)
            {Q[m1][m2]=0;Q[m2][m1]=0;sost=1;

                msgBox.setText("Point3.");
                msgBox.exec();

            }
            else
            {
            Nh++;
            history[Nh-1][0]=m1;history[Nh-1][1]=m2;save1();
            if (this->Is_solved()) {sost=5;this->solved=true;}
            else {sost=0;solved=false;}
            }
          }
          this->update();
        }
      }
  }

 //����������� ������� ����� ���� � ������� ��� ������������
int MainWindow::smeg(int Q1[36][36])
  {
       QMessageBox msgBox;

    int A1[36][36];
      for(int i=0;i<36;i++) for(int j=0;j<36;j++)A1[i][j]=0;

      for (int i=0;i<36;i++)
          for (int j=0;j<36;j++)
              if ((i<j)&&(Q1[i][j]>0))
          {

          int xx1=i/6;int yy1=i%6;
          int xx2=j/6;int yy2=j%6;
          if (xx1==xx2)
          {
              int Y1=xx1*6+yy1;
              int Y2=xx1*6+yy2;
              if (Y1>Y2){int Y=Y1;Y1=Y2;Y2=Y;}
              for (int ii=Y1;ii<=Y2;ii++)
                  for(int jj=Y1;jj<=Y2;jj++)
                  {
                        if ((abs(ii-jj)==1)||(abs(ii-jj)==6))
                        A1[ii][jj]++;

                  }

          }
          else if (yy1==yy2)
          {
              int X1=xx1*6+yy1;
              int X2=xx2*6+yy1;
              if (X1>X2){int X=X1;X1=X2;X2=X;}

              for (int ii=X1;ii<=X2;ii+=6)
                  for(int jj=X1;jj<=X2;jj+=6)
                  {
                  if ((abs(ii-jj)==1)||(abs(ii-jj)==6))
                  A1[ii][jj]++;

                   }
          }

          }
      int d[36];
       for(int i=0;i<36;i++) d[i]=0;
       for(int ii=0;ii<36;ii++)
           for(int jj=0;jj<36;jj++)
           {

         if ((jj!=ii)&&(A1[ii][jj]>0)) d[ii]++;
         if (d[ii]>2) {sost=1;

           //  msgBox.setText("Point3.1");
           //  msgBox.exec();
             return 1;}


           }

      // msgBox.setText("Beg");
     //  msgBox.exec();
       if (is_bad_povorots(A1))
       {
           sost=2;
          // msgBox.setText("Point3.2");
         //  msgBox.exec();

           return 1;
       }
       if (Is_bad_Contur(A1)){sost=3;
         //  msgBox.setText("Point3.3");
          // msgBox.exec();

           return 1;}
       if (this->Is_bad_Circle(A1)){sost=4;
          // msgBox.setText("Point3.4");
          // msgBox.exec();

           return 1;}
    for(int ii=0;ii<36;ii++)
        for(int jj=0;jj<36;jj++)
            A[ii][jj]=A1[ii][jj];
    sost=0;
    return 0;

  }
bool MainWindow::povorot(int i,int A1[36][36])
{
    int k1,k2;
    k1=i/6;k2=i%6;
    int i1=0;int j1=0;
    int ii=i-1;if ((k2>0)&&(A1[ii][i]>0)) j1=1;
    ii=i+1;if ((k2<5)&&(A1[ii][i]>0)) j1=1;
    int jj=i-6;if ((k1>0)&&(A1[jj][i]>0)) i1=1;
    jj=i+6;if ((k1<5)&&(A1[jj][i]>0)) i1=1;
    if ((i1>0)&&(j1>0)) return true;
    return false;
}
//������� ������������ �������� ������ ��������
 bool MainWindow::is_bad_povorots(int A1[36][36])
 {
     QMessageBox msgBox;
     int i1,i2,j1,j2,ii;
     int AA[36][36];
     for(int i=0;i<36;i++)for(int j=0;j<36;j++)AA[i][j]=A1[i][j];
     for (int i=0;i<36;i++)
     if (povorot(i,A1))
         {
         i1=i/6;i2=i%6;
         ii=i-1;
         while(ii>=i1*6)
         {
             if ((povorot(ii,A1))&&(A1[ii][ii+1]>0))
             {
               j1=ii/6;j2=ii%6;
               if ((C[i1][i2]==0)&&(C[j1][j2]==0))
               {
                 //  msgBox.setText("Point4.1");
                 //  msgBox.exec();

                   return  true;
               }
               if ((C[i1][i2]==1)&&(C[j1][j2]==1))
               {
                 //  msgBox.setText("Point4.2");
                 //  msgBox.exec();

                   return  true;
               }
             }
          if (A1[ii][ii+1]==0) break;
          ii--;
         }
         ii=i+1;
         while(ii<6*i1+6)
         {
             if ((povorot(ii,A1))&&(A1[ii][ii-1]>0))
             {
               j1=ii/6; j2=ii%6;
               if ((C[i1][i2]==0)&&(C[j1][j2]==0))
               {
                 //  msgBox.setText("Point4.3");
                //  msgBox.exec();

                   return  true;
               }
               if ((C[i1][i2]==1)&&(C[j1][j2]==1))
               {
                  // msgBox.setText("Point4.4");
                 //  msgBox.exec();

                   return  true;
               }

             }
            if (A1[ii][ii-1]==0) break;
            ii++;
         }
         ii=i-6;
         while(ii>=0)
         {
             if ((povorot(ii,A1))&&(A1[ii][ii+6]>0))
             {
               j1=ii/6;int j2=ii%6;
               if ((C[i1][i2]==0)&&(C[j1][j2]==0))
               {
                //   msgBox.setText("Point4.5");
                //   msgBox.exec();

                   return  true;
               }
               if ((C[i1][i2]==1)&&(C[j1][j2]==1))

               {
                 //  msgBox.setText("Point4.6");
                 // msgBox.exec();

                   return  true;
               }
             }
          if (A1[ii][ii+6]==0) break;
          ii-=6;
         }
         ii=i+6;

         while(ii<36)
         {
             if ((povorot(ii,A1))&&(A1[ii][ii-6]>0))
             {
               j1=ii/6;j2=ii%6;
               if ((C[i1][i2]==0)&&(C[j1][j2]==0))
               {
                 //  msgBox.setText("Point4.7");
                 //  msgBox.exec();

                   return  true;
               }
               if ((C[i1][i2]==1)&&(C[j1][j2]==1))
               {
                 //  msgBox.setText("Point4.8");
                //   msgBox.exec();

                   return  true;
               }

             }
            if (A1[ii][ii-6]==0) break;
            ii+=6;
         }

         }
     return false;
 }
//�������� ������������� �������
 int MainWindow::dfs(int k)
 {
     dost[k]=1;
     int H=1;
     for(int i=0;i<36;i++)
     if ((A[k][i]>0)&&(dost[i]==0))
         H=H+dfs(i);

     return H;


 }
  bool MainWindow::Is_solved()
{
int d[6][6];
for(int i=0;i<6;i++)for(int j=0;j<6;j++)d[i][j]=0;
for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
    {
    int ii=i*6+j;
    for(int jj=0;jj<36;jj++)
        if (A[ii][jj]>0) d[i][j]++;

    if (d[i][j]!=2) return false;
    }
     for (int i=0;i<36;i++)dost[i]=0;
    int H=dfs(0);
    if (H==36) return true;
    return false;

}


  void MainWindow::constr_from_history()
  {
      int m1,m2;
      for(int i=0;i<36;i++)
          for(int j=0;j<36;j++)
          {
          A[i][j]=0;Q[i][j]=0;

      }
      for (int i=1;i<=Nh;i++)
      {
          m1=history[i-1][0];
          m2=history[i-1][1];
          Q[m1][m2]=1;
          Q[m2][m1]=1;

      }
      int k=smeg(Q);
      update();
  }

void MainWindow::back()
{
   if (Nh>0) Nh--;
constr_from_history();
solved=Is_solved();
}
void MainWindow::allback()
{
   Nh=0;
   sost=0;
constr_from_history();

}
void MainWindow::load1()
{


    QFile file("LastGame.txt");
    file.open(QIODevice::ReadOnly);
 for(int i=0;i<6;i++)
    {

        QStringList lineData = QString(file.readLine()).split(" ");
        for(int j = 0; j < lineData.length(); ++j)
        {
            C[i][j]=lineData[j].toInt();

        }


    }
  QString L = QString(file.readLine());
  Nh=L.toInt();
   for(int i=0;i<Nh;i++)
  {
        QStringList lineData = QString(file.readLine()).split(" ");
       history[i][0]=lineData[0].toInt();
       history[i][1]=lineData[1].toInt();

   }
    sost=0;
    file.close();
    constr_from_history();


}
void MainWindow:: save1()
{

        QFile outputFile("LastGame.txt");
        if (outputFile.open(QIODevice::WriteOnly))
        {
           QTextStream out(&outputFile);
          for(int i=0;i<6;i++)
           {
              QString s="";
              for(int j=0;j<=5;j++)
                  s=s+QString::number(C[i][j])+" ";
              out<<s<<"\n";
           }
          out<<QString::number(Nh)<<"\n";
              for(int i=1;i<=Nh;i++)
          {
                QString s="";
                s=s+QString::number(history[i-1][0])+" "+
                  QString::number(history[i-1][1]);
                   out<<s<<"\n";
              }

               outputFile.close();
          }

}
void MainWindow:: exit()
{
   this->close();

}

void MainWindow::loadN()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        QString::fromUtf8("������� ����"),
        QDir::currentPath(), "Text files (*.txt)");

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    int i = 0;
    while(!file.atEnd())
    {
       i++;
        QStringList lineData = QString(file.readLine()).split(" ");
        for(int j = 0; j < lineData.length(); ++j)
        {
            C[i-1][j]=lineData[j].toInt();

        }

      if (i==6) break;
    }
    Nh=0;
    sost=0;
    file.close();
    constr_from_history();
}
bool MainWindow::Is_soed(int m1,int m2)
{
    if (m1>m2){int m=m1;m1=m2;m2=m;}
   int m=m1;
   int cod=0;
   while(m<m2)
   {
       m++;
       if (A[m][m-1]==0){cod=1;break;}

   }
    if (cod==0) return true;

    if ((m2-m1>5)&&((m2-m1)%6==0))
    {
        cod=0;
        m=m1;
    while(m<m2)
    {
        m+=6;
        if (A[m][m-6]==0){cod=1;break;}

    }
    if (cod==0) return true;

    }
    return false;
}
