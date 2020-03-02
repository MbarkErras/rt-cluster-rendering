#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	main()
{
	char *scene = "<scene ambiant=\"0.5\" AA=\"4\" reflection_depth=\"5\" refraction_depth=\"5\" resolution=\"720\" light_samples=\"20\"/>\n<camera position=\"(10, 20, 120)\" lookat=\"(0, 20, 0)\" fov=\"40\"/>\n <light center=\"(0, 200, 20)\" radius=\"3\" intensity=\"0.5\" color=\"#FFFFFF\"/>\n <light center=\"(0, 100, 100)\" radius=\"1\" intensity=\"0.5\" color=\"#FFFFFF\"/>\n <plane center=\"(0, -1, -10)\" U=\"(0, 1, 0)\" V=\"(1, 0, 0)\" color=\"#D3D3D3\" reflection=\"0.8\"/>\n <plane center=\"(0, -1, 0)\" lenght=\"(60, 60)\" U=\"(0, 0, 1)\" V=\"(1, 0, 0)\" color=\"#D3D3D3\" reflection=\"0.8\"/>\n <sphere center=\"(-20, 15, 10)\" translation=\"(3, 0, 0)\" color=\"#FF0000\" radius=\"5\" translation=\"(0, 2, 0)\"/>\n <sphere center=\"(-20, 20, 10)\" translation=\"(3, 0, 0)\" color=\"#FF0000\" radius=\"5\" translation=\"(0, 2, 0)\"/>\n <sphere center=\"(-20, 25, 10)\" translation=\"(3, 0, 0)\" color=\"#FF0000\" radius=\"5\" translation=\"(0, 2, 0)\"/>\n <sphere center=\"(-20, 10, 10)\" translation=\"(3, 0, 0)\" color=\"#FF0000\" radius=\"5\" translation=\"(0, 2, 0)\"/>\n <sphere center=\"(-20, 30, 10)\" translation=\"(3, 0, 0)\" color=\"#FF0000\" radius=\"5\" translation=\"(0, 2, 0)\"/>\n <ellipsoid center=\"(30, 3, -10)\" axis=\"(10,5, 5)\" translation=\"(3, 0, 0)\" color=\"#000000\" radius=\"4\" translation=\"(0, 2, 0)\"/>\n";
	write(1, scene, strlen(scene));
	write(1, "!\n", 2);
	int a = 360;
	write(1, &a, 4);
	a = 720;
	write(1, &a, 4);
}
