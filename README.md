<p align="center">
	<img src="Exstar.png" alt="Geno" width="80" height="80" style="border-radius: 15px"><h1 align="center">Exstar alpha 2.0</h1><p align="center"><a href="https://discord.gg/WacprUHpUF" style="text-decoration: none;color: rgb(150,150,255);">Discord</a></p>
</p>

<h3 align="center">Building</h3>
<h4 align="center" style="font-weight: 400;">
	When building on linux run "sh INSTALL.sh"<br><br>
	When on another OS use cmake to compile
	<br>
	<br>
</h4>

<h3 align="center">Compiling</h3>
<p align="center">
	<span style="font-weight: bold;">G++: </span> Use -lExstar when compiling<br><br>
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
	void render(exstar::Graphics g){
		//Set the Fill Color
		g.setColor(exstar::Color::Blue);
		//Render Rectangle at 0,0 with a width of 50 and height of 100
		g.drawRect(0,0,50,100);
	}

};
</code>
</pre>
<p>Compiling with G++</p>
<pre><code>
g++ main.cpp -o app -lExstar -Iinclude/
</code>
</pre>

