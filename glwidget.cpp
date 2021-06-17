#include "glwidget.h"

GLWidget::GLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    x1=0;
    y1=0;
    init=false;
    line=false;
}
void GLWidget::drawline(float fx1, float fy1,float fx2,float fy2)
{
    x1=fx1*38+width()/2;
    y1=fy1*38+height()/2;
    x2=fx2*38+width()/2;
    y2=fy2*38+height()/2;
    line=true;
    update();
}

void GLWidget::drawfunction(QVector<QLineF> const & l)
{
    func = l;
    function=true;
    update();

}
void GLWidget::initializeGL()
{
    glClearColor(1,1,1,0);
}
void GLWidget::paintEvent(QPaintEvent *e)
{
    if(!init)
    {
        QPainter p;
        p.begin(this);
        p.drawLine(width()/2,0,width()/2,height());
        p.drawLine(width(),height()/2,0,height()/2);
        float pas=38;
        for(int i=0;i*pas<height()/2;i++)
        {
            p.drawLine(width()/2-2,height()/2+i*pas,width()/2+2,(height()/2)+i*pas);
            p.drawLine(width()/2-2,height()/2-i*pas,width()/2+2,(height()/2)-i*pas);
        }
        for(int i=0;i*pas<width()/2;i++)
        {
            p.drawLine(width()/2+i*pas,height()/2+2,width()/2+i*pas,(height()/2)-2);
            p.drawLine(width()/2-i*pas,height()/2+2,width()/2-i*pas,(height()/2)-2);
        }
        init = true;
        return;

    }
    if(line)
        {
        QPainter p;
        p.begin(this);
        float a = (y2-y1)/(x2-x1);
        float b = y2-a*x2;
        if(a>0)
        {
            float maxX = (height()-b)/a;
            if(maxX>width() ||maxX<0)
                maxX=width();
            float minX = 0;
            if(b>height() || b<0)
                minX=(height()+b)/a;
            p.translate(0,height());
            p.drawLine(minX,minX*a-b,maxX,-(maxX*a+b));
            line=false;
        }
        else
        {

            float maxX = (0-b)/a;
            if(maxX>width()|| maxX<0)
                maxX=width();
            float minX = 0;
            if(b>height() || b<0)
                minX=(0+b)/a;
            p.translate(0,height());
            p.drawLine(minX,minX*a-b,maxX,-(maxX*a+b));
            line=false;

        }
    }
    if(function)
    {
        QPainter p;
        p.begin(this);
        p.drawLines(func);
    }

}



