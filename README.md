# Project Nimbus
### CSC3081 – Individual Computer Graphics Project

A 3D Quidditch Stadium simulation developed using **C++**, **OpenGL**, and **GLUT** as part of the CSC3081 Computer Graphics module.

The project recreates a textured Quidditch pitch inspired by the Harry Potter universe, featuring a fully modelled stadium environment, interactive camera controls, dynamic lighting, texture mapping, and procedurally generated stadium geometry.

---


## Features

### Core Graphics Components

- 3D stadium environment
- Quidditch pitch modelling
- Goal post modelling
- Spectator stand modelling
- Perspective projection
- Interactive camera system
- Keyboard navigation
- OpenGL lighting system
- Texture mapping
- Material properties
- Hierarchical transformations

### Stadium Components

- Elliptical Quidditch pitch
- Textured grass playing surface
- Textured sand goal areas
- Six Quidditch goal posts
- Multi-tier spectator seating
- Wooden outer stadium wall
- Decorative banner ring
- Wooden deck surrounding the pitch

### Lighting

- Movable sunlight source
- Ambient lighting
- Diffuse lighting
- Specular highlights
- Real-time light positioning controls
- Sun visualisation sphere

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

---

## Technologies Used

- C++
- OpenGL (Fixed Pipeline)
- GLUT
- GLU
- SOIL2 Texture Library
- Visual Studio

---

## Project Structure

```
Project_Nimbus/
│
├── main.cpp
│
├── Camera.cpp
├── Camera.h
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
├── Texture.cpp
├── Texture.h
│
└── Textures/
    ├── grass.jpg
    ├── sand.jpg
    ├── metal.jpg
    ├── wood.jpg
    ├── banner.png
    └── seats.jpg
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

This ensures:

- Even texture distribution
- Minimal stretching
- Seamless tiling

---

### Lighting Model

The project uses OpenGL's fixed-function lighting pipeline:

- Ambient component
- Diffuse component
- Specular component

Configured through:

```cpp
glLightfv()
glMaterialfv()
glMaterialf()
```

---

## Learning Outcomes

This project demonstrates practical understanding of:

- 3D Modelling
- Coordinate Systems
- Geometric Transformations
- Camera Systems
- Perspective Projection
- Texture Mapping
- Lighting and Materials
- OpenGL Rendering Pipeline
- Interactive Graphics Programming

---

## Build Instructions

### Requirements

- Visual Studio
- OpenGL
- GLUT
- SOIL2

### Build

1. Clone repository

```bash
git clone https://github.com/<username>/Project_Nimbus.git
```

2. Open solution in Visual Studio

3. Ensure OpenGL, GLUT, and SOIL2 dependencies are configured

4. Build and run

---

## Author

**Prabuddha Bandara**

Computer Science (Hons) Undergraduate  
Department of Statistics and Computer Science  
Faculty of Science  
University of Peradeniya  
Sri Lanka  

**CSC3081 – Computer Graphics Individual Project**

