# Project Nimbus
### CSC3081 – Individual Computer Graphics Project

A 3D Quidditch Stadium simulation developed using **C++**, **OpenGL**, and **GLUT** as part of the CSC3081 Computer Graphics module.

Project Nimbus recreates a Quidditch stadium inspired by the Harry Potter universe, featuring a fully modelled 3D environment, interactive camera controls, texture mapping, dynamic lighting, shadow projection, and procedurally generated stadium geometry.

---

## Features

### Core Graphics Components

- 3D object modelling
- Geometric transformations
- Hierarchical transformations
- Perspective projection
- Interactive camera system
- Keyboard controls
- OpenGL lighting and materials
- Texture mapping
- Real-time rendering
- Shadow projection (Advanced Technique)

### Stadium Components

- Elliptical Quidditch pitch
- Textured grass playing field
- Textured sand goal areas
- Six Quidditch goal posts
- Multi-tier spectator seating
- Wooden outer stadium wall
- Decorative banner ring
- Wooden spectator deck
- Raised earth embankment surrounding the stadium

### Lighting System

- Movable sunlight source
- Ambient lighting
- Diffuse lighting
- Specular highlights
- Real-time light positioning controls
- Sun visualisation sphere
- Lighting enable/disable toggle

### Shadow Projection

The project implements planar shadow projection using a shadow matrix generated from the light position and ground plane.

Shadowed objects include:

- Quidditch goal posts
- Goal rings
- Supporting structures

Features:

- Real-time shadow updates
- Dynamic shadows based on light movement
- Adjustable shadow projection scaling
- Ground plane shadow rendering

### Texture Mapping

The project uses image-based texture mapping for:

| Object | Texture |
|----------|----------|
| Pitch | Grass Texture |
| Goal Areas | Sand Texture |
| Goal Posts | Metal Texture |
| Stadium Wall | Wood Texture |
| Stadium Banners | Banner Texture |
| Seating Tiers | Seat Texture |
| Surrounding Terrain | Ground Texture |

---

## Technologies Used

- C++
- OpenGL (Fixed Pipeline)
- GLUT
- GLU
- SOIL2 Texture Library
- Visual Studio 2022

---

## Project Structure

```text
Project_Nimbus/
│
├── main.cpp
│
├── Camera.cpp
├── Camera.h
│
├── Controls.cpp
├── Controls.h
│
├── Ground.cpp
├── Ground.h
│
├── GoalPost.cpp
├── GoalPost.h
│
├── SpectatorStand.cpp
├── SpectatorStand.h
│
├── Shadow.cpp
├── Shadow.h
│
├── Texture.cpp
├── Texture.h
│
└── Textures/
    ├── grass.jpg
    ├── sand.jpg
    ├── metal.jpg
    ├── wood.jpg
    ├── banner.png
    ├── seats.jpg
    └── terrain.jpg
```

---

## Controls

### Camera Controls

| Key | Action |
|------|---------|
| W | Move Forward |
| S | Move Backward |
| A | Move Left |
| D | Move Right |
| Q | Move Up |
| E | Move Down |

### Sun Controls

| Key | Action |
|------|---------|
| I | Move Sun Up |
| K | Move Sun Down |
| J | Move Sun Left |
| L | Move Sun Right |
| U | Move Sun Backward |
| O | Move Sun Forward |
| P | Toggle Sun Visibility |

### Scene Controls

| Key | Action |
|------|---------|
| G | Toggle Ground Plane |
| X | Toggle Coordinate Axes |
| Z | Toggle Lighting On / Off |

---

## Technical Highlights

### Parametric Stadium Geometry

The stadium structure is generated using parametric equations based on trigonometric functions:

```cpp
x = radiusX * cos(theta);
z = radiusZ * sin(theta);
```

This approach enables:

- Smooth elliptical geometry
- Scalable stadium dimensions
- Reduced manual vertex specification
- Consistent symmetry

---

### Texture Mapping

Planar texture mapping is applied to the pitch and goal areas.

Example:

```cpp
u = (x + width / 2) / width;
v = (z + length / 2) / length;
```

Benefits:

- Even texture distribution
- Reduced distortion
- Seamless surface coverage

---

### Lighting Model

The project uses OpenGL's fixed-function lighting pipeline.

Components:

- Ambient lighting
- Diffuse lighting
- Specular reflections

Implemented using:

```cpp
glLightfv()
glMaterialfv()
glMaterialf()
```

---

### Shadow Projection

The advanced technique implemented for this project is **planar shadow projection**.

A shadow projection matrix is generated using:

- Ground plane equation
- Light source position

The matrix projects object geometry onto the ground plane to create realistic shadows that respond dynamically to light movement.

---

## Learning Outcomes

This project demonstrates practical understanding of:

- 3D Modelling
- Coordinate Systems
- Geometric Transformations
- Hierarchical Modelling
- Camera Systems
- Perspective Projection
- Lighting and Materials
- Texture Mapping
- Shadow Projection
- OpenGL Rendering Pipeline
- Interactive Graphics Programming

---


## Author

**Prabuddha Bandara**

Computer Science (Hons) Undergraduate  
Department of Statistics and Computer Science  
Faculty of Science  
University of Peradeniya  
Sri Lanka

**CSC3081 – Computer Graphics Individual Project (2026)**
