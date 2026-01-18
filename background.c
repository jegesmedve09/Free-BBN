#include <tamtypes.h>
#include <kernel.h>
#include <math.h>
#include "gfx.h"
#include "utils.h"
#include "background.h"


#define LAVA_WIDTH 65
#define LAVA_HEIGHT 53
#define VISIBLE_WIDTH 64
#define VISIBLE_HEIGHT 52
#define BLOCK_SIZE 10
#define OFFSET_START 0

// Buffers + pointers
static float U_buf1[LAVA_HEIGHT][LAVA_WIDTH];
static float V_buf1[LAVA_HEIGHT][LAVA_WIDTH];
static float U_buf2[LAVA_HEIGHT][LAVA_WIDTH];
static float V_buf2[LAVA_HEIGHT][LAVA_WIDTH];

static float (*U_current)[LAVA_WIDTH] = U_buf1;
static float (*V_current)[LAVA_WIDTH] = V_buf1;
static float (*U_next)[LAVA_WIDTH]    = U_buf2;
static float (*V_next)[LAVA_WIDTH]    = V_buf2;

// Smooth velocity (no acceleration buildup!)
static float current_vel_x = 0.0f;
static float current_vel_y = 0.0f;
static float target_vel_x  = 0.0f;
static float target_vel_y  = 0.0f;
static int direction_change_timer = 0;

static int offset_x = 0, offset_y = 0;
static int frame_counter = 0;

// Params
#define DU 0.16f
#define DV 0.08f
#define F  0.035f
#define K  0.062f
#define DT 1.0f

// Toroidal Laplacian
static float laplacian(float grid[LAVA_HEIGHT][LAVA_WIDTH], int x, int y)
{
    float sum = -grid[y][x];
    int left  = (x - 1 + LAVA_WIDTH) % LAVA_WIDTH;
    int right = (x + 1) % LAVA_WIDTH;
    int up    = (y - 1 + LAVA_HEIGHT) % LAVA_HEIGHT;
    int down  = (y + 1) % LAVA_HEIGHT;
    sum += grid[y][left]  * 0.2f;
    sum += grid[y][right] * 0.2f;
    sum += grid[up][x]    * 0.2f;
    sum += grid[down][x]  * 0.2f;
    sum += grid[up][left]   * 0.05f;
    sum += grid[up][right]  * 0.05f;
    sum += grid[down][left] * 0.05f;
    sum += grid[down][right]* 0.05f;
    return sum;
}

void init_lava_background(void)
{
    for (int y = 0; y < LAVA_HEIGHT; y++) {
        for (int x = 0; x < LAVA_WIDTH; x++) {
            U_buf1[y][x] = 1.0f;
            V_buf1[y][x] = 0.0f;
        }
    }
    for (int i = 0; i < 12; i++) {
        int cx = get_random_in_range(0, LAVA_WIDTH-1);
        int cy = get_random_in_range(0, LAVA_HEIGHT-1);
        int r = get_random_in_range(4, 10);
        for (int dy = -r; dy <= r; dy++) {
            for (int dx = -r; dx <= r; dx++) {
                if (dx*dx + dy*dy <= r*r) {
                    int nx = (cx + dx + LAVA_WIDTH) % LAVA_WIDTH;
                    int ny = (cy + dy + LAVA_HEIGHT) % LAVA_HEIGHT;
                    V_buf1[ny][nx] = 0.6f + (float)get_random_in_range(0, 40)/100.0f;
                    U_buf1[ny][nx] *= 0.4f;
                }
            }
        }
    }
}

void update_lava_background(void)
{
    frame_counter++;

    // Update simulation
    for (int y = 0; y < LAVA_HEIGHT; y++) {
        for (int x = 0; x < LAVA_WIDTH; x++) {
            float u = U_current[y][x];
            float v = V_current[y][x];
            float lap_u = laplacian(U_current, x, y);
            float lap_v = laplacian(V_current, x, y);
            U_next[y][x] = u + DT * (DU * lap_u - u*v*v + F * (1.0f - u));
            V_next[y][x] = v + DT * (DV * lap_v + u*v*v - (F + K) * v);
            if (U_next[y][x] < 0.0f) U_next[y][x] = 0.0f;
            if (U_next[y][x] > 1.0f) U_next[y][x] = 1.0f;
            if (V_next[y][x] < 0.0f) V_next[y][x] = 0.0f;
            if (V_next[y][x] > 1.0f) V_next[y][x] = 1.0f;
        }
    }

    if (frame_counter % 30 == 0) {
        int px = get_random_in_range(0, LAVA_WIDTH-1);
        int py = get_random_in_range(0, LAVA_HEIGHT-1);
        V_next[py][px] += 0.05f * (float)(get_random_in_range(0, 100)-50)/50.0f;
        U_next[py][px] -= 0.03f;
    }

    // Swap pointers
    {
        float (*temp_u)[LAVA_WIDTH] = U_current;
        float (*temp_v)[LAVA_WIDTH] = V_current;
        U_current = U_next;
        V_current = V_next;
        U_next = temp_u;
        V_next = temp_v;
    }

    // Ultra-smooth drift: very slow, no acceleration buildup
    direction_change_timer++;
    if (direction_change_timer >= get_random_in_range(100, 200)) {  // 1–2 minutes
        // New target: very gentle, strong upward bias
        target_vel_x = get_random_in_range(-5, 5) * 0.04f;   // -0.2 to +0.2 max
        target_vel_y = get_random_in_range(-12, 3) * 0.03f;  // mostly upward (negative)
        direction_change_timer = 0;
    }

    // Extremely slow lerp + damping (prevents speeding up)
    current_vel_x += (target_vel_x - current_vel_x) * 0.0008f;
    current_vel_y += (target_vel_y - current_vel_y) * 0.0008f;
    current_vel_x *= 0.998f;  // tiny damping
    current_vel_y *= 0.998f;

    // Apply directly (no accumulation that builds up)
    offset_x = (offset_x + (int)current_vel_x + LAVA_WIDTH) % LAVA_WIDTH;
    offset_y = (offset_y + (int)current_vel_y + LAVA_HEIGHT) % LAVA_HEIGHT;

    // Clear + draw
    gfx_clear(GS_SETREG_RGBAQ(0x00, 0x00, 0x08, 0x80, 0));

    for (int y = 0; y < VISIBLE_HEIGHT; y++) {
        for (int x = 0; x < VISIBLE_WIDTH; x++) {
            int sample_y = (y + offset_y) % LAVA_HEIGHT;
            int sample_x = (x + offset_x) % LAVA_WIDTH;
            int px = x * BLOCK_SIZE + OFFSET_START;
            int py = y * BLOCK_SIZE + OFFSET_START;

            if (px < 0) px = 0;
            if (py < 0) py = 0;
            if (px + BLOCK_SIZE > 640) px = 640 - BLOCK_SIZE;
            if (py + BLOCK_SIZE > 512) py = 512 - BLOCK_SIZE;

            float v = V_current[sample_y][sample_x];
            float wave_amp = v * 6.0f;
            float wave = sinf((float)frame_counter * 0.015f + (float)sample_x * 0.12f + (float)sample_y * 0.18f) * wave_amp;
            px += (int)(wave + 0.5f);
			py += (int)(wave * 0.7f + 0.5f);

			//if (px < 0 || py < 0 ||
			//	px + BLOCK_SIZE > 640 ||
			//	py + BLOCK_SIZE > 512)
			//{
			//	continue;
			//}


			//if (px < 0 || py < 0 || px + BLOCK_SIZE > 640 || py + BLOCK_SIZE > 512) continue;

            u8 intensity = (u8)(v * 0xB0 + 0x20);
            u64 color = GS_SETREG_RGBAQ(
                intensity / 5,
                intensity / 3,
                intensity,
                0x80,
                0
            );
            gfx_draw_square(px, py, BLOCK_SIZE, BLOCK_SIZE, color);
        }
    }

    // Partial last row
    for (int x = 0; x < VISIBLE_WIDTH; x++) {
        int sample_y = (VISIBLE_HEIGHT + offset_y) % LAVA_HEIGHT;
        int sample_x = (x + offset_x) % LAVA_WIDTH;
        int px = x * BLOCK_SIZE + OFFSET_START;
        int py = VISIBLE_HEIGHT * BLOCK_SIZE + OFFSET_START;

        float v = V_current[sample_y][sample_x];
        float wave_amp = v * 6.0f;
        float wave = sinf((float)frame_counter * 0.015f + (float)sample_x * 0.12f + (float)sample_y * 0.18f) * wave_amp;
        px += (int)wave;
        py += (int)(wave * 0.7f);

        //if (px < 0 || py < 0 ||
		//	px + BLOCK_SIZE > 640 ||
		//	py + 2 > 512)
		//{
		//	continue;
		//}


        u8 intensity = (u8)(v * 0xB0 + 0x20);
        u64 color = GS_SETREG_RGBAQ(
            intensity / 5,
            intensity / 3,
            intensity,
            0x80,
            0
        );
        gfx_draw_square(px, py, BLOCK_SIZE, 2, color);
    }
}
