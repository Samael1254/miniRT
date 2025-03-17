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

#### PARSING
- Create .mat file for materials
- Create materials with mt keyword
- Create texture with tx keyword
- Create normal map with nm keyword

#### SHAPES
- Infinite cone

#### MATERIALS
- Texture
- Checkerboard procedural texture
- Normal map
- Transparent textures

#### LIGHT
- Add a light structure (similar to objects) and a list of lights to the scene
- Phong reflection model

#### SCENES
- Add scenes to show off all the features


### TODO ULTIMATE

#### SHAPES
- Triangle
- Disk
- Box

#### PARSING
- .obj parser and triangle converter
- Add a sky object with two colors to change the sky color

#### GRAPHICS
- Anti aliasing
- Depth of field

#### Performance
- BVH

#### LIGHT
- Global illumination
- Soft shadows
- Directional light
- Refraction
- Wave lenght refraction (prisms)

#### MATERIALS
- Transparent materials
- Emissive materials
