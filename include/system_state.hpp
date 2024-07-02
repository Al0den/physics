#pragma once

class SystemState {
    public:
        SystemState();
        
        bool setObjectsCount(int count);
        void reset();
        void destroy();
        void copy(SystemState *ori);
        void clearAccelerations();

        double kineticEnergy();

        double dt;
        int n;

        double *a_x;
        double *a_y;

        double *v_x;
        double *v_y;

        double *p_x;
        double *p_y;

        double *theta;
        double *v_theta;
        double *a_theta;

        double *f_x;
        double *f_y;

        double *m;

};
