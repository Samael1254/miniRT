## MINIRT

A basic raytracer for 42 school project miniRT

### FEATURES

- Colored diffuse and ambiant lighting
- Basic shapes, from the outside as well as inside : plane, sphere, cylinder
- Basic shading : hard shadows, incidence and distance attenuation
- Single point light
- Camera with modifiable parameters (position, orientation, field of view)
- Scenes written in the dedicated .rt file format (documentation not yet available)
- Comes with a few pre-made scenes to select from

### TODO MANDATORY

#### PARSING
- Specify all errors
- Change warnings to errors in the end
- Handle omments with space after

### TODO BONUS

#### PARSING
- Create materials with mt keyword
- Create texture with tx keyword
- Create normal map with nm keyword

#### SHAPES
- Infinite cone

#### MATERIALS
- Add material structure
- Texture
- Normal map
- Phong reflection model
- Transparent textures

#### LIGHT
- Add a light structure (similar to objects) and a list of lights to the scene

#### SCENES
- Add scenes to show off all the features

### TODO ULTIMATE

#### SHAPES
- Triangle
- Disk
- Box

#### PARSING
- .obj parser and triangle converter

#### GRAPHICS
- Anti aliasing

#### Performance
- BVH

#### LIGHT
- Global illumination
- Directional light
- Refraction
- Wave lenght refraction (prisms)

#### MATERIALS
- Transparent materials
- Emissive materials
