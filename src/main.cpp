/*
  simple bitmap animation
*/
#include <QApplication>
#include <QMessageBox>

#include <QWidget>
#include <QTimer>    
#include <QPainter>  
#include <QPixmap>   
#include <QVector>   

class  BitmapAnimator : public QWidget {
  Q_OBJECT
  public:
    BitmapAnimator(QWidget *parent= nullptr): QWidget(parent), currentFrame(0){
      
      for (int i = 1; i <= 2; i++){
        QString path = QString(":/data/walking%1.png").arg(i);
        frames.append(QPixmap(path));
      }

      timer = new QTimer(this);
      connect(timer, &QTimer::timeout, this, [=](){
        currentFrame = (currentFrame + 1) % frames.size();
        update();
      });

      timer->start(100); 
    }

  protected:
    void paintEvent(QPaintEvent*) override {
      QPainter painter(this);
      if (!frames.isEmpty()){
        auto pix = frames[currentFrame];
        int x = (width() - pix.width()) / 2;
        int y = (height() - pix.height()) / 2;
        painter.drawPixmap(x, y, pix);
      }
    }

    QSize  sizeHint() const override {
      return QSize(400, 300);
    }

  private:
    QVector<QPixmap> frames;
    QTimer *timer;
    int currentFrame;
};


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    BitmapAnimator w;
    w.setWindowTitle("Bitmap Animation");
    w.show();
    return app.exec();
}

#include "main.moc"