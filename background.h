#ifndef BACKGROUND_H
#define BACKGROUND_H

void background_init(u8 R, u8 G, u8 B, float bright_min, float bright_mul);

void background_update(void);

extern u8 background_target_r;
extern u8 background_target_g;
extern u8 background_target_b;

extern float background_min_brightness;   // 0.0 = true black, 0.08–0.15 = gentle glow floor
extern float background_brightness_multiplier;


#endif
