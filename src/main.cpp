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
#include <QResizeEvent>

/*
  Gradient widget: write pixel values into a buffer (a QImage)
*/
class GradientWidget : public QWidget {
  Q_OBJECT
  public:
    GradientWidget(QWidget *parent = nullptr):
      QWidget(parent), img(width(), height(), QImage::Format_RGB32){
      
        updateImage();
        timer = new QTimer(this);
        // (object1, signal1, object2, signal2)
        connect(timer, &QTimer::timeout, this, [=](){
          offset = (offset + 2) % width(); // movement speed of gradient 2px each tick
          updateImage();
          update();
        });

        timer->start(30); // ~30 fps, the event is triggered 
      }
  protected:
    // recreates the image when the widget's size changes so you always paint the full area 
    void resizeEvent(QResizeEvent *event) override {
      img = QImage(event->size(), QImage::Format_RGB32);
      updateImage();
    }
    
    // blit the buffer onto the window 
    void paintEvent(QPaintEvent *) override {
      QPainter p(this);
      //          x, y -> top left point
      p.drawImage(0, 0, img);
    }

  private:
    // image buffer
    QImage img;
    QTimer *timer;
    int offset; 

    void updateImage(){
      const int width = img.width();
      const int height = img.height();
      uint32_t *pixels = reinterpret_cast<uint32_t*>(img.bits()); // pointer to the raw pixel data (treated as uint32_t), pixel is 1D array representing 2D image.
      const int stride = img.bytesPerLine() / 4; // width of image in terms of pixels (uint32_t)
      /*
       * top
       *  |
       *  |height increase
       *  |
       * down     width increase
       *  right ------------------ left 
       */
      for (int y = 0; y < height; ++y){ 
        for (int x = 0; x < width; ++x){ 
          uint8_t red   = static_cast<uint8_t>((x + offset) % 255); // as offset increases, the red values shift horizontally 
          uint8_t green = static_cast<uint8_t>(y % 255);
          uint8_t blue  = 128;
          // combine r,g,b into a single 32 bit pixel value
          pixels[y*stride+x] = qRgb(red, green, blue);
        }
      }
    }
};

/*
  main function
*/
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    GradientWidget gw;
    gw.setWindowTitle("Gradient show");
    gw.resize(400,300);
    gw.show();

    // lets start the event loop (smth that waits for the event to occur and call respective things)
    return app.exec();
}

#include "main.moc"
