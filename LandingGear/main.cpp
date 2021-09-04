#include "LandingGearApplication.h"

int main()
{
	LandingGearApplication* app = LandingGearApplication::GetInstance("LandingGearSystem");
	app->run();
	return 0;
}