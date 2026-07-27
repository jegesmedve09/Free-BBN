// OpenSCAD Particle Wave Animation

//$fn = 1; // Smoothness of the spheres
grid_size = 60; // Grid dimensions
spacing = 0.3;  // Distance between dots

// Turn on the loop matrix
for (x = [-grid_size : grid_size])
{
    for (y = [-grid_size : grid_size])
    {
        
        // WAVE MATH: Calculate Z height based on X, Y, and the Time ($t) variable
        // Multiplying ($t * 360) creates a flawless, seamless looping cycle
        z = sin(x * 12 + $t * 360) * cos(y * 8 + $t * 360) * 4;
        
        // Color the particles cyan/blue
        color([0, 0.5 + (z+4)/16, 1])
        {
            // Translate to the calculated position and render a tiny sphere
            translate([x * spacing, y * spacing, z])
                cube(0.4);
        }
    }
}
