// #include <EEPROM.h>


// TODO загрузка из EEPROM
bool banks[29][3][5]; // Массив банков [банки] [пресеты] [выходы]
int NO_bank = 0; // Номер банка
int NO_preset = 0; // Номер пресета
int NO_input = -1; // Номер входа 

// Кнопки
int menu_btn = A2;
int save_btn = A3;
int prev_btn = 3;
int next_btn = 5;
int a_btn = 6;
int b_btn = 7;
int c_btn = A0;
int d_btn = A1;

//Выхода
int output1 = 2;
int output2 = 4; 
int output3 = 8;
int output4 = 9;
int output5 = 10;
int output6 = 12;


bool menu_mode = false; // Флаг режима меню

void serial_banks_print(){
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
	Serial.print("\nNO_bank " ); Serial.print(NO_bank);
	Serial.print("\nNO_preset " ); Serial.print(NO_preset);
	Serial.print("\nNO_input "); Serial.print(NO_input);
	Serial.print("\nmenu_mode "); Serial.print(menu_mode);
}

// utils
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
	// TODO сохранить массив в EEPROM
}

void reset_preset(){ // Сбрасываем пресет
	NO_preset = 0;
}
//handlers
void press_menu_btn(){ // Нажатие на "меню"
	if (menu_mode == true)
		change_input_value(); // Меняет значение
	else
		on_menu_mode(); // Включает меню
}

void press_save_btn(){ // Нажатие на "сохранить"
	off_menu_mode();
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

void setup()
{	
	Serial.begin(9600);
	pinMode(menu_btn, INPUT);
	pinMode(save_btn, INPUT);
	pinMode(prev_btn, INPUT);
	pinMode(next_btn, INPUT);
	pinMode(a_btn, INPUT);
	pinMode(b_btn, INPUT);
	pinMode(c_btn, INPUT);
	pinMode(d_btn, INPUT);
	pinMode(output1, OUTPUT);
	pinMode(output2, OUTPUT);
	pinMode(output3, OUTPUT);
	pinMode(output4, OUTPUT);
	pinMode(output5, OUTPUT);
	pinMode(output6, OUTPUT);

}

void loop()
{
	if (digitalRead(menu_btn) == HIGH){
		on_menu_mode();
		press_menu_btn();
		serial_banks_print();

	} 
	if (digitalRead(save_btn) == HIGH){
		off_menu_mode();
		serial_banks_print();
	}
	if (digitalRead(prev_btn) == HIGH){
		press_prev_btn();
		serial_banks_print();
	}
	if (digitalRead(next_btn) == HIGH){
		press_next_btn();
		serial_banks_print();
	}
	if (digitalRead(a_btn) == HIGH){
		NO_preset = 0;
		serial_banks_print();
	}
	if (digitalRead(b_btn) == HIGH){
		NO_preset = 1;
		serial_banks_print();
	}
	if (digitalRead(c_btn) == HIGH){
		NO_preset = 2;
		serial_banks_print();
	}
	if (digitalRead(d_btn) == HIGH){
		NO_preset = 3;
		serial_banks_print();
	}
}


