#include "widget.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   Widget window;
   window.setWindowTitle("Color Pointing");
   window.resize(300, 250);
   window.show();
   return app.exec();
}
