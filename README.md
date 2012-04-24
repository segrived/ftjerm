# Ftjerm v0.01 (fork of Stjerm)
===============================
Ftjerm is a quake-style terminal. It is minimalistic and works well with compiz. Ftjerm can be configured via commandline or the .Xdefaults file.

The following list of options displays the .Xdefaults option first and then the commandline option. The commandline options have a higher priority and thus override the .Xdefaults options.

## Improvements over the original version of Stjerm:
* __Improved__: completely rewritten Makefile.
* __Added__: setting custom border width (not only choosing one of the proposed styles). _(key -b)_
* __Added__: setting custom key for switching to the full-screen mode. _(key -fk)_
* __Added__: turning on/off text cursor blinking. _(key -cb)_
* __Added__: alternative cursor shape. _(key -cs)_

## Requirements
pkgconfig, gtk2, vte

## Installation / Uninstallation
`sudo make install` for installation

`sudo make uninstall` for uninstallation

## Running
Simply run: ftjerm.

## Actions
__--help__: Displays menu with commandline options.

__--info__: Displays menu with .Xdefaults options.

__--version__: Display the current application version.

__--toggle__: Show/hide the current ftjerm instance.

## Options
<pre>
__key, -k__: Shortcut key which shows and hides ftjerm (eg: f12). If you don't specify a shortcut key, you  can only show/hide ftjerm if you run ftjerm with --toggle.

__fullscreenkey, -fk__: Shortcut key which toggle fullscreen mode of ftjerm (eg: f2). _Default: F11._

__mod, -m__: Modifier  key,  which has to be pressed in combination with the shortcut key to show/hide ftjerm: shift, control, alt, windows, none. _Default: none._

__keymod, -km__: Modifier for keyboard shortcuts. Can be a combination (with +)  of  modifiers  (eg:  control+alt). _Default: control+shift._

__autohide, -ah__: Whether or not to hide ftjerm when it looses focus. _Default: true._

__font, -fn__: Terminal font and size (eg: Sans 10). _Default: Fixed 9._

__background, -bg__: Background  color of the terminal. If the terminal is transparent this is the tint color. _Default: Black._

__foreground, -fg__: Foreground color of the terminal. This is the font color. _Default: White._

__allowbold, -ab__: Allow bold fonts or not. _Default: true_

__border, -b__: Border width. _Default: 0._

__opacity, -o__: Opacity _(range: 10 - 100)_. If compositing is enabled ftjerm will use real transparency.  Otherwise you get pseudo-transparency.

__bgimage, -bgimg__: Background image file. Specify the filename. _Default: disabled._

__width, -w__: Window width, either as an integer or a percentage (eg, 50%). _Default: 800._

__height, -h__: Window height, either as an integer or a percentage (eg, 50%). _Default: 400._

__position, -p__: Window position: top, bottom, left, right. _Default: top._

__scrollbar, -s__: Scrollbar position: left, right, none. _Default: none._

__shell, -sh__: Terminal shell. _Default: the user's default shell._

__lines, -l__: Scrollback lines. 0 to disable scrollback. _Default: 1000._

__showtab, -st__: Tabbar  visibility:  never,  one,  always. One means the tabbar is visible if more than one tab is opened. _Default: one._

__tabpos, -tp__: Tabbar position: top, bottom, left, right. _Default: bottom._

__tablabel, -tl__: Label of the tabs. The terminal number gets appended automatically. _Default: term._

__tabfill, -tf__: Whether tabs fill whole tabbar space. _Default: true._

__scroll, -sc__:  Whether to scroll the terminal on output. _Default: true._

__cursorblink, -cb__: Cursor blink: system, on, off. _Default: system._

__cursorshape, -cs__: Cursor shape: block, ibeam, underline. _Default: block._

__mouseautohide, -ma__: Hide cursor when the user presses a key and shown when the user moves the mouse. _Default: false._

__colorX, -cX__: Specify color X of the terminals color palette. You may specify no palette, or a complete one with 16  total  colors.   For  this  you  have  to  use  -c0,  -c1, ..., -c15 or the equivalent color0, color1,... color15.

__fixedX, -fX__: Overrides the calculated horizontal position of the window. Specifies the location of the left of the window.

__fixedY, -fY__: Overrides the calculated vertical position of the window. Specifies the location of the top of the window.

__allowreorder, -ar__: Allows the tabs of the tab bar to be reordered.
</pre>
## Authors
    Copyright (C) 2012 - Holden Cox <segrived@gmail.com>
    Copyright (C) 2011 - Mihail Szabolcs <szaby@szabster.net> (cursor blink and cursor shape parameters)
    Copyright (C) 2008 - Kristopher Wilson <kristopherwilson@gmail.com>
    Copyright (C) 2007 - Stjepan Glavina <stjepang@gmail.com>
    Copyright (C) 2007 - Markus Gross <xsdnyd@gmail.com>

## License
See __LICENSE__

## Contact
Feature requests, patches or anything else related to ftjerm can be send to: segrived@gmail.com