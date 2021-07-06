#include "v4f.h"

using namespace std;


int main()
{
	v4f v(13, 1.0f);
	
	cout << "pollo" << endl;
	v[1] = 3;
	v[9] = 3.14159265;
	for(int i=0;i<v.size();i++) cout << v[i] << " "; cout << endl;
	
	return 0;
}
