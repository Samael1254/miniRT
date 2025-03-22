## MINIRT

A basic raytracer for 42 school project miniRT

### FEATURES

- Colored diffuse, ambiant and specular lighting from multiple point sources
- Basic shapes, from the outside as well as inside : plane, sphere, cylinder, cone
- Basic shading : hard shadows, incidence and distance attenuation
- Texturing and normal mapping available for spheres and planes
- A background sky with a gradient of two colors
- Camera with modifiable parameters (position, orientation, field of view)
- Scenes written in the dedicated .rt file format (see documentation.rt for more details)
- Materials in .mrt files, able to load textures and normal maps from .xpm image files
- Comes with a few pre-made scenes to select from

### TODO MANDATORY

#### PARSING
- Change warnings to errors in the end


### TODO BONUS

#### MATERIALS
- Transparent textures

#### SCENES
- Add scenes to show off all the features

#### MISC
- check angle of cone in parsing
- merge kd and texture
- cylinder and cone normals


### TODO ULTIMATE

#### SHAPES
- Triangle
- Box

#### PARSING
- .obj parser and triangle converter
- Add a sky object with two colors to change the sky color

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
- Transparent materials
- Emissive materials
