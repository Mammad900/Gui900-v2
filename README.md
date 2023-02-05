# Gui900 v2

Gui900 is a GUI library for Arduino displays. It currently only supports touchscreens supported by MCUFRIEND_kbv and Adafruit touchscreen, but support for other display library can be added using a wrapper.

## Differences with the old Gui900

This library is a major upgrade over the previous Gui900 version. The following list describes what has been added and what has been removed or not implemented yet.

### New in v2

- Has the proper Arduino library structure
- Uses OOP instead of arrays and functions
- Everything is inside the namespace `Gui900`
- More efficient memory usage
- More flexible styles
  - Buttons no longer need the space padding workaround
- Ability to share a style between elements
- Hover effects
- Callbacks for buttons and check-boxes

### Removed / not implemented yet

These items may or may not be implemented in the future.

- Radio buttons
- Invisible / disabled elements
- Changing non-style properties (except a few)
- Screen auto-sleep and brightness
- Restarting the Arduino board
- Running another sketch
  - What were these two features doing in a GUI program in the first place?
