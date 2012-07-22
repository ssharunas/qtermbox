#include "keycontainer.h"

KeyContainer::KeyContainer(QObject *parent) :
	QObject(parent)
{
	registerQtKeys();
	registerKeys();
}

QList<Key *> KeyContainer::allKeys()
{
	return keys.values();
}

QList<Key *> KeyContainer::getKeys(QTermboxKeyEvent &ev)
{
	QList<Key *> result;

	if(ev.modifiers() & Qt::AltModifier)
		result << keys.values("ALT");

	if(ev.modifiers() & Qt::ControlModifier)
		result << keys.values("CTRL");

	if(ev.text().length()){
		result << keys.values(ev.text());
	}
	else{
		result << keys.values(qtKeyAsString(ev.key()));
	}

	foreach (Key* key, result) {
		if(key->isShift()){
			result << keys.values("SHIFT");
			break;
		}
	}

	return result;
}

QString KeyContainer::qtKeyAsString(int key)
{
	if(qtKey.contains(key))
		return qtKey[key];

	return "Not Found";
}

void KeyContainer::registerKeys()
{
	keys[QChar(27)] = new Key(this, 3, 5, QList<QChar>() << 'E' << 'S' << 'C');
	keys["Qt::Key_F1"] = new Key(this, 8, 5, QList<QChar>() << 'F' << '1');
	keys["Qt::Key_F2"] = new Key(this, 11, 5, QList<QChar>() << 'F' << '2');
	keys["Qt::Key_F3"] = new Key(this, 14, 5, QList<QChar>() << 'F' << '3');
	keys["Qt::Key_F4"] = new Key(this, 17, 5, QList<QChar>() << 'F' << '4');
	keys["Qt::Key_F5"] = new Key(this, 21, 5, QList<QChar>() << 'F' << '5');
	keys["Qt::Key_F6"] = new Key(this, 24, 5, QList<QChar>() << 'F' << '6');
	keys["Qt::Key_F7"] = new Key(this, 27, 5, QList<QChar>() << 'F' << '7');
	keys["Qt::Key_F8"] = new Key(this, 30, 5, QList<QChar>() << 'F' << '8');
	keys["Qt::Key_F9"] = new Key(this, 35, 5, QList<QChar>() << 'F' << '9');
	keys["Qt::Key_F10"] = new Key(this, 38, 5, QList<QChar>() << 'F' << '1' << '0');
	keys["Qt::Key_F11"] = new Key(this, 42, 5, QList<QChar>() << 'F' << '1' << '1');
	keys["Qt::Key_F12"] = new Key(this, 46, 5, QList<QChar>() << 'F' << '1' << '2');
	keys.insertMulti("NONE", new Key(this, 52, 5, QList<QChar>() << 'P' << 'R' << 'N'));
	keys.insertMulti("NONE", new Key(this, 56, 5, QList<QChar>() << 'S' << 'C' << 'R'));
	keys.insertMulti("NONE", new Key(this, 60, 5, QList<QChar>() << 'B' << 'R' << 'K'));
	keys.insertMulti("LED", new Key(this, 68, 5, QList<QChar>() << '-'));
	keys.insertMulti("LED", new Key(this, 72, 5, QList<QChar>() << '-'));
	keys.insertMulti("LED", new Key(this, 76, 5, QList<QChar>() << '-'));

	keys["`"] = new Key(this, 3, 8, QList<QChar>() << '`');
	keys["~"] = new Key(this, 3, 8, QList<QChar>() << '~', true);
	keys["1"] = new Key(this, 6, 8, QList<QChar>() << '1');
	keys["!"] = new Key(this, 6, 8, QList<QChar>() << '!', true);
	keys["2"] = new Key(this, 9, 8, QList<QChar>() << '2');
	keys["@"] = new Key(this, 9, 8, QList<QChar>() << '@', true);
	keys["3"] = new Key(this, 12, 8, QList<QChar>() << '3');
	keys["#"] = new Key(this, 12, 8, QList<QChar>() << '#', true);
	keys["4"] = new Key(this, 15, 8, QList<QChar>() << '4');
	keys["$"] = new Key(this, 15, 8, QList<QChar>() << '$', true);
	keys["5"] = new Key(this, 18, 8, QList<QChar>() << '5');
	keys["%"] = new Key(this, 18, 8, QList<QChar>() << '%', true);
	keys["6"] = new Key(this, 21, 8, QList<QChar>() << '6');
	keys["^"] = new Key(this, 21, 8, QList<QChar>() << '^', true);
	keys["7"] = new Key(this, 24, 8, QList<QChar>() << '7');
	keys["&"] = new Key(this, 24, 8, QList<QChar>() << '&', true);
	keys["8"] = new Key(this, 27, 8, QList<QChar>() << '8');
	keys["*"] = new Key(this, 27, 8, QList<QChar>() << '*', true);
	keys["9"] = new Key(this, 30, 8, QList<QChar>() << '9');
	keys["("] = new Key(this, 30, 8, QList<QChar>() << '(', true);
	keys["0"] = new Key(this, 33, 8, QList<QChar>() << '0');
	keys[")"] = new Key(this, 33, 8, QList<QChar>() << ')', true);
	keys["-"] = new Key(this, 36, 8, QList<QChar>() << '-');
	keys["_"] = new Key(this, 36, 8, QList<QChar>() << '_', true);
	keys["="] = new Key(this, 39, 8, QList<QChar>() << '=');
	keys["+"] = new Key(this, 39, 8, QList<QChar>() << '+', true);
	keys["\\"] = new Key(this, 42, 8, QList<QChar>() << '\\');
	keys["|"] = new Key(this, 42, 8, QList<QChar>() << '|', true);
	keys[QChar(8)] = new Key(this, 46, 8, QList<QChar>() << 0x2190 << 0x2500 << 0x2500);
	keys["Qt::Key_Insert"] = new Key(this, 52, 8, QList<QChar>() << 'I' << 'N' << 'S');
	keys["Qt::Key_Home"] = new Key(this, 56, 8, QList<QChar>() << 'H' << 'O' << 'M');
	keys["Qt::Key_PageUp"] = new Key(this, 60, 8, QList<QChar>() << 'P' << 'G' << 'U');
	keys.insertMulti("NONE", new Key(this, 67, 8, QList<QChar>() << 'N'));//Numlock
	keys.insertMulti("/", new Key(this, 70, 8, QList<QChar>() << '/'));
	keys.insertMulti("*", new Key(this, 73, 8, QList<QChar>() << '*'));
	keys.insertMulti("-", new Key(this, 76, 8, QList<QChar>() << '-'));

	keys[QChar(9)] = new Key(this, 3, 10, QList<QChar>() << 'T' << 'A' << 'B');
	keys["q"] = new Key(this, 8, 10, QList<QChar>() << 'q');
	keys["Q"] = new Key(this, 8, 10, QList<QChar>() << 'Q', true);
	keys["w"] = new Key(this, 11, 10, QList<QChar>() << 'w');
	keys["W"] = new Key(this, 11, 10, QList<QChar>() << 'W', true);
	keys["e"] = new Key(this, 14, 10, QList<QChar>() << 'e');
	keys["E"] = new Key(this, 14, 10, QList<QChar>() << 'E', true);
	keys["r"] = new Key(this, 17, 10, QList<QChar>() << 'r');
	keys["R"] = new Key(this, 17, 10, QList<QChar>() << 'R', true);
	keys["t"] = new Key(this, 20, 10, QList<QChar>() << 't');
	keys["T"] = new Key(this, 20, 10, QList<QChar>() << 'T', true);
	keys["y"] = new Key(this, 23, 10, QList<QChar>() << 'y');
	keys["Y"] = new Key(this, 23, 10, QList<QChar>() << 'Y', true);
	keys["u"] = new Key(this, 26, 10, QList<QChar>() << 'u');
	keys["U"] = new Key(this, 26, 10, QList<QChar>() << 'U', true);
	keys["i"] = new Key(this, 29, 10, QList<QChar>() << 'i');
	keys["I"] = new Key(this, 29, 10, QList<QChar>() << 'I', true);
	keys["o"] = new Key(this, 32, 10, QList<QChar>() << 'o');
	keys["O"] = new Key(this, 32, 10, QList<QChar>() << 'O', true);
	keys["p"] = new Key(this, 35, 10, QList<QChar>() << 'p');
	keys["P"] = new Key(this, 35, 10, QList<QChar>() << 'P', true);
	keys["["] = new Key(this, 38, 10, QList<QChar>() << '[');
	keys["{"] = new Key(this, 38, 10, QList<QChar>() << '{', true);
	keys["]"] = new Key(this, 41, 10, QList<QChar>() << ']');
	keys["}"] = new Key(this, 41, 10, QList<QChar>() << '}', true);
	keys.insertMulti(QChar(13), new Key(this, 45, 10,
		QList<QChar>() << 0x2591 << 0x2591 << 0x2591 << 0x2591
		<< 0x2591 << 0x2591 << 0x21B5 << 0x2591
		<< 0x2591 << 0x2591 << 0x2591 << 0x2591,
		false, 4));
	keys.insertMulti(QChar(13), new Key(this, 43, 12, QList<QChar>() << 0x2591 << 0x2591, false, 2));
	keys[QChar(0xFFF2)] = new Key(this, 52, 10, QList<QChar>() << 'D' << 'E' << 'L');
	keys["Qt::Key_End"] = new Key(this, 56, 10, QList<QChar>() << 'E' << 'N' << 'D');
	keys["Qt::Key_PageDown"] = new Key(this, 60, 10, QList<QChar>() << 'P' << 'G' << 'D');
	keys.insertMulti("7", new Key(this, 67, 10, QList<QChar>() << '7'));
	keys.insertMulti("8", new Key(this, 70, 10, QList<QChar>() << '8'));
	keys.insertMulti("9", new Key(this, 73, 10, QList<QChar>() << '9'));
	keys.insertMulti("+", new Key(this, 76, 10, QList<QChar>() << ' ' << '+' << ' ', false, 1));

	keys.insertMulti("NONE", new Key(this, 3, 12, QList<QChar>() << 'C' << 'A' << 'P' << 'S'));
	keys["a"] = new Key(this, 9, 12, QList<QChar>() << 'a');
	keys["A"] = new Key(this, 9, 12, QList<QChar>() << 'A', true);
	keys["s"] = new Key(this, 12, 12, QList<QChar>() << 's');
	keys["S"] = new Key(this, 12, 12, QList<QChar>() << 'S', true);
	keys["d"] = new Key(this, 15, 12, QList<QChar>() << 'd');
	keys["D"] = new Key(this, 15, 12, QList<QChar>() << 'D', true);
	keys["f"] = new Key(this, 18, 12, QList<QChar>() << 'f');
	keys["F"] = new Key(this, 18, 12, QList<QChar>() << 'F', true);
	keys["g"] = new Key(this, 21, 12, QList<QChar>() << 'g');
	keys["G"] = new Key(this, 21, 12, QList<QChar>() << 'G', true);
	keys["h"] = new Key(this, 24, 12, QList<QChar>() << 'h');
	keys["H"] = new Key(this, 24, 12, QList<QChar>() << 'H', true);
	keys["j"] = new Key(this, 27, 12, QList<QChar>() << 'j');
	keys["J"] = new Key(this, 27, 12, QList<QChar>() << 'J', true);
	keys["k"] = new Key(this, 30, 12, QList<QChar>() << 'k');
	keys["K"] = new Key(this, 30, 12, QList<QChar>() << 'K', true);
	keys["l"] = new Key(this, 33, 12, QList<QChar>() << 'l');
	keys["L"] = new Key(this, 33, 12, QList<QChar>() << 'L', true);
	keys[";"] = new Key(this, 36, 12, QList<QChar>() << ';');
	keys[":"] = new Key(this, 36, 12, QList<QChar>() << ':', true);
	keys["'"] = new Key(this, 39, 12, QList<QChar>() << '\'');
	keys["\""] = new Key(this, 39, 12, QList<QChar>() << '"', true);
	keys.insertMulti("4", new Key(this, 67, 12, QList<QChar>() << '4'));
	keys.insertMulti("5", new Key(this, 70, 12, QList<QChar>() << '5'));
	keys.insertMulti("6", new Key(this, 73, 12, QList<QChar>() << '6'));

	keys.insertMulti("SHIFT", new Key(this, 3, 14, QList<QChar>() << 'S' << 'H' << 'I' << 'F' << 'T'));
	keys["z"] = new Key(this, 11, 14, QList<QChar>() << 'z');
	keys["Z"] = new Key(this, 11, 14, QList<QChar>() << 'Z', true);
	keys["x"] = new Key(this, 14, 14, QList<QChar>() << 'x');
	keys["X"] = new Key(this, 14, 14, QList<QChar>() << 'X', true);
	keys["c"] = new Key(this, 17, 14, QList<QChar>() << 'c');
	keys["C"] = new Key(this, 17, 14, QList<QChar>() << 'C', true);
	keys["v"] = new Key(this, 20, 14, QList<QChar>() << 'v');
	keys["V"] = new Key(this, 20, 14, QList<QChar>() << 'V', true);
	keys["b"] = new Key(this, 23, 14, QList<QChar>() << 'b');
	keys["B"] = new Key(this, 23, 14, QList<QChar>() << 'B', true);
	keys["n"] = new Key(this, 26, 14, QList<QChar>() << 'n');
	keys["N"] = new Key(this, 26, 14, QList<QChar>() << 'N', true);
	keys["m"] = new Key(this, 29, 14, QList<QChar>() << 'm');
	keys["M"] = new Key(this, 29, 14, QList<QChar>() << 'M', true);
	keys[","] = new Key(this, 32, 14, QList<QChar>() << ',');
	keys["<"] = new Key(this, 32, 14, QList<QChar>() << '<', true);
	keys["."] = new Key(this, 35, 14, QList<QChar>() << '.');
	keys[">"] = new Key(this, 35, 14, QList<QChar>() << '>', true);
	keys.insertMulti("/", new Key(this, 38, 14, QList<QChar>() << '/'));
	keys["?"] = new Key(this, 38, 14, QList<QChar>() << '?', true);
	keys.insertMulti("SHIFT", new Key(this, 44, 14, QList<QChar>() << 'S' << 'H' << 'I' << 'F' << 'T'));
	keys["Qt::Key_Up"] = new Key(this, 56, 14, QList<QChar>() << '(' << 0x2191 << ')');
	keys.insertMulti("1", new Key(this, 67, 14, QList<QChar>() << '1'));
	keys.insertMulti("2", new Key(this, 70, 14, QList<QChar>() << '2'));
	keys.insertMulti("3", new Key(this, 73, 14, QList<QChar>() << '3'));
	keys.insertMulti(QChar(13), new Key(this, 76, 14, QList<QChar>() << 0x2591 << 0x2591 << 0x2591, false, 1));

	keys.insertMulti("CTRL", new Key(this, 3, 16, QList<QChar>() << 'C' << 'T' << 'R' << 'L'));
	keys.insertMulti("NONE", new Key(this, 8, 16, QList<QChar>() << 'W' << 'I' << 'N'));
	keys.insertMulti("ALT", new Key(this, 12, 16, QList<QChar>() << 'A' << 'L' << 'T'));
	keys[" "] = new Key(this, 16, 16, QList<QChar>()
		<< ' ' << ' ' << ' ' << ' ' << ' '
		<< 'S' << 'P' << 'A' << 'C' << 'E'
		<< ' ' << ' ' << ' ' << ' ' << ' ' );
	keys.insertMulti("ALT", new Key(this, 32, 16, QList<QChar>() << 'A' << 'L' << 'T'));
	keys.insertMulti("NONE", new Key(this, 36, 16, QList<QChar>() << 'W' << 'I' << 'N'));
	keys.insertMulti("NONE", new Key(this, 40, 16, QList<QChar>() << 'P' << 'R' << 'O' << 'P'));
	keys.insertMulti("CTRL", new Key(this, 45, 16, QList<QChar>() << 'C' << 'T' << 'R' << 'L'));
	keys["Qt::Key_Left"] = new Key(this, 52, 16, QList<QChar>() << '(' << 0x2190 << ')');
	keys["Qt::Key_Down"] = new Key(this, 56, 16, QList<QChar>() << '(' << 0x2193 << ')');
	keys["Qt::Key_Right"] = new Key(this, 60, 16, QList<QChar>() << '(' << 0x2192 << ')');
	keys.insertMulti("0", new Key(this, 67, 16, QList<QChar>() << ' ' << '0' << ' ' << ' '));
	keys.insertMulti(".", new Key(this, 73, 16, QList<QChar>() << '.'));
}

void KeyContainer::registerQtKeys()
{
	qtKey[Qt::Key_F1] = "Qt::Key_F1";
	qtKey[Qt::Key_F2] = "Qt::Key_F2";
	qtKey[Qt::Key_F3] = "Qt::Key_F3";
	qtKey[Qt::Key_F4] = "Qt::Key_F4";
	qtKey[Qt::Key_F5] = "Qt::Key_F5";
	qtKey[Qt::Key_F6] = "Qt::Key_F6";
	qtKey[Qt::Key_F7] = "Qt::Key_F7";
	qtKey[Qt::Key_F8] = "Qt::Key_F8";
	qtKey[Qt::Key_F9] = "Qt::Key_F9";
	qtKey[Qt::Key_F10] = "Qt::Key_F10";
	qtKey[Qt::Key_F11] = "Qt::Key_F11";
	qtKey[Qt::Key_F12] = "Qt::Key_F12";
	qtKey[Qt::Key_Insert] = "Qt::Key_Insert";
	qtKey[Qt::Key_Delete] = "Qt::Key_Delete";
	qtKey[Qt::Key_Home] = "Qt::Key_Home";
	qtKey[Qt::Key_End] = "Qt::Key_End";
	qtKey[Qt::Key_PageUp] = "Qt::Key_PageUp";
	qtKey[Qt::Key_PageDown] = "Qt::Key_PageDown";
	qtKey[Qt::Key_Up] = "Qt::Key_Up";
	qtKey[Qt::Key_Down] = "Qt::Key_Down";
	qtKey[Qt::Key_Left] = "Qt::Key_Left";
	qtKey[Qt::Key_Right] = "Qt::Key_Right";
	qtKey[Qt::Key_AsciiTilde] = "Qt::Key_AsciiTilde";
	qtKey[Qt::Key_2] = "Qt::Key_2";
	qtKey[Qt::Key_A] = "Qt::Key_A";
	qtKey[Qt::Key_B] = "Qt::Key_B";
	qtKey[Qt::Key_C] = "Qt::Key_C";
	qtKey[Qt::Key_D] = "Qt::Key_D";
	qtKey[Qt::Key_E] = "Qt::Key_E";
	qtKey[Qt::Key_F] = "Qt::Key_F";
	qtKey[Qt::Key_G] = "Qt::Key_G";
	qtKey[Qt::Key_Backspace] = "Qt::Key_Backspace";
	qtKey[Qt::Key_H] = "Qt::Key_H";
	qtKey[Qt::Key_Tab] = "Qt::Key_Tab";
	qtKey[Qt::Key_I] = "Qt::Key_I";
	qtKey[Qt::Key_J] = "Qt::Key_J";
	qtKey[Qt::Key_K] = "Qt::Key_K";
	qtKey[Qt::Key_L] = "Qt::Key_L";
	qtKey[Qt::Key_Return] = "Qt::Key_Return";
	qtKey[Qt::Key_M] = "Qt::Key_M";
	qtKey[Qt::Key_N] = "Qt::Key_N";
	qtKey[Qt::Key_O] = "Qt::Key_O";
	qtKey[Qt::Key_P] = "Qt::Key_P";
	qtKey[Qt::Key_Q] = "Qt::Key_Q";
	qtKey[Qt::Key_R] = "Qt::Key_R";
	qtKey[Qt::Key_S] = "Qt::Key_S";
	qtKey[Qt::Key_T] = "Qt::Key_T";
	qtKey[Qt::Key_U] = "Qt::Key_U";
	qtKey[Qt::Key_V] = "Qt::Key_V";
	qtKey[Qt::Key_W] = "Qt::Key_W";
	qtKey[Qt::Key_X] = "Qt::Key_X";
	qtKey[Qt::Key_Y] = "Qt::Key_Y";
	qtKey[Qt::Key_Z] = "Qt::Key_Z";
	qtKey[Qt::Key_Escape] = "Qt::Key_Escape";
	qtKey[Qt::Key_BraceLeft] = "Qt::Key_BraceLeft";
	qtKey[Qt::Key_3] = "Qt::Key_3";
	qtKey[Qt::Key_Backslash] = "Qt::Key_Backslash";
	qtKey[Qt::Key_4] = "Qt::Key_4";
	qtKey[Qt::Key_BraceRight] = "Qt::Key_BraceRight";
	qtKey[Qt::Key_5] = "Qt::Key_5";
	qtKey[Qt::Key_6] = "Qt::Key_6";
	qtKey[Qt::Key_7] = "Qt::Key_7";
	qtKey[Qt::Key_Slash] = "Qt::Key_Slash";
	qtKey[Qt::Key_Underscore] = "Qt::Key_Underscore";
	qtKey[Qt::Key_Space] = "Qt::Key_Space";
	qtKey[Qt::Key_Backspace] = "Qt::Key_Backspace";
	qtKey[Qt::Key_8] = "Qt::Key_8";
	qtKey[Qt::Key_unknown] = "Qt::Key_unknown";
}
