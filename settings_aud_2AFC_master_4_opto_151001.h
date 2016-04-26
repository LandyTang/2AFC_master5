// Settings for audi_2afc_cued_1.ino

#ifndef settings_user_anm01_h
#define settings_user_anm01_h

#define maxNumTrials 600
// ============================================================
// Rig and animal ID
// ============================================================
const char rig_name[] = "rig4";
const char animalName[] = "sc06";

// ============================================================
// Trial type Settings
// ============================================================
// const int maxNumTrials = 500;
char TrialSideType[] = "RandSide"; //"UserDefine"; //"BlockOdd"; //"RandSide"
const int maxSameSides =3;
const int leftProb = 50; // 50% of trials are left side.
const int ledControl = 1;  //mask; led_Pin 25
// const int optoStimTrial_frac =100;

int n_error_stay = 0;  // 

//Userdefine trials setting
int isRandomSides = 1;
int userDefinedSide = 0; //0 for left trials, 1 for right trials
/*const byte LEFT=0;
const byte RIGHT=1;
const byte MISS=1;*/

// 1, right side; 0, left side

//BlockOdd trials settings
byte BlockLocalNum = 10; //number of repeated same side trials
byte BlockOddNum = 2; //number of different side trials after same side trials
byte BlockGlobalSide = 0; // define the side of the global trials (the same side trials)

const int probeOptoTrial_frac = 50;
const int TrainingOptoTrial_frac =50;
const int probeTrial_frac = 50; // fraction of probe trials: 25% .



// ============================================================
// Cue parameters
// ============================================================
const int post_cue_stim_delay = 0; // delay time after cue and before stimulus
const int preStim_cue_frac = 0; // % of trials with pre-stimulus cues
const char preStim_cue_type[] = "noise"; 
const uint16_t preStim_cue_noise_band[2] = {3000, 40000};
const int preStim_cue_dur = 100; // in ms.
const int preStim_cue_onset_range[2] = {500, 2000};
const int preStim_cue_vol = 150;

// ============================================================
// Stimulus properties
// ============================================================ 


const int stimDur = 300;
byte vol[2] = {160,160};
const int vol_deviation = 0;

// pure tone
char stim_Type[] = "pureTone"; // "noise";// "pureTone";//"sweep";//randompureTone; //"2ToneSteps";
const uint16_t fq_pureTone[2] = {4000, 10000};//{16000, 22000}; //

// reference tone
const uint16_t referenceTones[2] = {10000, 17700};
const uint16_t testTones_hi[2] = {14000, 28000};
const uint16_t testTones_lo[2] = {7000, 14000};
const uint16_t toneInterval = 500;

const int Refer_stimDur = 600;
const uint16_t ranTone_left[3] = {6500, 7500, 8500};
const uint16_t ranTone_right[3] = {12500, 13500, 15500};
// noise
const uint16_t fq_noise_lo[]={6000, 12000};
const uint16_t fq_noise_hi[]={12000, 24000};
// sweep
const uint16_t fq_sweep_lo[] ={6000,12000};
const uint16_t fq_sweep_hi[] ={12000,24000};

//following settings will be used for SAM tone stimulus
int unit_dur = 2; //min time for each tone pips.
const uint16_t carrier_wave_freq = 10;
const double modu_depth = 0.001;


// ============================================================
// Probe trial parameters
// ============================================================
const int probe_sound_vol = 160;
char probe_stimType[] = "pureTone"; //"pureTone"; // "noise"; // "sweep"

//const uint16_t fq_pureTone_probe[6] ={9756,11888,14492,17665,21534,26250};
const uint16_t fq_pureTone_probe[4] ={11888,17665,21534,26250};
const uint16_t fq_pureTone_probe_left[3] ={17000,18000,19000};
const uint16_t fq_pureTone_probe_right[3] ={14000,15000,16000};

const uint16_t probe_noise_lo[2] = {1300, 1500};
const uint16_t probe_noise_hi[2] = {1200, 1600};

const uint16_t probe_sweep_lo[2] = {2100, 2200};
const uint16_t probe_sweep_hi[2] = {2300, 2400};


// ============================================================
// Reward parameters
// ============================================================
// const int isRandomReward = 0;
// const int isUserDefineBoundtryReward = 1;
const int RewardType = 1;
const int leftWaterValveDuration =  20;
const int rightWaterValveDuration = 20;

const byte LEFT = 0;
const byte RIGHT = 1;
const byte MISS = 2;

// ============================================================
// Timing parameters
// ============================================================
const int answerPeriod = 2000; // time when response can be accepted after stimulus.
const int gracePeriod = 0; // A random delay + a fixed delay before sound stimulation.
int stimOnsetRange[2] = {500, 1000};

const int waterValveDelay = 0;//temporally unused
const int responseDelay =0; // Delay after stimulus, where licking doens't count. Put responseDelay to 0, if want to test reaction time, but only after well trained.
const int ExtraITIDur = 1000; // this should be 0 if there are probe trials.

const int interTrialInterval = 2000;
const int drinkPeriod = 2000;

const int errorLedDur = 0; 
const int errorAirDur =0 ;
//============================================================
// opto After Answer timing parameters
//============================================================
/*char optoTime[] ="AfterAns"; //"BeforeSound";//"AfterAns";// "AfterSound" //"magnet_on" 
char userDefinedOptoSide[]="BOTH";// "RIGHT"//"BOTH"//"LEFT"
#define optoStim_duration (unsigned long)(0)

//set below parameners to ZERO
const int magnet_duration =0;   //xinyu
const int pre_trg_delay=0; // pre_trg_delay means pre-laser delay , only used in aftersound type opto stimulus
const int opto_PreSound_delay = 0;  //rand_stimOnset > = opto_PreSound_delay*/
//============================================================
// opto Before Sound timing parameters
//============================================================
char optoTime[] ="BeforeSound";
char userDefinedOptoSide[]="BOTH";// "RIGHT"//"BOTH"//"LEFT"
const int opto_PreSound_delay = 100;  //rand_stimOnset > = opto_PreSound_delay
#define optoStim_duration (unsigned long)(2000)

//set below parameners to ZERO
const int magnet_duration =0;   //xinyu
const int pre_trg_delay=0; // pre_trg_delay means pre-laser delay 
//============================================================
// opto After Sound timing parameters
//============================================================
/*char optoTime[] ="AfterSound";
char userDefinedOptoSide[]="BOTH";// "RIGHT"//"BOTH"//"LEFT"
#define optoStim_duration (unsigned long)(2000)
const int pre_trg_delay=50; // pre_trg_delay means pre-laser delay 

//set below parameners to ZERO
const int magnet_duration =0;   //xinyu
const int opto_PreSound_delay = 0;  //rand_stimOnset > = opto_PreSound_delay*/

// Optical stimulation parameters
// ============================================================
// 50% of trials giving optic stimulation
#define multi_pulse 0
#define single_pulse 1
const byte optoStimType = multi_pulse; // 0: multiple pulses
const uint16_t pulse_width = 5; // in ms
const float pulse_freq = 40; // in Hz


// const uint16_t optoStim_duration = 1000; // total duration of optic stimulation
//#define optoStim_duration (unsigned long)(preSound_time+stimDur+responseDelay+answerPeriod)
//const int opto_side  = 0; // 0"LEFT"; 1"RIGHT"
//const uint16_t optoStim_postTrial_time = 1000; 
#endif
//==========================================================================

