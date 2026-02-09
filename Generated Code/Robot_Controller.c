/*
 * Robot_Controller.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Robot_Controller".
 *
 * Model version              : 1.12
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Sat Jan 31 20:09:56 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Robot_Controller.h"
#include "rtwtypes.h"
#include <math.h>
#include "Robot_Controller_private.h"
#include <string.h>

/* Named constants for Chart: '<Root>/Chart' */
#define Robot_Contro_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Robot_Controller_IN_Emergency  ((uint8_T)1U)
#define Robot_Controller_IN_MoveForward ((uint8_T)2U)
#define Robot_Controller_IN_Stop       ((uint8_T)3U)
#define Robot_Controller_IN_TurnLeft   ((uint8_T)4U)
#define Robot_Controller_IN_TurnRight  ((uint8_T)5U)

/* Block signals (default storage) */
B_Robot_Controller_T Robot_Controller_B;

/* Continuous states */
X_Robot_Controller_T Robot_Controller_X;

/* Disabled State Vector */
XDis_Robot_Controller_T Robot_Controller_XDis;

/* Block states (default storage) */
DW_Robot_Controller_T Robot_Controller_DW;

/* Real-time model */
static RT_MODEL_Robot_Controller_T Robot_Controller_M_;
RT_MODEL_Robot_Controller_T *const Robot_Controller_M = &Robot_Controller_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Robot_Controller_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Robot_Controller_step();
  Robot_Controller_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Robot_Controller_step();
  Robot_Controller_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Robot_Controller_step(void)
{
  if (rtmIsMajorTimeStep(Robot_Controller_M)) {
    /* set solver stop time */
    if (!(Robot_Controller_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Robot_Controller_M->solverInfo,
                            ((Robot_Controller_M->Timing.clockTickH0 + 1) *
        Robot_Controller_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Robot_Controller_M->solverInfo,
                            ((Robot_Controller_M->Timing.clockTick0 + 1) *
        Robot_Controller_M->Timing.stepSize0 +
        Robot_Controller_M->Timing.clockTickH0 *
        Robot_Controller_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Robot_Controller_M)) {
    Robot_Controller_M->Timing.t[0] = rtsiGetT(&Robot_Controller_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Robot_Controller_M)) {
    /* Chart: '<Root>/Chart' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     *  Constant: '<Root>/Constant2'
     *  Constant: '<Root>/Constant3'
     *  Constant: '<Root>/Constant4'
     */
    if (Robot_Controller_DW.is_active_c3_Robot_Controller == 0) {
      Robot_Controller_DW.is_active_c3_Robot_Controller = 1U;
      Robot_Controller_DW.is_c3_Robot_Controller =
        Robot_Controller_IN_MoveForward;
      Robot_Controller_B.v_cmd = 0.5;
      Robot_Controller_B.w_cmd = 0.0;
    } else {
      switch (Robot_Controller_DW.is_c3_Robot_Controller) {
       case Robot_Controller_IN_Emergency:
        Robot_Controller_B.v_cmd = 0.0;
        Robot_Controller_B.w_cmd = 0.0;
        if (Robot_Controller_P.Constant3_Value == 0.0) {
          Robot_Controller_DW.is_c3_Robot_Controller = Robot_Controller_IN_Stop;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        }
        break;

       case Robot_Controller_IN_MoveForward:
        Robot_Controller_B.v_cmd = 0.5;
        Robot_Controller_B.w_cmd = 0.0;
        if (Robot_Controller_P.Constant1_Value < 0.5) {
          Robot_Controller_DW.is_c3_Robot_Controller = Robot_Controller_IN_Stop;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        } else if ((Robot_Controller_P.Constant3_Value == 1.0) ||
                   (Robot_Controller_P.Constant4_Value < 10.0)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_Emergency;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        }
        break;

       case Robot_Controller_IN_Stop:
        Robot_Controller_B.v_cmd = 0.0;
        Robot_Controller_B.w_cmd = 0.0;
        if ((Robot_Controller_P.Constant_Value < 0.5) &&
            (Robot_Controller_P.Constant2_Value > 0.5)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_TurnLeft;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.5;
        } else if ((Robot_Controller_P.Constant2_Value < 0.5) &&
                   (Robot_Controller_P.Constant_Value > 0.5)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_TurnRight;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = -0.5;
        } else if ((Robot_Controller_P.Constant3_Value == 1.0) ||
                   (Robot_Controller_P.Constant4_Value < 10.0)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_Emergency;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        }
        break;

       case Robot_Controller_IN_TurnLeft:
        Robot_Controller_B.v_cmd = 0.0;
        Robot_Controller_B.w_cmd = 0.5;
        if (Robot_Controller_P.Constant1_Value > 0.8) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_MoveForward;
          Robot_Controller_B.v_cmd = 0.5;
          Robot_Controller_B.w_cmd = 0.0;
        } else if ((Robot_Controller_P.Constant3_Value == 1.0) ||
                   (Robot_Controller_P.Constant4_Value < 10.0)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_Emergency;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        }
        break;

       default:
        /* case IN_TurnRight: */
        Robot_Controller_B.v_cmd = 0.0;
        Robot_Controller_B.w_cmd = -0.5;
        if (Robot_Controller_P.Constant1_Value > 0.8) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_MoveForward;
          Robot_Controller_B.v_cmd = 0.5;
          Robot_Controller_B.w_cmd = 0.0;
        } else if ((Robot_Controller_P.Constant3_Value == 1.0) ||
                   (Robot_Controller_P.Constant4_Value < 10.0)) {
          Robot_Controller_DW.is_c3_Robot_Controller =
            Robot_Controller_IN_Emergency;
          Robot_Controller_B.v_cmd = 0.0;
          Robot_Controller_B.w_cmd = 0.0;
        }
        break;
      }
    }

    /* End of Chart: '<Root>/Chart' */
    /* ToWorkspace: '<Root>/To Workspace' */
    if (rtmIsMajorTimeStep(Robot_Controller_M)) {
      rt_UpdateLogVar((LogVar *)(LogVar*)
                      (Robot_Controller_DW.ToWorkspace_PWORK.LoggedData),
                      &Robot_Controller_B.v_cmd, 0);
    }
  }

  /* Product: '<Root>/Product' incorporates:
   *  Integrator: '<Root>/Integrator'
   *  Trigonometry: '<Root>/Trigonometric Function'
   */
  Robot_Controller_B.Product = Robot_Controller_B.v_cmd * cos
    (Robot_Controller_X.Integrator_CSTATE);

  /* Product: '<Root>/Product1' incorporates:
   *  Integrator: '<Root>/Integrator'
   *  Trigonometry: '<Root>/Trigonometric Function1'
   */
  Robot_Controller_B.Product1 = Robot_Controller_B.v_cmd * sin
    (Robot_Controller_X.Integrator_CSTATE);
  if (rtmIsMajorTimeStep(Robot_Controller_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Robot_Controller_M->rtwLogInfo,
                        (Robot_Controller_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Robot_Controller_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Robot_Controller_M)!=-1) &&
          !((rtmGetTFinal(Robot_Controller_M)-
             (((Robot_Controller_M->Timing.clockTick1+
                Robot_Controller_M->Timing.clockTickH1* 4294967296.0)) * 0.2)) >
            (((Robot_Controller_M->Timing.clockTick1+
               Robot_Controller_M->Timing.clockTickH1* 4294967296.0)) * 0.2) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(Robot_Controller_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Robot_Controller_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Robot_Controller_M->Timing.clockTick0)) {
      ++Robot_Controller_M->Timing.clockTickH0;
    }

    Robot_Controller_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Robot_Controller_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Robot_Controller_M->Timing.clockTick1++;
      if (!Robot_Controller_M->Timing.clockTick1) {
        Robot_Controller_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Robot_Controller_derivatives(void)
{
  XDot_Robot_Controller_T *_rtXdot;
  _rtXdot = ((XDot_Robot_Controller_T *) Robot_Controller_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = Robot_Controller_B.w_cmd;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = Robot_Controller_B.Product1;

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = Robot_Controller_B.Product;
}

/* Model initialize function */
void Robot_Controller_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Robot_Controller_M, 0,
                sizeof(RT_MODEL_Robot_Controller_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Robot_Controller_M->solverInfo,
                          &Robot_Controller_M->Timing.simTimeStep);
    rtsiSetTPtr(&Robot_Controller_M->solverInfo, &rtmGetTPtr(Robot_Controller_M));
    rtsiSetStepSizePtr(&Robot_Controller_M->solverInfo,
                       &Robot_Controller_M->Timing.stepSize0);
    rtsiSetdXPtr(&Robot_Controller_M->solverInfo, &Robot_Controller_M->derivs);
    rtsiSetContStatesPtr(&Robot_Controller_M->solverInfo, (real_T **)
                         &Robot_Controller_M->contStates);
    rtsiSetNumContStatesPtr(&Robot_Controller_M->solverInfo,
      &Robot_Controller_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Robot_Controller_M->solverInfo,
      &Robot_Controller_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Robot_Controller_M->solverInfo,
      &Robot_Controller_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Robot_Controller_M->solverInfo,
      &Robot_Controller_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&Robot_Controller_M->solverInfo, (boolean_T**)
      &Robot_Controller_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&Robot_Controller_M->solverInfo, (&rtmGetErrorStatus
      (Robot_Controller_M)));
    rtsiSetRTModelPtr(&Robot_Controller_M->solverInfo, Robot_Controller_M);
  }

  rtsiSetSimTimeStep(&Robot_Controller_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Robot_Controller_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&Robot_Controller_M->solverInfo, false);
  Robot_Controller_M->intgData.y = Robot_Controller_M->odeY;
  Robot_Controller_M->intgData.f[0] = Robot_Controller_M->odeF[0];
  Robot_Controller_M->intgData.f[1] = Robot_Controller_M->odeF[1];
  Robot_Controller_M->intgData.f[2] = Robot_Controller_M->odeF[2];
  Robot_Controller_M->contStates = ((X_Robot_Controller_T *) &Robot_Controller_X);
  Robot_Controller_M->contStateDisabled = ((XDis_Robot_Controller_T *)
    &Robot_Controller_XDis);
  Robot_Controller_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&Robot_Controller_M->solverInfo, (void *)
                    &Robot_Controller_M->intgData);
  rtsiSetSolverName(&Robot_Controller_M->solverInfo,"ode3");
  rtmSetTPtr(Robot_Controller_M, &Robot_Controller_M->Timing.tArray[0]);
  rtmSetTFinal(Robot_Controller_M, 10.0);
  Robot_Controller_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Robot_Controller_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Robot_Controller_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Robot_Controller_M->rtwLogInfo, (NULL));
    rtliSetLogT(Robot_Controller_M->rtwLogInfo, "tout");
    rtliSetLogX(Robot_Controller_M->rtwLogInfo, "");
    rtliSetLogXFinal(Robot_Controller_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Robot_Controller_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Robot_Controller_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Robot_Controller_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Robot_Controller_M->rtwLogInfo, 1);
    rtliSetLogY(Robot_Controller_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Robot_Controller_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Robot_Controller_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Robot_Controller_B), 0,
                sizeof(B_Robot_Controller_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Robot_Controller_X, 0,
                  sizeof(X_Robot_Controller_T));
  }

  /* disabled states */
  {
    (void) memset((void *)&Robot_Controller_XDis, 0,
                  sizeof(XDis_Robot_Controller_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Robot_Controller_DW, 0,
                sizeof(DW_Robot_Controller_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Robot_Controller_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Robot_Controller_M), Robot_Controller_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Robot_Controller_M)));

  /* SetupRuntimeResources for ToWorkspace: '<Root>/To Workspace' */
  {
    int_T dimensions[1] = { 1 };

    Robot_Controller_DW.ToWorkspace_PWORK.LoggedData = rt_CreateLogVar(
      Robot_Controller_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(Robot_Controller_M),
      Robot_Controller_M->Timing.stepSize0,
      (&rtmGetErrorStatus(Robot_Controller_M)),
      "sim_data",
      SS_DOUBLE,
      0,
      0,
      0,
      1,
      1,
      dimensions,
      NO_LOGVALDIMS,
      (NULL),
      (NULL),
      0,
      1,
      0.2,
      1);
    if (Robot_Controller_DW.ToWorkspace_PWORK.LoggedData == (NULL))
      return;
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Robot_Controller_X.Integrator_CSTATE = Robot_Controller_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  Robot_Controller_X.Integrator1_CSTATE = Robot_Controller_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator2' */
  Robot_Controller_X.Integrator2_CSTATE = Robot_Controller_P.Integrator2_IC;

  /* SystemInitialize for Chart: '<Root>/Chart' */
  Robot_Controller_B.v_cmd = 0.0;
  Robot_Controller_B.w_cmd = 0.0;
  Robot_Controller_DW.is_active_c3_Robot_Controller = 0U;
  Robot_Controller_DW.is_c3_Robot_Controller = Robot_Contro_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void Robot_Controller_terminate(void)
{
  /* (no terminate code required) */
}
