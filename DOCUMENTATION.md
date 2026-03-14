# ESP32 Device Firmware Documentation

## Обзор проекта

Это прошивка для ESP32 с OLED дисплеем (128x64) и кнопками управления. Система построена на модульной архитектуре приложений.

## Архитектура

### Основные компоненты

- **Display** - управление OLED дисплеем
- **Button** - обработка нажатий кнопок с дебаунсингом
- **Navigation** - система навигации и обработки событий кнопок
- **ApplicationManager** - менеджер приложений, переключение между ними
- **Application** - базовый интерфейс для всех приложений

### Структура проекта

```
src/
├── apps/              # Приложения
│   ├── Application.h  # Базовый интерфейс
│   ├── MenuApplication.*
│   ├── CounterApplication.*
│   ├── TimerApplication.*
│   ├── ClockApplication.*
│   └── InfoApplication.*
├── core/              # Ядро системы
│   ├── ApplicationManager.*
│   ├── Display.*
│   ├── Button.*
│   └── Navigation.*
├── utils/             # Утилиты
│   ├── logger.*
│   └── SerialCommandParser.*
├── graphics/          # Графические ресурсы
│   └── bitmaps.*
├── config.h           # Конфигурация пинов
└── main.cpp           # Точка входа
```

## Создание нового приложения

### Шаг 1: Создайте заголовочный файл

Создайте файл `src/apps/YourApp.h`:

```cpp
#ifndef YOUR_APP_H
#define YOUR_APP_H

#include "Application.h"

class YourApp : public Application {
private:
    bool running;
    // Ваши переменные
    
public:
    YourApp();
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    // Обработчики кнопок
    void onUpButton() override;
    void onDownButton() override;
    void onLeftButton() override;
    void onRightButton() override;
    void onOkButton() override;
    void onBackButton() override;
    void onFunctionButton() override;
    void onBackLongPress() override;
    
    const char* getName() override;
    bool isRunning() override;
};

#endif
```

### Шаг 2: Реализуйте функционал

Создайте файл `src/apps/YourApp.cpp`:

```cpp
#include "YourApp.h"

YourApp::YourApp() : running(false) {}

void YourApp::initialize() {
    running = true;
    // Инициализация
}

void YourApp::update() {
    // Логика обновления (вызывается каждый кадр)
}

void YourApp::render(Display* display) {
    // Отрисовка на дисплее
    display->setTextSize(2);
    display->setCursor(10, 10);
    display->print("Hello!");
}

void YourApp::cleanup() {
    running = false;
}

// Обработчики кнопок
void YourApp::onUpButton() { /* действие */ }
void YourApp::onDownButton() { /* действие */ }
void YourApp::onLeftButton() { /* действие */ }
void YourApp::onRightButton() { /* действие */ }
void YourApp::onOkButton() { /* действие */ }
void YourApp::onBackButton() { running = false; } // Выход
void YourApp::onFunctionButton() { /* действие */ }
void YourApp::onBackLongPress() { running = false; }

const char* YourApp::getName() { return "Your App"; }
bool YourApp::isRunning() { return running; }
```

### Шаг 3: Зарегистрируйте приложение

В файле `src/main.cpp`:

1. Добавьте include:
```cpp
#include "apps/YourApp.h"
```

2. Создайте экземпляр:
```cpp
YourApp yourApp;
```

3. Зарегистрируйте в setup():
```cpp
appManager.registerApplication(&yourApp);
```

## API Display

```cpp
display->clear();                    // Очистить экран
display->setTextSize(1);            // Размер текста (1-3)
display->setCursor(x, y);           // Позиция курсора
display->print("Text");             // Вывести текст
display->drawLine(x1, y1, x2, y2);  // Линия
display->drawRect(x, y, w, h);      // Прямоугольник
display->fillRect(x, y, w, h);      // Залитый прямоугольник
display->drawCircle(x, y, r);       // Круг
display->update();                   // Обновить дисплей
```

## Встроенные приложения

### Counter
Счетчик с настраиваемым шагом
- UP/DOWN: увеличить/уменьшить
- LEFT/RIGHT: изменить шаг
- OK: сбросить счетчик

### Timer
Секундомер
- OK: старт/пауза
- FUNCTION: сброс

### Clock
Часы
- UP/DOWN: настройка часов
- LEFT/RIGHT: настройка минут
- FUNCTION: сброс секунд

### System Info
Информация о системе
- LEFT/RIGHT: переключение страниц

## Конфигурация пинов

Файл `src/config.h`:

```cpp
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13
#define BUTTON_LEFT_PIN 14
#define BUTTON_RIGHT_PIN 15
#define BUTTON_OK_PIN 16
#define BUTTON_BACK_PIN 17
#define BUTTON_FUNCTION_PIN 18

#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22
```

## Сборка и прошивка

```bash
# Сборка
pio run

# Прошивка
pio run --target upload

# Мониторинг Serial
pio device monitor
```

## Управление через Serial

Отправляйте команды через Serial (115200 baud):
- `UP`, `DOWN`, `LEFT`, `RIGHT`
- `OK`, `BACK`, `FUNCTION`
- `BACK_LONG`
- `GET_DISPLAY` - получить содержимое дисплея

## Советы по разработке

1. Используйте `running` флаг для контроля жизненного цикла
2. Всегда вызывайте `cleanup()` при выходе
3. Обработчик `onBackButton()` должен закрывать приложение
4. Используйте `update()` для логики, `render()` только для отрисовки
5. Размер дисплея: 128x64 пикселей
6. Максимум 25 приложений в системе

## Примеры использования

### Простой счетчик
```cpp
void CounterApp::onUpButton() {
    counter++;
}

void CounterApp::render(Display* display) {
    display->setTextSize(3);
    display->setCursor(40, 20);
    display->print(counter);
}
```

### Анимация
```cpp
void AnimApp::update() {
    x += speed;
    if (x > 128) x = 0;
}

void AnimApp::render(Display* display) {
    display->fillCircle(x, 32, 5);
}
```
