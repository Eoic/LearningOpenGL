### Rendering pipeline.
1. A series of stages that take place in order torender an image to the screen.
2. Four stages are progremmable via shaders:
    * Vertex
    * Fragment
    * Geometry 
    * Tesselation
    * Compute (since OpenGL 4.3)
3. Shaders are programs written in GLSL(OpenGL) or HLSL (Direct3D).

#### Stages
1. Vertex specification.
    * Usually, data is specified for triangles, but points, lines and quads can be used as well.
    * Setting up the data of the vertices for the primitives we want to render.
    * Done in the application itself.
2. [Programmable] Vertex shader.
3. [Programmable] Tesselation shader.
4. [Programmable] Geometry shader.
5. Vertex post-processing - end of all vertex operations.
6. Primitive assembly - handling groups of vertices. 
7. Resterization - conversion to fragments.
8. [Programmable] Fragment shader.
9. Per-sample operations.