#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QDebug>
//#include <QTextCodec>
#include <QDataStream>
#include <QString>
#include <QDialog>
#include <QFileDialog>
 #include <QMessageBox>
//Ăđŕôč÷ĺńęčé číňĺđôĺéń ôîđěű
namespace Ui {
    class MainWindow;
}
//Ęëŕńń ăëŕâíîăî îęíŕ
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Ńîáűňčĺ ęëčęŕ ěűřč
    void paintEvent(QPaintEvent*);
    // Ńîçäŕíčĺ ěĺíţ
    void createMenus();
    //Ńîçäŕíčĺ ďóíęňîâ ěĺíţ
    void createActions();
    //Óńňŕíîâęč íŕ÷ŕëüíîé čăđű
    void setC();
    //Ďđîâĺđęŕ ęîđđ. äîáŕâëĺííîăî ńĺăěęĺíňŕ č ďđńňđ. ěŕňđ.ńěĺćíîńňč
    int smeg(int Q1[36][36]);
    //Ďđîâĺđęŕ ÷ňî â äŕííîé ˙÷ĺéęĺ ĺńňü ďîâîđîň ęđčâîé
     bool povorot(int i, int A1[36][36]);
     //Ďđîâĺđęŕ íŕ íĺďđŕâčëüíűĺ ďîâîđňű ďđč äîáŕâë. ńĺăěĺíňŕ
    bool is_bad_povorots(int A1[36][36]);
    //Âîńńňŕíîâëĺíčĺ čăđű ďî ĺĺ čńňîđčč
    void constr_from_history();
    //Ďîäń÷ĺň ÷čńëŕ äîńňčćčěűő ęëĺňîę čç ęëĺňęč i ďî ăđŕôó ńĺăěĺíňîâ
    int  dfs(int k);
    //Ďđîâĺđęŕ íŕëč÷č˙ ęîíčóđŕ ńîäĺđćŕůĺăî ęëĺčęó k
    bool dfs1(int k);
    //Ďđîâĺđęŕ ăđŕôŕ  A1[36][36] čăđű íŕ íŕëč÷čĺ íĺďîëíűő ęîíňóđîâ
    bool Is_bad_Contur(int A1[36][36]);
    //Ďđîâĺđęŕ íŕ íŕëč÷čĺ ęđóăŕ ďđîőîäčěîăî áĺç ďîâîđîňŕ
    bool Is_bad_Circle(int A1[36][36]);
    //Ńňĺďĺíü ęëĺňęč i â ďđîâĺđ˙ĺěîě ăđŕôĺ čăđű A1[36][36]
    int deg(int i,int A1[36][36]);
    //Ďđîâĺđęŕ ÷ňî čăđŕ đĺřĺíŕ
    bool Is_solved();
    //Ďđîâĺđęŕ ÷ňî ęëĺňęč m1 č m2 ńîĺäčíĺíű ďđ˙ěűě îňđĺçęîě
    bool Is_soed(int m1,int nm2);
    //Đŕńďîëîćĺíčĺ ęđóćęîâ
    int C[6][6];
    //Ěŕňđčöŕ ńĺăěĺíňîâ
    int Q[36][36];
   //Ěŕňîčöŕ ńěĺćíîńňč ęëĺňîę ďî ńĺăěĺíňŕě
    int A[36][36];
    //Âńďîěîăŕüĺëüíŕ˙ čďđîáíŕ˙ ěŕňđčöŕ ńěĺćíîńňč
    int A2[36][36];
    //âĺęňîđ äîńňčćčěűő âĺđůčí ďđč dfs ďîčńęĺ
    int dost[36];
    //âĺęňîđ ďđĺäřĺńňâóţůčő âĺđřčí ďđč dfs ďîčńęĺ
    int prev[36];
    //Čńňîđč˙ ââĺäĺííűő ńĺăěĺíňîâ
    int history[50][2];
    //Ęîîđäčíŕňű âűáđŕííűő ęëĺňîę ďđč ďîńňđîĺíčč ńĺăěĺíňîâ
    int x1;
    int y1;
    int x2;
    int y2;
    //Ęîëč÷ĺńňâî řŕăîâ â čńňîđčč čăđű
    int Nh;
    //Ńęîëüęî ęëĺňîę âűáđŕíî  ěűřęîé- 0,1,2
    int para;
    //Ńîńňî˙íčĺ čăđű- íîđě., îřčáęŕ ęîíňóđŕ, čăđŕ đĺřĺíŕ
    int sost;
    //Đĺřĺíŕ čëč íĺň čăđŕ
    bool solved;
    //Ďóíęňű ěĺíţ
    QMenu* Pl;
    QMenu* Fl;
    //Ńîáűňčĺ ęëčęŕ ěűřęîé ďî ďîëţ čăđű
    void mousePressEvent (QMouseEvent* pe);
//äĺńňđóęňîđ ăëŕâíîăî îęíŕ

    ~MainWindow();
//ęîíńňđóęňîđ ăëŕâíîăî îęíŕ
    explicit MainWindow(QWidget *parent = 0);

private:
    //Cnhernehf jryf
    Ui::MainWindow *ui;

private slots:
    //Âĺđíóňüń˙ íŕ řŕă íŕçŕä
    void back();
    //Ŕĺđíóňüń˙ â íŕ÷ŕëî čăđű
    void allback();
    //Ńîőđŕíčňü čńňîđčţ čăđű â ôŕéä LastGame.txt
    void save1();
    //Çŕăđóçčňü čńňîđčţ ďîńëĺäíĺé íĺçŕâĺđřĺííîé čăđű
    void load1();
    //Çŕăđóçčňü íîâóţ čăđó
    void loadN();
    //çŕâĺđřřčňü čăđó
    void exit();

};

#endif // MAINWINDOW_H
