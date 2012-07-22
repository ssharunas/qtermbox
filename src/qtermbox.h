#ifndef QTERMBOX_H
#define QTERMBOX_H
#include "global.h"

/*!
\brief The QTermbox namespace contains miscellaneous identifiers used throughout the QTermbox library.
*/
namespace QTermbox
{
/*!
	\brief Termbox supported collors.
	*/
enum QTermboxColor
{
	Black,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
};


/*!
	\brief Style attributes for Termbox cell.
	*/
enum QTermboxAttribute
{
	NoAttribute = 0, //!< Does not apply any additional formating.
	Bold,   //!< Bolds text if used in foreground style. Blinks text if used in background style.
	Underline //!< Underlines text if used in foreground style.
};


/*!
	\brief Input modes for keybord events pool.
	*/
enum QTermboxInputMode
{
	AltInputMode,
	EscInputMode
};
}

#endif // QTERMBOX_H
