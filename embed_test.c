#include "generated_res.h"
#include <raylib.h>
#include <stdio.h>

void print_embedded(const unsigned char s[], const size_t size)
{
	printf("magic bytes: %.3s, size (bytes): %lu\n", s + 1, size);
}

int main()
{
	print_embedded(resources_something_png, resources_something_png_size);
	print_embedded(resources_sheya_sb_png, resources_sheya_sb_png_size);
	print_embedded(resources_sheya_fu_xuan_png, resources_sheya_fu_xuan_png_size);

	InitWindow(1600, 900, "embedding test");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	Image img_a = LoadImageFromMemory(".png", resources_something_png, resources_something_png_size),
	      img_b = LoadImageFromMemory(".png", resources_sheya_sb_png, resources_sheya_sb_png_size),
	      img_c = LoadImageFromMemory(".png", resources_sheya_fu_xuan_png, resources_sheya_fu_xuan_png_size);
	Texture2D a = LoadTextureFromImage(img_a), b = LoadTextureFromImage(img_b), c = LoadTextureFromImage(img_c);
	UnloadImage(img_a);
	UnloadImage(img_b);
	UnloadImage(img_c);
	const Texture2D *images[] = {&a, &b, &c};
	const char	*help	  = "Press the arrow keys to switch between images";
	for (int index = 0; !WindowShouldClose();) {
		bool go_right = IsKeyPressed(KEY_RIGHT);
		bool go_left  = IsKeyPressed(KEY_LEFT);
		if (go_right || go_left) {
			if (go_left) {
				index = (index + 2) % 3;
			} else {
				index = (index + 1) % 3;
			}
			printf("index changed: %i\n", index);
			float normalizing_value = GetScreenHeight();
			SetWindowSize(images[index]->width * (normalizing_value / images[index]->height),
				      normalizing_value);
		}

		BeginDrawing();
		if (IsTextureReady(*images[index])) {
			DrawTexturePro(*images[index],
				       (Rectangle){0, 0, images[index]->width, images[index]->height},
				       (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
				       (Vector2){0, 0},
				       0.0f,
				       WHITE);
		}
		DrawRectangle(10 - 5, 10 - 5, MeasureText(help, 20) + 10, 20 + 10, BLACK);
		DrawText(help, 10, 10, 20, GREEN);
		EndDrawing();
	}
	UnloadTexture(a);
	UnloadTexture(b);
	UnloadTexture(c);
	CloseWindow();
	return 0;
}
