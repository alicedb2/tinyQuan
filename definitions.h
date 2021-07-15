
#define CVIN_PIN A0
#define SCALE_PIN A2
#define KEY_OF_PIN A7
#define CHANGE_LAYOUT_PIN 6
#define CHANGE_CV_MODE_PIN 7
#define TRIGGER_PIN 8

// This is used for in_scale_cv_mode = 1 since we allow 5 octaves.
// There's no need to change this value
#define GETADC_AT_5V 26656

// It might unfortunately to recommended to calibrate this value
// according to one's particlar power supply. On USB I'm at ~4748 mV
// and the ADC's read 25376 amongst the noise
#define GETADC_AT_ARDUINO_HIGH 25200


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)


#define MAX_DAC_SEMITONE 57
const int16_t PROGMEM semitone_cvs_dac[MAX_DAC_SEMITONE] = {
  6, 79, 151, 224, 297, 368, 441, 509, 584, 653, 727, 799,
  870, 944, 1014, 1087, 1157, 1232, 1302, 1374, 1446, 1516, 1588, 1658,
  1733, 1802, 1876, 1946, 2018, 2091, 2162, 2237, 2306, 2381, 2452, 2525,
  2595, 2667, 2741, 2810, 2884, 2954, 3027, 3096, 3168, 3240, 3311, 3385,
  3453, 3528, 3596, 3669, 3739, 3812, 3884, 3954, 4030 // G#4
};

//const int16_t PROGMEM semitonecv_to_analogread[58] = {
//  0,  16, 32, 51, 69, 86, 104, 123, 141, 159, 177, 194, 213, 
//  230, 249, 267, 284, 303, 321, 339, 357, 375, 393, 411, 429,
//  447, 465, 483, 501, 519, 537, 556, 574, 592, 609, 627, 646,
//  664, 682, 700, 718, 736, 754, 772, 790, 808, 826, 844, 862,
//  880, 898, 916, 934, 952, 971, 989, 1007, 1022 // A4
//};



// 0  83  167  250  333  417  500  583  667  750  833  917
// Techically the ADC can distinguish amongst 63 semitones, but the DAC can
// only produce 57 because of the power of my USB port

#define SEMITONE_CV_UPPER_BOUNDARY_EXCLUSIVE 25328
const int16_t PROGMEM semitonecv_to_ADC16read[MAX_DAC_SEMITONE] = {
  -16, 448, 896, 1328, 1776, 2224, 2672, 3120, 2552, 4000, 4448, 4896, 
  5336, 5776, 6224, 6672, 7104, 7552, 8000, 8432, 8896, 9328, 9776, 10224,
  10672, 11104, 11152, 12000, 12432, 12896, 13328, 13776, 14224, 14656, 15104, 15552,  
  16000, 16448, 16880, 17328, 17776, 18224, 18656, 19104, 19552, 20000, 20432, 20880,
  21328, 21760, 22208, 22656, 23104, 23552, 23728, 24432, 24880 // 25328, 25760, 26208,
//  26656, 27104, 27536, // D5, end of the calibration I was able to reach slightly above 5V
  // We use a delta = 448 to extrapolate to the max the ADC can read = 6.14 V = 32768
//  27984, 28432, 28880, 29328, 29776, 30224, 30672, 31120, 31568, 32016, 32464 // D6
};


#define NUM_NOTES 12
#define NUM_SCALES 120

#define KEYBOARD_WIDTH 11
#define SCALE_BITS 12

#define WKEY_WIDTH 7
#define WKEY_HEIGHT 12

#define BKEY_WIDTH 5
#define BKEY_HEIGHT 10

#define KEYBOARD_LAYOUT_WIDTH 56
#define KEYBOARD_LAYOUT_HEIGHT 16

// Scales with note 1 in least significant bit
//                  flat-2 in bit 1
//                  2 in bit 2
// and 7 in most significant bit 11.

//    1 f2  2 f3  3  4 f5  5 f6  6 f7  7
//bit 0  1  2  3  4  5  6  7  8  9 10 11

// Main scales with 1st note at LSB
#define CHROMATIC 0xfff
#define MAJOR 0xab5
#define MINOR 0x5ad
#define HARMONIC_MINOR 0x9ad
#define MAJOR_PENTATONIC 0x295
#define MINOR_PENTATONIC 0x4a9
#define BLUES 0x4e9
#define JAPANESE 0x18d
#define FREYGISH 0x5b3
#define ROMANI 0x9cd
#define ARABIC 0x9b3
#define ALTERED 0x55b
#define WHOLE_TONE 0x555
#define HW_DIMINISHED 0x6db
#define WH_DIMINISHED 0xb6d

#define IONIAN 0xab5
#define DORIAN 0x6ad
#define PHRYGIAN 0x5ab
#define LYDIAN 0xad5
#define MIXOLYDIAN 0x6b5
#define AEOLIAN 0x5ad
#define LOCRIAN 0x56b
#define IONIAN_B2 0xab3
#define DORIAN_B5 0x66d
#define HARMONIC_PHRYGIAN 0x9ab
#define PHRYGIAN_MAJOR 0xaad
#define LYDIAN_B3 0xacd
#define MAJOR_LOCRIAN 0x575
#define MINOR_LOCRIAN 0x56d
#define SUPER_LOCRIAN 0x55b

#define LYDIAN_7B 0x6d5
//#define ALTERED
#define DIMINISHED 0x6db
#define MIXOLYDIAN_B13 0x5b5
#define MIXOLYDIAN_B9_B13 0x5b3
#define LYDIAN_7B_B2 0x6ab
#define BEBOP 0x6b5
//#define WHOLE_TONE
#define BLUES_MAJOR 0x29d
#define BLUES_MINOR 0x4e9
#define BLUES_COMBINED 0x6fd
#define LYDIAN_5 0xb55
#define JAZZ_MINOR 0xaad
#define HALF_DIMINISHED 0x56d
#define AUGMENTED 0x999

#define HUNGARIAN_MAJOR 0x9cd
#define HUNGARIAN_MINOR 0x6d9
#define NEAPOLITAN 0x9ab
#define SPANISH 0x5bb
#define GREEK 0x59d
#define JEWISH1 0x2db
#define JEWISH2 0x6cd
#define INDIAN1 0x9cd
#define INDIAN2 0xacd
#define INDIAN3 0x3a7
#define INDIAN4 0xcb9
#define MIDEAST1 0x9b3
#define MIDEAST2 0x973
#define MIDEAST3 0x66b
#define MIDEAST4 0x673

#define PENTATONIC_I 0x295
#define PENTATONIC_II 0x4a5
#define PENTATONIC_III 0x529
#define PENTATONIC_IV 0x2a5
#define PENTATONIC_V 0x4a9
#define HIRAJOSHI 0x18d
#define INSEN 0x4a3
#define KOKIN_JOSHI 0x1a5
#define AKEBONO 0x28d
#define RYUKUAN 0x8b1
#define ABHOGI 0x22d
#define BHUPKALI 0x195
#define HINDOLAM 0x529
#define BHUPALAM 0x18b
#define AMRITAVARSHINI 0x8d1

#define OCTATONIC 0xb6d
#define ACOUSTIC 0x6d5
//#define AUGMENTED
#define TRITONE 0x4d3
#define LEADING_WHOLE_TONE 0xd55
#define ENIGMATIC 0xd53
#define SCRIABIN 0x655
#define TCHEREPNIN 0xbbb
#define MESSIAEN_I 0x555
#define MESSIANE_II 0x6db
#define MESSIANE_III 0xddd
#define MESSIANE_IV 0x9e7
#define MESSIANE_V 0x8e3
#define MESSIANE_VI 0xd75
#define MESSIANE_VII 0xbef

#define NATURAL_MAJOR 0xab5
//#define LYDIAN
//#define MIXOLYDIAN
#define MAJOR_MINOR 0x5b5
#define HARMONIC_MAJOR 0x9b5
#define DOUBLE_HARMONIC_MAJOR 0x9b3
#define NEAPOLITAN_MAJOR 0xab3
#define BEBOP_MAJOR 0xbb5
#define HEXATONIC_1_MAJOR 0xa95
#define HEXATONIC_2_MAJOR 0x2b5
#define PENTATONIC_1_MAJOR 0x295
#define PENTATONIC_2_MAJOR 0x8b1
#define PENTATONIC_3_MAJOR 0xa91

#define NATURAL_MINOR 0x5ad
//#define DORIAN
//#define PHRYGIAN
#define MINOR_MAJOR 0xaad
//#define HARMONIC_MINOR
#define DOUBLE_HARMONIC_MINOR 0x9cd
#define NEAPOLITAIN_MINOR 0x9ab
#define MINOR_LOCRIAN 0x56d
//#define BLUES_MINOR
#define BEBOP_MINOR 0xdad
#define HEXATONIC_1_MINOR 0x58d
#define HEXATONIC_2_MINOR 0x1ad
#define PENTATONIC_1_MINOR 0x18d
#define PENTATONIC_2_MINOR 0x4a9
#define PENTATONIC_3_MINOR 0x589

const PROGMEM uint16_t scales[NUM_SCALES] = {
  CHROMATIC, MAJOR, MINOR, HARMONIC_MINOR, MAJOR_PENTATONIC,
  MINOR_PENTATONIC, BLUES, JAPANESE, FREYGISH, ROMANI,
  ARABIC, ALTERED, WHOLE_TONE, HW_DIMINISHED, WH_DIMINISHED,

  IONIAN, DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN,
  AEOLIAN, LOCRIAN, IONIAN_B2, DORIAN_B5, HARMONIC_PHRYGIAN,
  PHRYGIAN_MAJOR, LYDIAN_B3, MAJOR_LOCRIAN, MINOR_LOCRIAN, SUPER_LOCRIAN,

  LYDIAN_7B, ALTERED, DIMINISHED, MIXOLYDIAN_B13, MIXOLYDIAN_B9_B13,
  LYDIAN_7B_B2, BEBOP, WHOLE_TONE, BLUES_MAJOR, BLUES_MINOR,
  BLUES_COMBINED, LYDIAN_5, JAZZ_MINOR, HALF_DIMINISHED, AUGMENTED,

  HUNGARIAN_MAJOR, HUNGARIAN_MINOR, NEAPOLITAN, SPANISH, GREEK,
  JEWISH1, JEWISH2, INDIAN1, INDIAN2, INDIAN3,
  INDIAN4, MIDEAST1, MIDEAST2, MIDEAST3, MIDEAST4,

  PENTATONIC_I, PENTATONIC_II, PENTATONIC_III, PENTATONIC_IV, PENTATONIC_V,
  HIRAJOSHI, INSEN, KOKIN_JOSHI, AKEBONO, RYUKUAN,
  ABHOGI, BHUPKALI, HINDOLAM, BHUPALAM, AMRITAVARSHINI,

  OCTATONIC, ACOUSTIC, AUGMENTED, TRITONE, LEADING_WHOLE_TONE,
  ENIGMATIC, SCRIABIN, TCHEREPNIN, MESSIAEN_I, MESSIANE_II,
  MESSIANE_III, MESSIANE_IV, MESSIANE_V, MESSIANE_VI, MESSIANE_VII,

  NATURAL_MAJOR, LYDIAN, MIXOLYDIAN, MAJOR_MINOR, HARMONIC_MAJOR,
  DOUBLE_HARMONIC_MAJOR, NEAPOLITAN_MAJOR, MAJOR_LOCRIAN, BLUES_MAJOR, BEBOP_MAJOR,
  HEXATONIC_1_MAJOR, HEXATONIC_2_MAJOR, PENTATONIC_1_MAJOR, PENTATONIC_2_MAJOR, PENTATONIC_3_MAJOR,

  NATURAL_MINOR, DORIAN, PHRYGIAN, MINOR_MAJOR, HARMONIC_MINOR,
  DOUBLE_HARMONIC_MINOR, NEAPOLITAIN_MINOR, MINOR_LOCRIAN, BLUES_MINOR, BEBOP_MINOR,
  HEXATONIC_1_MINOR, HEXATONIC_2_MINOR, PENTATONIC_1_MINOR, PENTATONIC_2_MINOR, PENTATONIC_3_MINOR
};

const char Chromatic_string[] PROGMEM = "Chromatic";
const char Major_string[] PROGMEM = "Major";
const char Minor_string[] PROGMEM = "Minor";
const char Harm_Min_string[] PROGMEM = "Harm Min";
const char Maj_Penta_string[] PROGMEM = "Maj Penta";
const char Min_Penta_string[] PROGMEM = "Min Penta";
const char Blues_string[] PROGMEM = "Blues";
const char Japanese_string[] PROGMEM = "Japanese";
const char Freygish_string[] PROGMEM = "Freygish";
const char Romani_string[] PROGMEM = "Romani";
const char Arabic_string[] PROGMEM = "Arabic";
const char Altered_string[] PROGMEM = "Altered";
const char Whl_Tone_string[] PROGMEM = "Whl Tone";
const char H_W_Dim_string[] PROGMEM = "H-W Dim";
const char W_H_Dim_string[] PROGMEM = "W-H Dim";

const char Ionian_string[] PROGMEM = "Ionian";
const char Dorian_string[] PROGMEM = "Dorian";
const char Phrygian_string[] PROGMEM = "Phrygian";
const char Lydian_string[] PROGMEM = "Lydian";
const char Mixolydian_string[] PROGMEM = "Mixolydian";
const char Aeolian_string[] PROGMEM = "Aeolian";
const char Locrian_string[] PROGMEM = "Locrian";
const char Ionian_b2_string[] PROGMEM = "Ionian b2";
const char Dorian_b5_string[] PROGMEM = "Dorian b5";
const char Harm_Phry_string[] PROGMEM = "Harm Phry";
const char Phry_Maj_string[] PROGMEM = "Phry Maj";
const char Lydian_b3_string[] PROGMEM = "Lydian b3";
const char Maj_Locr_string[] PROGMEM = "Maj Locr";
const char Min_Locr_string[] PROGMEM = "Min Locr";
const char Super_Locr_string[] PROGMEM = "Super Locr";

const char Lydian_7b_string[] PROGMEM = "Lydian 7b";
//const char Altered_string[] PROGMEM = "Altered";
const char Diminished_string[] PROGMEM = "Diminished";
const char Mix_b13_string[] PROGMEM = "Mix b13";
const char Mix_b9_b13_string[] PROGMEM = "Mix b9 b13";
const char Lyd_7b_b2_string[] PROGMEM = "Lyd 7b b2";
const char Bebop_string[] PROGMEM = "Bebop";
//const char Whl_Tone_string[] PROGMEM = "Whl Tone";
const char Blues_Maj_string[] PROGMEM = "Blues Maj";
const char Blues_Min_string[] PROGMEM = "Blues Min";
const char Blues_Comb_string[] PROGMEM = "Blues Comb";
const char Lydian_5_string[] PROGMEM = "Lydian #5";
const char Jazz_Min_string[] PROGMEM = "Jazz Min";
const char Half_Dim_string[] PROGMEM = "Half Dim";
const char Augmented_string[] PROGMEM = "Augmented";

const char Hungar_Min_string[] PROGMEM = "Hungar Min";
const char Hungar_Maj_string[] PROGMEM = "Hungar Maj";
const char Neapolitan_string[] PROGMEM = "Neapolitan";
const char Spanish_string[] PROGMEM = "Spanish";
const char Greek_string[] PROGMEM = "Greek";
const char Jewish_1_string[] PROGMEM = "Jewish 1";
const char Jewish_2_string[] PROGMEM = "Jewish 2";
const char Indian_1_string[] PROGMEM = "Indian 1";
const char Indian_2_string[] PROGMEM = "Indian 2";
const char Indian_3_string[] PROGMEM = "Indian 3";
const char Indian_4_string[] PROGMEM = "Indian 4";
const char Mid_East_1_string[] PROGMEM = "Mid East 1";
const char Mid_East_2_string[] PROGMEM = "Mid East 2";
const char Mid_East_3_string[] PROGMEM = "Mid East 3";
const char Mid_East_4_string[] PROGMEM = "Mid East 4";

const char Pent_I_string[] PROGMEM = "Penta   I";
const char Pent_II_string[] PROGMEM = "Penta  II";
const char Pent_III_string[] PROGMEM = "Penta III";
const char Pent_IV_string[] PROGMEM = "Penta  IV";
const char Pent_V_string[] PROGMEM = "Penta   V";
const char Hirajoshi_string[] PROGMEM = "Hirajoshi";
const char Insen_string[] PROGMEM = "Insen";
const char KokinJoshi_string[] PROGMEM = "KokinJoshi";
const char Akebono_string[] PROGMEM = "Akebono";
const char Ryukuan_string[] PROGMEM = "Ryukuan";
const char Abhogi_string[] PROGMEM = "Abhogi";
const char Bhupkali_string[] PROGMEM = "Bhupkali";
const char Hindolam_string[] PROGMEM = "Hindolam";
const char Bhupalam_string[] PROGMEM = "Bhupalam";
const char Amritavars_string[] PROGMEM = "Amritavars";

const char Octatonic_string[] PROGMEM = "Octatonic";
const char Acoustic_string[] PROGMEM = "Acoustic";
//const char Augmented_string[] PROGMEM = "Augmented";
const char Tritone_string[] PROGMEM = "Tritone";
const char LeadingWhl_string[] PROGMEM = "LeadingWhl";
const char Enigmatic_string[] PROGMEM = "Enigmatic";
const char Scriabin_string[] PROGMEM = "Scriabin";
const char Tcherepnin_string[] PROGMEM = "Tcherepnin";
const char Messiaen_1_string[] PROGMEM = "Messiaen 1";
const char Messiaen_2_string[] PROGMEM = "Messiaen 2";
const char Messiaen_3_string[] PROGMEM = "Messiaen 3";
const char Messiaen_4_string[] PROGMEM = "Messiaen 4";
const char Messiaen_5_string[] PROGMEM = "Messiaen 5";
const char Messiaen_6_string[] PROGMEM = "Messiaen 6";
const char Messiaen_7_string[] PROGMEM = "Messiaen 7";

const char Nat_Maj_string[] PROGMEM = "Natur Maj";
//const char Lydian_string[] PROGMEM = "Lydian";
//const char Mixolydian_string[] PROGMEM = "Mixolydian";
const char Maj_Min_string[] PROGMEM = "Maj Min";
const char Harm_Maj_string[] PROGMEM = "Harm Maj";
const char DblHarmMaj_string[] PROGMEM = "DblHarmMaj";
const char NaepolMaj_string[] PROGMEM = "Naepol Maj";
const char Major_Loc_string[] PROGMEM = "Major Loc";
const char BluesMaj_string[] PROGMEM = "Blues Maj";
const char Bebop_Maj_string[] PROGMEM = "Bebop Maj";
const char Hexa_1_Maj_string[] PROGMEM = "Hexa 1 Maj";
const char Hexa_2_Maj_string[] PROGMEM = "Hexa 2 Maj";
const char Penta1_Maj_string[] PROGMEM = "Penta1 Maj";
const char Penta2_Maj_string[] PROGMEM = "Penta2 Maj";
const char Penta3_Maj_string[] PROGMEM = "Penta3 Maj";

const char Nat_Min_string[] PROGMEM = "Natur Min";
//const char Dorian_string[] PROGMEM = "Dorian";
//const char Phrygian_string[] PROGMEM = "Phrygian";
const char Min_Maj_string[] PROGMEM = "Min Maj";
//const char Harm_Min_string[] PROGMEM = "Harm Min";
const char DblHarmMin_string[] PROGMEM = "DblHarmMin";
const char NeapolMin_string[] PROGMEM = "Neapol Min";
const char Minor_Loc_string[] PROGMEM = "Minor Loc";
//const char Blues_Min_string[] PROGMEM = "Blues Min";
const char Bebop_Min_string[] PROGMEM = "Bebop Min";
const char Hexa_1_Min_string[] PROGMEM = "Hexa 1 Min";
const char Hexa_2_Min_string[] PROGMEM = "Hexa 2 Min";
const char Penta1_Min_string[] PROGMEM = "Penta1 Min";
const char Penta2_Min_string[] PROGMEM = "Penta2 Min";
const char Penta3_Min_string[] PROGMEM = "Penta3 Min";

const char *const short_scale_names[NUM_SCALES] PROGMEM = {
  Chromatic_string, Major_string, Minor_string, Harm_Min_string, Maj_Penta_string,
  Min_Penta_string, Blues_string, Japanese_string, Freygish_string, Romani_string,
  Arabic_string, Altered_string, Whl_Tone_string, H_W_Dim_string, W_H_Dim_string,

  Ionian_string, Dorian_string, Phrygian_string, Lydian_string, Mixolydian_string,
  Aeolian_string, Locrian_string, Ionian_b2_string, Dorian_b5_string, Harm_Phry_string,
  Phry_Maj_string, Lydian_b3_string, Maj_Locr_string, Min_Locr_string, Super_Locr_string,

  Lydian_7b_string, Altered_string, Diminished_string, Mix_b13_string, Mix_b9_b13_string,
  Lyd_7b_b2_string, Bebop_string, Whl_Tone_string, Blues_Maj_string, Blues_Min_string,
  Blues_Comb_string, Lydian_5_string, Jazz_Min_string, Half_Dim_string, Augmented_string,

  Hungar_Min_string, Hungar_Maj_string, Neapolitan_string, Spanish_string, Greek_string,
  Jewish_1_string, Jewish_2_string, Indian_1_string, Indian_2_string, Indian_3_string,
  Indian_4_string, Mid_East_1_string, Mid_East_2_string, Mid_East_3_string, Mid_East_4_string,

  Pent_I_string, Pent_II_string, Pent_III_string, Pent_IV_string, Pent_V_string,
  Hirajoshi_string, Insen_string, KokinJoshi_string, Akebono_string, Ryukuan_string,
  Abhogi_string, Bhupkali_string, Hindolam_string, Bhupalam_string, Amritavars_string,

  Octatonic_string, Acoustic_string, Augmented_string, Tritone_string, LeadingWhl_string,
  Enigmatic_string, Scriabin_string, Tcherepnin_string, Messiaen_1_string, Messiaen_2_string,
  Messiaen_3_string, Messiaen_4_string, Messiaen_5_string, Messiaen_6_string, Messiaen_7_string,

  Nat_Maj_string, Lydian_string, Mixolydian_string, Maj_Min_string, Harm_Maj_string,
  DblHarmMaj_string, NaepolMaj_string, Major_Loc_string, BluesMaj_string, Bebop_Maj_string,
  Hexa_1_Maj_string, Hexa_2_Maj_string, Penta1_Maj_string, Penta2_Maj_string, Penta3_Maj_string,

  Nat_Min_string, Dorian_string, Phrygian_string, Min_Maj_string, Harm_Min_string,
  DblHarmMin_string, NeapolMin_string, Minor_Loc_string, Blues_Min_string, Bebop_Min_string,
  Hexa_1_Min_string, Hexa_2_Min_string, Penta1_Min_string, Penta2_Min_string, Penta3_Min_string
};


const char key_C[2] PROGMEM = "C";
const char key_Csharp[6] PROGMEM = "C#/Db";
const char key_D[2] PROGMEM = "D";
const char key_Dsharp[6] PROGMEM = "D#/Eb";
const char key_E[2] PROGMEM = "E";
const char key_F[2] PROGMEM = "F";
const char key_Fsharp[6] PROGMEM = "F#/Gb";
const char key_G[2] PROGMEM = "G";
const char key_Gsharp[6] PROGMEM = "G#/Ab";
const char key_A[2] PROGMEM = "A";
const char key_Asharp[6] PROGMEM = "A#/Bb";
const char key_B[2] PROGMEM = "B";

const char *const notes[12] PROGMEM = {
  key_C, key_Csharp, key_D, key_Dsharp, key_E, key_F,
  key_Fsharp, key_G, key_Gsharp, key_A, key_Asharp, key_B
};


// Draws the layout smaller or bigger
#define PROP 2

#define ROOT_DOT_SIZE 3





// [0] = 0 -> white key
//     = 1 -> black key
// [1] delta x to next note (white->black or black->white might not be the same
//                           if one is thinner/wider than the other)
// [2] heigth of lower left corder
// [3] width
// [4] height
// [5] rounded corner radius
const int8_t piano_layout[12][6] =
{
  {0, 5, 2, 7, 14, 2},    // W
  {1, 3, 0, 5, 12, 2},    // K
  {0, 5, 2, 7, 14, 2},    // W
  {1, 3, 0, 5, 12, 2},   // K
  {0, 8, 2, 7, 14, 2},   // W
  {0, 5, 2, 7, 14, 2},   // W
  {1, 3, 0, 5, 12, 2},   // K
  {0, 5, 2, 7, 14, 2},   // W
  {1, 3, 0, 5, 12, 2},   // K
  {0, 5, 2, 7, 14, 2},   // W
  {1, 3, 0, 5, 12, 2},   // K
  {0, 8, 2, 7, 14, 2}    // W
};


const int8_t beatstep_layout[12][6] =
{
  {0, 0, 9, 7, 7, 2},    // W
  {1, 8, 1, 7, 7, 2},    // K
  {0, 0, 9, 7, 7, 2},    // W
  {1, 8, 1, 7, 7, 2},   // K
  {0, 8, 9, 7, 7, 2},   // W
  {0, 0, 9, 7, 7, 2},   // W
  {1, 8, 1, 7, 7, 2},   // K
  {0, 0, 9, 7, 7, 2},   // W
  {1, 8, 1, 7, 7, 2},   // K
  {0, 0, 9, 7, 7, 2},   // W
  {1, 8, 1, 7, 7, 2},   // K
  {0, 8, 9, 7, 7, 2}    // W

};

const int8_t (*keyboard_layouts[2])[6] = {piano_layout, beatstep_layout};
const int8_t (*keyboard_layout)[6];
