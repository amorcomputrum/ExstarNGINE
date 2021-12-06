#define GLFW_INCLUDE_NONE
//#define STB_IMAGE_IMPLEMENTATION
//include Libraries
#include "exstarGLFW/glfw3.h"
#include "exstarglad/gl.h"
#include "stb_image.h"

//include C++ libraries
#include "iostream"
#include "ostream"
#include "thread"
#include "chrono"
#if __WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

//include Exstar Files
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Utils/Math.h"
#include "Exstar/Utils/Key.h"
#include "Exstar/Utils/Exceptions.h"
#include "Exstar/Clock.h"
#include "Exstar/Utils/Dimension.h"
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Point.h"
#include "Exstar/Sprite/Image_Handler.h"
#include "Sprite/Sprite.h"
#include "Exstar/Camera.h"
#include "Exstar/Utils/MouseEvent.h"


namespace exstar{
	class Window {
	public:
		Window(int width,int height,const char* title);
		//-------------Virtual Functions-------------
		virtual void render(Camera camera);
		virtual void Update(double deltaTime);
		virtual void onResize(int w,int h);
		virtual void keyPressed(int key);
		virtual void keyReleased(int key);
		virtual void mousePressed(MouseEvent* event);
		virtual void mouseReleased(MouseEvent* event);
		//-------------Public Functions-------------
		void run();
		void close();
		void setFramerate(int frameRate);
		void setIcon(const char* path);
		void setTitle(const char* title);
		void setSizeLimits(int minW,int minH,int maxW,int maxH);
		void setSize(int width, int height);
		void setAdjustCameraOnResize(bool state);
		void setBackgroundColor(double r,double g,double b);
		const char* getTitle();
		bool isKeyPressed(int key);
		exstar::Dimension getSize();
		exstar::Point getMousePos();
		double DeltaTime();
		int getMouseX();
		int getMouseY();
		int getWidth();
		int getHeight();
		bool getAdjustCameraOnResize();

	private:
		static exstar::ArrayList<int>* keysPressed;
		static exstar::ArrayList<exstar::MouseEvent*>* mouseEvents;
		exstar::ArrayList<int>* keysPressedCopy = new exstar::ArrayList<int>();
		exstar::ArrayList<exstar::MouseEvent*>* mouseEventsCopy = new exstar::ArrayList<exstar::MouseEvent*>();
		double deltaTime = 0.0;
		int frameRate = 16;
		bool adjustCameraOnResize = true;
		exstar::Dimension size;
		const char* title;
		GLFWwindow* window;
		exstar::Camera* camera;
		exstar::Clock* clock;
		double backgroundColor[4];

		//-------------Private Functions-------------
		void initGL();
		void update();
		void resizeEvent(int width, int height);

		//-------------Static Functions-------------
		static void error_callback(int error, const char* description);
		static void mouse_callback(GLFWwindow* window,int button,int action,int mods);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

}