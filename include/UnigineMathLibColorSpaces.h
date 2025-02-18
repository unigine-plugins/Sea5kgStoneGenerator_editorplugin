/* Copyright (C) 2005-2025, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/

#pragma once

#include <UnigineVector.h>

namespace Unigine
{
namespace Math
{

/// <summary>Converts Hue color value to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 hueToRgb(float hue)
{
	float r = abs(hue * 6.0f - 3.0f) - 1.0f;
	float g = 2.0f - abs(hue * 6.0f - 2.0f);
	float b = 2.0f - abs(hue * 6.0f - 4.0f);
	return saturate(vec3(r, g, b));
}

/// <summary>Converts RGB (Red, Green, Blue) color values to HCV (Hue, Chroma, Value) color values.</summary>
UNIGINE_INLINE vec3 rgbToHcv(vec3 rgb)
{
	// Based on work by Sam Hocevar and Emil Persson
	vec4 p = (rgb.y < rgb.z) ? vec4(rgb.z, rgb.y, -1.0f, 2.0f / 3.0f) : vec4(rgb.y, rgb.z, 0.0f, -1.0f / 3.0f);
	vec4 q = (rgb.x < p.x) ? vec4(p.x, p.y, p.w, rgb.x) : vec4(rgb.x, p.y, p.z, p.x);
	float c = q.x - min(q.w, q.y);
	float h = abs((q.w - q.y) / (6.0f * c + Consts::EPS) + q.z);

	return vec3(h, c, q.x);
}

/// <summary>Converts RGB (Red, Green, Blue) color values to HSV (Hue, Saturation, Value) color values.</summary>
UNIGINE_INLINE vec3 rgbToHsv(vec3 rgb)
{
	float V = rgb.max();
	rgb /= V + Consts::EPS;

	vec3 hcv = rgbToHcv(rgb);
	float S = hcv.y / (hcv.z + Consts::EPS);
	return vec3(hcv.x, S, V);
}
/// <summary>Converts HSV (Hue, Saturation, Value) color values to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 hsvToRgb(vec3 hsv)
{
	vec3 rgb = hueToRgb(hsv.x);
	return ((rgb - vec3_one) * hsv.y + vec3_one) * hsv.z;
}

/// <summary>Converts RGB (Red, Green, Blue) color values to HCY (Hue, Chroma, Luma) color values.</summary>
UNIGINE_INLINE vec3 rgbToHcy(vec3 rgb)
{
	vec3 HCYwts = vec3(0.299f, 0.587f, 0.114f);

	// Corrected by David Schaeffer
	vec3 hcv = rgbToHcv(rgb);
	float Y = dot(rgb, HCYwts);
	float Z = dot(hueToRgb(hcv.x), HCYwts);
	if (Y < Z)
		hcv.y *= Z / (Consts::EPS + Y);
	else
		hcv.y *= (1 - Z) / (Consts::EPS + 1 - Y);
	return vec3(hcv.x, hcv.y, Y);
}
/// <summary>Converts HCY (Hue, Chroma, Luma) to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 hcyToRgb(vec3 hcy)
{
	vec3 HCYwts = vec3(0.299f, 0.587f, 0.114f);

	vec3 rgb = hueToRgb(hcy.x);
	float z = dot(rgb, HCYwts);
	if (hcy.z < z)
		hcy.y *= hcy.z / z;
	else if (z < 1.0f)
		hcy.y *= (1.0f - hcy.z) / (1.0f - z);
	return (rgb - z) * hcy.y + hcy.z;
}

/// <summary>Converts RGB (Red, Green, Blue) color values to HCL (Hue, Chroma, Luminance) color values.</summary>
UNIGINE_INLINE vec3 rgbToHcl(vec3 rgb)
{
	float HCLgamma = 3;
	float HCLy0 = 100;
	float HCLmaxL = 0.530454533953517f; // == exp(HCLgamma / HCLy0) - 0.5

	vec3 hcl;
	float H = 0;
	float U = min(rgb.x, min(rgb.y, rgb.z));
	float V = max(rgb.x, max(rgb.y, rgb.z));
	float Q = HCLgamma / HCLy0;
	hcl.y = V - U;
	if (hcl.y != 0)
	{
		H = atan2(rgb.y - rgb.z, rgb.x - rgb.y) / Consts::PI;
		Q *= U / V;
	}
	Q = exp(Q);
	hcl.x = frac(H / 2 - min(frac(H), frac(-H)) / 6);
	hcl.y *= Q;
	hcl.z = lerp(-U, V, Q) / (HCLmaxL * 2);
	return hcl;
}
/// <summary>Converts HCL (Hue, Chroma, Luminance) to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 hclToRgb(vec3 hcl)
{
	float HCLgamma = 3;
	float HCLy0 = 100;
	float HCLmaxL = 0.530454533953517f; // == exp(HCLgamma / HCLy0) - 0.5

	vec3 rgb = vec3_zero;
	if (hcl.z != 0)
	{
		float H = hcl.x;
		float C = hcl.y;
		float L = hcl.z * HCLmaxL;
		float Q = exp((1 - C / (2 * L)) * (HCLgamma / HCLy0));
		float U = (2 * L - C) / (2 * Q - 1);
		float V = C / Q;
		float A = (H + min(frac(2 * H) / 4, frac(-2 * H) / 8)) * Consts::PI * 2;
		float T;
		H *= 6;
		if (H <= 0.999)
		{
			T = tan(A);
			rgb.x = 1;
			rgb.y = T / (1 + T);
		} else if (H <= 1.001)
		{
			rgb.x = 1;
			rgb.y = 1;
		} else if (H <= 2)
		{
			T = tan(A);
			rgb.x = (1 + T) / T;
			rgb.y = 1;
		} else if (H <= 3)
		{
			T = tan(A);
			rgb.y = 1;
			rgb.z = 1 + T;
		} else if (H <= 3.999)
		{
			T = tan(A);
			rgb.y = 1 / (1 + T);
			rgb.z = 1;
		} else if (H <= 4.001)
		{
			rgb.y = 0;
			rgb.z = 1;
		} else if (H <= 5)
		{
			T = tan(A);
			rgb.x = -1 / T;
			rgb.z = 1;
		} else
		{
			T = tan(A);
			rgb.x = 1;
			rgb.z = -T;
		}
		rgb = rgb * V + U;
	}
	return rgb;
}

/// <summary>Converts RGB (Red, Green, Blue) color values to HSL (Hue, Saturation, Lightness) color values.</summary>
UNIGINE_INLINE vec3 rgbToHsl(vec3 rgb)
{
	vec3 hcv = rgbToHcv(rgb);
	float l = hcv.z - hcv.y * 0.5f;
	float s = hcv.y / (1.0f + Consts::EPS - abs(l * 2.0f - 1.0f));
	return vec3(hcv.x, s, l);
}
/// <summary>Converts HSL (Hue, Saturation, Lightness) to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 hslToRgb(vec3 hsl)
{
	vec3 color = saturate(vec3(abs(hsl.x * 6.0f - 3.0f) - 1.0f,
						  2.0f - abs(hsl.x * 6.0f - 2.0f),
						  2.0f - abs(hsl.x * 6.0f - 4.0f)));
	float c = (1.0f - abs(2.0f * hsl.z - 1.0f)) * hsl.y;
	return (color - vec3_half) * c + vec3(hsl.z);
}

/// <summary>Converts RGB (Red, Green, Blue) color values to YUV (Luminance, Delta Blue, Delta Red) color values.</summary>
UNIGINE_INLINE vec3 rgbToYuv(vec3 rgb)
{
	float y = 0.299f * rgb.x + 0.587f * rgb.y + 0.114f * rgb.z; // Luma
	float u = -0.147f * rgb.x - 0.289f * rgb.y + 0.436f * rgb.z; // Delta Blue
	float v = 0.615f * rgb.x - 0.515f * rgb.y - 0.100f * rgb.z; // Delta Red
	return vec3(y, u, v);
}
/// <summary>Converts YUV (Luminance, Delta Blue, Delta Red) to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 yuvToRgb(vec3 yuv)
{
	float r = yuv.x + 1.140f * yuv.z;
	float g = yuv.x - 0.395f * yuv.y - 0.581f * yuv.z;
	float b = yuv.x + 2.032f * yuv.y;
	return vec3(r, g, b);
}

/// <summary>Converts RGB (Red, Green, Blue) color values to YCbCr (Luma, Chrominance Blue, Chrominance Red) color values.</summary>
UNIGINE_INLINE vec3 rgbToYcbcr(vec3 rgb)
{
	float Y = 0.299f * rgb.x + 0.587f * rgb.y + 0.114f * rgb.z; // Luminance
	float Cb = -0.169f * rgb.x - 0.331f * rgb.y + 0.500f * rgb.z; // Chrominance Blue
	float Cr = 0.500f * rgb.x - 0.419f * rgb.y - 0.081f * rgb.z; // Chrominance Red
	return vec3(Y, Cb + 128.0f / 255.0f, Cr + 128.0f / 255.0f);
}
/// <summary>Converts YCbCr (Luma, Chrominance Blue, Chrominance Red) to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 ycbcrToRgb(vec3 ycc)
{
	vec3 c = ycc - vec3(0.0f, 128.0f / 255.0f, 128.0f / 255.0f);
	float r = c.x + 1.400f * c.z;
	float g = c.x - 0.343f * c.y - 0.711f * c.z;
	float b = c.x + 1.765f * c.y;
	return vec3(r, g, b);
}

/// <summary>Converts RGB (Red, Green, Blue) color values to YCgCo (Luma, Chrominance Green, Chrominance Orange) color values.</summary>
UNIGINE_INLINE vec3 rgbToYcgco(vec3 rgb)
{
	float Y = 0.25f * rgb.x + 0.5f * rgb.y + 0.25f * rgb.z;	// Luminance
	float Cg = -0.25f * rgb.x + 0.5f * rgb.y - 0.25f * rgb.z; // Chrominance Green
	float Co = 0.50f * rgb.x - 0.5f * rgb.z; // Chrominance Orange
	return vec3(Y, Cg, Co);
}
/// <summary>Converts YCgCo (Luma, Chrominance Green, Chrominance Orange) color values to RGB (Red, Green, Blue) color values.</summary>
UNIGINE_INLINE vec3 ycgcoToRgb(vec3 ycc)
{
	float r = ycc.x - ycc.y + ycc.z;
	float g = ycc.x + ycc.y;
	float b = ycc.x - ycc.y - ycc.z;
	return vec3(r, g, b);
}

}
}
