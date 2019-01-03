#pragma once

#include "hitable.h"

class sphere :public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, float r) :center(cen), radius(r) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
	
	vec3 center;
	float radius;
};

inline bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
}

