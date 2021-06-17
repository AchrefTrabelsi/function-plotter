#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QPainter>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
private:
    float  x1,y1,y2,x2;
    bool init,line,function;
    QVector<QLineF> func;
public:
    explicit GLWidget(QWidget * parent);
    void initializeGL() override;
    void drawline(float , float,float ,float );
    void drawfunction(QVector<QLineF> const &);
    void paintEvent(QPaintEvent *e) override;
};

#endif // GLWIDGET_H
