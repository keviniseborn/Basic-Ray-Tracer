#ifndef CAMERAH
#define CAMERAH
#define _USE_MATH_DEFINES

#include "Ray.h"
#include <math.h>

// random number generator
std::default_random_engine randomGeneratorThree;
std::uniform_real_distribution<float> distributionThree(0, 1);

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(distributionThree(randomGeneratorThree), distributionThree(randomGeneratorThree), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
	public:
		
		vec3 origin;
		vec3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		float lens_radius;

		camera(vec3 lookFrom, vec3 lookAt, vec3 upVector, float vertFoV, float aspect, float aperature, float focus_dist)
		{
			lens_radius = aperature / 2;
			float theta = vertFoV * M_PI / 180;
			float halfHeight = tan(theta / 2);
			float halfWidth = aspect * halfHeight;

			origin = lookFrom;
			w = unit_vector(lookFrom - lookAt);
			u = unit_vector(cross(upVector, w));
			v = cross(w, u);

			// "background" dimensions
			lower_left_corner = origin - halfWidth * focus_dist*u - halfHeight * focus_dist*v - focus_dist * w;
			horizontal = 2 * halfWidth*focus_dist*u;
			vertical = 2 * halfHeight*focus_dist*v;
		}

		ray get_ray(float s, float t)
		{
			vec3 rd = lens_radius * random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();
			return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
		}
};

#endif