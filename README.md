## MINIRT

A basic multithreaded raytracer for 42 school project miniRT


### FEATURES

- Colored diffuse, ambiant and specular lighting from multiple light sources
- Several primitive shapes, from the outside as well as inside : plane, sphere, cylinder, cone
- Mesh loading from .obj file and rendering
- Mesh are rendered with a Bounding Volume Hierarchy (BVH) to boost performance
- Basic shading : hard shadows, incidence and distance attenuation
- Texturing and normal mapping available for all shapes and meshes
- A background sky with a gradient of two colors
- The user can move and rotate the camera around in real time to get different views of the scene
- Modifiable camera parameters (field of view, movement and rotation speed)
- Scenes configured in the dedicated .rt file format (see documentation.rt for more details)
- Materials in .mrt files, able to load textures and normal maps from .xpm image files (see documentation.mrt for more details)
- Comes with a few pre-made scenes, meshes, textures and materials to select from

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

#### BUGS
- Cone cap disappears when in front


### TODO BONUS

#### MISC
- check angle of cone in parsing


### TODO ULTIMATE

#### SCENES
- Add scenes to show off all the features

#### PARSING
- Set the texture scaling in the .mrt file
- Set the texture repetition in the .mrt file

#### GRAPHICS
- Anti aliasing
- Depth of field

#### Optimisation
- Others

#### LIGHT
- Add a light structure (similar to objects) and a list of lights to the scene
- Global illumination
- Soft shadows
- Directional light
- Refraction
- Wave lenght refraction (prisms)
- Bloom

#### MATERIALS
- Transparent textures
- Non-repetitive textures
- Transparent materials
- Emissive materials

#### BUGS
- uv mapping inside a sphere is upside down
- cylinder base disapears when in axis
- abnormal deformation up and down the screen (fisheye)
- Crash when texture or normal map missing in material
- Crash when obj contains non-triangular faces
- Change content of help
