# Arcanum Game Engine

Ретро игровой движок с поддержкой DOS и современных платформ.

## Цели проекта

- Единое API для всех поддерживаемых платформ
- Модульная архитектура с заменяемыми backend'ами
- Поддержка различных компиляторов и платформ
- Минимальные зависимости и высокая производительность

## Поддерживаемые платформы и компиляторы

### Этап 1 - DOS Foundation
- **DOS 16-bit** - Borland C++ 3.1
- Базовая графика VGA Mode 13h (320x200x256)
- Клавиатура и мышь
- PC Speaker звук

### Этап 2 - Extended DOS
- **DOS 32-bit** - DJGPP (GCC для DOS)
- **DOS 32-bit** - Open Watcom C++
- Расширенная память
- SoundBlaster поддержка

### Этап 3 - Modern Platforms
- **Windows** - MinGW, MSVC
- **Linux** - GCC, Clang
- OpenGL/SDL2 backend

## Архитектура

```
arcanum/
├── core/           # Основное API
├── containers/     # Собственные контейнеры
├── backends/       # Platform-specific implementations
│   ├── dos16/     # Borland C++ 3.1
│   ├── dos32/     # DJGPP/Watcom
│   ├── win32/     # Windows
│   └── posix/     # Linux/Unix
├── examples/       # Демо игры
├── build/         # Build scripts
└── docs/          # Документация
```

## Компиляция

Каждая платформа имеет свои build скрипты:
- `build/dos16/` - Makefiles для Borland C++
- `build/dos32/` - DJGPP и Watcom makefiles  
- `build/modern/` - CMake для современных платформ

## Философия дизайна

1. **Простота** - минимальный API, легкий в использовании
2. **Производительность** - оптимизация для старых платформ
3. **Переносимость** - один код работает везде
4. **Ностальгия** - аутентичный опыт разработки под DOS
