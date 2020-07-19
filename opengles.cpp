#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#define ES_WINDOW_RGB 			0
#define ES_WINDOW_ALPHA 		1
#define ES_WINDOW_DEPTH 		2
#define ES_WINDOW_STENCIL 		4
#define ES_WINDOW_MULTISAMPLE 	8

Display *x_display;
Atom s_wmDeleteMessage;

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);

	const char *src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// To do error handling

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!";
		std::cout << std::endl;

		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Draw()
{
	glViewport(0, 0, 800, 400);
	
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLboolean UserInterrupt()
{
	XEvent xev;
	KeySym key;
	GLboolean userInterrupt = GL_FALSE;
	char text;

	while(XPending(x_display))
	{
		XNextEvent(x_display, &xev);
		if(xev.type == ClientMessage)
		{
			if(xev.xclient.data.l[0] == s_wmDeleteMessage)
				userInterrupt = GL_TRUE;
		}

		if(xev.type == DestroyNotify)
			userInterrupt = GL_TRUE;
	}	
	return userInterrupt;
}
int main()
{
	//Display *x_display;
	//Atom s_wmDeleteMessage;
	Window root;
	XSetWindowAttributes swa;
	XSetWindowAttributes xattr;
	Atom wm_state;
	XWMHints hints;
	XEvent xev;
	Window win;

	// open a connection to the X11 window manager
	x_display = XOpenDisplay(NULL); // opens the standard display (the primary screen)

	if(x_display == NULL)
	{
		std::cout << "Cannot connect to X server" << std::endl;
		return 1;
	}

	root = DefaultRootWindow(x_display); // get the root window (usually the whole screen)

	swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

	win = XCreateWindow( // create a window with the provided parameters
			x_display, root,
			0, 0, 800, 400, 0,
			CopyFromParent, InputOutput,
			CopyFromParent, CWEventMask,
			&swa);

	s_wmDeleteMessage = XInternAtom(x_display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(x_display, win, &s_wmDeleteMessage, 1);

	xattr.override_redirect = False;
	XChangeWindowAttributes(x_display, win, CWOverrideRedirect, &xattr);

	hints.input = True;
	hints.flags = InputHint;
	XSetWMHints(x_display, win, &hints);

	XMapWindow(x_display, win);
	XStoreName(x_display, win, "HELLO TRIANGLE");

	wm_state = XInternAtom(x_display, "_NET_WM_STATE", False);

	memset(&xev, 0, sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = False;

	XSendEvent( 	// send an event mask to the X-server
		x_display, DefaultRootWindow(x_display), False,
		SubstructureNotifyMask, &xev);

	// egl part - egl provides an interface to connect the graphics related
	// functionality of OpenGL ES with the windowing interface and functionality
	// of the native operation system (X11 in our case)

	EGLNativeWindowType eglNativeWindow;
	EGLNativeDisplayType eglNativeDisplay;

	EGLConfig config;
	EGLint majorVersion;
	EGLint minorVersion;

	EGLDisplay eglDisplay;
	EGLContext eglContext;
	EGLSurface eglSurface;

	eglNativeWindow = (EGLNativeWindowType) win;
	eglNativeDisplay = (EGLNativeDisplayType) x_display;

	const EGLint contextAttribs[] =
	{
 		EGL_CONTEXT_CLIENT_VERSION, 3,
		EGL_NONE
	};


	EGLint attribList[] = 
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, (ES_WINDOW_RGB & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (ES_WINDOW_RGB & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (ES_WINDOW_RGB & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (ES_WINDOW_RGB & ES_WINDOW_MULTISAMPLE) ? 1 : 0,

		EGL_NONE
	};


	eglDisplay = eglGetDisplay(eglNativeDisplay);

	if(eglDisplay == EGL_NO_DISPLAY)
	{
		// unable to open connection to local windowing system
		std::cout << "Got No EGL Display!" << std::endl;
		return 1;
	}

	if(!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		// unable to initialize EGL; handle and recover
		std::cout << "Unable to initialize EGL" << std::endl;
		return 1;
	}
 
	EGLint numConfigs = 0;

	if(!eglChooseConfig(eglDisplay, attribList, &config, 1, &numConfigs))
	{
		// something did not work... handle error situation
		std::cout << "Failed to choose config (eglerror: " << eglGetError() << ")" << std::endl;
		return 1;
	}

	if( numConfigs < 1)
	{
		std::cout << "numConfigs is less than 1\n";
		return 1;
	}

	eglSurface = eglCreateWindowSurface( eglDisplay, config, eglNativeWindow, NULL);

	if(eglSurface == EGL_NO_SURFACE)
	{
		std::cout << "Unable to create EGL Surface (eglerror: " << eglGetError() << ")" << std::endl;
		return 1;
	}

	eglContext = eglCreateContext( eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);

	if (eglContext == EGL_NO_CONTEXT)
	{
		std::cout << "Unable to create EGL Context (eglerror : " << eglGetError() << ")" << std::endl;
		return 1;
	}

	if ( !eglMakeCurrent ( eglDisplay, eglSurface, eglSurface, eglContext ) )
	{
		return 1;
	}

	float vertexArray[] = {
		 0.0f,  0.5f, 0.0f,		
		-0.5f, -0.5f, 0.0f,		
	 	0.5f, -0.5f, 0.0f,
	};

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertexArray);
	
	std::string vertexShader =
	"#version 300 es\n"
	"\n"
	"layout(location = 0) in vec4 vPosition;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vPosition;\n"
	"}\n";

	std::string fragmentShader =
	"#version 300 es\n"
	"\n"
	"precision mediump float;\n"
	"\n"
	"layout(location = 0) out vec4 color;\n"
	"\n"
	"void main()\n"
	"{\n"
	"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);

	glUseProgram(shader);

	while(UserInterrupt() == GL_FALSE)
	{
		Draw(); 
	
		eglSwapBuffers(eglDisplay, eglSurface);
	}

	glDeleteProgram(shader);
	return 0;	
}
