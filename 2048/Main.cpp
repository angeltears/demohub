#include"2048.h"
#include <conio.h> 
int main()
{
	printf("\n\n\n\n\n\n");
	cout << "                  --------------------------------------------------" << endl;
	cout << "                  |                      2048                      |" << endl;
	cout << "                  |                   Control by:                  |" << endl;
	cout << "                  |               w/s/a/d or W/S/A/D               |" << endl;
	cout << "                  |            press q or Q quit game!             |" << endl;
	cout << "                  --------------------------------------------------" << endl;
	cout << "                           Press any key to continue...			 " <<  endl;
	char r = _getch();
	system("cls");
	Game T;
	T.draw();
	while (1)
	{
		T.play();
	}
	return 0;
}