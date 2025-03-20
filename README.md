## MINIRT

A basic raytracer for 42 school project miniRT

### FEATURES

- Colored diffuse and ambiant lighting
- Basic shapes, from the outside as well as inside : plane, sphere, cylinder
- Basic shading : hard shadows, incidence and distance attenuation
- A background sky with a gradient of two colors
- Single point light
- Camera with modifiable parameters (position, orientation, field of view)
- Scenes written in the dedicated .rt file format (documentation not yet available)
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
- check angle of cone
- merge kd and texture
- plane normals


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
