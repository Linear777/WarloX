#include "Dependencies\glfw\glfw3.h"

class GameWork;

namespace WindowSpace
{
	struct WinParams
	{
		char * TITLE;
		unsigned __int16 WIDTH;
		unsigned __int16 HEIGHT;
		bool fullscreen;
	};

	class WindowInit
	{
		private:
			GameWork* Game_ptr;
			WinParams params;
			GLFWwindow* window_context;

		public:
			WindowInit();
			WindowInit(const int width,const int height,char * title);
			~WindowInit();

			void changeSize(const int width,const int height,bool fullscreen);
			void InitWindow(bool fullscreen);
			void UpdateSettings();
			void DestroyWindow();

			WinParams& getParams();
			GLFWwindow* getWindowContext();

			//Render Content
			void static Render(void);
	};

}