#ifndef QTERMBOXSTYLE_H
#define QTERMBOXSTYLE_H

#include "stdint.h"
#include "qtermbox.h"

/*!
	\brief Class to describe style for terbox cell.
	Class contains information about cell color and display attributes.
*/
class QTermboxStyle
{
public:
	QTermboxStyle(QTermbox::QTermboxColor color, QTermbox::QTermboxAttribute attribute = QTermbox::NoAttribute);
	void setStyle(QTermbox::QTermboxColor color, QTermbox::QTermboxAttribute attribute);//!< Sets style values for current object.
	inline uint16_t style() const { return _style; } //!< Termbox internaly used style code (or`ed value of color and attributes).

private:
	uint16_t convertToTermboxColor(QTermbox::QTermboxColor color);
	uint16_t convertToTermboxAttribute(QTermbox::QTermboxAttribute attribute);

private:
	int _style;
};

inline bool operator==(QTermboxStyle s1, QTermboxStyle s2) { return s1.style() == s2.style(); }
inline bool operator!=(QTermboxStyle s1, QTermboxStyle s2) { return !(s1 == s2); }

#endif // QTERMBOXSTYLE_H
