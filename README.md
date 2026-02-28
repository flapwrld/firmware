# ESP32 Device Firmware

Модульная прошивка для ESP32 с OLED дисплеем и системой приложений.

## Возможности

- Модульная архитектура приложений
- OLED дисплей 128x64
- 7 кнопок управления (D-pad + OK + Back + Function)
- Управление через Serial
- Встроенные приложения: Counter, Timer, Clock, System Info

## Быстрый старт

### Сборка и прошивка

```bash
# Установите PlatformIO
pip install platformio

# Соберите проект
pio run

# Прошейте устройство
pio run --target upload

# Мониторинг
pio device monitor
```

### Использование ESP Flasher

Минималистичная программа для прошивки и управления:

```bash
# Установите зависимости
pip install pyserial requests

# Запустите
python esp_flasher.py
```

Возможности:
- Прошивка последнего релиза с GitHub
- Прошивка локальной сборки
- Просмотр экрана устройства в реальном времени
- Управление кнопками через GUI или клавиатуру

## Встроенные приложения

### Counter
Счетчик с настраиваемым шагом
- ↑/↓: изменить значение
- ←/→: изменить шаг
- OK: сброс

### Timer
Секундомер с точностью до секунды
- OK: старт/пауза
- FUNC: сброс

### Clock
Часы с настройкой времени
- ↑/↓: часы
- ←/→: минуты
- FUNC: сброс секунд

### System Info
Информация о системе (CPU, память, flash)
- ←/→: переключение страниц

## Создание приложений

См. [DOCUMENTATION.md](DOCUMENTATION.md) для подробной инструкции.

Быстрый пример:

```cpp
class MyApp : public Application {
    bool running;
public:
    void initialize() override { running = true; }
    void render(Display* display) override {
        display->print("Hello!");
    }
    void onBackButton() override { running = false; }
    const char* getName() override { return "My App"; }
    bool isRunning() override { return running; }
    // ... остальные методы
};
```

## Конфигурация

Пины настраиваются в `src/config.h`:

```cpp
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13
// ...
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22
```

## Управление

### Кнопки
- D-pad: навигация
- OK: выбор/подтверждение
- Back: возврат/выход
- Function: дополнительная функция

### Serial команды (115200 baud)
- `UP`, `DOWN`, `LEFT`, `RIGHT`
- `OK`, `BACK`, `FUNCTION`
- `GET_DISPLAY` - получить содержимое экрана

## Структура проекта

```
src/
├── apps/       # Приложения
├── core/       # Ядро системы
├── utils/      # Утилиты
├── graphics/   # Графика
└── main.cpp    # Точка входа
```

## Лицензия

См. [LICENSE](LICENSE)
