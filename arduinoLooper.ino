#include <EEPROM.h>


// TODO загрузка из EEPROM
bool banks[29][3][5]; // Массив банков [банки] [пресеты] [входы]
int NO_bank = 0; // Номер банка
int NO_preset = 0; // Номер пресета
int NO_input = -1; // Номер входа 
bool menu_mode = false; // Флаг режима меню

void serial_banks_print(bool banks[29][3][5]){
	// Выводит банки в сериал порт 
	Serial.println(' ');
	for (int i = 0; i < 29; ++i){
		for (int j = 0; j < 3; ++j){
			Serial.print('(');

			for (int k = 0; k < 5; ++k){
				Serial.print(banks[i][j][k]);
			}

			Serial.print(')');
		}
	}
}

// utils
void off_menu_mode(){
	if (menu_mode == true) menu_mode = false;
}

void on_menu_mode(){
	if (menu_mode == false) menu_mode = true;
}

void change_input_value(){ // изменить значение входа

	if (banks[NO_bank][NO_preset][NO_input] == false)
		banks[NO_bank][NO_preset][NO_input] = true;
	else
		banks[NO_bank][NO_preset][NO_input] = false;
}
//handlers
void press_menu_btn(){ // Нажатие на "меню"
	on_menu_mode();

	if (NO_input == -1 || NO_input == 5) // Инициализируем или сбрасываем номер входа
		NO_input = 0;
	else if (NO_input) // перемещаемся вперед по входам
		NO_input++;
}

void press_save_btn(){ // Нажатие на "сохранить"
	off_menu_mode();
	//TODO Запись массива в EEPROM
	NO_input = -1;
}

void press_change_btn(){ // Нажатие на "change"
	change_input_value();
}


void setup()
{	

}

void loop()
{
	
}

