#ifndef MATERIALH
#define MATERIALH


//struct hit_record;

#include "ray.h"
#include "hitable.h"

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}
// random number generator
std::default_random_engine randomGeneratorTwo;
std::uniform_real_distribution<float> distributionTwo(0, 1);

bool Refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

//random in unit sphere
vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(distributionTwo(randomGeneratorTwo), distributionTwo(randomGeneratorTwo), distributionTwo(randomGeneratorTwo)) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& record, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
	public:
		vec3 albedo;

		lambertian(const vec3& a) : albedo(a) {}

		virtual bool scatter(const ray& r_in, const hit_record& record, vec3& attenuation, ray& scattered) const
		{
			vec3 target = record.p + record.normal + random_in_unit_sphere();
			scattered = ray(record.p, target - record.p);
			attenuation = albedo;
			return true;
		}
};

class metal : public material
{
	public:
		vec3 albedo;
		float fuzz;

		metal(const vec3& a, float f) : albedo(a) 
		{ 
			if (f < 1)
			{
				fuzz = f;
			}
			else
			{
				fuzz = 1;
			}
		}

		virtual bool scatter(const ray& r_in, const hit_record& record, vec3& attenuation, ray& scattered) const
		{
			vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
			scattered = ray(record.p, reflected + fuzz*random_in_unit_sphere());
			attenuation = albedo;
			return (dot(scattered.direction(), record.normal) > 0);
		}
};

class dielectric : public material
{
	public:
		float ref_idx;

		dielectric(float ri) : ref_idx(ri) {}

		virtual bool scatter(const ray& r_in, const hit_record& record, vec3& attenuation, ray& scattered) const
		{
			vec3 outward_normal;
			vec3 reflected = reflect(r_in.direction(), record.normal);
			float ni_over_nt;
			attenuation = vec3(1.0, 1.0, 1.0);
			vec3 refracted;
			float reflect_prob;
			float cosine;

			if (dot(r_in.direction(), record.normal) > 0)
			{
				outward_normal = -record.normal;
				ni_over_nt = ref_idx;
				cosine = ref_idx * dot(r_in.direction(), record.normal) / r_in.direction().length();
			}
			else
			{
				outward_normal = record.normal;
				ni_over_nt = 1.0 / ref_idx;
				cosine = -dot(r_in.direction(), record.normal) / r_in.direction().length();
			}

			if (Refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
			{
				reflect_prob = schlick(cosine, ref_idx);
			}
			else
			{
				scattered = ray(record.p, reflected);
				reflect_prob = 1.0;
			}

			if (distributionTwo(randomGeneratorTwo) < reflect_prob)
			{
				scattered = ray(record.p, reflected);
			}
			else
			{
				scattered = ray(record.p, refracted);
			}
			return true;
		}
};

#endif