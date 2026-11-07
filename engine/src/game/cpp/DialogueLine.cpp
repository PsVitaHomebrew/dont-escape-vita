#include "../game_all.h"

DialogueLine::DialogueLine()
{
}

DialogueLine::DialogueLine(P<TextFieldController> src, Vector3 tC, String t, TimelineFunction a, bool awt, bool dt, float tim)
{
	time = tim;
	source = src;
	textColor = tC;
	text = t;
	action = a;
	actionWithText = awt;
	displayText = dt;
}
