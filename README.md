# HAKLES - ESP32 Security Research Device

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Display](https://img.shields.io/badge/display-SH1106-yellow)
![License](https://img.shields.io/badge/license-MIT-green)

Устройство для исследования безопасности на базе ESP32 с дисплеем SH1106 OLED. Вдохновлено Flipper Zero.

## Возможности

- Современный минималистичный интерфейс
- Анимированный стартовый экран с прогресс-баром
- Карточный дизайн меню с закругленными углами
- Статус-бар с информацией
- WiFi сканирование и атаки (deauth, packet capture, evil portal)
- Bluetooth сканирование и атаки
- Работа с радиомодулем CC1101
- ИК-передатчик (выключение телевизоров)
- Файловый менеджер (SD карта)
- Бинарный калькулятор
- Секундомер
- Модульная архитектура приложений

## Аппаратные требования

- ESP32 (ESP32-WROOM-32)
- SH1106 OLED дисплей (128x64)
- MicroSD карта модуль
- 7 кнопок
- CC1101 модуль (опционально)
- ИК светодиод (опционально)

## Подключение

### Дисплей SH1106
```
ESP32         SH1106
GPIO21  ----> SDA
GPIO22  ----> SCL
3.3V    ----> VCC
GND     ----> GND
```

### SD карта
```
ESP32         SD Module
GPIO23  ----> MOSI
GPIO19  ----> MISO
GPIO18  ----> SCK
GPIO5   ----> CS
3.3V    ----> VCC
GND     ----> GND
```

### Кнопки
```
ESP32         Кнопки
GPIO12  ----> UP
GPIO13  ----> DOWN
GPIO14  ----> LEFT
GPIO15  ----> RIGHT
GPIO16  ----> OK
GPIO17  ----> BACK
GPIO18  ----> FUNCTION
```

## Установка

1. Клонируйте репозиторий:
```bash
git clone https://github.com/yourusername/hakles.git
cd hakles
```

2. Установите PlatformIO

3. Соберите прошивку:
```bash
pio run
```

4. Загрузите на ESP32:
```bash
pio run --target upload
```

## Архитектура

### Структура файлов
```
src/
├── main.cpp              # Точка входа
├── config.h              # Конфигурация
├── core/                 # Ядро системы
│   ├── ApplicationManager.*
│   ├── Button.*
│   ├── Display.*
│   └── Navigation.*
├── apps/                 # Приложения
│   ├── Application.h     # Базовый интерфейс
│   ├── MenuApplication.*
│   ├── SettingsApplication.*
│   ├── ExplorerApplication.*
│   ├── EnhancedWifiScannerApplication.*
│   ├── WiFiPacketCaptureApplication.*
│   ├── WiFiDeauthAttackApplication.*
│   ├── EvilPortalApplication.*
│   ├── BluetoothScannerApplication.*
│   ├── BluetoothAttackApplication.*
│   ├── CC1101Application.*
│   ├── IRTVOffApplication.*
│   ├── BinaryCalculatorApplication.*
│   └── StopwatchApplication.*
├── graphics/             # Графика
│   └── bitmaps.*
└── utils/                # Утилиты
    ├── logger.*
    └── SerialCommandParser.*
```

### Основные компоненты

#### ApplicationManager
Управляет всеми приложениями в системе.

```cpp
class ApplicationManager {
public:
    void registerApplication(Application* app);
    void switchToApplication(int index);
    void update();
    void render(Display* display);
};
```

#### Display
Обертка для работы с SH1106 дисплеем.

```cpp
class Display {
public:
    void initialize();
    void clear();
    void update();
    void drawString(int16_t x, int16_t y, const char* text);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], ...);
};
```

#### Navigation
Управление кнопками и навигацией.

```cpp
enum NavigationEvent {
    NAV_NONE, NAV_UP, NAV_DOWN, NAV_LEFT, NAV_RIGHT,
    NAV_OK, NAV_BACK, NAV_FUNCTION, NAV_BACK_LONG
};

class Navigation {
public:
    void update();
    NavigationEvent getEvent();
};
```

## Создание нового приложения

1. Создайте класс, наследующий `Application`:

```cpp
// MyApp.h
#include "Application.h"

class MyApp : public Application {
public:
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    void onUpButton() override;
    void onDownButton() override;
    void onOkButton() override;
    void onBackButton() override;
    // ... другие кнопки
    
    const char* getName() override { return "My App"; }
    bool isRunning() override { return running; }
    
private:
    bool running;
};
```

2. Реализуйте методы в `.cpp` файле

3. Зарегистрируйте в `main.cpp`:

```cpp
#include "apps/MyApp.h"

MyApp myApp;

void setup() {
    // ...
    appManager.registerApplication(&myApp);
    // ...
}
```

## Приложения

### Системные
- **StartupScreen** - Экран загрузки
- **MenuApplication** - Главное меню
- **SettingsApplication** - Настройки (батарея, переназначение кнопок)

### WiFi инструменты
- **EnhancedWifiScannerApplication** - Расширенный WiFi сканер
- **WiFiPacketCaptureApplication** - Захват WiFi пакетов
- **WiFiDeauthAttackApplication** - Deauth атака
- **EvilPortalApplication** - Фальшивая точка доступа

### Bluetooth инструменты
- **BluetoothScannerApplication** - Сканер Bluetooth устройств
- **BluetoothAttackApplication** - Bluetooth атаки

### Радио инструменты
- **CC1101Application** - Работа с CC1101 трансивером
- **IRTVOffApplication** - ИК команды для выключения ТВ

### Утилиты
- **ExplorerApplication** - Файловый менеджер
- **BinaryCalculatorApplication** - Бинарный калькулятор
- **StopwatchApplication** - Секундомер

## Удаленное управление

Устройство поддерживает управление через serial интерфейс (115200 baud).

### Команды
- `UP`, `DOWN`, `LEFT`, `RIGHT` - Навигация
- `OK` - Подтверждение
- `BACK` - Назад
- `FUNCTION` - Функциональная кнопка
- `BACK_LONG` - Длинное нажатие BACK
- `GET_DISPLAY` - Получить содержимое дисплея

### Python GUI контроллер

Запустите GUI контроллер:
```bash
python esp_controller_gui.py
```

Или используйте скрипты:
- Windows: `run_controller.bat`
- Linux/macOS: `./run_controller.sh`

Возможности:
- Виртуальный D-pad
- Визуализация дисплея в реальном времени (128x64)
- Горячие клавиши (стрелки, Enter, Escape, F1)
- Автоопределение порта

## Тестирование

Запустите тесты:
```bash
python -m pytest
```

Тестовые файлы:
- `test_serial_command_parser.py` - Парсер команд
- `test_navigation.py` - Навигация
- `test_application_manager.py` - Менеджер приложений
- `test_gui_controller.py` - GUI контроллер

## Сборка исполняемых файлов

### Windows
```bash
pyinstaller --onefile --windowed esp_controller_gui.py
```

### Linux
```bash
pyinstaller --onefile esp_controller_gui.py
```

Исполняемые файлы будут в папке `dist/`.

## Конфигурация

Основные настройки в `src/config.h`:

```cpp
// Пины дисплея
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22

// Пины кнопок
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13
// ...

// Настройки
#define BUTTON_DEBOUNCE_TIME 50
#define DISPLAY_UPDATE_INTERVAL 50
```

## Управление памятью

- Приложения создаются один раз и переиспользуются
- Двойная буферизация дисплея
- Дебаунсинг кнопок
- Эффективное использование ресурсов ESP32

## Отладка

Используйте Serial для отладки:
```cpp
Serial.begin(115200);
Serial.println("Debug message");
```

Мониторинг:
```bash
pio device monitor
```

## Лицензия

MIT License - см. файл [LICENSE](LICENSE)

## Документация

- [USER_MANUAL.md](USER_MANUAL.md) - Руководство пользователя
- [COMPREHENSIVE_DOCUMENTATION.md](COMPREHENSIVE_DOCUMENTATION.md) - Полная документация
- [UI_DESIGN.md](UI_DESIGN.md) - Дизайн интерфейса
- [CHANGELOG.md](CHANGELOG.md) - История изменений
