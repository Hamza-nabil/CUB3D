# CUB3D 
### My first RayCaster with miniLibX

cub3D is a remarkable playground to explore the playful practical applications of mathematics without having to understand the specifics .

       * the original game : http://users.atw.hu/wolf3d/
 The program  able to :
    • display an item (sprite) instead of a wall.
    • set the floor and ceilling colors to two different ones.
    •  save the first rendered image in bmp format when its second argument is "––save".
    • If no second argument is supllied, the program displays the image in a window and respects the following rules:
              ◦ The left and right arrow keys of the keyboard allow you to look left and right in the maze.
              ◦ The W, A, S and D keys allow you to move the point of view through the maze.
              ◦ Pressing ESC close the window and quit the program cleanly.
              ◦ Clicking on the red cross on the window’s frame  close the window and quit the program .
    • The program  take as a first argument a scene description file with the .cub extension.
    ◦ The map must be composed of only 4 possible characters: 0 for an empty space, 1 for a wall, 2 for an item and N,S,E or W for the player’s start position and spawning orientation.
              This is a simple valid map:
                              111111
                              100101
                              102001
                              1100N1
                              111111
    ◦ The map must be closed/surrounded by walls, if not the program return an error.
    ◦ Except for the map content which always has to be the last, each type of element can be set in any order in the file.
    ◦ Except for the map, each type of information from an element can be separated by one or more space(s).
    ◦ The map  parsed as it looks like in the file. Spaces are a valid part of the map. .
    ◦ Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as :
                    ∗ Resolution:
                          R 1920 1080
                            · identifier: R
                            · x render size
                            · y render size
                    ∗ North texture:
                          NO ./path_to_the_north_texture
                              · identifier: NO
                              · path to the north texure
                    ∗ South texture:
                           SO ./path_to_the_south_texture
                              · identifier: SO
                              · path to the south texure
                     ∗ West texture:
                           WE ./path_to_the_west_texture
                              · identifier: WE
                              · path to the west texure
                    ∗ East texture:
                          EA ./path_to_the_east_texture
                              · identifier: EA
                              · path to the east texure
                    ∗ Sprite texture:
                          S ./path_to_the_sprite_texture
                              · identifier: S
                              · path to the sprite texure
                    ∗ Floor color:
                        F 220,100,0
                              · identifier: F
                              · R,G,B colors in range [0,255]: 0, 255, 255
                              
                    ∗ Ceilling color:
                        C 225,30,0
                              · identifier: C
                              · R,G,B colors in range [0,255]: 0, 255, 255
      ◦ Example of the mandatory part with a minimalist .cub scene:
      
                          R 1920 1080
                          NO ./path_to_the_north_texture
                          SO ./path_to_the_south_texture
                          WE ./path_to_the_west_texture
                          EA ./path_to_the_east_texture
                          S ./path_to_the_sprite_texture
                          F 220,100,0
                          C 225,30,0
                          1111111111111111111111111
                          1000000000110000000000001
                          1011000001110000002000001
                          1001000000000000000000001
                          111111111011000001110000000000001
                          100000000011000001110111111111111
                          11110111111111011100000010001
                          11110111111111011101010010001
                          11000000110101011100000010001
                          10002000000000001100000010001
                          10000000000000001101010010001
                          11000001110101011111011110N0111
                          11110111 1110101 101111010001
                          11111111 1111111 111111111111
                          
      ◦ If any misconfiguration of any kind is encountered in the file, the program exit  and return "Error\n" followed by an explicit error message .
