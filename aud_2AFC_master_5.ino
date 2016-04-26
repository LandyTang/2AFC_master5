// #include "/home/lab/NAS/LabShare_NAS/Lab_Members/Tang_YY/2AFC_master_5/settings_aud_2AFC_master_4_opto_151001.h"
#include "/home/xulab/behavior_rig_06/behavior_data_rig_06/zzk/C57_3/Settings/settings_aud_2AFC_master_5_C57_3_20160419.h"
#include <SPI_TGM.h>
#include <SPLC.h>
#include <RCM.h>
#include <Wire.h>
#include <SPI.h>
#include <Pulse.h>
#include "CACHE.h" 

#include <SGL.h>
#include <SSD1331.h>
#include <SSD1331_S_SHOW.h>

#define leftWaterPort 11
#define rightWaterPort 12
//#define initButtonPin 39  //zl
#define initButtonPin 8
#define LeftLickPin 2 
#define RightLickPin 3
#define pauseButtonPin 38
// #define StimOutPin 9//#define led_lick_left 6// #define LedControlOutPin 7//#define punishment_air 7
#define punishment_air  45
// manual water delivery sensor pins
#define man_water_left 4
#define man_water_right 5

#define man_water_L 27
#define man_water_R 25

#define triggerPin 9
#define punishment_led 29
#define TriggerOutPin 36
#define LaserOutPin 41
#define led_Pin 25
// add pin for magnet 
#define Magnet_Pin 42  //  need to be comfirm 

//pinMode(man_water_left,INPUT);
//digitalWrite(man_water_left,LOW);


char oled_string0[16];
// #define pulse_dur 499// #define pusle_fq 20// #define pulse_width 10
byte currentSide = 1;
byte choice =3;
unsigned int clockSyncTime;
unsigned long trialStartMillis; // For offsetting trial events times.

String trialStartTime; // Trial start absolute time.
String sessionStartTime;

unsigned long stimOnTime;
unsigned long responseTime;
unsigned long waterValveOpenTime;
unsigned long optoStim_onset;
unsigned long optoStim_offTime;
unsigned long led_onset;
unsigned long led_offTime;
unsigned long RewardTime;






byte  lickCountLeft = 0;
byte  lickCountRight = 0;
int trialCount = 0;
int randNumber;
int randNumber_1;
int randNumber_2;
int randNumber_3;
byte doExtraITI;
int cueOnTime;
volatile int answer = 2;


//int lick_flag;
//volatile uint8_t  Trial_isOpto =9;// determine wether this trial is opto trial.

byte Correct = 3;
byte Wrong = 3;

// Initialize timing variables, to be set in setTimes()
int rand_stimOnset = 0;
int rand_cueOnset = 0;

// Store trial sides to an array
// int trialSides[maxNumTrials];
byte trialType[maxNumTrials];
byte isProbeTrial[maxNumTrials];
byte isOptoProbeTrial[maxNumTrials];
// byte preStim_cue_on[maxNumTrials];
byte isOptoTrainingTrial[maxNumTrials];
byte trialStart = 0;
byte trialEnd = 0;
// Sound intensity in DB, can be varied.
int toneFreq = 0;
int SPL_in_DB = 0;
int toneVolume = 0;

String lickTimeLeft;
String lickTimeRight;

uint32_t _millis_;
uint32_t _second_;
uint32_t _min_;
uint32_t _hour_;
uint32_t _date_;
uint32_t _month_;
uint32_t _year_;
uint32_t _init_second_;
uint32_t _init_min_;
uint32_t _init_hour_;
uint32_t _init_date_;
uint32_t _init_month_;
uint32_t _init_year_;

String probe_param_str = "";
String stim_param_str = "";

void setRandomTimes() {
  rand_stimOnset = random(stimOnsetRange[0], stimOnsetRange[1]);
  rand_cueOnset = random(preStim_cue_onset_range[0], preStim_cue_onset_range[1]);
}

void init_time(){
  RCM.init();
  byte temp_cm_sec = RCM.second();
  while(temp_cm_sec == RCM.second());
  // timer0_millis = 0;
  clockSyncTime = millis();
  _init_second_= RCM.second();
  _init_min_= RCM.minute();
  _init_hour_= RCM.hour();
  _init_date_= RCM.date();
  _init_month_= RCM.month();
  _init_year_ = RCM.year();
  _year_ = _init_year_;
  _month_ = _init_month_;
  _date_ = _init_date_;  
}

void realtime(){
  uint32_t temp_millis = millis() - clockSyncTime; 
  uint32_t temp_sec = temp_millis /1000;
  uint32_t temp_min = temp_sec/60;
  uint32_t temp_hour = temp_min/60;
  _second_ = _init_second_ + temp_sec;
  _min_ = _init_min_ + (_second_ / 60);
  _hour_ =  _init_hour_ + (_min_ / 60);
  _second_ = _second_ % 60;
  _min_ = _min_ % 60;
  _hour_ = _hour_ % 24;
  _millis_ = temp_millis % 1000;
}

void print_settings() {
  Serial.print("Rig_name = ");
  Serial.println(rig_name);
  
  Serial.print("animalName = ");
  Serial.println(animalName);

  Serial.print("sessionStartTime = ");
  Serial.println(sessionStartTime);

  Serial.print("maxNumTrials = ");
  Serial.println(maxNumTrials);
  Serial.print("maxSameSides = ");
  Serial.println(maxSameSides);

  Serial.print("Error_stay_number = ");
  Serial.println(n_error_stay);
  
  Serial.print("leftProb = ");
  Serial.println(leftProb);
  
  Serial.print("leftWaterValveDuration = ");
  Serial.println(leftWaterValveDuration);
  
  Serial.print("rightWaterValveDuration = ");
  Serial.println(rightWaterValveDuration);
  
  Serial.print("waterValveDelay = ");
  Serial.println(waterValveDelay);


  Serial.print("responseDelay = ");
  Serial.println(responseDelay);

  Serial.print("answerPeriod = ");
  Serial.println(answerPeriod);
  
  Serial.print("gracePeriod = ");
  Serial.println(gracePeriod);
  
  Serial.print("ExtraITIDur = ");
  Serial.println(ExtraITIDur);
  
  Serial.print("DrinkPeriod = ");
  Serial.println(drinkPeriod);

  Serial.print("interTrialInterval = ");
  Serial.println(interTrialInterval);

  Serial.print("userDefinedOptoSide = ");
  Serial.println(userDefinedOptoSide);
 
  if (strcmp(optoTime, "BeforeSound") == 0){
   Serial.print("optoTime = ");
   Serial.println(optoTime);
   Serial.print("PreSound_delay = ");//rand_stimOnset > = opto_PreSound_delay
   Serial.println(opto_PreSound_delay);
  }
  if (strcmp(optoTime, "AfterAns") == 0){
   Serial.print("optoTime = ");
   Serial.println(optoTime);
  }
  if (strcmp(optoTime, "AfterSound") == 0){
   Serial.print("optoTime = ");
   Serial.println(optoTime);
   Serial.print("pre_Sound_delay = "); // pre_trg_delay means pre-laser delay , only used in aftersound type opto stimulus
   Serial.println(pre_trg_delay);
  }

  if (strcmp(optoTime, "magnet_on") == 0){
   Serial.print("optoTime = ");
   Serial.println(optoTime);
   Serial.print("magnet_duration = ");
   Serial.println(magnet_duration);
  }

  
  if (strcmp(stim_Type, "pureTone") == 0)
  {
    Serial.print("toneFreq_L = ");
    Serial.println(fq_pureTone[0]); 
    Serial.print("toneFreq_R = ");
    Serial.println(fq_pureTone[1]); 
  }
  else if (strcmp(stim_Type, "noise") == 0)
  {
    Serial.print("noiseBand_L = ");
    Serial.print(fq_noise_lo[0]);Serial.print("\t"); 
    Serial.println(fq_noise_hi[0]);
    Serial.print("noiseBand_R = ");
    Serial.print(fq_noise_lo[1]);Serial.print("\t"); 
    Serial.println(fq_noise_hi[1]);
  }

  else if (strcmp(stim_Type, "sweep") == 0)
  {
    Serial.print("sweepRange_L = ");
    Serial.print(fq_sweep_lo[0]);Serial.print("\t"); 
    Serial.println(fq_sweep_hi[0]);
    Serial.print("sweepRange_R = ");
    Serial.print(fq_sweep_lo[1]);Serial.print("\t"); 
    Serial.println(fq_sweep_hi[1]);
  }

  else if (strcmp(stim_Type, "randompureTone") == 0)
  {
    Serial.print("randompureTone_L= ");
    Serial.print(ranTone_left[0]);Serial.print("\t"); 
    Serial.print(ranTone_left[1]);Serial.print("\t");
    Serial.println(ranTone_left[2]);   //Serial.print("\t"); Serial.print(":"); 
    Serial.print("randompureTone_R= ");
    Serial.print(ranTone_right[0]);Serial.print("\t"); 
    Serial.print(ranTone_right[1]);Serial.print("\t"); 
    Serial.println(ranTone_right[2]);
  }

  Serial.print("frac_TrainingOptoTrial = ");
  Serial.println(TrainingOptoTrial_frac);

  Serial.print("Frac_Probe_Trials = ");
  Serial.println(probeTrial_frac);

  Serial.print("probeOptoTrial_frac = ");
  Serial.println(probeOptoTrial_frac); 

  Serial.print("Probe_RewardType = ");
  Serial.println(RewardType);

  Serial.print("probe_stimType = ");
  Serial.println(probe_stimType);

   Serial.print("freqProbe_L = ");
   Serial.println(fq_pureTone_probe[0]);
   Serial.print("freqProbe_R = ");
   Serial.println(fq_pureTone_probe[1]);
  

  Serial.print("stimDuration = ");
  Serial.println(stimDur);
  Serial.print("preStim_cue_frac = ");
  Serial.println(preStim_cue_frac);
  // Serial.print("optoStimTrial_frac = ");
  // Serial.println(optoStimTrial_frac);


  Serial.println("###################");

}

int define_trial_types(int leftProb, int probeTrial_frac, int probeOptoTrial_frac) {
  
  // int trialType[maxNumTrials];
  // int isProbeTrial[maxNumTrials];
  // int preStim_cue_on[maxNumTrials];

  int right_count = 0;
  int left_count = 0;
  int consecutive_probe_trial_count = 0;
  int consecutive_cued_trial_count = 0;
  int tempval = 0;

  int i = 0;

  while (i < maxNumTrials) {
  randNumber = random(0, 100); // put a random number between 0 and 100 to the array
  if (randNumber < leftProb) {
    right_count = 0;
    left_count = left_count++;
    if (left_count <= maxSameSides) {
      trialType[i] = LEFT;
      i = i++;
    }
  }
  else {
    left_count = 0;
    right_count = right_count++;
    if (right_count <= maxSameSides) {
      trialType[i] = RIGHT;
      i = i++;
    }
  }

}

i = 0;
while (i < maxNumTrials) {
  randNumber = random(0, 100);

  if (randNumber < probeTrial_frac) {
    consecutive_probe_trial_count = consecutive_probe_trial_count ++;
    if (consecutive_probe_trial_count < 2) {
      isProbeTrial[i] = 1;
      i = i++;
    }
  }
  else {
    isProbeTrial[i] = 0;
    consecutive_probe_trial_count = 0;        
    i = i ++;
  }
}

i=0;
while (i < maxNumTrials) {
  randNumber_2 = random(0, 100);

  if (randNumber_2 < probeOptoTrial_frac) {
    
   
      isOptoProbeTrial[i] = 1;
      i = i++;
    
  }
  else {
    isOptoProbeTrial[i] = 0;
       
    i = i ++;
  }
}



}
// Serial.print( isProbeTrial[trialCount] );
void define_Optotrial_types( int TrainingOptoTrial_frac){
int i = 0;

while (i < maxNumTrials) {
  randNumber_2 = random(0, 100);
  if (randNumber_2 < TrainingOptoTrial_frac) { 
      isOptoTrainingTrial[i] = 1;
      i = i++;
  }
  else{      
      isOptoTrainingTrial[i] = 0;       
      i = i ++;
    }
}
}


 int sendTrialStartPulse() {
  // digitalWrite(LED, HIGH);
  // delayMicroseconds(100);
  // digitalWrite(LED, LOW);
  lickCountLeft = 0;
  lickCountRight = 0;
  lickTimeLeft = "|";
  lickTimeRight = "|"; 

  realtime();
  trialStartTime = String(_year_);
  trialStartTime += "_";
  trialStartTime += String(_month_);
  trialStartTime += "_";
  trialStartTime += String(_date_);
  trialStartTime += "_";
  trialStartTime += String(_hour_);
  trialStartTime += "_";
  trialStartTime += String(_min_);
  trialStartTime += "_";
  trialStartTime += String(_second_);
  trialStartTime += "_";
  trialStartTime += String(_millis_);
  trialStartMillis = millis() - clockSyncTime;
  stimOnTime = 0;
  responseTime = 0;
  waterValveOpenTime = 0;
  RewardTime = 0;
  optoStim_offTime = 0;
  optoStim_onset = 0;
  //lick_flag=0; 
  

  probe_param_str = "";
  probe_param_str += "/Stim_Probe_stimType=";
  probe_param_str += probe_stimType;

  stim_param_str = "";

  Serial.print("\nTrial_Start....................#");
  Serial.print(trialCount + 1);
  Serial.println("\t");
    
}

uint32_t trial_millis(){
  return millis() - trialStartMillis - clockSyncTime;
}

// led mask stimulus delivery
void ledStimDelivery(int ledStimType){
  if(ledStimType == 1){
      led_onset = trial_millis();
      PULSE.p2_sqr_wave(led_Pin,10000,40,10,TRG_H);
  }
  if(ledStimType == 0){
      led_offTime = trial_millis();
      PULSE.p2_cancel();
  }
}
// opto delivery function in prob trails
void optoProbeStimDelivery(byte isProbe) {   
	if (strcmp(optoTime, "BeforeSound") == 0) {
    SSD1331_S_SHOW.show_line(3,"Light "); 
    SSD1331_S_SHOW.show_line(2,"StimOn");
		delay(rand_stimOnset - opto_PreSound_delay);  //
		optoStimDelivery(optoStimType); // Light stimulation only in probe trials. 
		delay(opto_PreSound_delay);
		SoundDelivery(isProbe); // sound stimulus
	
	}
	else if (strcmp(optoTime, "AfterSound") == 0) {
    SSD1331_S_SHOW.show_line(2,"StimOn");
    SSD1331_S_SHOW.show_line(3,"Light "); 
		delay(rand_stimOnset);
   if (optoStimType == 0) {
      optoStim_onset = trial_millis()+pre_trg_delay;
      PULSE.p2_sqr_wave(LaserOutPin, optoStim_duration, pulse_freq, pulse_width, TRG_H, pre_trg_delay);
      optoStim_offTime = optoStim_onset + optoStim_duration;
   }
    
   if (optoStimType == 1) {
      optoStim_onset = trial_millis()+pre_trg_delay;
      float pulse_freq = (float)1000 / 2 / (float)optoStim_duration;
      PULSE.p2_sqr_wave(LaserOutPin, optoStim_duration, pulse_freq, pulse_width, TRG_H, pre_trg_delay); 
      optoStim_offTime = optoStim_onset + optoStim_duration;
   }
   SoundDelivery(isProbe); // sound stimulus
	}

	else if (strcmp(optoTime, "AfterAns") == 0){
    SSD1331_S_SHOW.show_line(2,"StimOn");
    SSD1331_S_SHOW.show_line(3,"Light "); 
    delay(rand_stimOnset);
    SoundDelivery(isProbe); 
	}

  else if (strcmp(optoTime, "magnet_on") == 0){
   digitalWrite(Magnet_Pin, HIGH);
   delay(magnet_duration);  // greater than 4ms 
   digitalWrite(Magnet_Pin,LOW);
  }
}

// opto delivery function in trails
void optoStimDelivery(int optoStimType) {
    
  if (optoStimType == 0) {
  	optoStim_onset = trial_millis();
    PULSE.p2_sqr_wave(LaserOutPin, optoStim_duration, pulse_freq, pulse_width, TRG_H);  
    optoStim_offTime = optoStim_onset + optoStim_duration;
  }
  if (optoStimType == 1) {
      optoStim_onset = trial_millis();
     PULSE.p1_pulse(LaserOutPin,optoStim_duration,TRG_H);
    optoStim_offTime = optoStim_onset + optoStim_duration;
  }
  if (optoStimType == 2) { 
  	optoStim_onset = trial_millis();
    PULSE.p1_cancel();
    optoStim_offTime = trial_millis();
  } 
}

// probe trail sound stimulus delivery 
void probeSoundStimDelivery() {
	  int probeToneFreq;
    int nProbe_sounds;
   // SSD1331_S_SHOW.show_line(2,"Stim On"); 
    
 
    if (strcmp(probe_stimType, "pureTone") == 0){  // ???????????????????????????
        if (currentSide==0){
          nProbe_sounds = sizeof(fq_pureTone_probe_left) / sizeof(fq_pureTone_probe_left[0]);
          probeToneFreq = fq_pureTone_probe_left[random(0,nProbe_sounds)];
         }
        if(currentSide==1){       
          nProbe_sounds = sizeof(fq_pureTone_probe_right) / sizeof(fq_pureTone_probe_right[0]);
          probeToneFreq = fq_pureTone_probe_right[random(0,nProbe_sounds)];
        }        
        // Play pure tone  
        stimOnTime = trial_millis(); 
        SPI_TGM.quick_tone_vol_cosramp_5ms(stimDur, probeToneFreq, probe_sound_vol);
        delay(stimDur);  //???????
      //  SSD1331_S_SHOW.show_line(2,"StimOn");

        Serial.print("\nProbe Pure Tone Freq--------------: ");
        Serial.println(probeToneFreq);
        Serial.print("setVolume = ");   
        Serial.println(probe_sound_vol);

        probe_param_str += "/Stim_Type=";
        probe_param_str += String(probe_stimType);
        probe_param_str += "/Stim_toneFreq=";
        probe_param_str += String(probeToneFreq);    
        probe_param_str += "/Stim_setVolume=";
        probe_param_str += String(probe_sound_vol);
        probe_param_str += "/stimDuration=";
        probe_param_str += String(stimDur);
     }   

    if (strcmp(probe_stimType, "noise") == 0){      
        int nProbe_sounds = sizeof(probe_noise_lo) / sizeof(probe_noise_lo[0]);
        int fq_lo = 0;
        int fq_hi = 0;
        int noiseID = random(0,nProbe_sounds);

        fq_lo = probe_noise_lo[noiseID];
        fq_hi = probe_noise_hi[noiseID];
        Serial.print("\nProbe Noise Freq--------------: ");
        Serial.print(fq_lo);Serial.print("\t"); 
        Serial.println(fq_hi);
        Serial.print("Volume = ");   
        Serial.println(probe_sound_vol);

        stimOnTime = trial_millis();
        SPI_TGM.quick_noise_cosramp_5ms(stimDur, fq_lo, fq_hi, probe_sound_vol, SWEEP_NOISE_WHITE);   
        delay(stimDur); 
        //SSD1331_S_SHOW.show_line(2,"StimOn");       

        probe_param_str += "/Stim_Type=";
        probe_param_str += String(probe_stimType);
        probe_param_str += "/Stim_noiseBand_lo=";
        probe_param_str += String(fq_lo);
        probe_param_str += "/Stim_noiseBand_hi=";
        probe_param_str += String(fq_hi);
        probe_param_str += "/Stim_setVolume=";
        probe_param_str += String(probe_sound_vol);
        probe_param_str += "/stimDuration=";
        probe_param_str += String(stimDur);          
    }

    if (strcmp(probe_stimType, "sweep") == 0){

          int nProbe_sounds = sizeof(probe_sweep_lo) / sizeof(probe_sweep_lo[0]);
          int fq_on = 0;
          int fq_off = 0;
          int sweepID = random(0,nProbe_sounds);

          fq_on = probe_sweep_lo[sweepID];
          fq_off = probe_sweep_hi[sweepID];
        
          Serial.print("\nProbe Sweep Freq--------------: ");
          Serial.print(fq_on);Serial.print("\t"); 
          Serial.println(fq_off);
          Serial.print("Volume = ");   
          Serial.println(probe_sound_vol);

          stimOnTime = trial_millis();
          SPI_TGM.quick_sweep_exp_cosramp_5ms(stimDur, fq_on, fq_off, probe_sound_vol);
          delay(stimDur);  
        //  SSD1331_S_SHOW.show_line(2,"StimOn");

          probe_param_str += "/Stim_Type=";
          probe_param_str += String(probe_stimType);
          probe_param_str += "/Stim_SweepOnsetFreq=";
          probe_param_str += String(fq_on);
          probe_param_str += "/Stim_SweepOffsetFreq=";
          probe_param_str += String(fq_off);
          probe_param_str += "/Stim_setVolume=";
          probe_param_str += String(probe_sound_vol);
          probe_param_str += "/stimDuration=";
          probe_param_str += String(stimDur);
      
      } 
}

void soundStimDelivery(int trialCount, int currentSide, char* stim_type) {
  	//stimOnTime = trial_millis();// Play sound stimulus  

    if (strcmp(stim_type, "pureTone") == 0){     

        toneVolume = vol[currentSide]; 
        toneFreq = fq_pureTone[currentSide];
      
        Serial.print("\nTone Freq--------------: ");
        Serial.println(toneFreq);
        Serial.print("setVolume = ");   
        Serial.println(toneVolume);  

        stimOnTime = trial_millis();
        SPI_TGM.quick_tone_vol_cosramp_5ms(stimDur, toneFreq, toneVolume);
        delay(stimDur);


        stim_param_str += "/Stim_Type=";
        stim_param_str += String(stim_type);
        stim_param_str += "/Stim_toneFreq=";
        stim_param_str += String(toneFreq);
        stim_param_str += "/Stim_setVolume=";
        stim_param_str += String(toneVolume);
        stim_param_str += "/stimDuration=";
        stim_param_str += String(stimDur); //??????????????

     }   
    if (strcmp(stim_type, "noise") == 0){
    
        int fq_lo = 0;
        int fq_hi = 0;

          if (currentSide == LEFT){ // upward sweeps
            fq_lo = fq_noise_lo[0];
            fq_hi = fq_noise_hi[0];
          }
          if (currentSide == RIGHT){ // downward sweeps
            fq_lo = fq_noise_lo[1];
            fq_hi = fq_noise_hi[1];
          }

          stimOnTime = trial_millis();
          SPI_TGM.quick_noise_cosramp_5ms(stimDur, fq_lo, fq_hi,vol[currentSide], SWEEP_NOISE_WHITE);
          delay(stimDur);

          Serial.print("\nNoise Freq--------------: ");
          Serial.print(fq_lo);Serial.print("\t"); 
          Serial.println(fq_hi);
          Serial.print("setVolume = ");   
          Serial.println(vol[currentSide]);
          stim_param_str += "/Stim_Type=";
          stim_param_str += String(stim_type);
          stim_param_str += "/Stim_noiseBand_lo=";
          stim_param_str += String(fq_lo);
          stim_param_str += "/Stim_noiseBand_hi=";
          stim_param_str += String(fq_hi);
          stim_param_str += "/Stim_setVolume=";
          stim_param_str += String(vol[currentSide]);
          stim_param_str += "/stimDuration=";
          stim_param_str += String(stimDur);
    }
    if (strcmp(stim_type, "sweep") == 0){

          int fq_on = 0;
          int fq_off = 0;

          if (currentSide == LEFT){ // upward sweeps
            fq_on = fq_sweep_lo[0];
            fq_off = fq_sweep_hi[0];
          }
          if (currentSide == RIGHT){ // downward sweeps
            fq_on = fq_sweep_lo[1];
            fq_off = fq_sweep_hi[1];
          }

          stimOnTime = trial_millis();
          SPI_TGM.quick_sweep_exp_cosramp_5ms(stimDur, fq_on, fq_off, vol[currentSide]);
          delay(stimDur);

          Serial.print("\nSweep Freq--------------: ");
          Serial.print(fq_on);Serial.print("\t"); 
          Serial.println(fq_off);
          Serial.print("setVolume = ");   
          Serial.println(vol[currentSide]);
          stim_param_str += "/Stim_Type=";
          stim_param_str += String(stim_type);
          stim_param_str += "/Stim_SweepOnsetFreq=";
          stim_param_str += String(fq_on);
          stim_param_str += "/Stim_SweepOffsetFreq=";
          stim_param_str += String(fq_off);
          stim_param_str += "/Stim_setVolume=";
          stim_param_str += String(vol[currentSide]);
          stim_param_str += "/stimDuration=";
          stim_param_str += String(stimDur);

        }
      if (strcmp(stim_type, "randompureTone") == 0){
          int vol_side[] = {0, 0};        
          toneVolume = vol[currentSide] + random(0, vol_deviation);

          if (currentSide == LEFT){ // upward sweeps
            toneFreq = ranTone_left[random(0,3)];
          }
          if (currentSide == RIGHT){ // downward sweeps
           toneFreq = ranTone_right[random(0,3)];
          }

          stimOnTime = trial_millis();
          SPI_TGM.quick_tone_vol_cosramp_5ms(stimDur, toneFreq, toneVolume);
          delay(stimDur);

          Serial.print("\nTone Freq--------------: ");
          Serial.println(toneFreq);
          Serial.print("setVolume = ");   
          Serial.println(toneVolume);
          stim_param_str += "/Stim_Type=";
          stim_param_str += String(stim_type);
          stim_param_str += "/Stim_toneFreq=";
          stim_param_str += String(toneFreq);
          stim_param_str += "/Stim_toneIntensity=";
          stim_param_str += String(SPL_in_DB);
          stim_param_str += "/Stim_setVolume=";
          stim_param_str += String(vol[currentSide]);
          stim_param_str += "/stimDuration=";
          stim_param_str += String(stimDur);
        }

      if (strcmp(stim_type, "2ToneSteps") == 0){
        stim_param_str += "/Stim_Type=";
        stim_param_str += String(stim_type);
        two_tone_step(currentSide);
      }

} 

void two_tone_step(int currentSide) {

  int nRef_Tones = sizeof(referenceTones) / sizeof(referenceTones[0]);
  int randID = random(0,nRef_Tones);
  int currentRefTone = referenceTones [randID];
  //int randID = random(0,2);
  uint16_t currentTestTone = 0;
  //uint16_t referenceTone = 0;  //??????????????????
  //uint16_t currentRefTone = 0;
  toneVolume = vol[currentSide];
  if (currentSide == LEFT) {
    currentTestTone = testTones_lo [ randID ];
  }
  if (currentSide == RIGHT) {
      currentTestTone = testTones_hi [ randID ];
  }
  Serial.print("playing reference tone -------- ");
  Serial.println(currentRefTone);

  stimOnTime = trial_millis();
  SPI_TGM.quick_tone_vol_cosramp_5ms(stimDur, currentRefTone, toneVolume);
  delay(stimDur + toneInterval);
  Serial.print("playing test tone -------- ");
  Serial.println(currentTestTone);
  SPI_TGM.quick_tone_vol_cosramp_5ms(stimDur, currentTestTone, toneVolume);
 
  stim_param_str += "/Stim_RefTone=";
  stim_param_str += String(currentRefTone);
  stim_param_str += "/Stim_TestTone=";
  stim_param_str += String(currentRefTone);
  stim_param_str += "/Stim_toneIntensity=";
  stim_param_str += String(SPL_in_DB);
  stim_param_str += "/Stim_setVolume=";
  stim_param_str += String(vol[currentSide]);
  stim_param_str += "/stimDuration=";
  stim_param_str += String(stimDur);
}

// Reward Section
void rewardDelivery(int rewardSide) {
  if (rewardSide == 1) {
    RewardTime = trial_millis();
    digitalWrite(rightWaterPort, HIGH);
    delay(rightWaterValveDuration);
    digitalWrite(rightWaterPort, LOW);
   // Serial.println("rightWaterPort_rewardDelivery");
  }
  else if (rewardSide == 0) {

  	RewardTime = trial_millis();
    digitalWrite(leftWaterPort, HIGH);
    delay(leftWaterValveDuration);
    digitalWrite(leftWaterPort, LOW);
    //Serial.println("leftWaterPort_rewardDelivery");

  }
}


// Punishment section, currently only use extra ITI.
void punishmentSection(int doExtraITI) {
  unsigned long ExtraITIStart;
  unsigned long eITI_passed;

  if (doExtraITI == 1) {

    ExtraITIStart = millis();
    eITI_passed = 0;
    answer = MISS;

    while (eITI_passed < ExtraITIDur) {
      eITI_passed = (millis() - ExtraITIStart);
      if (answer == Wrong) {
        error_led();
        eITI_passed = 0;
        ExtraITIStart = millis();
        answer = MISS;
      }
    }
    digitalWrite(punishment_led, LOW);
    digitalWrite(punishment_air, LOW);
  }
}

void OnLickLeft() {
  answer = LEFT;
  lickCountLeft ++;
  lickTimeLeft += "|";
  lickTimeLeft += String(trial_millis());

}


void OnLickRight() {
  answer = RIGHT;
  lickCountRight ++;
  lickTimeRight += "|";
  lickTimeRight += String(trial_millis());
}

void sendOutResults() {
  int deadTime = 1000;
  char* stimType_str;
  delay(deadTime);
  
  Serial.print("o");
  Serial.print("/Trial_Num=");
  Serial.print(trialCount + 1);
  Serial.print("/Trial_Type=");
  Serial.print(currentSide);
  Serial.print("/Trial_GPeriod=");
  Serial.print(gracePeriod);
  Serial.print("/Trial_isProbeTrial=");
  Serial.print(isProbeTrial[trialCount]);
  
  Serial.print(stim_param_str);
  Serial.print(probe_param_str);

  Serial.print("/Time_randStimOnset=");
  Serial.print(rand_stimOnset);

  if(isProbeTrial[trialCount] ==1){
    Serial.print("/Trial_isOptoProbeTrial=");
    Serial.print(isOptoProbeTrial[trialCount]);
    Serial.print("/Trial_isOptoTraingTrial=");
    Serial.print(0);
    }
  else {
    Serial.print("/Trial_isOptoProbeTrial=");
    Serial.print(0);
    Serial.print("/Trial_isOptoTraingTrial=");
    Serial.print(isOptoTrainingTrial[trialCount]);
   }

  if ((isProbeTrial[trialCount]+isOptoProbeTrial[trialCount])==2 || (isOptoTrainingTrial[trialCount]>isProbeTrial[trialCount])) 
  {  // opto trails
     Serial.print("/Trial_isOpto=1");
  }
  else{
     Serial.print("/Trial_isOpto=0");
  }
    


  Serial.print("/Time_trialStart=");
  Serial.print(trialStartTime);
  Serial.print("/Time_stimOnset=");
  Serial.print(stimOnTime);
  Serial.print("/Time_optoStimOnset=");
  Serial.print(optoStim_onset);
  Serial.print("/Time_optoStimOffTime=");
  Serial.print(optoStim_offTime);
  Serial.print("/Time_answer=");
  Serial.print(responseTime);
  Serial.print("/Time_reward=");
  Serial.print(RewardTime);
  // animal responses
  Serial.print("/Action_numLickLeft=");
  Serial.print(lickCountLeft);
  Serial.print("/Action_lickTimeLeft=");
  Serial.print(lickTimeLeft);

  Serial.print("/Action_numLickRight=");
  Serial.print(lickCountRight);
  Serial.print("/Action_lickTimeRight=");
  Serial.print(lickTimeRight);

  Serial.print("/Action_choice=");
  Serial.print(choice);
  Serial.println("/EOL");
  // print performance
  if (choice == Correct) {
    Serial.println("CORRECT!");
  }
  else if (choice == Wrong){
    Serial.println("ERROR!");
  }
  else {
    Serial.println("MISS!");
  }
}


void man_waterValve() {
  if (digitalRead(man_water_left) == HIGH ){//| digitalRead(man_water_L)==LOW) {
    // Open left water valve
    digitalWrite( leftWaterPort, HIGH);
    delay(leftWaterValveDuration);
    digitalWrite(leftWaterPort, LOW);
   // Serial.println("left_man_waterValve");

    delay (500);
  }
  if (digitalRead(man_water_right) == HIGH ){//| digitalRead(man_water_R)==LOW) {
    // Open right water valve
    digitalWrite( rightWaterPort, HIGH);
    delay(rightWaterValveDuration);
    digitalWrite(rightWaterPort, LOW);
  //  Serial.println("right_man_waterValve");
    delay(500);
  }
}

void drinkTime() {
  int drinkStart = millis();
  int timePassed = 0;
  while (timePassed < drinkPeriod) {
    timePassed = millis() - drinkStart;
  }
}

void choice_outcome_state() {
  // Start answer judgement
  unsigned long timePassed = 0;
  unsigned long timeAnswerStart = millis();
  
  int gracePeriod_onset = trial_millis();
  int gracePeriod_pass = 0;
  // Initialize answer value as MISS.// "answer" changes upon every lick, // use "choice" to record the final behavioral response.
  answer = MISS;
  choice = MISS; 
  // Enter Answer period
  while (timePassed < answerPeriod) {
    // Deliver water when manually press the sensors
    man_waterValve();

    timePassed = millis() - timeAnswerStart;

    if (answer != MISS) {
      //responseTime = trial_millis();
      if ((strcmp(optoTime, "AfterAns")==0) & ((isProbeTrial[trialCount]+isOptoProbeTrial[trialCount])==2 || (isOptoTrainingTrial[trialCount]>isProbeTrial[trialCount])))
      {
         optoStimDelivery(optoStimType);
       }
   
     //  Probe trials
     // if (isProbeTrial[trialCount] == 1) {
     //    choice = answer;
     //    delay(waterValveDelay);
     //    if (round(random(0, 100)/50) == 1) {
     //      rewardDelivery(choice);
     //      waterValveOpenTime = trial_millis();
     //    }
     //    // rewardDelivery(answer);
     //    break;
     //  }
      if (answer == Correct) {
        responseTime = trial_millis();
        delay(waterValveDelay);  //waterValveDelay=0
        rewardDelivery(Correct);
        SSD1331_S_SHOW.show_line(4,"Bingo!"); //ssd  //waterValveOpenTime = trial_millis();
        choice = Correct;
        drinkTime();
        break;
      }
      if (answer == Wrong) {
        responseTime = trial_millis();
        error_led(); // give feedback to animal of Wrong choice.
        SSD1331_S_SHOW.show_line(4,"Wrong!");//ssd,print at OLED line3
        gracePeriod_pass = trial_millis() - gracePeriod_onset;
        if (gracePeriod_pass > gracePeriod) {// Use extra ITI as punishment
              doExtraITI = 1;
              punishmentSection(doExtraITI);
              choice = Wrong; // This is for "Error Stay" training, // repeat the same side in the next n trials
              for (int counts=1; counts<=n_error_stay; counts++) {
                trialType[ trialCount + counts ] = currentSide;  
              }          
          break;
        }
      }
       // answer = getAnswers(answerPeriod);
    if (answer == 2) {
    // Miss! Do nonthing.
    SSD1331_S_SHOW.show_line(4,"MISS  ");//ssd
      }
      //lick_flag=0; 
    }
  }
}




void error_led() {
  digitalWrite(punishment_led, HIGH);
  delay(errorLedDur); 
  digitalWrite(punishment_led,LOW);

 digitalWrite(punishment_air, HIGH);
  delay(errorAirDur); 
  digitalWrite(punishment_air,LOW);
}

//sound delivery function
void SoundDelivery(byte isProbe){
//  Serial.println("SoundDelivery");
	if (isProbe>0){
		probeSoundStimDelivery(); 
		//delay(stimDur);
	}
	else {
    char* stimType_str = stim_Type; 
		soundStimDelivery(trialCount, currentSide, stimType_str);
		//delay(stimDur);
	}
}  

//total stimulus delivery function// add magnet stim in here 
void TotalStim(byte isProbe, byte isOptoProbe, byte isOptoTraining){                 // change here //Prob,byte isoptoControl){	// isoptotraining
      if ((isProbe+isOptoProbe)==2 || (isOptoTraining>isProbe)) {  // opto trails
      	optoProbeStimDelivery(isProbe);
      }
      else{
        delay(rand_stimOnset);
      	SoundDelivery(isProbe); 	//stimulus delivery	//Summed sound delivery function

      }

}

void setup() {
 Serial.begin(115200);
 SPLC.init();
 init_time();
 realtime();
 randomSeed(_second_);
 sessionStartTime = String(_year_);
 sessionStartTime += "_";
 sessionStartTime += String(_month_);
 sessionStartTime += "_";
 sessionStartTime += String(_date_);
 sessionStartTime += "_";
 sessionStartTime += String(_hour_);
 sessionStartTime += "_";
 sessionStartTime += String(_min_);
 PULSE.init();
 delay(1000);
 SPI_TGM.init(MEGA2560);
 define_trial_types(leftProb, probeTrial_frac, probeOptoTrial_frac);
 define_Optotrial_types(TrainingOptoTrial_frac);

 Serial.println("=================================================");  
 Serial.print("#");

 Serial.println("Push the start button to start and make sure the pause button being pressed");


 print_settings();
 attachInterrupt(0, OnLickLeft, RISING);
 attachInterrupt(1, OnLickRight, RISING);

 pinMode(leftWaterPort, OUTPUT);
 pinMode(rightWaterPort, OUTPUT);
  // pinMode(StimOutPin, OUTPUT);
  pinMode(LaserOutPin, OUTPUT);
  digitalWrite(LaserOutPin, LOW);
  pinMode(led_Pin, OUTPUT);
  digitalWrite(led_Pin, LOW);  
  pinMode(LeftLickPin, INPUT);
  pinMode(RightLickPin, INPUT);
  pinMode(initButtonPin, INPUT);
  pinMode(pauseButtonPin, INPUT);

  pinMode(punishment_led, OUTPUT);
  pinMode(punishment_air, OUTPUT);
  pinMode(TriggerOutPin, OUTPUT);
  digitalWrite(initButtonPin, LOW);
  digitalWrite(pauseButtonPin, LOW);
  digitalWrite(leftWaterPort, LOW);
  digitalWrite(rightWaterPort, LOW);
  pinMode(man_water_left,INPUT);
 // digitalWrite(man_water_left,HIGH);
  pinMode(man_water_right,INPUT);
 // digitalWrite(man_water_right,HIGH);

  pinMode(man_water_L,INPUT);
//  digitalWrite(man_water_L,HIGH);

  pinMode(man_water_R,INPUT);
  digitalWrite(man_water_R,HIGH);

  //pinMode(led_lick_left, OUTPUT);
  //pinMode(led_lick_right, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  SSD1331_S_SHOW.init();
}

void loop() {
  while (trialCount < maxNumTrials) {
      // pause high start low
      if (digitalRead(pauseButtonPin) ==  HIGH)
      {// Wait for the first trial to start
        if (trialCount < 1) {
          while (digitalRead(initButtonPin) == LOW) {   //startbutton        
          }
      }

     
     

      sprintf(oled_string0,"%s%3d","Tri",trialCount+1);
     
      SSD1331_S_SHOW.show_line(0,oled_string0);

      setRandomTimes();
      sendTrialStartPulse();
 
      if (isRandomSides == 1) {
        currentSide = trialType[trialCount];
      }
      else {
        currentSide = userDefinedSide;
      }
      if (currentSide == LEFT) {
        Correct  = LEFT;
        Wrong = RIGHT;
        
       SSD1331_S_SHOW.show_line(1, "Side:L");

      }
      else if (currentSide == RIGHT) {
        Correct  = RIGHT;
        Wrong = LEFT;
          
       SSD1331_S_SHOW.show_line(1,"Side:R");

      }

      digitalWrite(TriggerOutPin, HIGH);
      delay(1);
      digitalWrite(TriggerOutPin, LOW);

  		if(ledControl == 1){ 
        ledStimDelivery(1);
        }  // mask 

       if (strcmp(userDefinedOptoSide, "LEFT") == 0){
             if (currentSide==LEFT){
             TotalStim(isProbeTrial[trialCount], isOptoProbeTrial[trialCount], isOptoTrainingTrial[trialCount]);
           }
        else{
             delay(rand_stimOnset);
             SoundDelivery(isProbeTrial[trialCount]); 
         }
       }
       if (strcmp(userDefinedOptoSide, "RIGHT") == 0){
             if (currentSide==RIGHT){
             TotalStim(isProbeTrial[trialCount], isOptoProbeTrial[trialCount], isOptoTrainingTrial[trialCount]);
            }
          else{
              delay(rand_stimOnset);
              SoundDelivery(isProbeTrial[trialCount]); 
          }
        }
      if (strcmp(userDefinedOptoSide, "BOTH") == 0){
      
       TotalStim(isProbeTrial[trialCount], isOptoProbeTrial[trialCount], isOptoTrainingTrial[trialCount]);
     }  		

      delay(responseDelay);

      choice_outcome_state();   

  	  ledStimDelivery(0);
  	  sendOutResults();
    
  	  trialCount++;
      SSD1331_S_SHOW.erase_screen();
  	  delay(interTrialInterval);
   }
 }
}


