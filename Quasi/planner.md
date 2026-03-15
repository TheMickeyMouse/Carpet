# Mickey's Project Planner
## Things to do: 
- Library jargon
  * [ ] Iterators
  * [ ] Resource Manager
  * [ ] Interfaces

- High Priority (ABSOLUTELY NECESSARY)
  * [ ] `[TODO]` [Bloom](https://learnopengl.com/Advanced-Lighting/Bloom)
  * [ ] `[TODO]` [Advanced Lighting](https://learnopengl.com/Advanced-Lighting/Bloom)
  * [ ] `[TODO]` [PBR](https://learnopengl.com/PBR/Theory)
  * [ ] `[TODO]` High Level (abstracted) Rendering
- Medium Priority (Feature is needed)
  * [ ] `[FIXME]` Fix Rich Text Parsing
  * [ ] `[TODO]` Add Anti-aliasing
  * [ ] `[TODO]` Physics Engine
  * [ ] `[TODO]` Real-time editing (shaders?)
- Low Priority (Would be nice to have)
  * [ ] `[TODO]` Custom GUI
- Misc (I have no idea)
- Done (Finished!)
  * [X] ~~`[TODO]` Particle System~~
  * [X] ~~`[TODO]` Add Instancing~~
  * [X] ~~`[DONE]` Add Tests for Geometry shaders~~
  * [X] ~~`[DONE]` Add Geometry shader support~~
  * [X] ~~`[DONE]` Make Matrix Variations `matrix<N, M, T>`~~
  * [X] ~~`[DONE]` Make Vector share same class `vecn<N, T>` (and use less macros)~~
  * [X] ~~`[DONE]` Add Easy Shader Args~~
  * [X] ~~`[DONE]` Add Easy Vertex Conversion~~
  * [X] ~~`[DONE]` Integrate `post_build.bat` to CMake~~


```cpp
struct IGeom {
  struct DynTable {
    FnPtr<float, Dyn<IGeom>> _calcArea;
    FnPtr<void, Dyn<IGeom>, float> _scale;
    std::string* name; // static dynamic variable
  };
  
  std::string Format(Dyn<IGeom> self);
};

template <>
struct Dyn<IGeom> {
  IGeom::DynTable _dyntable;
  IGeom::
};

// QInterface$(
  Iterable,
  
// )
```