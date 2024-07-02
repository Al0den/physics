
#include "collisions.hpp"
#include "config.hpp"

#include <math.h>

void SolveCollisions(SystemState *system) {
    bool collision = true;
    while (collision) {
        collision = false;
        for (int i=0; i<system->n; i++) {
            for(int j=0; j<system->n; j++) {
                if(i == j) continue;
                double dx = system->p_x[i] - system->p_x[j];
                double dy = system->p_y[i] - system->p_y[j];

                double d = sqrt(dx*dx + dy*dy);
                if (d < 2 * radius) {
                    collision = true;
                    // Calculate the penetration depth
                    double overlap = 2 * radius - d;

                    // Unit normal vector
                    double nx = dx / d;
                    double ny = dy / d;

                    // Relative velocity
                    double rvx = system->v_x[j] - system->v_x[i];
                    double rvy = system->v_y[j] - system->v_y[i];

                    // Relative velocity in normal direction
                    double v_rel_normal = rvx * nx + rvy * ny;

                    // Calculate the impulse scalar
                    double e = damping;  // Coefficient of restitution (elastic collision)
                    double j_s = -(1 + e) * v_rel_normal / 2.0;

                    // Impulse vector
                    double jx = j_s * nx;
                    double jy = j_s * ny;

                    // Apply impulse to velocities
                    system->v_x[i] -= jx;
                    system->v_y[i] -= jy;
                    system->v_x[j] += jx;
                    system->v_y[j] += jy;

                    // Positional correction to avoid sinking
                    double correction_x = overlap * nx / 2.0;
                    double correction_y = overlap * ny / 2.0;

                    system->p_x[i] += correction_x;
                    system->p_y[i] += correction_y;
                    system->p_x[j] -= correction_x;
                    system->p_y[j] -= correction_y;
                }
            }
            if(system->p_x[i] > width) {
                system->p_x[i] = width;
                system->v_x[i] = -system->v_x[i];
            } else if(system->p_x[i] < 0) {
                system->p_x[i] = 0;
                system->v_x[i] = -system->v_x[i];
            }

            if(system->p_y[i] > height) {
                system->p_y[i] = height;
                system->v_y[i] = -system->v_y[i];
            } else if(system->p_y[i] < 0) {
                system->p_y[i] = 0;
                system->v_y[i] = -system->v_y[i];
            }
        }
    }
}
