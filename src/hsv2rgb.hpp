/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * HSV-to-RGB conversion
 */

#ifndef _hsv2rgb_hpp_
#define _hsv2rgb_hpp_

#include "pixel.hpp"

/// Convert HSV color to RGB color
/// \param h Hue (0..359)
/// \param s Saturation (0..255)
/// \param v Value (0..255)
/// \return RGB pixel
pixel hsv2rgb(int h, uint8_t s, uint8_t v);

#endif // _hsv2rgb_hpp_
