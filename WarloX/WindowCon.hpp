#include <vector>

using namespace std;

class WindowInit;

class WindowCon
{
private:
	 vector<WindowInit*> Window_context;

public:

	WindowCon();
	~WindowCon();

	WindowInit* getWindowContext(unsigned short key);
	void setWindowContext(WindowInit* window);

};