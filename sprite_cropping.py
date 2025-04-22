## Sprite Cropping

from PIL import Image
import os
import shutil

sprite_sheet = Image.open("sprite.png")
# Picture has dimensions 64 x 72 (width x height)
# Each sprite width = 16 (OK)
# Each sprite height: 72 / 3 = 24 (additional 8 pixels, 4 at top and bottom)

# Dimensions
tile_width = 16
actual_tile_height = 16
tile_height_with_padding = 24
padding_top = 4

# Output folder
output_folder = "cropped_sprites"
if os.path.exists(output_folder):
    shutil.rmtree(output_folder)
os.makedirs(output_folder)

# Get sheet size 
sheet_width, sheet_height = sprite_sheet.size
print(sheet_width, sheet_height)

# Count how many tiles horizontally and vertically
tiles_x = sheet_width // tile_width
tiles_y = sheet_height // tile_height_with_padding

print(tiles_x, tiles_y)

# Crop each tile
count = 0
for y in range(tiles_y):
    for x in range(tiles_x):
        left = x * tile_width
        upper = y * tile_height_with_padding + padding_top
        right = left + tile_width
        lower = upper + actual_tile_height + padding_top

        cropped = sprite_sheet.crop((left, upper, right, lower))
        cropped.save(os.path.join(output_folder, f"sprite_{count}.png"))
        count += 1

print(f"Cropped {count} sprites to folder '{output_folder}'")