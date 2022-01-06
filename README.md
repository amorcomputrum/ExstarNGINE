<p align="center">
	<img src="Exstar.png" alt="Geno" width="80" height="80" style="border-radius: 15px"><h1 align="center">Exstar</h1><p align="center"><a href="https://discord.gg/WacprUHpUF" style="text-decoration: none;color: rgb(150,150,255);">Discord</a></p>
</p>
<h2 align="center">Proper OpenGL with GLSL Implementation is being redone, Commits to main branch are on hold until alpha release 1.0</h2>

<h3 align="center">Building</h3>
<h4 align="center" style="font-weight: 400;">
	When building on linux run "sh INSTALL.sh"<br><br>
	When on another OS use cmake to compile
	<br>
	<br>
</h4>

<h3 align="center">Compiling</h3>
<p align="center">
	<span style="font-weight: bold;">G++: </span> Use -lExstar -lglfw when compiling<br><br>
	<a href="https://github.com/benajah/GEASY/releases/tag/Release" style="text-decoration: none; color: black;"><span style="font-weight: bold;">Geasy:</a> </span> Set in configuration file  "libPrefixes":["-lExstar","-lglfw"]<br><br>
</p>
<hr noshade>
<h3 align="center">Coming Soon</h3>
<p align="center">
	Exstar will contain 2 physics engines<br>
	One of them will be made by Exstar, this will be a simple general use engine<br>
	The other will be an implementation of Box2D, this will be an advanced engine
</p>
<hr noshade>
<h3 align="center">
	Example
</h3>
<p>main.cpp</p>
<pre>
<code>
#include "Window.hpp"
int main()
{
	Window* window = new Window(800,200,"Test Window");
	window->setBackgroundColor(exstar::Color::Black);
	window->run();
	return 0;
}
</code>
</pre><br>
<p>include/Window.hpp</p>
<pre>
<code>
#include "Exstar/Window.h"
class Window : public exstar::Window
{
public:
	Window(int width,int height,const char* title) : exstar::Window(width,height,title) {
		//Set framerate to 60
		setFramerate(60);
	}
	void render(exstar::Camera camera){
		//Set the Fill Color
		camera.setColor(exstar::Color::Blue);
		//Render Rectangle at 0,0 with a width of 50 and height of 100
		camera.drawRect(0,0,50,100);
	}

};
</code>
</pre>
<p>Compiling with G++</p>
<pre><code>
g++ main.cpp -o app -lExstar -lglfw -Iinclude/
</code>
</pre>
<p>Or setup GEASY config</p>
<p>conf.json</p>
<pre>
<code>
{
        "libPrefixes":["-lExstar","-lglfw"],
        "libs":[],
        "Include":[
                "include/"
        ],
        "file":"main.cpp "
}
</code>
</pre>
<p>Compiling with GEASY</p>
<pre>
<code>
Geasy
</code>
</pre>
