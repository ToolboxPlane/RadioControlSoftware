uint16_t r8g8b8Tor5g6b5(uint32_t original){
  uint32_t r = (uint32_t)(original & (0x00FF0000));
  uint32_t g = (uint32_t)(original & (0x0000FF00));
  uint32_t b = (uint32_t)(original & (0x000000FF));

  r >>= 16;
  g >>= 8;

  r /= 8;
  g /= 4;
  b /= 8;

  return (r<<11 | g<<5 | b);
}

uint16_t r8g8b8Tor5g6b5(uint32_t original, uint8_t brightness){
  uint32_t r = (uint32_t)(original & (0x00FF0000));
  uint32_t g = (uint32_t)(original & (0x0000FF00));
  uint32_t b = (uint32_t)(original & (0x000000FF));

  r >>= 16;
  g >>= 8;

  r = (uint8_t)(r * (brightness/255.0f));
  g = (uint8_t)(g * (brightness/255.0f));
  b = (uint8_t)(b * (brightness/255.0f));
  
  r /= 8;
  g /= 4;
  b /= 8;

  return (r<<11 | g<<5 | b);
}

