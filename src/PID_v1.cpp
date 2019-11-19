/**********************************************************************************************
 * Arduino PID Library - Version 1.2.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under the MIT License
 **********************************************************************************************/


#include "PID_v1.h"
#include "pid.h"


int millisCount;
int millis(void)
{
   return millisCount; 
}

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
PID::PID(float* Input, float* Output, float* Setpoint,
        float Kp, float Ki, float Kd, bool isRevrse)
{
    myOutput = Output;
    myInput = Input;
    mySetpoint = Setpoint;
    a = 0;
    inAuto = true;
    inPositional = true;

    SetOutputLimits(0, 255);				//default output limit corresponds to
												//the arduino pwm limits

    SampleTime = 100;							//default Controller Sample Time is 0.1 seconds

    SetControllerDirection(isRevrse);
    SetTunings(Kp, Ki, Kd);

    lastTime = millis()-SampleTime;
}


/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/
void PID::Incremental() //DU(K)=Kp*(e(k)-e(k-1))+ki*e(k)+kd*(e(k)-2*e(k-1)+e(k-2))
{
    float input = *myInput;
    float error = *mySetpoint - input;
    float ud = kd * (error - 2*last + Prev);
     
    outputSum += kp * (error-last);   
    outputSum += ki * error;
    outputSum += (1-a) * ud + a * lastUd;
    
    if(outputSum > outMax) outputSum = outMax;
    else if(outputSum < outMin) outputSum = outMin;
    
    *myOutput = outputSum;
    Prev = last;
    last = error;
    lastUd = ud;
}
void PID::Positional() //U(K)=Kp*e(k)+ki*Sum(e)+kd*(e(k)-e(k-1))
{
    float input = *myInput;
    float error = *mySetpoint - input;

    float dInput = last - input;  //改进算法 dInput =  error - lastError;
    
    outputSum+= (ki * error);

    if(outputSum > outMax) outputSum= outMax;
    else if(outputSum < -outMax) outputSum= -outMax;
    
    float ud = kd * dInput;
    
    float output = kp * error + outputSum;
    output += (1-a)*ud + a*lastUd;
    
    if(output > outMax) output = outMax;
    else if(output < outMin) output = outMin;
    
	*myOutput = output;
    last = input;
    lastUd = ud;
//-----------------------------    
//    Pout = kp * error;
//    Iout = outputSum;
//    Dout = kd * dInput;   
}

bool PID::Compute()   
{
   if(!inAuto) return false;
   unsigned long now = millis();
   unsigned long timeChange = (now - lastTime);
   if(timeChange>=SampleTime)
   {
       if(inPositional) Positional();
       else Incremental();
       lastTime = now;
	   return true;
   }
   else return false;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void PID::SetTunings(float Kp, float Ki, float Kd)
{
   if (Kp<0 || Ki<0 || Kd<0) return;


   dispKp = Kp; dispKi = Ki; dispKd = Kd;

   float SampleTimeInSec = ((float)SampleTime)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;

  if(controllerDirection ==inRevrse)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed
 ******************************************************************************/
void PID::SetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      float ratio  = (float)NewSampleTime
                      / (float)SampleTime;
      ki *= ratio;
      kd /= ratio;
      SampleTime = (unsigned long)NewSampleTime;
   }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void PID::SetOutputLimits(float Min, float Max)
{
   if(Min >= Max) return;
   outMin = Min;
   outMax = Max;

   if(inAuto)
   {
	   if(*myOutput > outMax) *myOutput = outMax;
	   else if(*myOutput < outMin) *myOutput = outMin;

	   if(outputSum > outMax) outputSum= outMax;
	   else if(outputSum < outMin) outputSum= outMin;
   }
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void PID::SetMode(bool isAuto)
{
    bool newAuto = isAuto; //(Mode == AUTOMATIC);
    if(newAuto && !inAuto)
    {  /*we just went from manual to auto*/
        PID::Initialize();
    }
    inAuto = newAuto;
}
void PID::SetAlgorithm(bool isPositional)
{
    bool newPositional = isPositional;//(inPositional == POSITIONAL);
    if(newPositional != inPositional)
    {
        PID::Initialize();
        inPositional = newPositional;
    }
}
/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void PID::Initialize()
{
    outputSum = *myOutput;
    if(inPositional)last = *myInput;
    else Prev = last = *mySetpoint - *myInput;
    
    if(outputSum > outMax) outputSum = outMax;
    else if(outputSum < outMin) outputSum= outMin;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void PID::SetControllerDirection(bool isRevrse)
{
   if(inAuto && isRevrse != inRevrse)
   {
	  kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
   inRevrse = isRevrse;
}

void PID::SetFilter(float filter)
{
    if((filter < 1)&&(filter >=0 )) a = filter;
}
/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
float PID::GetKp(){ return  dispKp; }
float PID::GetKi(){ return  dispKi;}
float PID::GetKd(){ return  dispKd;}
bool PID::isAuto(){ return  inAuto;}
bool PID::isRevrse(){ return inRevrse;}

//----------------------------以下是C语言接口-------------------------------------------------

#include <stdlib.h>
#include <string.h>
  
///--------------------------
void* Pid_create(float* Input,float* Output,float* Setpoint,float Kp, float Ki, float Kd,int isRevrse)
{
    PID tempPID(Input, Output, Setpoint ,Kp, Ki, Kd, isRevrse);
    void* p = malloc(sizeof(tempPID));    
    memcpy(p,&tempPID,sizeof(tempPID));
    return p;
}

int Pid_compute(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->Compute();
}

void Pid_setTunings(void* pid,float Kp, float Ki, float Kd)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetTunings(Kp ,Ki, Kd);
}

void Pid_setSampleTime(void* pid,int NewSampleTime)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetSampleTime(NewSampleTime);
}

void Pid_SetOutputLimits(void* pid,float Min, float Max)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetOutputLimits(Min,Max);
}

void Pid_SetMode(void* pid,int Mode)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetMode(Mode);
}

void Pid_SetControllerDirection(void* pid,int inRevrse)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetControllerDirection(inRevrse);
}

void Pid_SetAlgorithm(void* pid,int isPositional)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetAlgorithm(isPositional);
}

void Pid_SetFilter(void* pid,float filter)
{
    PID* tempPID = (PID*)pid;
    tempPID->SetFilter(filter);
}

float Pid_GetKp(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->GetKp();
}   

float Pid_GetKi(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->GetKi();
}

float Pid_GetKd(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->GetKd();
}

int Pid_isAuto(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->isAuto();
} 

int Pid_isRevrse(void* pid)
{
    PID* tempPID = (PID*)pid;
    return tempPID->isRevrse();
}

