#pragma once

class RigidBody {
    public:
        RigidBody(double x, double y, double theta, double m, double I);
        ~RigidBody();

        void localToWorld(double lx, double ly, double *wx, double *wy);
        void worldToLocal(double wx, double wy, double *lx, double *ly);

        double p_x;
        double p_y;
        
        double v_x;
        double v_y;

        double theta;
        double v_theta;

        double m;
        double I;

        int index;

        void reset();
        void energy() const;
};
