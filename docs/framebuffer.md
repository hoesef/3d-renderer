# Contents

# Framebuffer
Framebuffer is a class that stores pixel information (rgb values, depth values) about a scene during the rendering process. Once the rendering is complete, this pixel information is written to a PPM file to form the final image. 

The framebuffer has three attributes; width and height (the dimensiosn of the image), and fb (the actual pixel buffer).