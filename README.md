## MINIRT

A basic multithreaded raytracer for 42 school project miniRT


### FEATURES

- Colored diffuse, ambiant and specular lighting from multiple light sources
- Basic shapes, from the outside as well as inside : plane, sphere, cylinder, cone
- Basic shading : hard shadows, incidence and distance attenuation
- Texturing and normal mapping available for all shapes
- A background sky with a gradient of two colors
- Camera with modifiable parameters (position, orientation, field of view)
- The user can move and rotate the camera around in real time to get different views of the scene without changing the camera configuration in the scene file
- Scenes written in the dedicated .rt file format (see documentation.rt for more details)
- Materials in .mrt files, able to load textures and normal maps from .xpm image files (see documentation.mrt for more details)
- Comes with a few pre-made scenes, textures and materials to select from

### INSTALLATION

### KEYBINDINGS

The following keybindings allow the user to interact with miniRT:

- Help : H
- Exit program : Escape
- Move horizontally : WASD
- Rotate horizontally : JL
- Move up/down : QE
- Rotate up/down : IK
- Change movement speed : Up/Down arrows
- Change rotation speed : Left/Right arrows


### TODO MANDATORY

#### PARSING
- Change warnings to errors in the end


### TODO BONUS

#### SCENES
- Add scenes to show off all the features

#### MISC
- check angle of cone in parsing


### TODO ULTIMATE

#### SHAPES
- Triangle intersection
- Box intersection

#### CAMERA MOVEMENT
- Up/down movement
- Up/down rotation

#### PARSING
- Add a sky object with two colors to change the sky color
- Set the texture scaling in the .mrt file

#### GRAPHICS
- Anti aliasing
- Depth of field

#### Optimisation
- BVH

#### LIGHT
- Add a light structure (similar to objects) and a list of lights to the scene
- Global illumination
- Soft shadows
- Directional light
- Refraction
- Wave lenght refraction (prisms)

#### MATERIALS
- Transparent textures
- Transparent materials
- Emissive materials

#### BUGS
- uv mapping inside a sphere is upside down
- cylinder base disapears when in axis
