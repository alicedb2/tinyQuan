#include <avr/pgmspace.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MCP4725.h>
#include <ADS1X15.h>
#include "tinyquantizer.h"


// This is used for in_scale_cv_mode = 1 since we allow 5 octaves.
// There's no need to change this value
#define GETADC_AT_5V 26656

// It might unfortunately to recommended to calibrate this value
// according to one's particlar power supply. On USB I'm at ~4748 mV
// and the ADC's read 25376 amongst the noise
#define GETADC_AT_ARDUINO_HIGH 25376


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MCP4725 MCP(0x60);
ADS1115 ADS(0x48);

#define CVIN_PIN A0
#define SCALE_PIN A2
#define KEY_OF_PIN A7
#define CHANGE_LAYOUT_PIN 6
#define CHANGE_CV_MODE_PIN 7
#define GATE_PIN 8

uint8_t layout_index = 0;
uint8_t last_layout_button_state = false;
long int last_layout_button_change_millis = millis();

uint8_t last_cv_mode_button_state = false;
long int last_cv_mode_button_change_millis = millis();

uint8_t pixel_loc = 0;

#define PROP 2

char key_buffer[10];
int16_t key0 = 0;

char short_scale_name_buffer[15];
int16_t current_key_of = 0;

uint8_t current_scale = 0;
uint16_t current_scale_mask = CHROMATIC;
uint8_t nb_notes_in_scale = 12;

// in_scale_cv_mode = 0 ->  1 semitone / 83 mV  (non-constant CV difference to change note in scale)
//         = 1 ->   1 note in_scale / 83 mV (constant CV difference to change note in scale
bool in_scale_cv_mode = true;

void setup() {

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(GATE_PIN, OUTPUT);
  pinMode(CHANGE_CV_MODE_PIN, INPUT);
  pinMode(CHANGE_LAYOUT_PIN, INPUT);
  pinMode(SCALE_PIN, INPUT);
  pinMode(CVIN_PIN, INPUT);

  display.clearDisplay();

  Wire.begin();
  Wire.setClock(400000);

  MCP.begin();
  ADS.begin();
  ADS.setGain(0);

  keyboard_layout = keyboard_layouts[layout_index];

}

void loop() {

  //////////////////////////////////////////////
  ////////// Change cv mode button /////////////
  //////////////////////////////////////////////

  bool in_scale_cv_mode_state;
  in_scale_cv_mode_state = digitalRead(CHANGE_CV_MODE_PIN);

  if (millis() - last_layout_button_change_millis > 100) {
    last_layout_button_change_millis = millis();
    if (in_scale_cv_mode_state == HIGH && last_cv_mode_button_state == LOW) {
      in_scale_cv_mode_state = HIGH;
      in_scale_cv_mode = !in_scale_cv_mode;
    }
    if (in_scale_cv_mode_state == LOW && last_cv_mode_button_state == HIGH) {
      last_cv_mode_button_state = LOW;
      //    in_scale_cv_mode = false;
    }
  }

  Serial.println(in_scale_cv_mode);
  Serial.println();
  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  /////////////////////////////////////////////
  ////////// Change layout button /////////////
  /////////////////////////////////////////////
  bool layout_button_state;

  if (millis() - last_cv_mode_button_change_millis > 100) {
    last_cv_mode_button_change_millis = millis();

    layout_button_state = digitalRead(CHANGE_LAYOUT_PIN);
    if (layout_button_state == HIGH && last_layout_button_state == LOW) {
      last_layout_button_state = HIGH;
      layout_index = (layout_index + 1) % 2;
      keyboard_layout = keyboard_layouts[layout_index];
      drawKeyboard(current_scale, current_key_of, 0);
      display.display();
    }
    if (layout_button_state == LOW && last_layout_button_state == HIGH) {
      last_layout_button_state = LOW;
    }
  }
  /////////////////////////////////////////////
  /////////////////////////////////////////////
  /////////////////////////////////////////////

  int16_t new_scale = ADS.readADC(1);

  if (abs(new_scale - current_scale) < GETADC_AT_ARDUINO_HIGH / NUM_SCALES * 1.5) {
    new_scale = current_scale;
  }

  new_scale = map(new_scale, 0, GETADC_AT_ARDUINO_HIGH, -1, NUM_SCALES);
  new_scale = constrain(new_scale, 0, NUM_SCALES - 1);


  int16_t new_key_of = ADS.readADC(2);

  new_key_of = map(new_key_of, 0, GETADC_AT_ARDUINO_HIGH, -1, NUM_NOTES);
  new_key_of = constrain(new_key_of, 0, NUM_NOTES - 1);

  if ((new_key_of != current_key_of) || (new_scale != current_scale)) {

    current_key_of = new_key_of;
    current_scale = new_scale;
    current_scale_mask = pgm_read_word_near(scales + current_scale);

    nb_notes_in_scale = 0;
    for (uint8_t i = 0; i < 12; i++) {
      nb_notes_in_scale += bitRead(current_scale_mask, i);
    }

    display.clearDisplay();
    printKey(current_key_of, 2);
    printScale(current_scale, 2);

    //    drawKeyboard(current_scale, current_key_of, current_key_of);
    drawKeyboard(current_scale, current_key_of, 0);

    pixel_loc = map(current_scale, 0, NUM_SCALES - 1, 0, SCREEN_WIDTH - 8);
    display.fillRect(pixel_loc, 15, 8, 1, SSD1306_WHITE);

    display.display();

  }

  ////////////////////////////////////
  ////////////////////////////////////
  ////////////////////////////////////
  // Here is where the magic happen //
  ////////////////////////////////////
  ////////////////////////////////////
  ////////////////////////////////////

  int16_t cv_to_quantize = ADS.readADC(0);
  // Serial.println();
  // Serial.print("cv_to_quantize:");
  // Serial.print(cv_to_quantize);
  // Serial.print("  ");
  uint8_t semitone;
  uint8_t semitone_in_scale;
  uint8_t note_in_scale;

  if (in_scale_cv_mode) {
    note_in_scale = map(cv_to_quantize,
                        -16, SEMITONE_CV_UPPER_BOUNDARY_EXCLUSIVE,
                        0, 5 * nb_notes_in_scale + 1);

    note_in_scale = constrain(note_in_scale, 0, MAX_DAC_SEMITONE - 1);

    semitone_in_scale = current_key_of;
    for (uint8_t i = current_key_of, note_idx = 0; i < MAX_DAC_SEMITONE; i++) {
      bool Qsemitone_in_scaleQ = bitRead(rotate12Right(current_scale_mask, i), 0);
      semitone_in_scale = Qsemitone_in_scaleQ ? i : semitone_in_scale;
      note_idx += Qsemitone_in_scaleQ;
      if (note_idx >= note_in_scale) break;
    }

  } else {

    for (uint16_t semitone = current_key_of; semitone < MAX_DAC_SEMITONE; semitone++) {

      if (bitRead(rotate12Right(current_scale_mask, current_key_of + semitone), 0)) {
        semitone_in_scale = semitone;
      }

      if (cv_to_quantize <= (int16_t)pgm_read_word_near(semitonecv_to_ADC16read + semitone)) {
        break;
      }

    }

  }

  MCP.setValue((int16_t)pgm_read_word_near(semitone_cvs_dac + semitone_in_scale));

  ////////////////////////////////////
  ////////////////////////////////////
  ////////////////////////////////////
  ////////////////////////////////////
  ////////////////////////////////////
}



void printKey(int8_t key, int8_t text_size) {
  display.fillRect(0, 0, SCREEN_WIDTH, 8 * text_size, SSD1306_BLACK);
  display.setTextSize(text_size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  strcpy_P(key_buffer, (char *)pgm_read_word(&(notes[key])));
  display.println(key_buffer);
}



void printScale(int16_t scale, int8_t text_size) {
  display.fillRect(0, 16, SCREEN_WIDTH, 8 * text_size, SSD1306_BLACK);
  display.setTextSize(text_size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  strcpy_P(short_scale_name_buffer, (char *)pgm_read_word(&(short_scale_names[scale])));
  display.println(short_scale_name_buffer);
}



void drawKeyboard(int16_t scale, int8_t key_of, int8_t origin_key) {
  uint16_t on_keys = 0;

  static int16_t x0 = 0;
  static int16_t y0 = SCREEN_HEIGHT - PROP * keyboard_layout_HEIGHT;

  display.fillRect(x0, y0, SCREEN_WIDTH, PROP * keyboard_layout_HEIGHT, SSD1306_BLACK);

  static uint8_t keys_to_display = ceil(12.0 * float(SCREEN_WIDTH) / float(PROP * keyboard_layout_WIDTH));

  //  uint16_t on_keys = scales[scale];
  on_keys = pgm_read_word_near(scales + scale);



  // Align with the key at origin of display
  if (key_of > origin_key) {
    on_keys = rotate12Left(on_keys, key_of - origin_key);
  }
  else if (key_of < origin_key) {
    on_keys = rotate12Right(on_keys, origin_key - key_of);
  }
  // Last nudge to print _k = -1
  on_keys = rotate12Left(on_keys, 1);

  // Draw white notes
  int8_t x_offset = -keyboard_layout[mod(origin_key - 1, 12)][1] / 2;
  for (int16_t _k = -1, k; _k < keys_to_display + 1; _k++) {

    k = mod(_k + origin_key, 12);

    if (keyboard_layout[k][0] == 0) {
      if (on_keys & 0b1) {
        display.fillRoundRect(x0 + PROP * x_offset,
                              y0 + PROP * keyboard_layout[k][2],
                              PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                              keyboard_layout[k][5], SSD1306_WHITE);
      }
      else
      {
        display.drawRoundRect(x0 + PROP * x_offset,
                              y0 + PROP * keyboard_layout[k][2],
                              PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                              keyboard_layout[k][5], SSD1306_WHITE);
      }

    }

    x_offset += keyboard_layout[k][1];
    on_keys = rotate12Right(on_keys, 1);
  }


  //////////////////
  on_keys = pgm_read_word_near(scales + scale);
  if (key_of > origin_key) {
    on_keys = rotate12Left(on_keys, key_of - origin_key);
  }
  else if (key_of < origin_key) {
    on_keys = rotate12Right(on_keys, origin_key - key_of);
  }
  on_keys = rotate12Left(on_keys, 1);
  //////////////////

  x_offset = -keyboard_layout[mod(origin_key - 1, 12)][1] / 2;
  for (int8_t _k = -1, k; _k < keys_to_display + 1; _k++) {

    k = mod(_k + origin_key, 12);

    if (keyboard_layout[k][0] == 1) {
      if (on_keys & 1) {
        display.fillRoundRect(x0 + PROP * x_offset,
                              y0 + PROP * keyboard_layout[k][2],
                              PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                              keyboard_layout[k][5], SSD1306_WHITE);

        // Draw a black line around black notes that are ON
        // only when the layout is keyboard because black notes
        // in the BSP layout do not overlap white notes
        if (layout_index == 0) {
          display.drawRoundRect(x0 + PROP * x_offset,
                                y0 + PROP * keyboard_layout[k][2],
                                PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                                keyboard_layout[k][5], SSD1306_BLACK);
        }
      }
      else {
        display.fillRoundRect(x0 + PROP * x_offset,
                              y0 + PROP * keyboard_layout[k][2],
                              PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                              keyboard_layout[k][5], SSD1306_BLACK);

        display.drawRoundRect(x0 + PROP * x_offset,
                              y0 + PROP * keyboard_layout[k][2],
                              PROP * keyboard_layout[k][3], PROP * keyboard_layout[k][4],
                              keyboard_layout[k][5], SSD1306_WHITE);
      }
    }

    x_offset += keyboard_layout[k][1];
    on_keys = rotate12Right(on_keys, 1);

  }

}

int mod(int x, int m) {
  return (x % m + m) % m;
}

uint16_t rotate12Left(uint16_t n, uint16_t d) {
  return 0xfff & ((n << (d % 12)) | (n >> (12 - (d % 12))));
}

uint16_t rotate12Right(uint16_t n, uint16_t d) {
  return 0xfff & ((n >> (d % 12)) | (n << (12 - (d % 12))));
}