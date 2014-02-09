#include "qtermboxlabel.h"
#include "../../core/qtermboxcore.h"

static QTermboxTheme* defaultTermboxLabelTheme = 0;

QTermboxLabel::QTermboxLabel(QObject *parent) :
	QTermboxWidget(parent), _theme(0)
{
}

QTermboxTheme *QTermboxLabel::defaultTheme()
{
	if(!defaultTermboxLabelTheme){
		defaultTermboxLabelTheme = new QTermboxTheme(0);
		setDefaultThemeValues(defaultTermboxLabelTheme);
	}

	return defaultTermboxLabelTheme;
}

void QTermboxLabel::setDefaultTheme(QTermboxTheme *theme)
{
	defaultTermboxLabelTheme = theme;
	update(false);
}

void QTermboxLabel::setTheme(QTermboxTheme *theme)
{
	if(_theme != theme){
		_theme = theme;

		update(false);
	}
}

void QTermboxLabel::setText(QString text)
{
	_text = text;
	update();
}

void QTermboxLabel::paint()
{
	const QTermboxTheme& theme = getActiveTheme();

	if(geometry().height() > 0 && geometry().width() > 0){
		QTermboxCore::putCell(geometry().x(), geometry().y(), geometry().width(), geometry().height(), text(),
							  theme.foreground(), theme.background());
	}
}
