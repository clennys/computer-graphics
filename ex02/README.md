## OpengGL - Exercise 2

### Subject / Goals:

Understand transformations and how to apply them to objects. In addition, we get to know normals and experiment with them.

### Tasks:

- Apply rotation, translation, and scalings for a shape object (see 'Additional Information below).
- Let the cube spin around one or multiple axis of choice.
- Transform the torus to be spun around the view direction.
- Show the normals for the torus as a MultiLine object.
- Show the torus with colors according to normals.
- Calculate the normal matrix, apply it to the normals of the torus, and compare the color output.
- [optional] Apply the normal matrix of the torus also to manipulate the line object.

### How to Submit:

Create a **.zip** file with the source code (please include only the source files, the **src/** and **shader/** folders), and upload it to OLAT with a screenshot of the rendering window working on your computer. 

### Learning Targets:

- Apply a transformation to a model matrix.
- Draw lines-based objects.
- Apply a normal matrix to normals, and see the difference between right and wrong normals.

### Additional Information:

The starting point of this exercise is two objects (torus and cube) located at the same position. Implement the corresponding methods in the Shape class.

Look at the shaders (vertex and fragment shaders) for the objects' coloring.

Some screenshots of the initial state and examples of drawing the normals as lines and using them to color the cube and torus are inside the doc folder.
