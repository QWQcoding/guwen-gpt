#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
using namespace std;
const QString Re[150] = { "比", "鄙", "兵", "病", "乘", "持", "从", "达", "当", "道", "得", "尔", "伐", "犯", "方", "负", "赋", "更", "苟", "故", "顾", "观", "归", "过", "好", "号", "还", "会", "惠", "及", "极", "计", "济", "假", "间", "简", "见", "竭", "尽", "进", "居", "举", "具", "俱", "聚", "遽", "决", "绝", "类", "临", "虑", "论", "漫", "明", "名", "命", "难", "平", "戚", "强", "窃", "请", "穷", "求", "取", "去", "全", "任", "入", "若", "善", "少", "舍", "涉", "生", "胜", "师", "施", "实", "食", "使", "释", "市", "恃", "数", "属", "说", "素", "汤", "徒", "亡", "为", "委", "务", "鲜", "向", "效", "谢", "信", "行", "形", "兴", "修", "徐", "许", "寻", "业", "遗", "贻", "夷", "异", "易", "诣", "益", "阴", "引", "盈", "余", "狱", "御", "缘", "远", "云", "章", "知", "止", "志", "致", "质", "专", "走", "足", "卒", "作", "坐", "卑鄙", "布衣", "菲薄", "其实", "亲戚", "驱驰", "无论", "牺牲", "鸿儒", "白丁", "阡陌", "交通", "问津", "绝境", "妻子" };
const QString Im[6] = { "之", "其", "而", "以", "何", "于" };
const QString Type[2] = { "实词", "虚词" };
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->total->setReadOnly(1);
    ui->current->setReadOnly(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
struct Node{
    int pos,type,id;
    bool operator<(const Node&x)const{
        return pos<x.pos||pos==x.pos&&type<x.type||pos==x.pos&&type==x.type&&id<x.id;
    }
};

vector<Node> current;
void MainWindow::on_startButton_clicked()
{
    ui->total->clear();
    ui->current->clear();
    current.clear();
    QString s=ui->originText->toPlainText();
    int tot=0,totIm=0,totRe=0;
    for(int i=0;i<150;i++){
        int now=s.indexOf(Re[i]);
        while(now!=-1){
            current.push_back((Node){now,0,i});
            tot++;
            totRe++;
            now=s.indexOf(Re[i],now+1);
        }
    }
    for(int i=0;i<6;i++){
        int now=s.indexOf(Im[i]);
        while(now!=-1){
            current.push_back((Node){now,1,i});
            tot++;
            totIm++;
            now=s.indexOf(Im[i],now+1);
        }
    }
    sort(current.begin(),current.end());
    QString sumRe="共 "+QString::number(totRe)+" 个实词";
    QString sumIm="共 "+QString::number(totIm)+" 个虚词";
    QString sum="总计 "+QString::number(tot)+" 个";
    ui->total->appendPlainText(sumRe);
    ui->total->appendPlainText(sumIm);
    ui->total->appendPlainText(sum);
    for(int i=0;i<current.size();i++){
        QString now=QString::number(i+1)+". "+Type[current[i].type]+": ";
        if(current[i].type==0){
            now+=Re[current[i].id];
        }
        else{
            now+=Im[current[i].id];
        }
        ui->current->appendPlainText(now);
    }
}

