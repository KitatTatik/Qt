    #ifndef Hfl_H
    #define Hfl_H
     
    #include <QObject>
    #include <QGraphicsItem>
    #include <QPainter>
    #include <QGraphicsScene>
    #include <QKeyEvent>
    #include <QDebug>
    #include <QGraphicsObject>

     
         
    class Hfl : public QGraphicsObject
    {
        Q_OBJECT

    public:
        explicit Hfl();
        Qt::FocusPolicy StrongFocus;
        Qt::FocusPolicy grabKeyboard;
        void setXY (int,int);

        ~Hfl();


    signals:
     
    protected:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void keyPressEvent(QKeyEvent *event);
    private:
        qreal angle,ratio;
        int ix,iy;

     
    };
     
    #endif // Hfl_H
