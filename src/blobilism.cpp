#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
#include <math.h>

using namespace tinygl;

struct Color{
  float R;
  float G;
  float B;
};

struct CurrentInfo{
  int size;
  float transparency;
  Color currentColor;
  int x;
  int y;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) override {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      CurrentInfo myCircle ={myInfo.size,myInfo.transparency,myInfo.currentColor,x,y};
      circles.push_back(myCircle);
    }
  }
  
  virtual void mouseDown(int button, int mods) override{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      int ix = 50;
      for(Color myColor:myPallet){
        if(sqrt(pow(mx-ix,2)+pow(my-40,2))<=25.0){
          myInfo.currentColor = myColor;
          std::cout << "Setting color to "<<myColor.R<<" "<<myColor.G<<" "<<myColor.B<< std::endl;
        }
        ix+=60;
      }
    }
  }

  void keyDown(int key, int mods) override {
    if (key == GLFW_KEY_UP) {
      myInfo.size += 5;
      std::cout << "Pressed UP: Increase point size to "<<myInfo.size<< std::endl;
    } 
    else if (key == GLFW_KEY_DOWN) {
      myInfo.size -= 5;
      if(myInfo.size<1){
        myInfo.size = 1;
      }
      std::cout << "Pressed DOWN: Decrease point size to "<<myInfo.size<< std::endl;
    }
    else if (key == GLFW_KEY_LEFT) {
      myInfo.transparency -=0.05;
      if(myInfo.transparency<0){
        myInfo.transparency = 0;
      }
      std::cout << "Pressed LEFT: Decrease transparency to "<<myInfo.transparency<< std::endl;
    }
    else if (key == GLFW_KEY_RIGHT) {
      myInfo.transparency +=0.05;
      if(myInfo.transparency>1){
        myInfo.transparency = 1.0;
      }
      std::cout << "Pressed RIGHT: Increase transparency to "<<myInfo.transparency<< std::endl;
    }
    else if (key == GLFW_KEY_SPACE) {
      circles.clear();
    }
    else if (key == GLFW_KEY_Z) {
      circles.pop_back();
    }    
    else if (key == GLFW_KEY_E) {
      myInfo.currentColor={0.95f,0.95f,0.95f};
    }
  }


  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    for(CurrentInfo i:circles){
      color(i.currentColor.R,i.currentColor.G,i.currentColor.B,i.transparency);
      circle(i.x,i.y,i.size);
    }

    color(0.1f, 0.1f, 0.1f);
    square(width()/2.0f, 35, width(), 70);

    int cx = 50;
    for(Color myColor: myPallet){
      color(myColor.R,myColor.G,myColor.B);
      circle(cx,40,50);
      cx+=60;
    }

  }
 private:
  Color myColor1{0.97f, 0.93f, 0.88f};
  Color myColor2{0.96f, 0.75f, 0.37f};
  Color myColor3{0.96f, 0.79f, 0.76f};
  Color myColor4{0.52f, 0.65f, 0.62f};
  Color myColor5{0.95f, 0.52f, 0.51f};
  Color myColor6{0.66f, 0.85f, 0.86f};
  Color myPallet[6] = {myColor1,myColor2,myColor3,myColor4,myColor5,myColor6};
  CurrentInfo myInfo{10,1.0,{0.95f, 0.95f, 0.95f},0,0};

  std::vector<CurrentInfo> circles; 
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
