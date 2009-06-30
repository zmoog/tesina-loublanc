/*
 *  paolo_solve.c
 *
 *
 *  GSL ODE solver for the vector field named: paolo
 *
 *  This file was generated by the program VFGEN (Version:2.4.0)
 *  Generated on 22-Jun-2009 at 23:37
 *
 *  To compile and run this program:
 *      gcc -c paolo_gvf.c
 *      gcc -c paolo_solve.c
 *      gcc -o paolo_solve  paolo_solve.o paolo_gvf.o -lgsl -lgslcblas -lm
 *  This creates an executable file called paolo_solve
 */

#include <string.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

#include "paolo_gvf.h"



int use(int argc, char *argv[], int nv, char *vname[], double y_[], int np, char *pname[], double p_[])
    {
    int i;
    printf("use: %s [options]\n",argv[0]);
    printf("options:\n");
    printf("    -h    Print this help message.\n");
    for (i = 0; i < nv; ++i)
        printf("    %s=<initial_condition>   Default value is %e\n",vname[i],y_[i]);
    for (i = 0; i < np; ++i)
        printf("    %s=<parameter_value>   Default value is %e\n",pname[i],p_[i]);
    printf("    abserr=<absolute_error_tolerance>\n");
    printf("    relerr=<relative_error_tolerance>\n");
    printf("    stoptime=<stop_time>\n");
    return 0;
    }


int assign(char *str[], int ns, double v[], char *a)
    {
    int i;
    char name[256];
    char *e;

    e = strchr(a,'=');
    if (e == NULL)
        return(-1);
    *e = '\0';
    strcpy(name,a);
    *e = '=';
    ++e;
    for (i = 0; i < ns; ++i)
        if (strcmp(str[i],name)==0)
            break;
    if (i == ns)
        return(-1);
    v[i] = atof(e);
    return(i);
    }


int main (int argc, char *argv[])
    {
    int i;
    double alpha1, alpha2, gamma1, gamma2, mu_f, mu_m;
    const int P_ = 6;
    double def_p_[6] = {1.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00, 1.0000000000000000e+00};
    alpha1     = def_p_[0];
    alpha2     = def_p_[1];
    gamma1     = def_p_[2];
    gamma2     = def_p_[3];
    mu_f       = def_p_[4];
    mu_m       = def_p_[5];
    double p_[6];
    const int N_ = 2;
    double def_y_[2] = {1.0000000000000000e+00, 1.0000000000000000e+00};
    double y_[2];
    double solver_param_[3] = {1.0e-6,0.0,10.0};
    char *varnames_[2] = {"F", "M"};
    char *parnames_[6] = {"alpha1", "alpha2", "gamma1", "gamma2", "mu_f", "mu_m"};
    char *solver_param_names_[3] = {"abserr","relerr","stoptime"};

    for (i = 0; i < N_; ++i)
        y_[i] = def_y_[i];
    for (i = 0; i < P_; ++i)
        p_[i] = def_p_[i];
    for (i = 1; i < argc; ++i)
        {
        int j;
        if (strcmp(argv[i],"-h") == 0)
            {
            use(argc,argv,N_,varnames_,def_y_,P_,parnames_,def_p_);
            exit(0);
            }
        j = assign(varnames_,N_,y_,argv[i]);
        if (j == -1)
            {
            j = assign(parnames_,P_,p_,argv[i]);
            if (j == -1)
                {
                j = assign(solver_param_names_,3,solver_param_,argv[i]);
                if (j == -1)
                    {
                    fprintf(stderr,"unknown argument: %s\n",argv[i]);
                    use(argc,argv,N_,varnames_,def_y_,P_,parnames_,def_p_); 
                    exit(-1);
                    }
                }
            }
        }

    const gsl_odeiv_step_type *T_  = gsl_odeiv_step_rk8pd;
    gsl_odeiv_step    *step_    = gsl_odeiv_step_alloc(T_,N_);
    gsl_odeiv_control *control_ = gsl_odeiv_control_y_new(solver_param_[0], solver_param_[1]);
    gsl_odeiv_evolve  *evolve_  = gsl_odeiv_evolve_alloc(N_);
    gsl_odeiv_system sys_ = {paolo_vf, paolo_jac, N_, &(p_[0])};

    double t_  = 0.0;
    double t1_ = solver_param_[2];
    double h_ = 1e-6;

    while (t_ < t1_)
        {
        int j_;
        int status_ = gsl_odeiv_evolve_apply(evolve_, control_, step_, &sys_, &t_, t1_, &h_, y_);
        if (status_ != GSL_SUCCESS)
            {
            fprintf(stderr,"status=%d\n",status_);
            break;
            }
        printf("%.8e",t_);
        for (j_ = 0; j_ < N_; ++j_)
            printf(" %.8e",y_[j_]);
        printf("\n");
        }

    gsl_odeiv_evolve_free(evolve_);
    gsl_odeiv_control_free(control_);
    gsl_odeiv_step_free(step_);
    return 0;
    }