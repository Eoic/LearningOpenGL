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
    * Uses VAOs and VBOs.
        * VAO - defines what data a vertex has (e.g. position, color).
        * VBO - defines the data itself.
        * Attribute pointers define where and how shaders can access vertex data. In othr words, for connections VBOs and VAOs to the shaders.
2. [Programmable][Required] Vertex shader.
    * Handles vertices individually.
    * Must store something in `gl_Position`.
    * Can specify additional outputs that can be used by other user defined shaders in the pipeline.
    * Inputs consist of the vertex data.

    Example:
    ```
    #version 330

    layout (location = 0) in vec3 pos;

    void main() {
        gl_Position - vec4(pos, 1.0);
    }
    ```
3. [Programmable] Tesselation shader.
    * Allows to divide data into smaller primitives.
    * Can be used to add higher level of detail.
4. [Programmable] Geometry shader.
    * Handles primitives (group of vertices).
    * Takes primitives and returns their vertices to create the given primitive, or new primitives.
    * Can change primitive type.
5. Vertex post-processing - end of all vertex operations.
    5.1. Transform feedback.
        * Save vertex and geometry stages to buffers.
    5.2. Clipping.
        * Invisible primitives are removed.
        * Positions converted from `clip space` to `window space`.
6. Primitive assembly
    * Handling groups of vertices.
    * Vertices are converted into primitives.
    * Does face-culling.
7. Resterization
    * Converts primitives into fragments (data for each pixel).
    * Fragment data is interpolated.
8. [Programmable] Fragment shader.
    * Handles data for each fragment.
    * Outputs color for each pixel.
    * Only has one output.

    Example:
    ```
    #version 330

    out vec4 color;
 
    void main() {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    ```
9. Per-sample operations.
    * Series of tests if the fragment should be drawn.
    * Most important - depth test.
    * Color blending - colors are blended together with overlapping fragments.
