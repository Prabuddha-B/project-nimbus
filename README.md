# Project Nimbus
### CSC3081 – Individual Computer Graphics Project

A fully playable 3D Quidditch simulation and mini-game developed using **C++**, **OpenGL**, and **GLUT** as part of the CSC3081 Computer Graphics module.

Project Nimbus recreates a highly detailed, interactive Quidditch stadium inspired by the Harry Potter universe. What began as a static 3D environment has been transformed into a complete mini-game featuring a rigged, textured player model, smooth momentum-based physics, procedural AI, and a fully managed game state engine.

---

## Features

### Gameplay & Core Mechanics
- **Playable Mini-Game:** Complete gameplay loop with Start, Play, and Victory states.
- **Smooth Flight Physics:** Joystick-style analog handling with acceleration, drag friction, and smooth momentum-based steering.
- **Procedural AI (The Golden Snitch):** Autonomous waypoint navigation featuring vector weaving, speed surging, and active player-evasion mechanics.
- **Collision Detection:** Mathematical elliptical boundaries keep entities confined to the pitch, while distance-based hitboxes handle Snitch-catching.
- **2D UI Overlays:** Orthographic projection is used to render start-screen instructions and a massive, scalable stroke-font victory screen.

### Advanced Graphics & Environment
- **Dynamic Camera System:** Switch seamlessly between Free Roam, Chase Cam (locked behind the player), Tactical Top-Down, and a Cinematic Front Camera upon victory.
- **Day/Night Cycle:** Toggle between a bright daytime environment and a moody night scene featuring volumetric fog and dynamic lighting from the stadium towers.
- **Hierarchical 3D Modelling:** A fully rigged player model constructed from hierarchical primitives, featuring a dynamically animating cape using overlapping sine waves.
- **Rich Environments:** Surrounding procedurally placed pine forests, a backdrop of Hogwarts Castle, a flying Ford Anglia with an elliptical flight path, and towering House spectator stands.
- **Shadow Projection:** Planar shadow projection matrix rendering dynamic ground shadows that react to light position.

### Texturing & Materials
The project uses image-based texture mapping extensively across the environment and characters:

| Object | Texture | Object | Texture |
|----------|----------|----------|----------|
| **Pitch** | Grass | **Player Body** | Quidditch Robes |
| **Goal Areas** | Sand | **Player Cape** | Gryffindor Crest |
| **Goal Posts** | Metal | **Broomstick** | Wood & Bristles |
| **Stadium Wall**| Wood | **Player Head** | Custom Face Mapping |
| **Seating** | Stadium Seats | **Towers** | House Flags & Brick |
| **Surroundings**| Terrain | **Castle** | Stone Walls & Roofs |

---

## Technologies Used

- C++
- OpenGL (Fixed Pipeline)
- GLUT / GLU
- SOIL2 Texture Library
- Visual Studio 2022

---

## Project Structure

```text
Project_Nimbus/
│
├── main.cpp                # Core rendering loop, 2D UI overlays, and input handling
│
├── Game.h / .cpp           # Game state machine, boundary math, and smooth physics engine
├── Player.h / .cpp         # Hierarchical 3D player model and dynamic cape animation
├── Snitch.h / .cpp         # Procedural AI, vector weaving, and evasion logic
├── Camera.h / .cpp         # Multi-mode camera logic and boolean input flags
│
├── Ground.h / .cpp         # Stadium geometry, pitch, and boundary lines
├── SpectatorStand.h / .cpp # Parametric seating tiers and walls
├── Tower.h / .cpp          # Four house towers with dynamic point lights
├── GoalPost.h / .cpp       # Goal rings and poles
├── Forest.h / .cpp         # Procedural tree generation and layout
├── Castle.h / .cpp         # Backdrop environment rendering
├── Sky.h / .cpp            # Skydome, Sun, and Day/Night cycle
├── FlyingCar.h / .cpp      # Animated background vehicle
│
├── Shadow.h / .cpp         # Planar shadow matrix calculations
├── Controls.h / .cpp       # Legacy debug controls
├── Texture.h / .cpp        # SOIL2 texture loading definitions
│
└── Textures/               # .jpg and .png assets for all models and environments


```

---

## Technical Highlights

### 1. Procedural Snitch AI & Vector Weaving

To mimic the erratic behavior of the Golden Snitch, the AI calculates a normalized straight-line vector toward a random waypoint and modifies it every frame by adding overlapping `sin()` and `cos()` waves to a perpendicular vector. Combined with active player-distance evasion logic, this creates chaotic and organic flight paths that closely resemble the unpredictable movement of the Snitch.

### 2. Momentum-Based Physics

Keyboard inputs are decoupled from direct movement. Instead, key presses toggle boolean state flags that are processed by a physics engine each frame. The engine calculates acceleration, velocity limits, and drag friction to produce smooth, joystick-like movement rather than instant positional changes.

### 3. Mathematical Collision Confinement

Instead of relying on complex mesh collision detection, the playable area is constrained mathematically using an ellipse equation:

```text
(x² / a²) + (z² / b²) ≤ 1
```

Each frame, the player's and Snitch's next positions are evaluated against this boundary. If the calculated value exceeds 1, movement is blocked and momentum is cancelled, ensuring all gameplay remains within the Quidditch pitch.

### 4. Parametric Stadium Geometry

The stadium layout is generated using parametric equations based on trigonometric functions:

```text
x = r * cos(θ)
z = r * sin(θ)
```

This approach allows the spectator stands, towers, and surrounding structures to remain perfectly symmetrical and scalable while minimizing manual vertex placement.

### 5. Planar Shadow Projection

Dynamic shadows are produced using a planar shadow projection matrix derived from the ground plane equation and the current light position. Object geometry is projected onto the ground plane to create realistic shadows that change naturally as the light source moves throughout the scene.


---

## Author

**Prabuddha Bandara**  
Computer Science (Hons) Undergraduate  
Department of Statistics and Computer Science  
University of Peradeniya  

**CSC3081 – Computer Graphics Individual Project (2026)**

---

