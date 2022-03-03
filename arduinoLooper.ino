#include <OneButton.h>
#include <EEPROM.h>

// TODO загрузка из EEPROM

bool banks[30][4][6]; // Массив банков [банки] [пресеты] [выходы]
uint8_t NO_bank; // Номер банка
uint8_t NO_preset; // Номер пресета
uint8_t NO_input = -1; // Номер входа 


// Кнопки
OneButton menu_btn(A2, false, false);
OneButton save_btn(A3, false, false);
OneButton prev_btn(3, false, false);
OneButton next_btn(5, false, false);
OneButton a_btn(6, false, false);
OneButton b_btn(7, false, false);
OneButton c_btn(A0, false, false);
OneButton d_btn(A1, false, false);



//Выхода
const uint8_t led_outputs[6] PROGMEM = {2, 4, 8, 9, 10, 12};

bool menu_mode = false; // Флаг режима меню

void serial_banks_print(){

}

////////
// UTILS
////////

void clean_eeprom(){
	bool banks[30][4][6]; // Массив банков [банки] [пресеты] [выходы]
	uint8_t NO_bank = 0; // Номер банка
	uint8_t NO_preset = 0; // Номер пресета
	for (uint8_t i = 0; i < 30; ++i){
		for (uint8_t j = 0; j < 4; ++j){
			for (uint8_t k = 0; k < 6; ++k){
				banks[i][j][k] = false;
			}
			
		}
	}
	EEPROM.put(30, banks);
	EEPROM.put(1, NO_bank);
}

void off_menu_mode(){
	if (menu_mode == true) menu_mode = false;
	NO_input = -1;
}

void on_menu_mode(){
	if (menu_mode == false) menu_mode = true;
	NO_input = 0; // Выставляет первый вход
}


void change_input_value(){ // изменить значение входа
	if (banks[NO_bank][NO_preset][NO_input] == false){
		banks[NO_bank][NO_preset][NO_input] = true;
	}else{
		banks[NO_bank][NO_preset][NO_input] = false;
	}
}

void save_banks(){
	EEPROM.put(30, banks);
}

void save_state(){
	EEPROM.put(1, NO_bank);
}

void reset_preset(){ // Сбрасываем пресет
	NO_preset = 0;
}

///////////
// HANDLERS
///////////

void press_menu_btn(){ // Нажатие на "меню"
	if (menu_mode == true){
		change_input_value(); // Меняет значение
	}else{
		on_menu_mode(); // Включает меню
	}
}

void press_save_btn(){ // Нажатие на "сохранить"
	off_menu_mode();
	save_banks();
	Serial.print("\nSAVE!");
	//TODO Запись массива в EEPROM
}

void press_prev_btn(){ // Нажитие на "prev"
	if (menu_mode == true){ // Если режим меню
		if (NO_input == 0)
			NO_input = 5;
		else
			NO_input--;
	} else { // если режим пользования
		reset_preset();
		if (NO_bank <= 0)
			NO_bank = 29;
		else 
			NO_bank--;
	}
}


void press_next_btn(){ // Нажитие на "next"
	if (menu_mode == true){ // Если режим меню
		if (NO_input == 5)
			NO_input = 0;
		else
			NO_input++;
	} else { // если режим пользования
		reset_preset();
		if (NO_bank >= 29)
			NO_bank = 0;
		else 
			NO_bank++;
	}
	
}

void press_a_btn(){
	NO_preset = 0;
}
void press_b_btn(){
	NO_preset = 1;
}
void press_c_btn(){
	NO_preset = 2;
}
void press_d_btn(){
	NO_preset = 3;
}

void refrash_led(){	// Обновление светодиодов
	for (uint8_t i = 0; i < 6; i++){
		if (banks[NO_bank][NO_preset][i] == true){
			digitalWrite(led_outputs[i], HIGH);
		} else {
			digitalWrite(led_outputs[i], LOW);
		}
	}
}


void setup()
{	
	Serial.begin(9600);
	
	// clean_eeprom();
	serial_banks_print();
	refrash_led();

	menu_btn.attachClick([](){
		press_menu_btn();
		refrash_led();
		serial_banks_print();

	});

	save_btn.attachClick([](){
		press_save_btn();
		refrash_led();
	});

	prev_btn.attachClick([](){
		press_prev_btn();
		refrash_led();
		serial_banks_print();
		save_state();
	});

	next_btn.attachClick([](){
		press_next_btn();
		refrash_led();
		serial_banks_print();
		save_state();
	});

	a_btn.attachClick([](){
		press_a_btn();
		refrash_led();
		serial_banks_print();
		save_state();
	});

	b_btn.attachClick([](){
		press_b_btn();
		refrash_led();
		serial_banks_print();
		save_state();	
	});

	c_btn.attachClick([](){
		press_c_btn();
		refrash_led();
		serial_banks_print();
		save_state();
	});

	d_btn.attachClick([](){
		press_d_btn();
		refrash_led();
		serial_banks_print();
		save_state();
	});

	for (uint8_t i=0; i < 6; i++)
		pinMode(led_outputs[i], OUTPUT);



    EEPROM.get(30, banks);
	EEPROM.get(1, NO_bank);
	

}

void loop()
{
	menu_btn.tick();
	save_btn.tick();
	prev_btn.tick();
	next_btn.tick();
	a_btn.tick();
	b_btn.tick();
	c_btn.tick();
	d_btn.tick();

}
