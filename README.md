# miniRT

A basic multithreaded raytracer for 42 school project miniRT.

![Minirt title picture](./preview/minirt.png "Title")

### *️⃣ Features

Create scenes containing varied shapes, meshes and lights, and render them through the technique of ray-tracing

Basic shading : hard shadows, incidence and distance attenuation

Several primitive shapes, from the outside as well as inside : plane, sphere, cylinder, cone

##### Colors and texturing
Colored diffuse, ambiant and specular lighting from multiple light sources

Texturing and normal mapping available for all objects.
![Different textures with normal maps](./preview/text1.png "Textures")

##### OBJ rendering
Mesh loading from .obj file and rendering.
Meshes are rendered with a Bounding Volume Hierarchy (BVH) to boost performance.
![A statue mesh loaded from a .obj file](./preview/bust.png "Reflections")

##### Reflection
![Infinite reflections between two spheres](./preview/refl2.png "Reflections")
![A metallic statue of a bull](./preview/bull.png "Metal")

- Refraction
![Image of a statue refracted through a glass ball](./preview/refr2.png "Refraction")
![A glass skull](./preview/refr1.png "Refraction")
- A background sky with a gradient of two colors

##### Post-processing
Apply post-processing filters to your scene

![A glass skull](./preview/neg.png "Refraction")
![A glass skull](./preview/sepia.png "Refraction")
![A glass skull](./preview/poster.png "Refraction")

##### User Interaction
Toggle FPS counter
The user can move and rotate the camera around in real time to get different views of the scene
- Modifiable camera parameters (field of view, movement and rotation speed)
- Scenes configured in the dedicated .rt file format (see documentation.rt for more details)
- Materials in .mrt files, able to load textures and normal maps from .xpm image files (see documentation.mrt for more details)
- Comes with a few pre-made scenes, meshes, textures and materials to select from

### 📦 Installation

### ⌨️ Keybindings

The following keybindings allow the user to interact with miniRT:

- Help : H
- Exit program : Escape
- Move horizontally : WASD
- Rotate horizontally : JL
- Rotate : hold alt+movement key
- Rotate up/down : IK
- Toggle FPS counter : F
- Toggle lights visibility : L
- Change movement speed : Up/Down arrows
- Change rotation speed : Left/Right arrows


### TODO ULTIMATE

#### PARSING
- Set the texture scaling in the .mrt file

#### Optimisation
- Others

#### BUGS
- uv mapping inside a sphere is upside down
- lights appear through plane-like surfaces
- abnormal deformation up and down the screen (fisheye)


### TODO AFTER

#### PARSING
- Set the texture scaling in the .mrt file

#### GRAPHICS
- Depth of field

#### Optimisation
- Others

#### CAMERA MOVEMENT
- Better movements
- Partial rendering when moving

#### LIGHT
- Add a light structure (similar to objects) and a list of lights to the scene
- Global illumination
- Soft shadows
- Directional light
- Wave lenght refraction (prisms)
- Bloom

#### MATERIALS
- Transparent textures
- Non-repetitive textures
- Emissive materials
