#pragma once

#include "ray.h"

struct hit_record
{
	float t;
	vec3 p;//ÊÀ½ç×ø±ê
	vec3 normal;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const = 0;
};