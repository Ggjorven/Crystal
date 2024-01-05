### Crystal Engine

## 1. Architecture
TODO

## Notes:
### Steps taken:
- Create a window + basic input functions
- Add OpenGL support (vertexarrays/shaders)
- Created a custom 2D renderer to simplify rendering plus added texture loading.
- Added cameras
- Created an ECS
- Custom projects files + a real time editor to change them
- Add C# Scripting support
- Added Collision detection
- Added basic 3D

### Issues:
- Tried to implement mono for C# scripting
- Having ECS components on the heap
- Crashes upon C# loading
- Scene duplication in heap memory
- Crash upon on scene switch when running (cause reading m_Storage that doesn't exist)
