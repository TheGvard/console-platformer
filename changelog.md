# Changelog

## [1.4.0] - 2025-11-28
### Added
- Camera system
- More debug commands
### Refactored
- Player is now being rendered separately from the rest of the grid
- Moved `enum` to global variables
- Moved tile rendering in a separate function

## [1.3.0] - 2025-10-30
### Added
- Debug mode with console commands
- Multiple ends on the same map

### Refactored
- Changed static array `coords` to vector
- Replaced numbers defining tiles with `enum` for better understanding

## [1.2.0] - 2025-10-22
### Added
- Key-door puzzle mechanics (types 11-20)
- Multiple doors of the same type support

### Changed
- Translated all comments to English
- Improved user interface

## [1.1.0] - 2025-10-21
### Refactored
- Removed `special` intermediary variable
- Replaced while loops with for loops
- Fixed logical AND operator

## [1.0.0] - 2025-10-18
### Initial Release
- Basic platformer engine
- Player movement and collisions
- Win condition
